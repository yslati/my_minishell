#!/bin/bash

ls -dl ./srcs/*/*.c | echo -n "$(awk  '{print $NF}')" > source_files
./makefile_maker
cat Makefile_test
rm -rf source_files
