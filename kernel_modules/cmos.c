/* https://github.com/cirosantilli/linux-kernel-module-cheat#procfs */

#include <linux/debugfs.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h> /* seq_read, seq_lseek, single_open, single_release */
#include <uapi/linux/stat.h> /* S_IRUSR */

static const char *filename = "cmos";
unsigned char  cmos[10];
char *day[] = { "", "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"  };
char *month[] = { "", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
	"JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };


static int show(struct seq_file *m, void *v)
{
	int i;
	int month_index;

	for (i = 0; i < 10; i++) {
		outb(i, 0x70);
		cmos[i] = inb(0x71);
	}

	seq_printf(m, "\t  CMOS Real-Time Clock/Calendar:");
	seq_printf(m, " %02X", cmos[4]  );	// current hour
	seq_printf(m, ":%02X", cmos[2]  );	// current minutes
	seq_printf(m, ":%02X", cmos[0]  );	// current seconds	
	seq_printf(m, " on");
	// FIXME: seems day-name not correct.
	seq_printf(m, " %s, ", day[cmos[6]]);	// day-name
	seq_printf(m, "%02X", cmos[7]);		// day-number
	month_index = ((cmos[8] & 0xF0)>>4)*10 + (cmos[8] & 0x0F);
	seq_printf(m, " %s", month[month_index]); // month-name
	seq_printf(m, " 20%02X\n", cmos[9]);	// year-number

	return 0;
}

static int open(struct inode *inode, struct  file *file)
{
	return single_open(file, show, NULL);
}

static const struct file_operations fops = {
	.llseek = seq_lseek,
	.open = open,
	.owner = THIS_MODULE,
	.read = seq_read,
	.release = single_release,
};

static int myinit(void)
{
	proc_create(filename, 0, NULL, &fops);
	return 0;
}

static void myexit(void)
{
	remove_proc_entry(filename, NULL);
}

module_init(myinit)
module_exit(myexit)
MODULE_LICENSE("GPL");
