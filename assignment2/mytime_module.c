#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define LENGTH 128

MODULE_LICENSE("GPL");

/* Prototypes */
static ssize_t read_dev(struct file *, char __user *, size_t, loff_t *);


static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = read_dev
};

static struct miscdevice my_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mytime",
	.fops = &fops
};

static ssize_t read_dev(struct file *file, char __user * out, size_t size, loff_t *off) {
	char buf[LENGTH];

	struct timespec ktime = current_kernel_time();
	struct timespec time;

	getnstimeofday(&time);

	if(!access_ok(VERIFY_WRITE, out, LENGTH * sizeof(char))) {
		return -1;
	}

	sprintf(buf, "current_kernel_time: %lu %lu\ngetnstimeofday: %lu %lu\n", ktime.tv_sec, ktime.tv_nsec, time.tv_sec, time.tv_nsec);
	return copy_to_user(out, buf, strlen(buf)+1);
}

int __init init_module() {
	printk(KERN_INFO "mytime: Initializing mytime module\n");
	misc_register(&my_dev);
        return 0;
}

void __exit cleanup_module() {
	printk(KERN_INFO "mytime: Cleaning up mytime module\n");
	misc_deregister(&my_dev);
}

