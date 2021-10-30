#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/quicklist.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>
#include <linux/vmalloc.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/kernel_stat.h>

#define PROC_NAME "my_info"




static int show(struct seq_file *m, void *v)
{
    return 0;
}

static void *start(struct seq_file *m, loff_t *pos)
{
    return pos;
}


static void *next(struct seq_file *m, void *v, loff_t *pos)
{
    if(++(*pos) < 1)return pos;
    else return NULL;
}

static void stop(struct seq_file *m, void *v)
{
}

const struct seq_operations info_op =
{
    .start	= start,
    .next	= next,
    .stop	= stop,
    .show	= show,
};

static int my_open(struct inode *inode, struct file *file)

{

    return seq_open(file, &info_op);

};



static const struct file_operations my_file_ops =
{

    .open = my_open,

    .read = seq_read,

};

static int __init procfs_init(void)

{

    struct proc_dir_entry *entry;

    entry = proc_create(PROC_NAME, 0, NULL, &my_file_ops);

    return 0;

}



static void __exit procfs_exit(void)

{

    remove_proc_entry(PROC_NAME, NULL);

    pr_debug("/proc/%s removed\n", PROC_NAME);

}



module_init(procfs_init);

module_exit(procfs_exit);



MODULE_LICENSE("GPL");
