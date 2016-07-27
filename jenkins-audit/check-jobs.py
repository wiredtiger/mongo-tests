#! /usr/bin/python
import xml.etree.ElementTree
import os
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
            print("Error, job %s has no email notification setup" % job)
            return True
        recips = mailer.find("recipientList")
    else:
        recips = mailer.find("recipients")
    if check_recips(recips):
        return True

for job in os.listdir(job_dir):
    config_file = job_dir + job + "/config.xml"
    if not os.path.exists(config_file): 
        print("Old Job found - %s" % job)
        continue
    root = xml.etree.ElementTree.parse(config_file).getroot()
    if check_mail(root):
        continue
