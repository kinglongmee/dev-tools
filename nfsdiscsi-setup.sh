tgtadm --lld iscsi --op new --mode target --tid 1 --targetname iqn.nfs-server-test
tgtadm --lld iscsi --op new --mode logicalunit --tid 1 --lun 1 -b /dev/sdc
tgtadm --lld iscsi --op new --mode logicalunit --tid 1 --lun 2 -b /dev/sdd
tgtadm --lld iscsi --op new --mode logicalunit --tid 1 --lun 3 -b /dev/sde
tgtadm --lld iscsi --op bind --mode target --tid 1 -I ALL
tgtadm --lld iscsi --op show --mode target
