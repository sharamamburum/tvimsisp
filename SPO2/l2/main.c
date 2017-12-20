#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;
    int i = 0;
    pid = fork();// fork a new child process

    if (pid < 0){
        printf("fork failed!\n");
	exit(1);
    }

    if (pid > 0){
	printf("pid of child process %d \n", pid);
	exit(0);
    }

    umask(0);//unmasking the file mode

    sid = setsid();//set new session
    if(sid < 0)
    {
        exit(1);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    fp = fopen ("mydaemonfile.txt", "w+");
    while (i < 3)
    {
	fprintf(fp, "%d\n", 18 * i);
        sleep(18);
	fprintf(fp, "fedorov\n");
	i++;
    }
    fclose(fp);
    system("ping google.com -c1 | grep % | tee -a mydaemonfile.txt");
    return (0);
}
