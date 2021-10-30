#obj-m += proc1.o 
#obj-m += proc8.o
obj-m += my_info.o
all:
	#sudo rmmod proc3.ko
	#git fetch origin
	#git pull origin	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	#sudo insmod proc3.ko
git:
	#sudo rmmod proc3.ko
	git fetch origin
	git pull origin	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	sudo insmod proc3.ko
 

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
