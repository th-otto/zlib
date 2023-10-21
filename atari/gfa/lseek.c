#include <unistd.h>
#include <osbind.h>

off_t lseek(int fd, off_t offset, int whence)
{
	return Fseek(offset, fd, whence);
}
