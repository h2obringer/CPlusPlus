CC=gcc
CFLAGS=-Wall -O2 -pedantic -g #-Werror
LDFLAGS=-L.
LDLIBS=-lnet -lnsl -lsocket 

#
# the library files
#
LIBFILES = connectsock.c connecttcp.c error.c lport.c passivesock.c passivetcp.c encrypt.c help.c #handleCommands.c
LIBOBJS = ${LIBFILES:.c=.o}
LIBNET = libnet.a

#
# which programs to build
#
PROGS=myssh mysshd
all: ${LIBNET} ${PROGS}

#
# how to build the library
#
${LIBOBJS}: libnet.h
${LIBNET}: ${LIBOBJS}
	${AR} -r ${LIBNET} ${LIBOBJS}
	ranlib ${LIBNET}

${PROGS}: ${LIBNET}

clean:
	rm -f *.o core ${PROGS} ${LIBNET} 
	rm -rf *.dSYM/

