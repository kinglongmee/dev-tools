rmmod nfs_layout_nfsv41_files nfs_layout_flexfiles blocklayoutdriver nfsv2 nfsv3 nfsv4 nfs fscache
lsmod | grep nfs
cp -f fs/nfs/blocklayout/blocklayoutdriver.ko /lib/modules/`uname -r`/kernel/fs/nfs/blocklayout/
cp -f fs/nfs/filelayout/nfs_layout_nfsv41_files.ko /lib/modules/`uname -r`/kernel/fs/nfs/filelayout/
cp -f fs/nfs/flexfilelayout/nfs_layout_flexfiles.ko /lib/modules/`uname -r`/kernel/fs/nfs/flexfilelayout/
cp -f fs/nfs/nfsv4.ko /lib/modules/`uname -r`/kernel/fs/nfs/
cp -f fs/nfs/nfs.ko /lib/modules/`uname -r`/kernel/fs/nfs/
cp -f fs/fscache/fscache.ko /lib/modules/`uname -r`/kernel/fs/fscache/
