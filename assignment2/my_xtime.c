/*
 * my_xtime system call
 * Name: Eric W. Li
 * CS 350: Operating Systems
 */

#include <asm/uaccess.h>
#include <linux/export.h>
#include <linux/linkage.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/time.h>

asmlinkage int my_xtime(struct timespec *current_time) {
	struct timespec k_time;
	unsigned long long time;

	/* Check that memory pointed to by current_time is writable */
	if (!access_ok(VERIFY_WRITE, current_time, sizeof(struct timespec))) {
		return -EFAULT;
	}

	k_time = current_kernel_time();

	if (copy_to_user(current_time, &k_time, sizeof(struct timespec))) {
		return -EFAULT;
	}

	time = k_time.tv_sec * 1000000000 + k_time.tv_nsec;

	printk(KERN_ALERT "current kernel time (ns) = %llu\n", time);

	return 0;
}

EXPORT_SYMBOL(my_xtime);
