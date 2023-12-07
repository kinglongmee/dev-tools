
INSTALL_DIR="/usr/sbin/"

all:
	gcc -o filemap filemap.c
	gcc -o readdir readdir.c
	gcc -o getdents getdents.c
	gcc -o create_random_files create_random_files.c
	gcc -o lockfile lockfile.c
	gcc -o data-ctest data-ctest.c
install: all
	cp -rf *.sh $(INSTALL_DIR)
	cp -rf filemap readdir getdents create_random_files lockfile data-ctest $(INSTALL_DIR)
clean:
	rm -rf filemap readdir getdents create_random_files lockfile data-ctest
