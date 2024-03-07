
#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <assert.h>

struct linux_dirent {
	long		d_ino;
	off_t		d_off;
	unsigned short	d_reclen;
	char		d_name[];
	/*
	char		pad;		// Zero padding byte
	char		d_type;		// File type (only since Linux
					// 2.6.4); offset is (d_reclen - 1)
	*/
};

#define BUFSIZE 1048576ULL

int main(int argc, char **argv)
{
	char *dirpath = NULL, *dirbuf = NULL;
	struct linux_dirent *dirp = NULL;
	int fd = -1, nread = -1, len = 0, title = 1;
	char d_type = 0;

	if (argc < 2) {
		printf("Usage: %s dirpath.\n", argv[0]);
		return -1;
	}

	dirpath = argv[1];
	fd = open(dirpath, O_DIRECTORY);
	if (fd < 0) {
		printf("Open directory %s failed: %m", dirpath);
		return -1;
	}

	dirbuf = malloc(BUFSIZE);
	assert(dirbuf);

	for ( ; ; ) {
		nread = syscall(SYS_getdents, fd, dirbuf, BUFSIZE);
		if (nread < 0) {
			printf("Getdents failed: %m", dirpath);
			return -1;
		} else if (nread == 0)
			break;

		if (title) {
			printf("----------------------- nread=%d ----------------------\n", nread);
			printf("          i-node  d_reclen               d_off  d_type  d_name\n");
			title = 0;
		}

		for (len = 0; len < nread; ) {
			dirp = (struct linux_dirent *) (dirbuf + len);
			d_type = *((char *)dirp + (dirp->d_reclen - 1));
			printf("%16lu  ", dirp->d_ino);
			printf("%8u  0x%.16llx  %6u  %s\n", dirp->d_reclen,
				(long long) dirp->d_off, d_type, dirp->d_name);
			len += dirp->d_reclen;
		}
	}

	return 0;
}
