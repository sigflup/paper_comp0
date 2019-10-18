#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define HOST_LITTLE_ENDIAN

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


int main(void) {
 int i;
 unsigned char dat;
 FILE *text, *data;
 struct stat text_stat, data_stat;
 unsigned char *text_buf;

 if((text = fopen("rom.text_rodata", "rb"))<0) {
  perror("rom.text_rodata");
  return 0;
 }
 fstat(fileno(text), &text_stat);

 if((data = fopen("rom.data", "rb"))<0) {
  perror("rom.data");
  return 0;
 }
 fstat(fileno(data), &data_stat);


 text_buf = (unsigned char *)malloc(text_stat.st_size);
 fread(text_buf , 1, text_stat.st_size, text);

 *(unsigned int *)&text_buf[ 0x100] = swap_32(text_stat.st_size);
 *(unsigned int *)&text_buf[ 0x104] = swap_32(data_stat.st_size);

 fclose(text);

 for(i=0;i<text_stat.st_size;i++)
  putchar(text_buf[i]);

 free(text_buf);

 for(i=0;i<data_stat.st_size;i++) {
  fread(&dat, 1,1, data);
  putchar(dat);
 } 

 fclose(data);
 return 0;
}
