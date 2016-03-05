// g++ usb_monitor.cpp usb_monitor_standalone.cpp -o usb_monitor -lhidapi-libusb -std=gnu++11

#include "usb_monitor.h"
#include <cstdio>

int main(int argc, char**argv){
	//printf("hello\n");
	//usb_monitor_list_hid_devices();
	usb_monitor_main(argc, argv);
}

/*

/// ADD to XMega code (with ASF USB generic HID) ////

#include <string.h>
#include <stdio.h>
#include <stdarg.h>


static void vserprintf(const char* fmt, va_list argp){
	char str_buffer[128] = {0};
	vsprintf(str_buffer, fmt, argp);
	//str_buffer[0] = 'w';
	udi_hid_generic_send_report_in((uint8_t*)str_buffer);
}


static void serprintf(const char* fmt, ...){
	va_list argp;
	va_start(argp, fmt);
	vserprintf(fmt, argp);
}

*/