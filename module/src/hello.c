#define pr_fmt(fmt) "[MemModule] %s: " fmt, __func__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/sock.h>



// taken from xmake demo project
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ElCapor");
MODULE_DESCRIPTION("A Module ");
MODULE_ALIAS("Simple Module To Read Your Mom");

/*
PROCESS UTILITIES
*/
void read_proc(void);


/*
SETUP NETLINK
*/


int hello_init(void)
{
    pr_info("Loaded \n");
    read_proc();
    return 0;
}

void hello_exit(void)
{
    pr_info("Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
