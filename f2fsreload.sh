service nfs-server stop
umount -f /f2fs/
rmmod f2fs
lsmod | grep f2fs
cp -f fs/f2fs/f2fs.ko /lib/modules/`uname -r`/kernel/fs/f2fs/f2fs.ko
mount -a
service nfs-server start
