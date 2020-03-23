#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fdtable.h>
#include <linux/init_task.h>
#include <uapi/linux/sched.h>

static int __int print_pid(void)
{
    struct task_struct *task, *p;
    struct list_head *pos;
    int count = 0;
    printk(KERN_INFO"printf process'message begin:\n");
    task = &init_task;

    //遍历进程链表
    list_for_each(pos, &task->tasks)
    {
        p = list_entry(pos, struct task_struct, tasks);
        ++count;
        printk("\n\n");
        printk(KERN_INFO"pid:%d; state:%lx; prio:%d; static_prio:%d; parent'pid:%d;", p->pid, p->state, p->prio, p->static_prio, (p->parent)->pid);
    }

    printk(KERN_INFO"进程的个数: %d\n", count);
    return 0;
}

static void __exit pid_exit(void)
{
    printk(KERN_INFO"exiting...\n");
}

module_init(print_pid);
module_exit(pid_exit);
MODULE_LICENSE("GPL");
