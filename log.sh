#!/bin/bash
journalctl --since "1 hour ago" | grep -w "\[MemModule\]"