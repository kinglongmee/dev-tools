cp -f fs/nfsd/nfsd.ko /lib/modules/`uname -r`/kernel/fs/nfsd/nfsd.ko
service nfs start
service nfs status
