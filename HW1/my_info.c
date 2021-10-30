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

static int show_my_info(struct seq_file *m, void *v)
{



    struct cpuinfo_x86 *c = v;

   

   
    /*cpu information*/

   

    seq_printf(m, "processor\t: %u\n"
               "model name\t: %s\n"
               "physical id\t: %d\n"
               "core id\t\t: %d\n"
               "cpu cores\t: %d\n"
               "cache size\t: %u KB\n"
               "clflush size\t: %u\n"
               "cache_alignment\t: %d\n"
               "address sizes\t: %u bits physical, %u bits virtual\n",
               c->cpu_index,
               c->x86_model_id[0] ? c->x86_model_id : "unknown",
               c->phys_proc_id,
               c->cpu_core_id,
               c->booted_cores,
               c->x86_cache_size,
               c->x86_clflush_size,
               c->x86_cache_alignment,
               c->x86_phys_bits, c->x86_virt_bits
              );
   

    return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
static int flag = 1;
if(flag){
/*version information*/
    seq_printf(m, "=============Version=============\n");
    seq_printf(m, "Linux version %s\n",utsname()->release);
    seq_printf(m, "\n=============CPU================\n");
    flag--;
}
    *pos = cpumask_next(*pos - 1, cpu_online_mask);
	if ((*pos) < nr_cpu_ids)
		return &cpu_data(*pos);
	return NULL;
}


static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
    (*pos)++;
    return c_start(m, pos);
}

static void c_stop(struct seq_file *m, void *v)
{
    struct sysinfo i;
    unsigned long pages[NR_LRU_LISTS];
    int lru;

    struct timespec uptime;
    struct timespec idle;
    u64 nsec;
    u32 rem;
    int j;

/*mem informatiom*/

    seq_printf(m, "\n============Memory==============\n");

    si_meminfo(&i);

    for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
        pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

    seq_printf(m, "MemTotal\t: %lu kB\n", i.totalram << (PAGE_SHIFT - 10));
    seq_printf(m, "MemFree\t\t: %lu kB\n", i.freeram << (PAGE_SHIFT - 10));

    seq_printf(m, "Buffers\t\t: %lu kB\n", i.bufferram << (PAGE_SHIFT - 10));
    seq_printf(m, "Active\t\t: %lu kB\n", (pages[LRU_ACTIVE_ANON] +
                                           pages[LRU_ACTIVE_FILE]) << (PAGE_SHIFT - 10));
    seq_printf(m, "Inactive\t: %lu kB\n", (pages[LRU_INACTIVE_ANON] +
                                           pages[LRU_INACTIVE_FILE]) << (PAGE_SHIFT - 10));


    seq_printf(m, "Dirty\t\t: %lu kB\n",
               global_node_page_state(NR_FILE_DIRTY) << (PAGE_SHIFT - 10));
    seq_printf(m, "Writeback\t: %lu kB\n",
               global_node_page_state(NR_WRITEBACK) << (PAGE_SHIFT - 10));

    seq_printf(m, "Shmem\t\t: %lu kB\n", i.sharedram << (PAGE_SHIFT - 10));

    seq_printf(m, "KernelStack\t: %lu kB\n",
               global_zone_page_state(NR_KERNEL_STACK_KB));
    seq_printf(m, "PageTables\t: %lu kB\n",
               global_zone_page_state(NR_PAGETABLE) << (PAGE_SHIFT - 10));






    /*time information*/
    seq_printf(m, "\n=============Time================\n");

    nsec = 0;
    for_each_possible_cpu(j)
    nsec += (__force u64) kcpustat_cpu(j).cpustat[CPUTIME_IDLE];

    get_monotonic_boottime(&uptime);
    idle.tv_sec = div_u64_rem(nsec, NSEC_PER_SEC, &rem);
    idle.tv_nsec = rem;
    seq_printf(m, "Uptime\t\t: %lu.%02lu (s)\n"
               "Idletime\t: %lu.%02lu (s)\n",
               (unsigned long) uptime.tv_sec,
               (uptime.tv_nsec / (NSEC_PER_SEC / 100)),
               (unsigned long) idle.tv_sec,
               (idle.tv_nsec / (NSEC_PER_SEC / 100)));

}

const struct seq_operations info_op =
{
    .start	= c_start,
    .next	= c_next,
    .stop	= c_stop,
    .show	= show_my_info,
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
