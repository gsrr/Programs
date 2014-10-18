#include <sys/cred.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <fcntl.h>
#include <sys/dkio.h>
#include <sys/vtoc.h>
#include <unistd.h>
#include <stropts.h>
#include <stdio.h>

int main()
{
	struct dk_cinfo diskInfo;
	int fd = open('/dev/dsk/c3d0p0', O_RDONLY | O_NONBLOCK);
	ioctl(fd, DKIOCINFO, &diskInfo);
	printf("%s\n", diskInfo.dki_cname);
	printf("%d\n", diskInfo.dki_flags);
	printf("%s\n", diskInfo.dki_dname);
	return 0;
}

