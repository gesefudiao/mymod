#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/signal.h>
#include<linux/moduleparam.h>
#include<linux/pid.h>
#include<linux/sched.h>

MODULE_LICENSE("GPL");

static int pid_n=-1;
module_param(pid_n,int,0644);

static int hello_init(void){
	
	struct task_struct *p_task,*p_task_f,*p_sib,*p_chi;
	struct pid *p_pid;
	int count=0;
	printk(KERN_ALERT "M2 running!>>>>>>>>>>>>>>>>>>>\n");

	// check pid_n
	if(pid_n!=-1)printk("pid_n receive successfully:%d!",pid_n);
	else {
		printk("error:pid_n receive nothing!\n");
		return -EFAULT;
	}

	p_pid=find_get_pid(pid_n);
	p_task=pid_task(p_pid,PIDTYPE_PID);
	if(p_task==NULL){
		printk("error:p_task should be noPointer!\n");
		return -EFAULT;
	}

	// print father
	printk("print father start!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	p_task_f=p_task->parent;
	if(p_task==NULL)printk("p_task_f=NULL!\n");
	else{
		printk("********************************************\n");
		printk("*                  father                  *\n");
		printk("********************************************\n");
		printk("*name---------%s\n",p_task_f->comm);
		printk("*PID----------%d\n",p_task_f->pid);
		printk("*state--------%ld\n",p_task_f->state);
		printk("\n");
	}

	// print sibling
	printk("print sibling start!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	if(&p_task->sibling==NULL)printk("no subling!\n");
	else{
		list_for_each_entry(p_sib,&p_task->sibling,sibling){
			printk("********************************************\n");
			printk("*               sibling%02d                  *\n",count++);
			printk("********************************************\n");
			printk("*name---------%s\n",p_sib->comm);
			printk("*PID----------%d\n",p_sib->pid);
			printk("*state--------%ld\n",p_sib->state);
			printk("\n");
		}
	}
	

	// print children
	printk("print children start!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	count=0;
	if(&p_task->children==NULL)printk("no children!\n");
	else{
		list_for_each_entry(p_chi,&p_task->children,children){
			printk("********************************************\n");
			printk("*              children%02d                  *\n",count++);
			printk("********************************************\n");
			printk("*name---------%s\n",p_chi->comm);
			printk("*PID----------%d\n",p_chi->pid);
			printk("*state--------%ld\n",p_chi->state);
			printk("\n");
		}
	}
	

	return 0;
}

static void hello_exit(void){
	printk(KERN_ALERT "M2 exit!>>>>>>>>>>>>>>>>>>>>>\n");
}

module_init(hello_init);
module_exit(hello_exit);
