
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>

#ifndef SEEK_DATA
#define SEEK_DATA      3
#define SEEK_HOLE      4
#endif

static struct stat regstat;
static int fd = -1;

static void output_filemap(char *filename)
{
	off_t cur_pos = 0, next_pos = 0, seek_type = SEEK_HOLE;
	char *smsg = NULL;
	int parti = 1;

	printf("Filemap for %s, size=%ld,\n", filename, regstat.st_size);

	while (1) {
		next_pos = lseek(fd, cur_pos, seek_type);

		if (seek_type == SEEK_DATA) {
			seek_type = SEEK_HOLE;
			smsg = "HOLE";
		} else {
			seek_type = SEEK_DATA;
			smsg = "DATA";
		}

		/* Avoid bad seek type */
		if (next_pos == cur_pos)
			continue;

		if (next_pos == -1) {
			if (cur_pos != regstat.st_size) {
				printf("Part%5d: %s 0x%010llx ---> 0x%010llx\n",
					parti++, smsg, cur_pos, regstat.st_size);
			}
			return ;
		}

		printf("Part%5d: %s 0x%010llx ---> 0x%010llx\n",
			parti++, smsg, cur_pos, next_pos);
		cur_pos = next_pos;
	}
}

int main(int argc, char **argv)
{
	char *regfile = argv[1];

	if (argc < 2) {
		printf("Usage: %s regfile\n", argv[0]);
		return 1;
	}

	if (stat(regfile, &regstat)) {
		printf("Get %s's stat information failed: %m\n", regfile);
		return 1;
	}

	fd = open(regfile, O_RDONLY);
	if (fd < 0) {
		printf("Open %s with readonly failed: %m\n", regfile);
		return 1;
	}

	output_filemap(regfile);
	close(fd);
	return 0;
}
