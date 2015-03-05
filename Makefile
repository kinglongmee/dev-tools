
INSTALL_DIR="/usr/sbin/"

all: install
install:
	cp -rf gentags.sh $(INSTALL_DIR)
	cp -rf rmnfsdko.sh $(INSTALL_DIR)
	cp -rf loadnfsdko.sh $(INSTALL_DIR)
