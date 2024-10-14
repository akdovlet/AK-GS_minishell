#!/bin/bash

bash -c "echo Hello World"
./minishell -c "echo Hello World"

export BOOM=URMOM

bash -c "echo $BOOM is BOOM"
./minishell -c "echo $BOOM is BOOM"
