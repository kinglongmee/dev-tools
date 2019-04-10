
#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <errno.h>

static int longsyscall;

#define BUFSIZE 4096

int main(int argc, char **argv)
{
	struct linux_dirent64 *dirp64;
	struct linux_dirent *dirp;
	const char *d_name = argv[1];
	int fd = -1, retval = -1;
	void *buf = NULL;

	if (argc < 2) {
		printf("needs a dir path");
		return -1;
	}

	buf = malloc(BUFSIZE);
	dirp64 = buf;
	dirp = buf;

	fd = open(d_name, O_RDONLY);
	if (fd == -1) {
		printf("open of directory failed");
		return -1;
	}
next:
	if (longsyscall)
		retval = syscall(SYS_getdents64, fd, dirp64, BUFSIZE);
	else
		retval = syscall(SYS_getdents, fd, dirp, BUFSIZE);

	if (retval < 0) {
		if (errno == ENOSYS)
			printf("syscall not implemented");
		else
			printf("getdents failed unexpectedly");
	}

	if (retval > 0)
		goto next;

	if (close(fd) == -1)
		printf("Directory close failed");

	return 0;
}
