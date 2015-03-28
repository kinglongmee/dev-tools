service nfs stop
umount /proc/fs/nfsd/
lsmod | grep nfsd
rmmod nfsd
