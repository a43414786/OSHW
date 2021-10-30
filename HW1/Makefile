obj-m += my_info.o
obj-m += my_info0.o
obj-m += my_info1.o
obj-m += my_info2.o
obj-m += my_info3.o
obj-m += my_info4.o

all:
	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

git:

	git fetch origin
	git pull origin	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
 
ins:
	sudo insmod my_info.ko

ins0:
	sudo insmod my_info0.ko

ins1:
	sudo insmod my_info1.ko

ins2:
	sudo insmod my_info2.ko

ins3:
	sudo insmod my_info3.ko

ins4:
	sudo insmod my_info4.ko

rm:
	sudo rmmod my_info

rm0:
	sudo rmmod my_info0

rm1:
	sudo rmmod my_info1

rm2:
	sudo rmmod my_info2

rm3:
	sudo rmmod my_info3

rm4:
	sudo rmmod my_info4

ls:
	sudo lsmod | grep my

cat:
	sudo cat /proc/my_info

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
