
volatile unsigned char *out_addr = (unsigned char *)0x410000;

void console_putchar(unsigned char in) {
 *out_addr = (unsigned char)in; 
}

void console_puts(unsigned char *in) {
 int i;

 for(i=0;;i++) {
  if(in[i] == 0) { console_putchar('\n'); break; }
  console_putchar(in[i]);
 }

}
