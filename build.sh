#!/bin/bash
rmmod hello
make
make clean_objs
modinfo hello.ko
insmod hello.ko