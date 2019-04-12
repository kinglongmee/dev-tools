
INSTALL_DIR="/usr/sbin/"

all:
	gcc -o filemap filemap.c
	gcc -o readdir readdir.c
	gcc -o getdents getdents.c
install: all
	cp -rf *.sh $(INSTALL_DIR)
	cp -rf filemap readdir getdents $(INSTALL_DIR)
clean:
	rm -rf filemap readdir getdents
