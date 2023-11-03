#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <linux/types.h>

int main( int argc, char **argv, char **envp )
{
	int fd_gpio;
	int value;
	struct timespec sleeptime;
	__u8 t;

	fd_gpio=open("/dev/fastgpio", O_WRONLY);
	if (fd_gpio<0) {
		printf("kann /dev/fastgpio nicht oeffnen.\n");
		return -1;
	}

	sleeptime.tv_sec = 0;
	sleeptime.tv_nsec= 500000000;
	while (1) {
		value = 1;
		write( fd_gpio, &value, sizeof(value) );
		clock_nanosleep( CLOCK_MONOTONIC, 0, &sleeptime, NULL );
		value = 0;
		write( fd_gpio, &value, sizeof(value) );
		clock_nanosleep( CLOCK_MONOTONIC, 0, &sleeptime, NULL );
	}
	return 0;
}
