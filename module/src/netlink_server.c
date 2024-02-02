#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#define MY_NETLINK 30

struct sock *nl_sk = NULL;

void netlink_rcv(struct sk_buff *skb)
{
    int pid, res, msg_size;
    pr_info("Hello guys %s", __FUNCTION__);

    // get header of receieved message
    nlmsghdr *nlhead;
    nlhead = (struct nlmsghdr*)skb->data;
}