/* my_xtime system call
 * Name: Eric W. Li
 * CS 350: Operating Systems
 */

#include <linux/time.h>

asmlinkage int my_xtime(struct timespec *current_time) {
	/* Check that memory pointed to by current_time is writable */
	if (!access_ok(VERIFY_WRITE, current_time, sizeof(struct timespec)) {
		return -EFAULT;
	}

	struct timespec k_time = current_kernel_time();
	copy_to_user(current_time, k_time, sizeof(struct timespec));
	printk(KERN_ALERT "current kernel time = %d\n", k_time.tv_nsec);

	return 0;
}
