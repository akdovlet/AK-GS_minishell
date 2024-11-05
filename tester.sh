#!/bin/bash

bash -c "echo Hello World"
./minishell -c "echo Hello World"

export BOOM=URMOM

bash -c "echo $BOOM is BOOM"
./minishell -c "echo $BOOM is BOOM"

>out1 <Makefile cat >out2 <segfault_test.c >>out3 <<EOF <shell_script.sh <tester.sh >out5 >out6 >out7 <Makefile <<EOF2 && ls <<EOF3
<<EOF cat && <<EOF2 cat && <<EOF3 cat || <<EOF4 cat
