service nfs stop
sleep 1s
umount -f /proc/fs/nfsd/
sleep 1s
lsmod | grep nfsd
rmmod nfsd
lsmod | grep nfsd
cp -f fs/nfsd/nfsd.ko /lib/modules/`uname -r`/kernel/fs/nfsd/nfsd.ko
service nfs start
service nfs status
