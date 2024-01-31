#define pr_fmt(fmt) "[MemModule] %s: " fmt, __func__
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Ruki");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("a simplest module");


int add(int a, int b);

int hello_init(void)
{
    pr_info("Hello World: %d\n", add(1, 2));
    
    return 0;
}

void hello_exit(void)
{
    pr_info("Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
