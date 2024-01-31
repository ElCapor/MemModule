#define pr_fmt(fmt) "[MemModule] %s: " fmt, __func__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Ruki");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("a simplest module");


int add(int a, int b);

void read_proc(void)
{
    struct task_struct* task_list;
        size_t process_counter = 0;
        for_each_process(task_list) {
                pr_info("== %s [%d]\n", task_list->comm, task_list->pid);
                ++process_counter;
        }
        pr_info("== Number of process: %zu\n", process_counter);
}

int hello_init(void)
{
    pr_info("Hello World: %d\n", add(1, 2));
    read_proc();
    return 0;
}

void hello_exit(void)
{
    pr_info("Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
