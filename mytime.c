#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>


#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>

MODULE_LICENSE("GPL");

static int show_all_process_init(void)
{
 	struct task_struct *p;
	p=NULL;

	struct timex txc;
	struct rtc_time tm;
	do_gettimeofday(&(txc.time));
	rtc_time_to_tm(txc.time.tv_sec,&tm);
	printk(KERN_ALERT"UTC time :%d-%d-%d %d:%d:%d /n",tm.tm_year+1900,tm.tm_mon, tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
	printk(KERN_ALERT"show_all_process_init() begin");
	// for_each_process(p){
	//         if(p->mm==NULL)
    //     	{
    // 			printk(KERN_ALERT"%20s %5d %5ld %5d %5d\n",p->comm,p->pid, p->state,p->prio,p->parent->pid);
    //     	}	
    // 	}
	// printk(KERN_ALERT"\n");
	// return 0;
}

static void show_all_process_exit(void)
{
	printk(KERN_ALERT" show_all_process_init() has exited\n");
}

module_init(show_all_process_init);
module_exit(show_all_process_exit);

MODULE_AUTHOR("WFJ");
MODULE_DESCRIPTION("This is a simple example!/n");
MODULE_ALIAS("A simple example");

