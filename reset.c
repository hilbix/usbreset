#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>

int
ok(int fd, const char *s)
{
  if (fd>=0)
    return fd;

  perror(s);
  exit(1);
}

int
main(int argc, char **argv)
{
  int	fd;
  
  fd	= ok(open(argv[1], O_WRONLY), "open");
  ok(ioctl(fd, USBDEVFS_RESET, 0), "ioctl");
  ok(close(fd), "close");
  return 0;
}

