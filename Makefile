
INSTALL_DIR="/usr/sbin/"

all:
	gcc -o filemap filemap.c
	gcc -o readdir readdir.c
install:
	cp -rf *.sh $(INSTALL_DIR)
	cp -rf filemap readdir $(INSTALL_DIR)
clean:
	rm -rf filemap readdir
