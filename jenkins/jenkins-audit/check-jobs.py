#! /usr/bin/python

import xml.etree.ElementTree as etree
import argparse
import os
import re
import requests
import json

strict_skips = [
    "wiredtiger-osx",
    "wiredtiger-compat-r1",
    "wiredtiger-compat-r2",
    "wiredtiger-compat-develop",
    "wiredtiger-compatibility",
    "wiredtiger-test-mongodb-3.0",
    "wiredtiger-test-mongodb-3.2"
]

email_check_skip = [
    "wiredtiger-fault-inject",
    "mongodb-100gb-cache",
    "mongodb-million-collections",
    "wiredtiger-relevant-history-suite",
    "wiredtiger-test-format-stress-relevant-history",
    "wiredtiger-test-race-condition-stress-sanitizer-relevant-history",
    "wiredtiger-test-checkpoint-stress-relevant-history",
]

match_jobs = [
    ["wiredtiger-test-format-stress-sanitizer", None]
]

clean_skips = [
    "wiredtiger-pull-request",
    "jenkins-audit",
    "wiredtiger-perf-long-jobs",
    "wiredtiger-perf",
    "mongodb-perf-ycsb-compare-releases",
]

archive_stats_skips = [
    "mongodb-perf-ycsb-compare-releases",
]

mongodb_branch_skips = [
    "3.0",
    "3.2",
    "5.1",
    "master",
]

match_jobs_set = False

github_branches = []

def check_recips (description, recips):
    # Jobs should always email someone.
    if recips == None:
        print("Error, job %s has no recipients set" % job)
        return True

    # Most test should email testing@ on failure
    should_email_testing = True
    # There is a magic description string to flag tests being written which
    # should email their creator, rather than everyone.
    dev_test_string = 'This test is under active development.'
    if dev_test_string in str(description.text):
        should_email_testing = False
    email = recips.text
    does_email_testing = False
    if re.search('testing@wiredtiger.com', email):
        does_email_testing = True

    if should_email_testing and not does_email_testing:
        print("Error: Job %s should email testing@wiredtiger.com, but instead emails %s" % (job, email))
        print("\t If the test is being worked on add: \"%s\" to the job description" % (dev_test_string))
        return True
    elif not should_email_testing and does_email_testing:
        print("Error: Job %s shouldn't email testing@wiredtiger.com." % (job))
        print("\t If the test is fully working, remove: \"%s\" from the job description" % (dev_test_string))
        return True
    return False

def check_mail (root):
    # Skip the top multijob processes, they dont send emails
    if root.tag == 'com.tikal.jenkins.plugins.multijob.MultiJobProject':
        return True
    description = root.find('./description')
    mailer = root.find('./publishers/hudson.tasks.Mailer')
    recips = None
    if mailer == None:
        mailer = root.find('./publishers/hudson.plugins.emailext.ExtendedEmailPublisher')
        if mailer == None:
            print("Error; Job %s has no email notification setup" % job)
            return True
        recips = mailer.find("recipientList")
    else:
        recips = mailer.find("recipients")
    if check_recips(description, recips):
        return True

def check_email_plots(root, job):
    mailer = root.find('./publishers/hudson.plugins.emailext.ExtendedEmailPublisher')
    if mailer == None:
        return True
    content = mailer.find("defaultContent")
    if content == None:
        return True
    contentBody = content.text
    if "Plot:" in contentBody:
        if not job in contentBody:
            return False
    return True

def check_clean(text):
    if "clean -fdqx" in text:
        return True

def check_configure(text):
    if "configure" in text:
        return True

def check_strict(text):
    regex = re.compile(r"CC=\".*clang")
    # Skip those tests which set explicit warnings
    if "$warnings" in text:
        return True
    if "-W" in text:
        return True
    if "CC=\"clang" in text:
        return True
    if "enable-strict" in text:
        return True
    if re.search(regex, text) != None:
        return True
    return False

