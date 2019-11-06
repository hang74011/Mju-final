#include <stdio.h>                                                                                                              
#include <stdlib.h>
#include <string.h>                                                          
#include <unistd.h>                                                        
#include <sys/types.h>
#include <sys/wait.h>                                                       //사용할 함수들이 정의되어있는 헤더파일들      

int main( int arg , char *argv[])
{

    pid_t pid1,pid2,pid3,pid4,pid5;
int status,stat;
     pid1 =fork();

if(pid1>0)
{
           stat = waitpid(pid1,&status,0);
           usleep(100);
           pid2=fork();
      
}

else if(pid1 ==0)
{
      usleep(100); 
    execlp("sudo","sudo","wpa_cli","add_network",(char *)0);
}

else 
printf("fork fail\n");

if(pid2>0)
{
           stat = waitpid(pid1,&status,0);
           usleep(100);
           pid3=fork();
      
}

else if(pid2 ==0)
{
      usleep(100); 
    execlp("sudo","sudo","wpa_cli","set_network","1","ssid","\'\"Embedded\"\'",(char *)0);
}

else 
printf("fork fail\n");



if(pid3>0)
{
           stat = waitpid(pid1,&status,0);
           usleep(100);
           pid4=fork();
      
}

else if(pid3 ==0)
{
      usleep(100); 
    execlp("sudo","sudo","wpa_cli","set_network","1","key_mgmt","NONE",(char *)0);
}

else 
printf("fork fail\n");


if(pid4>0)
{
           stat = waitpid(pid1,&status,0);
           usleep(100);
           pid5=fork();
      
}

else if(pid4 ==0)
{
      usleep(100); 
    execlp("sudo","sudo","wpa_cli","select_network","1",(char *)0);
}

else 
printf("fork fail\n");



if(pid5>0)
{
           stat = waitpid(pid1,&status,0);
           usleep(100);
        
      
}

else if(pid5==0)
{
      usleep(100); 
    execlp("sudo","sudo","dhclient","wlan0",(char *)0);
}

else 
printf("fork fail\n");


}
