
#define HOST_LITTLE_ENDIAN

typedef enum {
 TRUE,
 FALSE
} bool_t;

unsigned short swap_16(unsigned short in);
unsigned int   swap_32(unsigned int in);

int main(int argc, char **argv);
