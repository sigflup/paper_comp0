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

unsigned short swap_16(unsigned short in) {
#ifndef HOST_LITTLE_ENDIAN
 return in;
#else
 return (in>>8) | (in<<8);
#endif
}
unsigned int   swap_32(unsigned int in) {
#ifndef HOST_LITTLE_ENDIAN
 return in;
#else
 return ((in>>24)&0xff) | 
	((in<<8)&0xff0000) |
	((in>>8)&0xff00)  |
	((in<<24)&0xff000000);
	
#endif

}

int int_handler(int a) {
 printf("sdfsdf\n");
 m68k_set_irq(0);
 return 0;
}

int main(int argc, char **argv) {
 struct termios ios;
 tcflag_t old_lflag;
 cc_t old_cc; 
 char data;
 int done;

 tcgetattr(fileno(stdin), &ios);
 old_lflag = ios.c_lflag;
 memcpy(&old_cc, &ios.c_cc, sizeof(cc_t));
 ios.c_lflag &= ~ICANON;
 ios.c_lflag &= ~ECHO;
 ios.c_cc[VMIN]=0;
 tcsetattr(fileno(stdin), TCSANOW, &ios);

 init_io_table();

 m68k_set_cpu_type(M68K_CPU_TYPE_68000);

 m68k_init();



 m68k_pulse_reset();

 puts("press ESC to quit");

 done =0;
 for(;;) {
  if(done == 1) break;
  m68k_execute(500);
  while(read(fileno(stdin), &data, 1) !=0) {
   if(data=='\33') 
    done = 1;
   else {
    printf("key\n");
    m68k_set_irq(25);
   }
  }
 }

 ios.c_lflag = old_lflag;
 memcpy(&ios.c_cc, &old_cc, sizeof(cc_t));
 tcsetattr(fileno(stdin), TCSANOW, &ios);
}
