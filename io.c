#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>

#include <sys/time.h>

#include <string.h>



#include "cpu/m68k.h"
#include "main.h"
#include "mem.h"
#include "io.h"

unsigned int io_read(unsigned int addr, unsigned char data_size) {
 return 0;
}

void io_write(unsigned int addr, unsigned data, unsigned char data_size ){

 switch(addr) {
  case 0xa10000: 
   printf("storage commnand\n");
   break;
  case 0xa10008:
   putchar(data);
   fflush(stdout); 
   break;
 }	 


}

