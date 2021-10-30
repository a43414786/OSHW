#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "my_info"

static const struct file_operations my_file_ops =
{
    .read = seq_read,
};

static int __init init(void)

{

    struct proc_dir_entry *entry;

    entry = proc_create(PROC_NAME, 0, NULL, &my_file_ops);

    return 0;

}



static void __exit exit(void)

{

    remove_proc_entry(PROC_NAME, NULL);

}



module_init(init);

module_exit(exit);



MODULE_LICENSE("GPL");
