service nfs stop
sleep 1s
umount -f /proc/fs/nfsd/
sleep 1s
lsmod | grep nfsd
rmmod nfsd
lsmod | grep nfsd
cp -f fs/lockd/lockd.ko /lib/modules/`uname -r`/kernel/fs/lockd/lockd.ko
cp -f fs/nfsd/nfsd.ko /lib/modules/`uname -r`/kernel/fs/nfsd/nfsd.ko
cp -f net/sunrpc/sunrpc.ko /lib/modules/`uname -r`/kernel/net/sunrpc/sunrpc.ko
service rpcbind start
sleep 1s
service nfs start
service nfs status
