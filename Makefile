CC = cc

LDFLAGS = ${LIBS}
CFLAGS = -D_DEFAULT_SOURCE -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}

all: common.o mm/memory.o ptrace/ptrace.o debug/debug.o types.h
	${CC} -o promody promody.c common.o mm/memory.o ptrace/ptrace.o debug/debug.o ${CFLAGS} 

common.o: common.c common.h
	${CC} -o common.o -c common.c ${CFLAGS}

mm/memory.o: mm/memory.c mm/memory.h
	${CC} -o mm/memory.o -c mm/memory.c ${CFLAGS}

ptrace/ptrace.o: ptrace/ptrace.h ptrace/ptrace.c
	${CC} -o ptrace/ptrace.o -c ptrace/ptrace.c ${CFLAGS}

debug/debug.o: debug/debug.h debug/debug.c
	${CC} -o debug/debug.o -c debug/debug.c ${CFLAGS}

clean: 
	-rm promody 
	-rm common.o
	-rm mm/memory.o
	-rm ptrace/ptrace.o

options:
	@echo promody build options:
	@echo "CFLAGS	=${CFLAGS}"
	@echo "LDFLAGS	=${LDFLAGS}"
	@echo "CC	=${CC}"
