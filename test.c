#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int		main()
{
	pid_t	pid;
	int		fd;
	int		st = 0;
	char	*args[] = { "ls", "-l", "-a", (char *)0 };
    char	*env_args[] = { "PATH=/bin", (char*)0 };

	pid = fork();
	if (pid == 0)
	{
		fd = open("txt", O_WRONLY);
		dup2(fd, 1);
		execve(args[0], args, env_args);
	}
	else if (pid < 0)
		printf("Error fork\n");
	waitpid(pid, &st, 0);
}

void executePipeCommands(char **commands[], int n, int op1, int op2, char *redirectfile)
{
int fin, fout;
fin = dup(0)
// ...
// Iterate over all commands
for(i=0; i<n; i++)
{
	dup2(fin, 0);
	close(fin);
if(i == n-1)
{
	// If it's the last command, 
	// check where the o/p is to be redirected
	if(op1 != 0)
		fout = open(redirectfile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	else if(op2 != 0)
		fout = open(redirectfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

	else
	{
		// No redirectio. So, use OUTPUT.txt
		fout = open("OUTPUT.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP |S_IWUSR); 
	}
}
else 
{
    // Use pipe for everything in between. 
    int pipefd[2];
    pipe(pipefd);
    fin = pipefd[0];
    fout = pipefd[1];
}
dup2(fout, 1);
close(fout);
if((pid = fork()) < 0) 
	perror("Fork error");
else if(pid == 0)
{
	// child
	execvp(commands[i][0], commands[i]);
	printf("Couldn't execute this command\n");
}
else
{
	// parent
	do
	{
		wpid = waitpid(pid, &status, 0);
	}
	while(!WIFEXITED(status) && !WIFSIGNALED(status));
}