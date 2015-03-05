service nfs stop
umount /proc/fs/nfsd/
rmmod nfsd
lsmod | grep nfsd
