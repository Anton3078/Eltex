#include <linux/module.h>
#include <linux/kernel.h>

int 
init_module()
{
    pr_info("===== Hello my_module! =====\n");
    return 0;
}

void
cleanup_module()
{
    pr_info("===== my_module unloaded =====\n");
}

MODULE_LICENSE("GPL");
