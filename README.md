# minishell

## Usage

Clone repositery

```https://github.com/akdovlet/AK-GS_minishell.git minishell```

cd into it

```cd minishell```

compile

```make```

execute

```./minishell```

## Goals

The goal of this project is to reproduce a functional shell, with a set of basic and limited features:

- a prompt waiting for input
- functional prompt history
- command execution based on `PATH` variable , relative or absolute path
- manage single and double quotes just like in bash
- functional redirections `>`, `>>`, `<` and `<<`
- functional pipes `|`
- functional logical operators `&&` (AND) and `||` (OR)
- functional environement variables and their expansion with `$VARNAME`
- exit code expansion `$?`
- wildcard `*` expansion for the current directory
- signal management with `ctrl-C`, `ctrl-D` and `ctrl-\`
- functional interactive and non interactive shell
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

Inspired by bash posix for its portability, the project should follow these rules:

- No memory leaks, including still reachables (except for readline)
- No leftover open file descriptors, every open FD should be closed when no longer in use
- The program is not allowed to crash, every error should print a message and exit or continue graciously
- Only one global variable and it can only be used to catch signals.
- Coding on the master branch is forbidden, every feature has its own branch and is then merged with master

## How to
