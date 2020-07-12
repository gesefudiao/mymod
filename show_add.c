#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/signal.h>
#include<linux/moduleparam.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<asm/pgtable.h>

MODULE_LICENSE("GPL");
// 进程的pid
static int pid_n=-1;
module_param(pid_n,int,0644);

static int show_add_init(void){

	struct task_struct *p_task;
	struct pid *p_pid;
	struct mm_struct *p_mm;
	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t  *pte;
	struct page *p;
	unsigned long phys;
	int i, j, k, l;

	printk(KERN_ALERT "scanning running!>>>>>>>>>>>>>>>>>>>\n");

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

	printk("*name---------%s\n",p_task->comm);
	printk("*PID----------%d\n",p_task->pid);
	printk("*state--------%ld\n",p_task->state);
	printk("\n");

	p_mm = p_task->mm;
	for (i = 0; i < PTRS_PER_PGD; ++i)
	{
    		pgd_t *pgd = p_mm->pgd + i;
    		if (pgd_none(*pgd) || pgd_bad(*pgd))
        		continue;
    	for (j = 0; j < PTRS_PER_PUD; ++j)
    	{
        	pud = (pud_t *)pgd_page_vaddr(*pgd) + j;
        	if (pud_none(*pud) || pud_bad(*pud))
            		continue;
        	for (k = 0; k < PTRS_PER_PMD; ++k)
        	{
            		pmd = (pmd_t *)pud_page_vaddr(*pud) + k;
            		if (pmd_none(*pmd) || pmd_bad(*pmd))
                	continue;

            	for (l = 0; l < PTRS_PER_PTE; ++l)
            	{
                	pte = (pte_t *)pmd_page_vaddr(*pmd) + l;
                	if (!pte || pte_none(*pte))
                    		continue;
                	p = pte_page(*pte);
                	phys = page_to_phys(p);
                	printk(KERN_NOTICE "addr %lx", phys);
				
            }
        }
    }
}
	return 0;
}

static void show_add_exit(void){
	printk(KERN_ALERT "scanning exit!>>>>>>>>>>>>>>>>>>>>>\n");
}

module_init(show_add_init);
module_exit(show_add_exit);
