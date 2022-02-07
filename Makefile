LIBS = 
INCS = 

CC = cc

LDFLAGS = ${LIBS}
CFLAGS = -D_DEFAULT_SOURCE -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}

SRC = promody.c common.c

OBJ = ${SRC:.c=.o}

all: promody options

options:
	@echo promody build options:
	@echo "CFLAGS	=${CFLAGS}"
	@echo "LDFLAGS	=${LDFLAGS}"
	@echo "CC	=${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

promody: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean: 
	rm promody *.o

