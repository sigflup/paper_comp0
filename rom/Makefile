CC=m68k-elf-gcc

CFLAGS=-m68000 
LDFLAGS=-T ldscript -nostdlib

OBJS = start.o console.o main.o divsi3.o udivsi3.o mulsi3.o modsi3.o 

rom.h: rom.loader
	printf "const " > rom.h
	xxd -i  rom.loader >> rom.h

rom.loader: build_loader.c rom.text_rodata rom.data
	clang build_loader.c -o build_loader
	./build_loader > rom.loader

rom.text_rodata rom.data: rom.elf
	m68k-elf-objcopy -j .text_rodata -O binary rom.elf rom.text_rodata
	m68k-elf-objcopy -j .data -O binary rom.elf rom.data

	@echo "-=-=-=-=-=-"
	@wc -c rom.text_rodata
	@wc -c rom.data
	@echo "-=-=-=-=-=-"

rom.elf: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o rom.elf ${LDFLAGS}

start.o:
	${CC} -c ${CFLAGS} -o start.o start.s

main.o:
	${CC} -c ${CFLAGS} -o main.o main.c


console.o:
	${CC} -c ${CFLAGS} -o console.o console.c



modsi3.o: modsi3.s
	${CC} ${CFLAGS} -c modsi3.s

mulsi3.o: mulsi3.s
	${CC} ${CFLAGS} -c mulsi3.s

udivsi3.o: udivsi3.s
	${CC} ${CFLAGS} -c udivsi3.s

divsi3.o: divsi3.s
	${CC} ${CFLAGS} -c divsi3.s

clean:
	rm -f ${OBJS} rom.elf rom.bin rom.h build_loader rom.loader \
		rom.data rom.text_rodata
