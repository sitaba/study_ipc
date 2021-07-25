
CC     = gcc
CFLAGS = -Wall
TARGET = ready pipe named_pipe ipc posix-ipc socket shared_memory

.PHONY: clean


all: $(TARGET)


ready:
	./ready_test_files.sh

pipe: pipe.c
	${CC} $^ -o $@.exe ${CFLAGS}

named_pipe: named_pipe.c
	${CC} $^ -o $@.exe ${CFLAGS}

ipc: ipc.c
	${CC} $^ -o $@.exe ${CFLAGS}

posix-ipc: posix-ipc.c
	${CC} $^ -o $@.exe ${CFLAGS}

socket: socket.c
	${CC} $^ -o $@.exe ${CFLAGS}

shared_memory: shared_memory.c
	${CC} $^ -o $@.exe ${CFLAGS}


clean:
	-rm *.exe *.txt
