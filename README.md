# OS-Shell
An OS shell replicated in C using system calls.

## Getting Started

### Running the project
```make```  
```./shell```

## Description:
The OS replicates built-in commands as both background and foreground processes. Add '&' to run process as a background process.

## Commands:
* ls -a -l -al /path
* echo <text>
* pwd
* pinfo
* history

## Coded using:
* c

## Files:
* cd.c : ```cd``` command
* echo.c : ```echo``` command
* history.c : ```history``` command
* main.c : start of the program
* pinfo.c : ```pinfo``` command
* pwd.c : ```pwd``` command
* processInput.c : for manipulating input and calling functions accordingly
* readInput.c : for reading input and storing in string
* systemCommands.c : to implement system commands and manage foreground/baclground processes

## Author
Atirek Kumar  
Github handle: https://github.com/atirek-ak/
