#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 32

int main(int argc, char **argv)
{
	int fd = 0, i = 0, ret = 0, fw = 0;	
	static int first = 1;
	char buf[BUFSIZE];

	if (argc < 3) {
		fprintf(stdout, "argc error\n");
		fprintf(stdout, "Usage: a.out file<source>  file<distnation>i\n");
		return -1;
	}
	
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		fprintf(stdout, "open source error\n");
		return -1;
	}

	fw = open(argv[2], O_CREAT|O_RDWR, 0755);
	if (fw < 0) {
		fprintf(stdout, "open distnation error\n");
		return -1;
	}

	for (; ;) {
		ret = read(fd, buf, BUFSIZE);
		
		if (ret < 0) {
			fprintf(stdout, "read error\n");
			close(fd);
			return -1;
		}
		
		if (ret == 0) {
			fprintf(stdout, "read over\n");
			close(fd);
			return 0;
		}

		for (i = 0; i < ret; i++) {
			if (isspace(buf[i])) {
				first = 1;
			} else if (isalpha(buf[i]) && first == 1) {
				buf[i] = buf[i] - ('a' - 'A');
				first = 0;
			} else {
//				continue;
			}
		}

		ret = write(fw, buf, ret);
		if (ret < 0) {
			fprintf(stdout, "write error\n");
			close(fd);
			close(fw);
			return -1;
		}
	}
	close(fw);

	return 0;
}
