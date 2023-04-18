#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


#define READ 0
#define WRITE 1

int primenum(int n)
{
	 if(n<2){
		return 0;
		}
	for(int i=2;i*i<=n;i++)
{
	if(n%i==0){
	return 0;
	}
}
return 1;
}

void sigint_handler(int sig)
{
printf("\nyou enter ctrl+c bye2\n");
}

int main(void)
{
int fd[2];
pipe (fd);
pid_t pid;
int num,res;

void sigint_handler(int sig);


if(signal(SIGINT,sigint_handler)==SIG_ERR)
{
perror("signal");
exit(1);
}

if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

if(pid==0)
{
//child process
close(fd[READ]);
printf("Enter a number: ");
scanf("%d",&num);
res = primenum(num);
write(fd[WRITE], &res, sizeof(res));
close(fd[WRITE]);
exit(0);
}

else{
//parent process
close(fd[WRITE]);
read(fd[READ],&res, sizeof(res));

if (res){
	printf("THE NUMBER IS A PRIME NUMBER :)\n");
	
}
else{
	printf("THE NUMBER IS NOT A PRIME NUMBER SORRY :(\n");
	
}
close(fd[READ]);
pause();

}

return 0;
}
