# minishell

## As beautiful as shell with `@aa`

![letumany's 42 minishell Score](https://badge42.vercel.app/api/v2/cl1l8hert000609l6rjl6rx6o/project/2509597)

# Introduction

This project is all about recreating our very own shell, taking bash  as reference. This was our first group project, and I was honored to do it with [@aaavvvooo](https://github.com/aaavvvooo)

#### What is the Shell?

The shell is perhaps the most important program on the Unix system, from the end-user's standpoint. The shell is your interface with the Unix system, the middleman between you and the kernel.

`CONCEPT`: The shell is a type of program called an interpreter. An interpreter operates in a simple loop: It accepts a command, interprets the command, executes the command, and then waits for another command. The shell displays a "prompt," to notify you that it is ready to accept your command.

The shell recognizes a limited set of commands, and you must give commands to the shell in a way that it understands: Each shell command consists of a command name, followed by command options (if any are desired) and command arguments (if any are desired). The command name, options, and arguments, are separated by blank space.

`CONCEPT`: The shell is a program that the Unix kernel runs for you. A program is referred to as a process while the kernel is running it. The kernel can run the same shell program (or any other program) simultaneously for many users on a Unix system, and each running copy of the program is a separate process.

Many basic shell commands are actually subroutines built in to the shell program. The commands that are not built in to the shell require the kernel to start another process to run them.

`CONCEPT`: When you execute a non built-in shell command, the shell asks the kernel to create a new subprocess (called a "child" process) to perform the command. The child process exists just long enough to execute the command. The shell waits until the child process finishes before it will accept the next command.

## Our Implementation of Minishell

The general idea for this shell is reading a string of commands in a prompt using [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html). Before anything, it is highly recommended to take a deep dive into the [bash manual](https://www.gnu.org/software/bash/manual/bash.html), as it goes over every detail we had to have in mind when doing this project. ``Minishell`` involves heavy parsing of the string read by ``readline``, thus it is crucial to divide the code of the project into different parts: the ``lexer``, the ``expander``, the ``parser``, and lastly the ``executor``

## Builtins

We were asked to implement some basic builtins with the help of some functions, here is a brief overview of them:

|  Builtin  |                            Description                            | Options | Parameters |                       Helpful Functions                       |
| :--------: | :----------------------------------------------------------------: | :-----: | :--------: | :------------------------------------------------------------: |
|  ``echo``  |   Prints arguments separated with a space followed by a new line   | ``-n`` |    ✔️    |    [write](https://man7.org/linux/man-pages/man2/write.2.html)    |
|   ``cd``   | Changes current working directory, updating ``PWD`` and ``OLDPWD`` |   ❌   |    ✔️    |    [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html)    |
|  ``pwd``  |                  Prints current working directory                  |   ❌   |     ❌     | [getcwd](https://www.man7.org/linux/man-pages/man3/getcwd.3.html) |
|  ``env``  |                         Prints environment                         |   ❌   |     ❌     |    [write](https://man7.org/linux/man-pages/man2/write.2.html)    |
| ``export`` |               Adds/replaces variable in environment               |   ❌   |    ✔️    |                               ❌                               |
| ``unset`` |                 Removes variable from environment                 |   ❌   |    ✔️    |                               ❌                               |

### Basic Usage

As per the norm, this project compiles an executable called ``minishell`` (saved inside a ``bin/`` folder), and it is compiled using the ``.c`` files inside the ``src/`` folder

``cd minishell && make me``

### Credits

`Avo Midoyan` – `lexer` `parser`

`Leo Tumanyan` – `expander` `executor`
