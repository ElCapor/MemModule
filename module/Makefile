ifneq ($(KERNELRELEASE),)
    obj-m := hello.o
	hello-objs := ./src/hello.o ./src/netlink_server.o ./src/proc_server.o ./src/kjson_main.o ./src/kjson_parser.o
else
    KERN_DIR ?= /usr/lib/modules/6.6.10-1-MANJARO/build/
    PWD := $(shell pwd)
	BIN_DIR := $(PWD)/bin

default:
	$(MAKE) -C $(KERN_DIR) V=1 M=$(PWD) modules
	@mkdir -p $(BIN_DIR)
	@mv *.ko $(BIN_DIR)/
endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions .order .mod .symvers
	rm -rf src/*.o src/*~ core src/.depend src/.*.cmd src/*.ko src/*.mod.c src/.tmp_versions

clean_objs:
	rm -rf *.o *~ core .depend .*.cmd *.mod.c .tmp_versions .order .mod .symvers
	rm -rf src/*.o src/*~ core src/.depend src/.*.cmd src/*.ko src/*.mod.c src/.tmp_versions


