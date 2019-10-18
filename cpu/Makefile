
CC = clang
AR = llvm-ar
RANLIB = llvm-ranlib
CFLAGS = -O2 -Wall -ggdb 
LIBNAME=libcpu.a

OBJS = m68kcpu.o m68kopac.o m68kopdm.o m68kopnz.o m68kops.o

${LIBNAME}: ${OBJS}
	${AR} -q ${LIBNAME} ${OBJS}
	${RANLIB} ${LIBNAME}

draw.o: m68kcpu.c 
	${CC} -c ${CFLAGS} m68kcpu.c

draw.o: m68kopac.c
	${CC} -c ${CFLAGS} m68kopac.c

m68kopdm.o: m68kopdm.c
	${CC} -c ${CFLAGS} m68kopdm.c

m68kopnz.o: m68kopnz.c
	${CC} -c ${CFLAGS} m68kopnz.c

m68kops.o: m68kops.c
	${CC} -c ${CFLAGS} m68kops.c

clean:
	rm -f ${LIBNAME} ${OBJS}

include depend
