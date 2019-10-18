
#define RAM_START	0x800000

typedef union {
 void           *v;
 unsigned char  *b;
 unsigned short *w;
 unsigned int   *l;
} pointer_u;

extern unsigned char ram[0x800000];
 
extern unsigned int 
 (*io_read_table[0x1000])(unsigned int addr, unsigned char data_size);
extern void
 (*io_write_table[0x1000])(unsigned int addr, unsigned int data, 
		           unsigned char data_size);
void init_io_table(void); 

unsigned int ram_reader(unsigned int addr, unsigned char data_size);

unsigned int  m68k_read_memory_8(unsigned int address);
unsigned int  m68k_read_memory_16(unsigned int address);
unsigned int  m68k_read_memory_32(unsigned int address);
void m68k_write_memory_8(unsigned int address, unsigned int value);
void m68k_write_memory_16(unsigned int address, unsigned int value);
void m68k_write_memory_32(unsigned int address, unsigned int value);

