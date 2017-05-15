#! /usr/bin/python
import xml.etree.ElementTree as etree
import os

strcit_skips = [
    "wiredtiger-osx",
    "wiredtiger-compat-r1",
    "wiredtiger-compat-r2",
    "wiredtiger-compat-develop",
    "wiredtiger-test-mongodb-3.0",
    "wiredtiger-test-mongodb-3.2"
]

email_check_skip = [
    "wiredtiger-syscall-linux",
    "wiredtiger-fault-inject",
    "wiredtiger-massive-scale",
]

match_jobs = [
    ["wiredtiger-test-format-stress-sanitizer", None],
    ["wiredtiger-test-format-stress-sanitizer-old-branches", None]
]

clean_skips = [
    "wiredtiger-pull-request",
    "jenkins-audit",
    "wiredtiger-perf-long-jobs",
    "wiredtiger-perf",
]

match_jobs_set = False

job_dir = "/home/jenkins/jenkins/jobs/"
def check_recips (recips):
    if recips == None:
        print("Error, job %s has no recipients set" % job)
        return True
    email = recips.text
    if email != 'testing@wiredtiger.com' and email != '${ghprbActualCommitAuthorEmail}, testing@wiredtiger.com':
        print("Error, job %s not got testing as the email address, it has %s" % (job, email))
        return True

def check_mail (root):
    # Skip the top multijob processes, they dont send emails
    if root.tag == 'com.tikal.jenkins.plugins.multijob.MultiJobProject':
        return True
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
    if check_recips(recips):
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
    # Skip those tests which set explicit warnings
    if "$warnings" in text:
        return True
    if "-W" in text:
        return True
    if "CC=\"clang" in text:
        return True
    if "enable-strict" in text:
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

    if job in strcit_skips:
        return True
    
    return found_strict


for job in os.listdir(job_dir):
    config_file = job_dir + job + "/config.xml"
    if not os.path.exists(config_file):
        print("Old Job found - %s" % job)
        continue
    root = etree.parse(config_file).getroot()
    for match in match_jobs:
        if job == match[0]:
            check_matches(root, job)
    if job not in email_check_skip:
        check_mail(root)
    if not check_builds(root, job):
        print("Error; Builder(s) in job %s don't have --enable-strict" % job)
    if not check_email_plots(root, job):
        print("Error; Email of plots in job %s doesn't have the correct URL" % job)
