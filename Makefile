
CC = clang
CFLAGS = -O2 -Wall -DNOTRACE -ggdb 
LIBS=
PROGNAME=paper


OBJS = main.o mem.o io.o cpu/libcpu.a

${PROGNAME}: ${OBJS} 
	${CC} -o ${PROGNAME}  ${OBJS} ${LIBS}

main.o: main.c
	${CC} -c ${CFLAGS} main.c

mem.o: mem.c rom/rom.h
	${CC} -c ${CFLAGS} mem.c

io.o: io.c io.h
	${CC} -c ${CFLAGS} io.c

cpu/libcpu.a:
	cd cpu && make
rom/rom.h:
	cd rom && make

clean:
	cd cpu && make clean
	cd rom && make clean
	rm -f ${PROGNAME} ${PROGNAME}.core core ${OBJS}
