/*
 * We create a .so library to set the LD_PRELOAD.
 * In this library, we try to intercept open, read, write, lseek, and close.
 * After we intercept the calls, we print out the arguments to recheck whether
 * the value of the arguments is correct or not. Then, we call the original function. 
 *
 *
 * DeviceFile team
 */


#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
// #include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <fcntl.h>

int open(const char *path, int flags, ...)
{

/*
NAME
       open, creat - open and possibly create a file or device

SYNOPSIS
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

       int open(const char *pathname, int flags);
       int open(const char *pathname, int flags, mode_t mode);

RETURN VALUE
       open() and creat() return the new file  descriptor,  or  -1  if  an
       error occurred (in which case, errno is set appropriately).
*/
  printf("Lib || Open args: path %s flags %d\n", path, flags);
  int (*original_open)(const char*, int);
  original_open = dlsym(RTLD_NEXT, "open");
  char* err = NULL;
  if ((err = dlerror()) != NULL)
  {
     fprintf(stderr, "%s\n",err);
     return -1;
  }

  return (*original_open)(path, flags);
}

size_t read(int fd, void *buf, size_t count)
{
/*
NAME
       read - read from a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION
       read()  attempts to read up to count bytes from file descriptor fd into
       the buffer starting at buf.

       If count is zero, read() returns zero and has  no  other  results.   If
       count is greater than SSIZE_MAX, the result is unspecified.

RETURN VALUE
       On success, the number of bytes read is returned (zero indicates end of
       file), and the file position is advanced by this number.  It is not  an
       error  if  this  number  is smaller than the number of bytes requested;
       this may happen for example because fewer bytes are actually  available
       right  now  (maybe  because we were close to end-of-file, or because we
       
       Manual page read(2) line 1 (press h for help or q to quit)
*/
//  fprintf(stderr,"\nLib || Read fd buf count: %x, %p, %zd\n", fd, buf, count);
   
   ssize_t (*ourOriginal_read)(int, void*, size_t);
   ourOriginal_read = dlsym(RTLD_NEXT, "read");
   char* err = NULL;
   if ((err = dlerror()) != NULL)
   {
      fprintf(stderr, "%s\n",err);
      return -1;
   }


   return (*ourOriginal_read)(fd, buf, count);

}

ssize_t write(int fd, const void *buf, size_t count)
{
/*
NAME
       write - write to a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);

DESCRIPTION
       write()  writes  up  to  count bytes from the buffer pointed buf to the
       file referred to by the file descriptor fd.

       The number of bytes written may be less than  count  if,  for  example,
       there  is  insufficient space on the underlying physical medium, or the
       RLIMIT_FSIZE resource limit is encountered (see setrlimit(2)),  or  the
       call was interrupted by a signal handler after having written less than
       count bytes.  (See also pipe(7).)
*/
   fprintf(stderr,"Lib || Write fd buf count: %x, %p, %zd\n", fd, buf, count);
   fprintf(stderr,"Lib || buf mesg: %s\n", (char*)buf);
   ssize_t (*ourOriginal_write)(int, const void*, size_t);
   ourOriginal_write = dlsym(RTLD_NEXT, "write");
   char* err = NULL;
   if ((err = dlerror()) != NULL)
   {
      fprintf(stderr, "%s\n",err);
      return -1;
   }

   return (*ourOriginal_write)(fd, buf, count);

}

off_t lseek(int fd, off_t offset, int whence) 
{

/*
   #include <unistd.h>
   off_t lseek(int fd, off_t offset, int whence);
   Returns new file offset if successful, or –1 on error
 */
  fprintf(stderr,"Lib || lseek fd offset whence: %d %d %d\n", fd, (int) offset, whence);
  off_t (*ourOriginal_lseek)(int, off_t, int);
  ourOriginal_lseek = dlsym(RTLD_NEXT, "lseek");
  char* err = NULL;
  if ((err = dlerror()) != NULL)
  {
    fprintf(stderr, "%s\n",err);
    return -1;
  }
  return (*ourOriginal_lseek)(fd, offset, whence);
}

int close(int fd) 
{
/*
NAME
       close - close a file descriptor

SYNOPSIS
       #include <unistd.h>


int close(int fd);

DESCRIPTION
  close()  closes  a  file descriptor, so that it no longer refers to
  any file and may be reused.  Any record locks (see  fcntl(2))  held
  on  the  file it was associated with, and owned by the process, are
  removed (regardless of the file descriptor that was used to  obtain
  the lock).

  If  fd is the last file descriptor referring to the underlying open
  file description (see open(2)), the resources associated  with  the
  open  file  description  are  freed; if the descriptor was the last
  reference to a file which has been removed using unlink(2) the file
  is deleted.

RETURN VALUE
  close()  returns  zero  on  success.  On error, -1 is returned, and
  errno is set appropriately.
*/
 
   fprintf(stderr,"Lib || Close fd %d\n", fd);
   ssize_t (*ourOriginal_close)(int);
   ourOriginal_close = dlsym(RTLD_NEXT, "close");
   char* err = NULL;
   if ((err = dlerror()) != NULL)
   {
      fprintf(stderr, "%s\n", err);
      return -1;
   }

   return (*ourOriginal_close)(fd);

}
