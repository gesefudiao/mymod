#include<linux/errno.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/signal.h>
#include<linux/moduleparam.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<asm/pgtable.h>
#include<linux/fs.h>
#include<linux/buffer_head.h>
#include<linux/rmap.h>
#include<asm/segment.h>
#include<asm/uaccess.h>
#include<asm/tlbflush.h>




#define PROC_LOG_FILE "/home/gesefudiao/add.txt"
#define PROC_IN_FILE "/home/gesefudiao/in.txt"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("scan");

struct file *logfile = NULL;
struct file *infile = NULL;


char buf[2048];

// struct proc_stat
// {
//     unsigned long scanned_pages;
//     unsigned long active_file_pages;
//     unsigned long active_ano_pages;
//     unsigned long inactive_file_pages;
//     unsigned long inactive_ano_pages;
// };

// 进程的pid
static int pid_n=-1;
// module_param(pid_n,int,0644);

// 打开文件
static struct file *file_open(const char *path, int flags, int rights)
{
    int err = 0;
    struct file *filp = NULL;
    mm_segment_t oldfs;

    oldfs = get_fs();
    set_fs(get_ds());
    filp = filp_open(path, flags, rights);
    set_fs(oldfs);
    if (IS_ERR(filp)) {
        err = PTR_ERR(filp);
        return NULL;
    }
    return filp;
}

//  关闭文件
static void file_close(struct file *file) 
{
    filp_close(file, NULL);
}

// 从文件中读取数据
static int file_read(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size) 
{
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_read(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
} 

// 将数据写入文件
static int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size) 
{
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());
    printk("in file_write");

    ret = vfs_write(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}

// 同步文件
static void file_sync(struct file *file) 
{
    vfs_fsync(file, 0);
}


// static void scan_add_tsk(struct task_struct *task, struct file *file, unsigned long long offset, unsigned char *buf)
// {
// 	struct mm_struct *p_mm;
//   //pgd_t *pgd;
// 	pmd_t *pmd;
// 	pud_t *pud;
// 	pte_t  *pte;
//     p_mm = task->mm;
//     struct page *p;
// 	unsigned long phys;
// 	int i, j, k, l,m = 0 ;
//     int count = 25;
// 	for (i = 0; i < PTRS_PER_PGD; ++i)
// 	{
//         printk("c\n");
//     	pgd_t *pgd = p_mm->pgd + i;
//     	if (pgd_none(*pgd) || pgd_bad(*pgd))
//         	continue;
//     	for (j = 0; j < PTRS_PER_PUD; ++j)
//     	{
//         	pud = (pud_t *)pgd_page_vaddr(*pgd) + j;
//         	if (pud_none(*pud) || pud_bad(*pud))
//             	continue;
//         	for (k = 0; k < PTRS_PER_PMD; ++k)
//         	{
//             	pmd = (pmd_t *)pud_page_vaddr(*pud) + k;
//             	if (pmd_none(*pmd) || pmd_bad(*pmd))
//                 	continue;

//             	for (l = 0; l < PTRS_PER_PTE; ++l)
//             	{
//                 	pte = (pte_t *)pmd_page_vaddr(*pmd) + l;
//                 	if (!pte || pte_none(*pte))
//                     	continue;
//                 	p = pte_page(*pte);
//                 	phys = page_to_phys(p);
//                     printk("addr %lx", phys);
//                     while(m < count)
//                     {
//                         sprintf(buf+strlen(buf),"addr %lx\n",phys);
//                         m++;
//                         continue;
//                     }
                    
//                     if(file!=NULL)
//                     {
//                         printk("d\n");
//                 	    file_write(file, offset, (char *)buf, strlen(buf));
//                         memset(buf,0,2048);
//                         m = 0;
//                     }
//                 }
//             }
//         }
//     }
// }

