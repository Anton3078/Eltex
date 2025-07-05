#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#include <linux/uaccess.h>

static int major = 0;
static rwlock_t lock;
static char string[15] = "Hello!\0";

ssize_t test_read (struct file* fd, char __user *buff, size_t size, loff_t *off)
{
    size_t rc;
    
    pr_info("test_read: buff=%p, size=%zu, off=%lld\n", buff, size, *off);

    if(!access_ok(buff, size)) {
        pr_info("access_ok\n");    
        return -EFAULT;
    }

    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, string, 15);
    read_unlock(&lock);
    pr_info("string: %s\n", string);
    pr_info("Success read from buffer\n");
    return rc;
}

ssize_t test_write(struct file* fd, const char __user *buff, size_t size, loff_t *off)
{
    pr_info("===== test_write =====");
    size_t rc = 0;
    if (size > 15)
       return -EINVAL;

    write_lock(&lock);
    rc = simple_write_to_buffer(string, 15, off, buff, size);
    write_unlock(&lock);
    
    return rc;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};

int 
init_module()
{
    pr_info("===== my_module2 loaded  =====\n");
    rwlock_init(&lock);
    major = register_chrdev(0, "module2", &fops);

    if (major < 0)
       return major;
    pr_info("Major number is %d\n", major);

    return 0;
}

void
cleanup_module()
{
    pr_info("===== my_module2 unloaded =====\n");
    unregister_chrdev(major, "module2");
}

MODULE_LICENSE("GPL");

