#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kobject.h>
#include <linux/proc_fs.h>

static int svar;

static int major = 0;
static rwlock_t lock;
static char string[15] = "Hello!\0";

static struct kobject *test_kobj = NULL;

static struct proc_dir_entry *test = NULL;

//= Sysfs =========================================================================================
static ssize_t
svar_read_test (struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    pr_info("===== Start svar_read_test =====\n");
    return sysfs_emit(buf, "%d\n", svar); 
}

static ssize_t
svar_write_test (struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int rc;

    rc = kstrtoint(buf, 10, &svar);
    if (rc < 0)
        return rc;

    return count;
}

static struct kobj_attribute svar_attribute = __ATTR(svar, 0644, svar_read_test, svar_write_test);

static struct attribute *attrs[] =  {
    &svar_attribute.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs
};


//======================================================================================== Sysfs =

//= proc_fs=======================================================================================
ssize_t 
test_proc_read (struct file* fd, char __user *buff, size_t size, loff_t *off)
{
    size_t rc;
    
    pr_info("test_proc_read: buff=%p, size=%zu, off=%lld\n", buff, size, *off);
    
    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, string, 15);
    read_unlock(&lock);
    pr_info("string: %s\n", string);
    pr_info("Success read from buffer\n");
    return rc;
}

ssize_t 
test_proc_write(struct file* fd, const char __user *buff, size_t size, loff_t *off)
{
    pr_info("===== test_proc_write =====\n");
    size_t rc = 0;
    if (size > 15)
       return -EINVAL;

    write_lock(&lock);
    rc = simple_write_to_buffer(string, 15, off, buff, size);
    write_unlock(&lock);
    pr_info("Success write to buffer (proc)\n");
     
    return rc;
}

static const struct proc_ops prcops = {
    .proc_read = test_proc_read,
    .proc_write = test_proc_write,
};

//====================================================================================== proc_fs =


//= Character device ============================================================ 
ssize_t 
test_read (struct file* fd, char __user *buff, size_t size, loff_t *off)
{
    size_t rc;
    
    pr_info("test_read: buff=%p, size=%zu, off=%lld\n", buff, size, *off);
    
    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, string, 15);
    read_unlock(&lock);
    pr_info("string: %s\n", string);
    pr_info("Success read from buffer\n");
    return rc;
}

ssize_t 
test_write(struct file* fd, const char __user *buff, size_t size, loff_t *off)
{
    pr_info("===== test_write =====\n");
    size_t rc = 0;
    if (size > 15)
       return -EINVAL;

    write_lock(&lock);
    rc = simple_write_to_buffer(string, 15, off, buff, size);
    write_unlock(&lock);
    pr_info("Success write to buffer\n");
    
    return rc;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};
//========================================================== Charecter device  = 


//= Main =======================================================================
int 
init_module()
{
    int retval;

    pr_info("===== my_module3 loaded  =====\n");
    
    rwlock_init(&lock);
    major = register_chrdev(0, "module3", &fops);
    
    if (major < 0) return major;
    pr_info("Major number is %d\n", major);
    
    test = proc_create("test", 0666, NULL, &prcops);
    if (NULL == test) {
        pr_info("Error: Could not initialize proc/test\n");
        return -ENOMEM;
    } else {
        pr_info("proc/test created\n");
    }

    test_kobj = kobject_create_and_add("kobject_example", kernel_kobj);
    if (!test_kobj) {
        pr_info("Error: Could not intialoze kobject_example\n");    
        return -ENOMEM;
    } else {
        pr_info("kobject_example created\n");
    }
 

    retval = sysfs_create_group(test_kobj, &attr_group);
    if (retval) {
        kobject_put(test_kobj);
        return retval;
    }
    

    return 0;
}

void
cleanup_module()
{
    unregister_chrdev(major, "module3");
    proc_remove(test);
    kobject_put(test_kobj);
    pr_info("===== my_module3 unloaded =====\n");
}
//====================================================================== Main =

MODULE_LICENSE("GPL");
