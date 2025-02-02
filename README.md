# minishell

## Usage

Clone repositery
```
git clone https://github.com/akdovlet/AK-GS_minishell.git
```
compile & run
```
make && ./minishell
```
compile & run with valgrind
```
make val
```
## Goals

The goal of this project is to reproduce a functional shell, inspired by bash posix for its portability, with a set of basic and limited features:

- a prompt waiting for input with a history
- command execution based on `PATH` variable , relative or absolute path
- handle single and double quotes simialr to bash
- output and input redirections with `>`, `>>`, `<` and `<<`
- inter-process communication with pipes `|`
- logical operators `&&` (AND) and `||` (OR)
- subshell feature and logical priority with the use of parenthesis `( list )`
- functional environement variables and their expansion with `$VARNAME`
- exit code expansion `$?`
- wildcard `*` expansion for the current directory
- signal management with `ctrl-C`, `ctrl-D` and `ctrl-\`
- interactive and non interactive shell
- implement builtins:
   - `echo`
   - `cd`
   - `pwd`
   - `export`
   - `unset`
   - `env`
   - `exit`
-  gracious error management

## Rules

- No memory leaks in main or child processes, including still reachables (except for readline)
- No leftover open file descriptors, every open FD should be closed when no longer in use, including in child processes
- The program is not allowed to crash, every error should print a message similar to bash and exit (if fatal) or continue graciously
- Only one global variable for the sole purpose of catching signals.
- Coding on the master branch is forbidden, every feature has its own branch and is then merged with master

## To do

- When syscall such as pipe() or fork() fails, terminate all the pipeline and return the correct exit code (128 or 126)
