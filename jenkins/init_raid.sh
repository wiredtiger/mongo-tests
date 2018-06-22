#!/usr/bin/env bash
#
# Use this script to set up software RAID device and mount it for Jenkins use.
# RAID level 0 is used to distribute traffic and increase overall throughput.
#
set -ex

# Make sure only root can run our script
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

# Sometimes AWS automatically mounts the ephemeral drive. Unmount it.
umount /media/ephemeral0
umount /media/ephemeral1

# Partition our two ephemeral drives.
hdd="/dev/xvdb /dev/xvdc"
for i in $hdd;do
echo "n
p
1


t
fd
w
"|fdisk $i;done

# Create the software raid device
echo "y
" | mdadm --create --verbose --auto=yes /dev/md0 --level=0 --raid-devices=2 /dev/xvdb /dev/xvdc

# Make the XFS filesytem on our raid device
mkfs -t xfs /dev/md0

# Mount the device
[ ! -d /mnt/fast ] && mkdir /mnt/fast
mount /dev/md0 /mnt/fast

# Create jenkins directory
mkdir /mnt/fast/jenkins
chown jenkins:jenkins /mnt/fast/jenkins
