#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

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