/*
 * Programming Assignment 1 - Intro to Processes
 * Rene Molina
 * EE 4374 - Operating Systems
 */
 
// Create 2 Processes:
// "uname -a"
// "echo Hello there"
 
// Wait for both to terminate
 
// Create 1 Process:
// "ls -l"

// Print "Goodbye!"
// Exit w/o waiting for last process to complete
 
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>		// UNIX System Call Library
#include <stdio.h>		// Standard I/O Library
#include <sys/wait.h>	// Provides wait() Function
#include <signal.h>		// Signal Handler Library

int main()
{
    pid_t pid1, pid2, pid3;

    pid1 = fork();

	// Error forking process
    if(pid1 < 0) {
        fprintf(stderr,"Process Forking Error\n");
        return -1;
    }
	
	// This is child process 1 (uname)
	else if (pid1 == 0)
		execlp("uname", "uname", "-a", NULL);
	
	// This is parent process - create 2nd child process
	else {
		pid2 = fork();
		
		// Error forking process
		if(pid2 < 0) {
			fprintf(stderr,"Process Forking Error\n");
			return -1;
		}
		
		// This is child process 2 (echo)
		else if (pid2 == 0)
			execlp("echo", "echo", "Hello there", NULL);
		
		// This is parent process - waith for children to terminate
		else {
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	
	pid3 = fork();
	
	// Error forking process
	if (pid3 < 0) {
		fprintf(stderr, "Process Forking Error\n");
		return -1;
	}
	
	// This is child process 3 (ls)
	else if (pid3 == 0)
		execlp("ls", "ls", "-l", NULL);
	
	// Exit parent process without waiting for child to terminate
	printf("Goodbye!\n");
    return 0;
}
