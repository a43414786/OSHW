#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>
#include <linux/mm.h>

#define PROC_NAME "my_info"

static int show(struct seq_file *m, void *v)
{
    struct cpuinfo_x86 *c = v;
    /*cpu information*/
    seq_printf(m, "\nprocessor\t: %u\n"
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

static void *start(struct seq_file *m, loff_t *pos)
{
    /*version information*/
    seq_printf(m, "=============Version=============\n");
    seq_printf(m, "Linux version %s\n",utsname()->release);
    seq_printf(m, "\n=============CPU================");

    *pos = cpumask_next(*pos - 1, cpu_online_mask);
    if ((*pos) < nr_cpu_ids)
        return &cpu_data(*pos);
    return NULL;
}

static void *next(struct seq_file *m, void *v, loff_t *pos)
{
    (*pos)++;
    *pos = cpumask_next(*pos - 1, cpu_online_mask);
    if ((*pos) < nr_cpu_ids)
        return &cpu_data(*pos);
    return NULL;
}

static void stop(struct seq_file *m, void *v)
{
    struct sysinfo i;
    unsigned long pages[NR_LRU_LISTS];
    int lru;

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

    seq_printf(m, "Shmem\t\t: %lu kB\n", i.sharedram << (PAGE_SHIFT - 10));

    seq_printf(m, "Dirty\t\t: %lu kB\n",
               global_node_page_state(NR_FILE_DIRTY) << (PAGE_SHIFT - 10));
    seq_printf(m, "Writeback\t: %lu kB\n",
               global_node_page_state(NR_WRITEBACK) << (PAGE_SHIFT - 10));

    seq_printf(m, "KernelStack\t: %lu kB\n",
               global_zone_page_state(NR_KERNEL_STACK_KB));
    seq_printf(m, "PageTables\t: %lu kB\n",
               global_zone_page_state(NR_PAGETABLE) << (PAGE_SHIFT - 10));

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

static int __init my_init(void)

{

    struct proc_dir_entry *entry;

    entry = proc_create(PROC_NAME, 0, NULL, &my_file_ops);

    return 0;

}

static void __exit my_exit(void)

{

    remove_proc_entry(PROC_NAME, NULL);

}

module_init(my_init);

module_exit(my_exit);

MODULE_LICENSE("GPL");
