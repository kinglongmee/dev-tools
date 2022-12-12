
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	struct flock flck;
	char *filepath = NULL;
	int fd = -1;
	int ret = 0;

	if (argc < 2) {
		printf("Usage: %s filepath.\n", argv[0]);
		return -1;
	}

	filepath = argv[1];
	fd = open(filepath, O_RDWR | O_CREAT, 0777);
	if (fd < 0) {
		printf("Openf %s failed: %m.\n", filepath);
		return -1;
	}

	memset(&flck, 0, sizeof(flck));
	flck.l_type = F_WRLCK;
	flck.l_whence = SEEK_SET;
	flck.l_start = 0;
	flck.l_len = 0;
	flck.l_pid = getpid();

	ret = fcntl(fd, F_SETLK, &flck);
	if (ret < 0) {
		printf("Lock %s of (0:0) failed: %m.\n", filepath);
	} else {
		printf("Press enter to continue...\n");
		getchar();
	}

	flck.l_type = F_UNLCK;
	ret = fcntl(fd, F_SETLK, &flck);
	if (ret < 0) {
		printf("Unlock %s of (0:0) failed: %m.\n", filepath);
	}

	close(fd);
	return 0;
}
