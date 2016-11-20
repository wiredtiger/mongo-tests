#! /usr/bin/python
import xml.etree.ElementTree
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
    "wiredtiger-syscall-linux"
]
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


def check_builds(root):
    builders = root.find('./builders')
    # Check if this test builds something
    if builders == None:
        return True
    found_compile = False
    found_strict = False
    for b in list(builders):
        command = b.find("./command")
        if command == None:
            continue
        if check_configure(command.text):
            found_compile = True
            if check_strict(command.text):
                found_strict = True
    # If the job doesn't do a WT compile, there is no issue
    if not found_compile:
        return True
    return found_strict


for job in os.listdir(job_dir):
    config_file = job_dir + job + "/config.xml"
    if not os.path.exists(config_file):
        print("Old Job found - %s" % job)
        continue
    root = xml.etree.ElementTree.parse(config_file).getroot()
    if job not in email_check_skip:
        check_mail(root)
    if job not in strcit_skips:
        if not check_builds(root):
            print("Error; Builder(s) in job %s don't have --enable-strict" % job)
