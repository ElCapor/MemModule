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


/*
SETUP NETLINK
*/
#define MY_NETLINK 30

struct sock *nl_sk = NULL;

void netlink_rcv(struct sk_buff *skb)
{
    pr_info("Hello guys %s \n", __FUNCTION__);

    // get header of receieved message
    struct nlmsghdr* nlhead;
    nlhead = nlmsg_hdr(skb);

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
