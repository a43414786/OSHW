#include <linux/module.h>
#include <linux/proc_fs.h>

#define PROC_NAME "my_info"

static const struct file_operations my_file_ops =
{
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