def check_matches(root, job):
    global match_jobs
    global match_jobs_set
    builders = root.find('./builders')
    if builders == None:
        print("Error, no builders found in job %s" % job)
        return False
    for counter, member in enumerate(match_jobs):
        if job == match_jobs[counter][0]:
            match_jobs[counter][1] = etree.tostring(builders)

    if match_jobs_set == False:
        match_jobs_set = True
    else:
        if match_jobs[0][1] != match_jobs[1][1]:
            print("Error, jobs %s and %s don't match!" % (match_jobs[0][0], match_jobs[1][0]))
            return False
    return True

def check_archiving_perf_jobs(root, job):
    found_stats = False
    plots = root.find('./publishers/hudson.plugins.plot.PlotPublisher') 

    # If there is no plotting, we don't care
    if plots == None:
        return True

    archives = root.find('./publishers/hudson.tasks.ArtifactArchiver/artifacts')

    # If there is nothing archived, then we have failed
    if archives == None:
        print("Error; perf job %s doesn't archive stats" % job)
        return False

    if "diagdata" in archives.text:
        found_stats = True

    if "diagnostic.data" in archives.text:
        found_stats = True

    if "WiredTigerStat" in archives.text:
        found_stats = True

    if found_stats == False:
        print("Error; perf job %s doesn't archive stats" % job)

    return found_stats

def check_builds(root, job):

    builders = root.find('./builders')
    # Check if this test builds something
    if builders == None:
        return True
    found_compile = False
    found_strict = False
    found_clean = False
    for b in list(builders):
        command = b.find("./command")
        if command == None:
            continue
        if check_configure(command.text):
            found_compile = True
            if check_strict(command.text):
                found_strict = True

        if check_clean(command.text):
            found_clean = True

    if job not in clean_skips:
        if not found_clean:
            print("Error; Builder(s) in job %s don't have git clean" % job)

    # If the job doesn't do a WT compile, there is no issue
    if not found_compile:
        return True

    if job in strict_skips:
        return True
    
    return found_strict

# Remove MongoDB branches that are begin tested
def check_mongodb_builds(root, job):
    global github_branches
    if "mongodb-perf-ycsb-mongodb-" not in job:
        return
    m = re.search('(\d\.\d)', job)
    branch = m.groups(0)[0]
    if branch not in github_branches:
        print("Error; Job %s doesn't have a matching branch on Github" % job)
    github_branches.remove(branch)

# Grab all the mongodb branches on github into a list to remove from later
def setup_mongodb_branches():
    global github_branches
    r = requests.get('https://api.github.com/repos/wiredtiger/wiredtiger/branches')
    if(r.ok):
        repoItem = json.loads(r.text or r.content)
        for i in repoItem:
            branch_name = i["name"]
            if "mongodb-" in branch_name:
                branch_name = branch_name.split("-",1)[1]
                if branch_name not in mongodb_branch_skips:
                    github_branches.append(branch_name)

# Main - setup for local testing if requested
parser = argparse.ArgumentParser()
parser.add_argument('--job_dir', nargs='?', help='Jenkins configuration jobs directory', default='/home/jenkins/jenkins/jobs')
args = parser.parse_args()
job_dir = args.job_dir


setup_mongodb_branches()
for job in os.listdir(job_dir):
    config_file = job_dir + "/" + job + "/config.xml"
    if not os.path.exists(config_file):
        print("Old Job found - %s" % job)
        continue
    root = etree.parse(config_file).getroot()
    check_mongodb_builds(root, job)
    for match in match_jobs:
        if job == match[0]:
            check_matches(root, job)
    if job not in email_check_skip:
        check_mail(root)
    if not check_builds(root, job):
        print("Error; Builder(s) in job %s don't have --enable-strict" % job)
    if not check_email_plots(root, job):
        print("Error; Email of plots in job %s doesn't have the correct URL" % job)
    if job not in archive_stats_skips:
        check_archiving_perf_jobs(root, job)

# We should have at max 1 branch, the current head of mongodb, which is tested by develop
if len(github_branches) > 1:
    print("Error; There are branches that aren't tested by mongodb-perf Jenkins jobs")
