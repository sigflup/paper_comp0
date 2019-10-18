#include <stdio.h>
#include <stdlib.h>

#include "cpu/m68k.h"
#include "main.h"
#include "mem.h"
#include "rom/rom.h"

unsigned char ram[0x800000];

unsigned int 
 (*io_read_table[0x1000])(unsigned int addr, unsigned char data_size);
void 
 (*io_write_table[0x1000])(unsigned int addr, unsigned int data, 
		           unsigned char data_size);


void write_only(unsigned int addr, unsigned int data, unsigned char data_size) {
 printf("fuck %x\n", addr);
 printf("EE write attempted at %x\n", addr);
}

unsigned int rom_reader(unsigned int addr, unsigned char data_size) {
 union {
  void           *v;
  unsigned char  *b;
  unsigned short *w;
  unsigned int   *l;
 } ptr_u;

 ptr_u.v = (void *)&rom_loader[addr];

 switch(data_size) {
  case 8: return *ptr_u.b;
  case 16:return swap_16(*ptr_u.w);
  case 32:return swap_32(*ptr_u.l);
 }
 return 0;
}

unsigned int ram_reader(unsigned int addr, unsigned char data_size) {
 union {
  void           *v;
  unsigned char  *b;
  unsigned short *w;
  unsigned int   *l;
 } ptr_u;

 ptr_u.v = (void *)&ram[addr - RAM_START];

 switch(data_size) {
  case 8: 
   return *ptr_u.b;
  case 16:
   return swap_16(*ptr_u.w);
  case 32:
   return swap_32(*ptr_u.l);
 }
 return 0;

}


void ram_writer(unsigned int addr, unsigned int data, unsigned char data_size) {
 union {
  void           *v;
  unsigned char  *b;
  unsigned short *w;
  unsigned int   *l;
 } ptr_u;

 ptr_u.v = (void *)&ram[addr - RAM_START];


 switch(data_size) {
  case 8: 
   *ptr_u.b = data;
   break;
  case 16:
   *ptr_u.w = swap_16(data);

   break;
  case 32:
   *ptr_u.l = swap_32(data);
   break;
 }

}
unsigned int null_read(unsigned int addr, unsigned char data_size) {return 0;}
void null_write(unsigned int addr, 
		unsigned int data,
		unsigned char data_size) {return;}



void init_io_table(void) {
 int s, i;


 /* clear the table so there are no seg-faulting holes */
 for(i = 0; i<0x1000; i++) {
  io_read_table[i] = null_read;
  io_write_table[i] =null_write;
 }

// for(i=(RAM_START/0x1000);i< (0xffffff / 0x1000);i++) {
 for(i=(RAM_START/0x1000);i<  0x1000;i++) {
 
  io_read_table[i] = ram_reader;
  io_write_table[i] =ram_writer;
 }

 s = rom_loader_len / 0x1000;
 if((rom_loader_len % 0x1000)!=0)
  s++;

 if(s == 0) {
  printf("no rom\n");
  exit(0);
 }
 for(i = 0; i<s; i++) {
  io_read_table[i] = rom_reader;
  io_write_table[i] =write_only;
 }
 printf("\33[37;45m%d rom io table %s\33[0m\n", s, s == 1 ? "entry" : "entries");


}

unsigned int  m68k_read_memory_8(unsigned int address) {
#ifdef TRACE
 printf("read 8 %x\n", address);
#endif
 return io_read_table[address / 0x1000](address, 8);
}

unsigned int  m68k_read_memory_16(unsigned int address) {
#ifdef TRACE
 printf("read 16 %x\n", address);
#endif
 return io_read_table[address / 0x1000](address, 16);
}
unsigned int  m68k_read_memory_32(unsigned int address) {
#ifdef TRACE
 printf("read 32 %x\n", address);
// printf("::%X::\n", io_read_table[address/0x1000](address, 32));
#endif 
 return io_read_table[address / 0x1000](address, 32);
}

void m68k_write_memory_8(unsigned int address, unsigned int value) {
 if(address == 0x410000) { putchar(value); fflush(stdout); }
#ifdef TRACE
 printf("write 8 %x %x\n", address,value);
#endif 

 io_write_table[address / 0x1000](address, value, 8);
}
void m68k_write_memory_16(unsigned int address, unsigned int value) {
#ifdef TRACE
 printf("write 16 %x %x\n", address,value);
#endif 

 io_write_table[address / 0x1000](address, value, 16);
}
void m68k_write_memory_32(unsigned int address, unsigned int value) {


#ifdef TRACE
 printf("write 32 %x %x\n", address,value);
#endif 

 io_write_table[address / 0x1000](address, value, 32);
}


