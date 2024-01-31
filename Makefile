ifneq ($(KERNELRELEASE),)
    obj-m := hello.o
	hello-objs := ./src/hello.o ./src/add.o
else
    KERN_DIR ?= /usr/lib/modules/6.6.10-1-MANJARO/build/
    PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERN_DIR) V=1 M=$(PWD) modules
endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions .order .mod .symvers
	rm -rf src/*.o src/*~ core src/.depend src/.*.cmd src/*.ko src/*.mod.c src/.tmp_versions

clean_objs:
	rm -rf *.o *~ core .depend .*.cmd *.mod.c .tmp_versions .order .mod .symvers
	rm -rf src/*.o src/*~ core src/.depend src/.*.cmd src/*.ko src/*.mod.c src/.tmp_versions


