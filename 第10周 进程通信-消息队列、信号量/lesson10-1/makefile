EXEC1 = msgsend
OBJS1 = msgsend.o
EXEC2 = msgreceive 
OBJS2 = msgreceive.o
HEADERS = 

CC = gcc
INC = -I.
CFLAGS = ${INC} -g 

all:${EXEC1} ${EXEC2}
${EXEC1} : ${OBJS1}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS1} 
${OBJS1} : ${HEADERS}
${EXEC2} : ${OBJS2}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS2} 

${OBJS2} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS1} ${EXEC1}
	-rm -f ${OBJS2} ${EXEC2}
