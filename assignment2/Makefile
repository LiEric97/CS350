obj-m := mytime_module.o

all: modules user_mytime_module user_my_xtime

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

user_mytime_module: user_mytime_module.c
	gcc -g user_mytime_module.c -o user_mytime_module

user_my_xtime: user_my_xtime.c
	gcc -g user_my_xtime.c -o user_my_xtime

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f user_mytime_module
	rm -f user_my_xtime
