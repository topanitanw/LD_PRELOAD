#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  //setenv("$LD_PRELOAD", "/441/wgross/palacios/LD_PRELOAD_our2/ld2/ourFileOp.so", 0);
  char cwd[1024];
  getcwd(cwd, 1024);
  printf("Pro || Open a file named test.txt into %s\n",cwd);

  int fd = open("test.txt", O_CREAT|O_RDWR);
  if(fd == -1)
  {
     printf("Pro || cannot open the file\n");
     exit(-1);
  }
  printf("Pro || Open the fd: %d\n", fd);
  printf("Pro || Write Hello World to the file\n");
  int byte = write(fd, (void*)"Hello World\n", 12);
  printf("Pro || Set the file offset to the begining of the file\n");
  int lsk = (int)lseek(fd, 0, SEEK_SET);
  if(lsk != 0)
    printf("Pro || cannot read from the starting file %d\n", lsk);
  else 
    printf("Pro || new file offset = %d\n", lsk);

  cwd[byte] = '\0';
  printf("Pro || Read what we wrote in the file test.txt back\n");
  byte = read(fd, cwd, byte);
  printf("Pro || Read mesg: %s\n", cwd);

  printf("Pro || close the file\n");
  close(fd);
  return 0;
}
  
