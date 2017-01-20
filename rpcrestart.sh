service nfs stop
umount -f /proc/fs/nfsd/
rmmod nfsd rpcsec_gss_krb5 auth_rpcgss nfsv4 blocklayoutdriver nfs lockd nfs_acl
umount /var/lib/nfs/rpc_pipefs/
rmmod sunrpc
lsmod | grep rpc
cp -f net/sunrpc/sunrpc.ko /lib/modules/`uname -r`/kernel/net/sunrpc/sunrpc.ko
service rpcbind start
