
CC     = gcc
CFLAGS = -Wall
TARGET = random.txt pipe.exe named_pipe.exe ipc.exe posix-ipc.exe socket.exe shared_memory.exe

.PHONY: clean ready


all: $(TARGET)


random.txt: ready_test_files.sh
	./$^

pipe.exe: pipe.c
	${CC} $^ -o $@ ${CFLAGS}

named_pipe.exe: named_pipe.c
	${CC} $^ -o $@ ${CFLAGS}

ipc.exe: ipc.c
	${CC} $^ -o $@ ${CFLAGS}

posix-ipc.exe: posix-ipc.c
	${CC} $^ -o $@ ${CFLAGS}

socket.exe: socket.c
	${CC} $^ -o $@ ${CFLAGS}

shared_memory.exe: shared_memory.c
	${CC} $^ -o $@ ${CFLAGS}


ready: random.txt

clean:
	-rm *.exe *.txt