// static void count_page_tsk(struct task_struct *task, struct file *file, unsigned long long offset, unsigned char *buf)
// {
//     struct proc_stat page_stat=
//     {
//         .scanned_pages=0,
//         .active_file_pages=0,
//         .active_ano_pages=0,
//         .inactive_file_pages=0,
//         .inactive_ano_pages=0,
//     };
//     unsigned long vm_flags;
// 	struct mm_struct *p_mm;
//   //pgd_t *pgd;
// 	pmd_t *pmd;
// 	pud_t *pud;
// 	pte_t  *pte;
//     p_mm = task->mm;
//     struct page *p;
// 	unsigned long phys;
// 	int i, j, k, l,m = 0 ;
//     int count = 25;
// 	for (i = 0; i < PTRS_PER_PGD; ++i)
// 	{
//         printk("c\n");
//     	pgd_t *pgd = p_mm->pgd + i;
//     	if (pgd_none(*pgd) || pgd_bad(*pgd))
//         	continue;
//     	for (j = 0; j < PTRS_PER_PUD; ++j)
//     	{
//         	pud = (pud_t *)pgd_page_vaddr(*pgd) + j;
//         	if (pud_none(*pud) || pud_bad(*pud))
//             	continue;
//         	for (k = 0; k < PTRS_PER_PMD; ++k)
//         	{
//             	pmd = (pmd_t *)pud_page_vaddr(*pud) + k;
//             	if (pmd_none(*pmd) || pmd_bad(*pmd))
//                 	continue;

//             	for (l = 0; l < PTRS_PER_PTE; ++l)
//             	{
//                 	pte = (pte_t *)pmd_page_vaddr(*pmd) + l;
//                 	if (!pte || pte_none(*pte))
//                     	continue;
//                 	p = pte_page(*pte);
//                     if(IS_ERR_OR_NULL(p))
//                         continue;
//                     else
//                     {
//                         if(PageAnon(p))
//                         {
//                             page_stat.scanned_pages++;
//                             if (p && p->mem_cgroup && page_referenced(p, 0, p->mem_cgroup, &vm_flags))
// 								page_stat.active_ano_pages++;
//                             else
//                                 page_stat.inactive_ano_pages++;
//                         }
//                         else
//                         {
//                             page_stat.scanned_pages++;
//                             if (p && p->mem_cgroup && page_referenced(p, 0, p->mem_cgroup, &vm_flags))
// 								page_stat.active_file_pages++;
//                             else
//                                 page_stat.inactive_file_pages++;                           
//                         }
//                     }
//                 }
//             }
//         }      
//     }
//     sprintf(buf+strlen(buf),"%25s %25s %25s %25s\n","active_file_count","active_ano_count","inactive_file_count","inactive_ano_count"); 
//     sprintf(buf+strlen(buf),"%25ld %25ld %25ld %25ld\n",page_stat.active_file_pages,page_stat.active_ano_pages,page_stat.inactive_file_pages,page_stat.inactive_ano_pages);       
//     if(file!=NULL)
//     {
//         file_write(file, offset, (char *)buf, strlen(buf));
//     }
// }



static int show_add_init(void){

	struct task_struct *p_task;
	struct pid *p_pid;
    unsigned long long f_offset=0;
    unsigned long long f_inoffset=0;
    char inbuf[512];

 //   logfile = file_open(PROC_LOG_FILE, O_RDWR | O_APPEND | O_CREAT, 0644);
    infile = file_open(PROC_IN_FILE, O_RDWR, 0644);
//    printk("%p",logfile);
    printk("%p",infile);
//    memset(buf, 0, 2048);
    // sprintf(buf, "%s","scanning running!>>>>>>>>>>>>>>>>>>>\n");
    file_read(infile, f_inoffset, (char *)inbuf, 512);
    kstrtouint(inbuf,10,&pid_n);
	printk(KERN_ALERT "scanning running!>>>>>>>>>>>>>>>>>>>\n");
    printk("%d,buf len:%ld!\n",pid_n,strlen(buf));
	//  check pid_n
	if(pid_n!=-1)
        printk("pid_n receive successfully:%d!",pid_n);
        // sprintf(buf+strlen(buf), "pid_n receive successfully:%d!",pid_n);
                  
	else {
		printk("error:pid_n receive nothing!\n");
        // sprintf(buf+strlen(buf), "%s","pid_n receive successfully:%d!\n");   
		return -EFAULT;
	}

    file_close(infile);
	// return 0;
}

static void show_add_exit(void){
	printk(KERN_ALERT "scanning exit!>>>>>>>>>>>>>>>>>>>>>\n");
}

module_init(show_add_init);
module_exit(show_add_exit);
