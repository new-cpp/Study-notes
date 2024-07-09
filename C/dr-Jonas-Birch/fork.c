#include <stdio.h>
#include <unistd.h> /* standard symbolic constants and types  */

int main()
  {


    FILE* fd = NULL;

    pid_t pid = fork(); /* fork and duplicates the process */

    /*
     *if pid == 0 => child process
     *else pid > 0  parent process
     *else pid == -1 faild fork
     */


    while(1)
      {
        fd = fopen("test.txt", "a");
        fprintf(fd,"%d\n",pid);
        fclose(fd);

        sleep(1);
      }
    return 0;
  }
