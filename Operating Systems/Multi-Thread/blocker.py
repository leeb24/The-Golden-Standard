import os,time
from shutil import copyfile

##backUp the raw hosts file

if not os.path.isfile("/etc/hostsbackup"):
     copyfile("/etc/hosts","/etc/hostsbackup")

##get the raw data of hosts
length = raw_input("how long(in miniutes) do you want to block the websites?")

with open("/etc/hostsbackup","r") as rawf:
    rawContent = rawf.read()
##clear the data in hosts
open("/etc/hosts","w").close()

##add the website you want to block here
changedContent = rawContent + '\n' + '127.0.0.1\twww.facebook.com\n'

##now write the changed data into hosts
with open("/etc/hosts","a") as f:
    f.write(changedContent)
##set the blocking length here
time.sleep(float(length) * 60)

##clear the hosts
open("/etc/hosts","w").close()

##write back the raw data into hosts
with open("/etc/hosts","a") as f:
    f.write(rawContent)