#define pr_fmt(fmt) "[MemModule] %s: " fmt, __func__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/sock.h>

#define MY_NETLINK = 30

struct sock *nl_sk = NULL; // pointer to our netlink reciever

// taken from xmake demo project
MODULE_LICENSE("GPL");
MODULE_AUTHOR("PompeChasseur360NoScope");
MODULE_DESCRIPTION("A Module ");
MODULE_ALIAS("Simple Module To Read Your Mom");

void myNetLink_recv_msg(struct skbuff* skb)
{
    struct nlmsghdr *nlhead;
    struct sk_buff *skb_out;
    int pid, res, msg_size;
    char *msg = "Hello msg from kernel";

    pr_info("Entering: %s\n", __FUNCTION__);

    msg_size = strlen(msg);

    nlhead = (struct nlmsghdr*)skb->data; //nlhead message comes from skb's data... (sk_buff: unsigned char *data)

    pr_info("MyNetlink has received: %s\n",(char*)nlmsg_data(nlhead));


    pid = nlhead->nlmsg_pid; // Sending process port ID, will send new message back to the 'user space sender'


    skb_out = nlmsg_new(msg_size, 0);    //nlmsg_new - Allocate a new netlink message: skb_out

    if(!skb_out)
    {
        pr_info("Failed to allocate new skb\n");
        return;
    }

    nlhead = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);   // Add a new netlink message to an skb

    NETLINK_CB(skb_out).dst_group = 0;                  


    strncpy(nlmsg_data(nlhead), msg, msg_size); //char *strncpy(char *dest, const char *src, size_t count)

    res = nlmsg_unicast(nl_sk, skb_out, pid); 

    if(res < 0)
        pr_info("Error while sending back to user\n");
}

int myNetLink_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input = myNetLink_recv_msg,
    };

       /*netlink_kernel_create() returns a pointer, should be checked with == NULL */
    nl_sk = netlink_kernel_create(&init_net, MY_NETLINK, &cfg);
    pr_info("Entering: %s, protocol family = %d \n",__FUNCTION__, MY_NETLINK);
    if(!nl_sk)
    {
        pr_info("Error creating socket.\n");
        return -10;
    }

    pr_info("MyNetLink Init OK!\n");
    return 0;
}
static void myNetLink_exit(void)
{
    pr_info("exiting myNetLink module\n");
    netlink_kernel_release(nl_sk);
}

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
    //read_proc();
    myNetLink_init();
    return 0;
}

void hello_exit(void)
{
    pr_info("Goodbye World\n");
    myNetLink_exit();
}

module_init(hello_init);
module_exit(hello_exit);
