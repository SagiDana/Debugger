LIBS = 
INCS = 

CC = cc

LDFLAGS = ${LIBS}
CFLAGS = -D_DEFAULT_SOURCE -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}

SRC = debugger.c

OBJ = ${SRC:.c=.o}

all: debugger options

options:
	@echo debugger build options:
	@echo "CFLAGS	=${CFLAGS}"
	@echo "LDFLAGS	=${LDFLAGS}"
	@echo "CC	=${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

debugger: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean: 
	rm debugger *.o

