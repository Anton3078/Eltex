obj-m += module1.o

all:
	make -C /lib/modules/6.1.0-28-amd64/build M=$(PWD) modules

clean:
	make -C /lib/modules/6.1.0-28-amd64/build M=$(PWD) clean

