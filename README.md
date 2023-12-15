Daniel Edward Mwihoti simple shell project

Simple shell 0.1

-UNIX command line interpreter

Handle command lines with arguments

Handle the PATH
fork must not be called if the command doesn’t exist

shell was built and tested on Ubuntu 14.04 LTS.

built-in commands:

Command	Definition
exit [n]	Exit the shell, with an optional exit status, n.
env	Print the environment.
setenv [var][value]	Set an environment variable and value. If the variable exists, the value will be updated.
alias[name[='value]]	Reads aliases name
unsetenv [var]	Remove an environment variable.
cd [dir]	Change the directory.
help [built-in]	Read documentation for a built-in.
