#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#define N 100
#define MAX_LENGTH 128

int main() {
	int i;
	struct timeval gtodTimes[N];
	char *procClockTime[N];

	/* Allocate memory for character buffers */
	for (i = 0; i < N; i++)
		procClockTime[i] = (char *) malloc(MAX_LENGTH);

	int fd = open("/dev/mytime", O_RDONLY);

	/* Check for errors */
	if (fd == -1) {
		fprintf(stderr, "open error: %s\n", strerror(errno));
		exit(1);
	}
	for (i = 0; i < N; i++) {
		if (gettimeofday(&gtodTimes[i], 0) == -1)
			fprintf(stderr, "gettimeofday error: %s\n", strerror(errno));

		size_t bytes_read = read(fd, procClockTime[i], MAX_LENGTH);
		/* Handle read error */
		if (bytes_read == -1) {
			fprintf(stderr, "read error: %s\n", strerror(errno));
			exit(1);
		}
	}
	if (close(fd) == -1)
		fprintf(stderr, "close error: %s\n", strerror(errno));

	for (i = 0; i < N; i++) {
		printf("gettimeofday: %lu %lu\n%s\n", gtodTimes[i].tv_sec, gtodTimes[i].tv_usec, procClockTime[i]);
	}

	return 0;
}
