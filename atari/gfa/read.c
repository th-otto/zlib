#include <unistd.h>
#include <osbind.h>

ssize_t read(int fd, void *buf, size_t nbytes)
{
    long result;

    result = Fread(fd, nbytes, buf);
	if (result < 0)
		result = -1;
    return result;
}
