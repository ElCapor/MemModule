#!/bin/bash
# um will load & remove manually
make
make clean_objs
modinfo ../bin/hello.ko