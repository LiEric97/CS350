#include <stdio.h>
#include <unistd.h>
#include <linux/time.h>
#include <linux/unistd.h>

#define my_x_time 326

int main(void) {
	struct timespec time;
	int ret;
	ret = syscall(my_x_time, &time);
	printf("time.tv_sec = %lu, time.tv_nsec = %lu\n", time.tv_sec, time.tv_nsec);
	printf("system call return value = %d\n", ret);

}
