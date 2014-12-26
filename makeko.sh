mkfile='KERNELDIR:=/lib/modules/`uname -r`/build\nPWD:=`pwd`\ndefault:\n\t$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules\nclean:\n\trm -rf *.o *.mod.c *.mod.o *.ko'
if [ "$#" -lt "1" ]
then
	echo "Usage: $0 module_name"
fi

makeko() {
	cd $dir
	cp Makefile Makefile.bak
	echo -e $mkfile >> Makefile
	make
	mv -f Makefile.bak Makefile
	cd -
}

for mod in $@
do
	for dir in `find . -name $mod`
	do
		if [ -e $dir/Makefile ]
		then
			makeko
		fi
	done
done
