
INSTALL_DIR="/usr/sbin/"

all:
	gcc -o filemap filemap.c
install:
	cp -rf *.sh $(INSTALL_DIR)
	cp -rf filemap $(INSTALL_DIR)
clean:
	rm -rf filemap
