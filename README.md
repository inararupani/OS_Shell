# OS_Shell
In this assignment We create our own shell program, Mav shell (msh), similar to bourne shell (bash), c-shell (csh), or korn shell (ksh). 
It will accept commands, fork a child process and execute those commands. The shell, like csh or bash, will run and accept commands until the user exits the shell.

## Compilation and Run instruction
- Should compile on omega.uta.edu
- gcc -Wall msh.c -o msh —std=c99

## Functional Requirements
- Requirement 1: Your program will print out a prompt of msh> when it is ready to accept input
- Requirement 2: If the command is not supported your shell shall print the invalid command followed by “: Command not found.”
- Requirement 3: If the command option is an invalid option then your shell shall print the command followed by “: invalid option --” and the option that was invalid as well as a prompt to try —help. exec() outputs this automatically make sure you
pass it on to your user.
- Requirement 4: After each command completes, your program shall print the msh>
prompt and accept another line of input.
- Requirement 5: Your shell will exit with status zero if the command is “quit” or “exit”.
- Requirement 6: If the user types a blank line, your shell will, quietly and with no other
output, print another prompt and accept a new line of input.
- Requirement 7: Your version of Mav shell shall support up to 10 command line
parameters in addition to the command.
- Requirement 8: Your shell shall support and execute any command entered. Any
command in /bin, /usr/bin/, /usr/local/bin/ and the current working directory
is to be considered valid for testing.
Your shell shall search in the following PATH order:
1. Current working directory,
2. /usr/local/bin
3. /usr/bin
4. /bin
Parameters may also be combined. For example, ps may be executed as: ps –aef or ps
–a –e -f
- Requirement 9: Mav shell shall be implemented using fork(), wait() and one of the
exec family of functions. Must not use system()
- Requirement 10: Your shell shall support the cd command to change directories. Your
shell must handle cd ..
- Requirement 11: Your shell shall support the showpids command to list the PIDs of
the last 15 processes spawned by your shell. If there have been less than 15 processes
spawned then it shall print only those process PIDs.
- Requirement 12: Your shell shall support the history command which will list the last
15 commands entered by the user. Typing !n, where n is a number between 1 and 15 will
result in your shell re-running the nth command. If the nth command does not exist then
your shell will state “Command not in history.”. The output shall be a list of
numbers 1 through n and their commands, each on a separate line, single spaced.


The part of code was forked using professor skeleton file at github repository at: https://github.com/CSE3320/Shell-Assignment.
