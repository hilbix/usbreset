/* See also http://www.roman10.net/how-to-reset-usb-device-in-linux/
 *
 * The libusb-1.0 documentation sucks, sorry!
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <libusb-1.0/libusb.h>

#define	USB_CTX	NULL

void
verror(const char *what, const char *err, va_list list)
{
  int		e=errno;

  fprintf(stderr, "error (%s): ", what);
  vfprintf(stderr, err, list);
  if (e)
    fprintf(stderr, ": %s", strerror(errno));
  fprintf(stderr, "\n");
  exit(1);
}

int
ok(int ret, const char *fn, ...)
{
  va_list	list;

  if (ret>=0)
    return ret;

  va_start(list, fn);
  verror("failed", fn, list);
  va_end(list);
  return -1;
}

#if 0
void
one_dev(struct usb_device *dev)
{
  int	c;

  printf("class=%d\n", dev->descriptor.bDeviceClass);

  for (c=-1; ++c<dev->descriptor.bNumConfigurations; )
    {
      int i;

      for (i = 0; i < dev->config[c].bNumInterfaces; i++)
        {
	  int a;
          for (a = 0; a < dev->config[c].interface[i].num_altsetting; a++)
            {
	      printf("%d:%d:%d intclass=%d\n", c,i,a, dev->config[c].interface[i].altsetting[a].bInterfaceClass);
            }
        }
    }
}
#endif

void
all_devs(void)
{
  libusb_device	**devs, **pptr, *dev;

  ok(libusb_get_device_list(USB_CTX, &devs), "device list");

  for (pptr=devs; (dev= *pptr)!=0; pptr++)
    {
      struct libusb_device_descriptor	d;
      struct libusb_device_handle	*h;
      int				bus, nr;

      bus	= libusb_get_bus_number(dev);
      nr	= libusb_get_device_address(dev);
      ok(libusb_get_device_descriptor(dev, &d), "descriptor %d:%d", bus, nr);
      printf("bus %03d dev %03d vend %04x prod %04x\n", bus, nr, d.idVendor, d.idProduct);
      ok(libusb_open(dev, &h), "open %d:%d", bus, nr);
#if 0
      ok(libusb_reset_device(h), "reset %d:%d", bus, nr);
#endif
      libusb_close(h);
    }
  libusb_free_device_list(devs, 1);
}

/* How to find out that libusb_get_version is there?
 */
#undef GET_VERSION
#ifdef GET_VERSION
static void
get_version(void)
{
  struct libusb_version *v;

  v = libusb_get_version();
  printf("libusb %d.%d.%d.%d%s %s\n"
	 , v->major
	 , v->minor
	 , v->micro
	 , v->nano
	 , v->rc
	 , v->describe
	 );
}
#endif

int
main(int argc, char **argv)
{
  ok(libusb_init(USB_CTX), "init");

#ifdef GET_VERSION
  get_version();
#endif

  all_devs();
  return 0;
}


/*
 open(filename, O_WRONLY);
 ioctl(fd, USBDEVFS_RESET, 0);
*/
