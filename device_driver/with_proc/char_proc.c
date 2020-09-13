#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

int len,temp;
static char *dirname="driver/mydriver";
static char *dirname2="settings";
struct proc_dir_entry *parent;
struct proc_dir_entry *parent2;
char msg[100];

int read_proc(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{

	if(count>temp)
	{
	//	printk(KERN_INFO "count > temp t: %d , c: %d\n",temp,count);
		count=temp;
	}
	temp=temp-count;
	//printk(KERN_INFO "copy to user call t: %d , c: %d\n",temp,count);
	copy_to_user(buf,msg, count);
	//printk(KERN_INFO "copy to user done t: %d , c: %d\n",temp,count);
		
	if(count==0)
	{
		temp=len;
	//	printk(KERN_INFO "count=0 t: %d , c: %d\n",temp,count);
	}   
	return count;
}

int write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp ) 
{
	printk(KERN_INFO "copy from user call , c: %d\n",count);
	copy_from_user(msg,buf,count);
	msg[count]='\0';
	printk(KERN_INFO "copy from user done ,string rcv: %s , c: %d\n",msg,count);
	return count;
}


struct file_operations proc_fops = {
read: read_proc,
write: write_proc
};


int proc_init (void) {

	parent = proc_mkdir(dirname, NULL);
	parent2 = proc_mkdir(dirname2,parent);
	proc_create("hello",0666,parent2,&proc_fops);
	strcpy(msg," Hello World ");
	len=strlen(msg);
	temp=len;
	printk(KERN_INFO "1.len=%d",len);
	return 0;
}

void proc_cleanup(void) {
	remove_proc_entry("hello",parent2);
	remove_proc_entry(dirname2,parent);
    	remove_proc_entry(dirname,NULL);
}

MODULE_LICENSE("GPL"); 
module_init(proc_init);
module_exit(proc_cleanup);
