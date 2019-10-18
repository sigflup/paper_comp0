#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char **argv) {

 init_io_table();

 m68k_set_cpu_type(M68K_CPU_TYPE_68000);

 m68k_init();



 m68k_pulse_reset();

// write_only(0x100, 0xfe, 8);

// m68k_pulse_reset();
 for(;;)
  m68k_execute(50000);

 return 0;
}
