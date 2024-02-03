#define pr_fmt(fmt) "[MemModule] %s: " fmt, __func__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/stat.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <uapi/linux/string.h>


#include "kjson.h"
#include "kjstring.h"

// taken from xmake demo project
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ElCapor");
MODULE_DESCRIPTION("A Module ");
MODULE_ALIAS("Simple Module To Read Your Mom");

/*
PROCESS UTILITIES
*/
void read_proc(void)
{
    struct task_struct* task_list;
    // gather the number of processes for our list
    size_t process_counter = 0;
    for_each_process(task_list) {
        //pr_info("== %s [%d]\n", task_list->comm, task_list->pid);
        ++process_counter;
    }
    pr_info("== Number of process: %zu\n", process_counter);
    // the main container to hold everything
    struct kjson_container* main_ctr = kjson_new_container();
    if (main_ctr == NULL)
    {
        pr_info("Failed to allocate main ctr \n");
    }
    // array of process containers
    struct kjson_container* kters[process_counter];
    int process_counter_old = process_counter;
    process_counter = 0;
    struct kjson_container* kprocess = NULL;
    for_each_process(task_list) {
        if (process_counter < process_counter_old)
        {
            kprocess = NULL;
            kprocess = kjson_new_container(); // init
            if (kprocess == NULL)
            {
                pr_info("Allocation failed \n");
            }
            kjson_push_string(kprocess, "name",task_list->comm);
            kjson_push_integer(kprocess, "pid", task_list->pid);
            kters[process_counter] = kprocess;
            //pr_info("== %s [%d]\n", task_list->comm, task_list->pid);
            ++process_counter;
        }
    }
    kjson_push_object(main_ctr, "result", KOBJECT_TYPE_OBJECT_ARRAY, kters, process_counter);
    pr_info("== Number of process: %zu\n", process_counter);

    struct kjstring_t* dump = kjson_dump(main_ctr);
    if (dump)
        pr_info("%s \n", kjstring_str(dump)); 

    // what should i add here ?
    // i dont think that this works : kjson_push_container_array(main_ctr, "result", kters);

    // free everything
    kjson_delete_container(main_ctr);
    kjson_delete_container(kprocess);
    kjstring_free(dump);

}


/*
SETUP NETLINK
*/
#define MY_NETLINK 30

struct sock *nl_sk = NULL;

void netlink_rcv(struct sk_buff *skb)
{
    pr_info("Zoe ❤️ %s \n", __FUNCTION__);

    // get header of receieved message
    struct nlmsghdr* nlhead;
    nlhead = nlmsg_hdr(skb);

    if (strcmp((char*)nlmsg_data(nlhead), "lap") == 0)
    {
        read_proc();
    }
    pr_info("Receieved Message %s from %d \n", (char*)nlmsg_data(nlhead),nlhead->nlmsg_pid);
    
}

int netlink_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input = netlink_rcv,
    };

    nl_sk = netlink_kernel_create(&init_net, MY_NETLINK, &cfg);
    pr_info("Entering: %s, protocol family = %d \n", __FUNCTION__, MY_NETLINK);
    if (!nl_sk)
    {
        pr_err("Failed to create socket !!!");
        return -ENOMEM;
    }
    pr_info("Netlink OK !");
    return 0;
}

void netlink_exit(void)
{
    pr_info("Bye bye netlink");
    netlink_kernel_release(nl_sk);
}


int hello_init(void)
{
    pr_info("Loaded \n");
    read_proc();
    netlink_init();
    return 0;
}

void hello_exit(void)
{
    pr_info("Goodbye World\n");
    netlink_exit();
}

module_init(hello_init);
module_exit(hello_exit);
