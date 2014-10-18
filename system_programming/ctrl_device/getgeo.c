
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/hdreg.h>

int main(int argc,char **argv)
{
	int cdrom;                           /* CDROM device file descriptor */

	/* Open the CDROM device. The linux/cdrom.h header file specifies that
	 *    ** it must be given the O_NONBLOCK flag when opening. My tests showed
	 *       ** that if this isn't done, this program will not work. 
	 *          */
	if ((cdrom = open("/dev/sda",O_RDONLY | O_NONBLOCK)) < 0) {
		perror("open");
		exit(1);
	}

	/* Use ioctl to send the CDROMEJECT command to the device
	 *    */
	struct hd_geometry geo;
	if (ioctl(cdrom,HDIO_GETGEO,&geo)<0) {
		perror("ioctl");
		exit(1);
	}
	printf("%d\n", geo.heads);
	printf("%d\n", geo.sectors);
	printf("%d\n", geo.cylinders);
	unsigned char identity[512];
	ioctl(cdrom, HDIO_GET_IDENTITY, identity);
	printf("%s\n", identity);
	int i = 0;
	for(i ; i < 10 ; i++)
	{
		printf("%d ", identity[i]);
	}
	printf("\n");

	struct hd_driveid hd;
	ioctl(cdrom,HDIO_GET_IDENTITY, &hd);
	printf("Hard disk model: %s\n",hd.model);
	printf("Serial number: %s\n",hd.serial_no); 

	close(cdrom);
}

