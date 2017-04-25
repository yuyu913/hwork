#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
pid_t pid;
pid = fork();//複製一個子進程

if (pid < 0) //PID不夠
{  
fprintf(stderr, "Fork Failed");
return 1;
}
else if (pid == 0) 
{ // 子進程行為
execlp("/bin/ls","ls",NULL);
}

else { //父進程行為
 sleep(60);//殭屍進程存活時間
wait(NULL);//父進程等子進程完成
printf("Child Complete");
}

return 0;
}
 
