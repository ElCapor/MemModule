#!/bin/bash
rmmod hello
modinfo bin/hello.ko
insmod bin/hello.ko