For example for device 2-3.1.1:

```bash
$ cat /sys/bus/usb/devices/2-3.1.1/devnum
12
$ sudo ./reset /dev/bus/usb/002/012
```

Alternatives:

```bash
echo 2-3.1.1 > /sys/bus/usb/drivers/usb/unbind
echo 2-3.1.1 > /sys/bus/usb/drivers/usb/bind
```

`./usbreset` does a complete reset of all USB bus devices if enabled (in source, the `#if 0` must be changed to `#if 1`).

However up to now I have not tested if this all does something reasonable.
