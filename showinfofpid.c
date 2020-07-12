#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static pid_t pid=1;
module_param(pid,int,0644);


static int show_all_process_init(void)
{
 	struct task_struct *p;
	struct list_head *pp;
	struct task_struct *psibling;
	
	// 当前进程的PID
	p = pid_task(find_vpid(pid), PIDTYPE_PID);
	printk("me: %d %s\n", p->pid, p->comm);
	
	// 父进程
	if(p->parent == NULL ){
		printk("No Parent\n");
	else{
		printk("Parent:%d %s\n", p->parent->pid, p->parent->comm);

	    }

	}
	// 兄弟进程
        list_for_each(pp, &p->parent->children)
        {
        	psibling = list_entry(pp, struct task_struct, sibling);
        	printk("sibling %d %s \n", psibling->pid, psibling->comm);
        }

    	// 子进程
    	list_for_each(pp, &p->children)
    	{
        	psibling = list_entry(pp, struct task_struct, sibling);
        	printk("children %d %s \n", psibling->pid, psibling->comm);
    	}

    	return 0;
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

