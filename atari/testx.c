#include <stdio.h>
#include <fcntl.h>

#define filename "x"

char buf[32000];

int main(void)
{
	int fd;
	size_t nread;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "cnt open %s\n", filename);
		return 1;
	}
	nread = read(fd, buf, sizeof(buf));
	close(fd);
	printf("nread: %lu\n", nread);
	printf("__TURBOC__: %x\n", __TURBOC__);
	printf("__PUREC__: %x\n", __PUREC__);
	return 0;
}