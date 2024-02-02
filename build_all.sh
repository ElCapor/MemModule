#!/bin/bash
cd module
./build.sh
mv bin/hello.ko ../bin/hello.ko
cd ../um
make
mv netlink_client ../bin/netlink_client