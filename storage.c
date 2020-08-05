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
#include "storage.h"

unsigned int storage_read(unsigned int addr, unsigned char data_size) {
 return 0;
}

void storage_write(unsigned int addr, unsigned data, unsigned char data_size ){
 if(addr == 0xa10000) printf("storage command\n"); 

}

