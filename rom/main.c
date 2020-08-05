
#include "console.h"

void main(void) {
 console_puts("\33[41m \33[0m - boot loader "
	      "\33[42m \33[0m - kernel\n");
 console_puts("\33[31mloading kernel...\33[0m\n");
}
