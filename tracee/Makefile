CC = cc

LDFLAGS = ${LIBS}
CFLAGS = -D_DEFAULT_SOURCE -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}

all: 
	${CC} -o tracee tracee.c ${CFLAGS}

clean:
	-rm -rf tracee
