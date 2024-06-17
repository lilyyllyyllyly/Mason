# i tried so, so hard to make this nicer
# but i lost all my sanity and i feel like i understand makefiles even less now
# so it will have to remain like this

CC=clang
CFLAGS=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-but-set-variable -O2
DEBUG=-fsanitize=address,undefined -g3

INCLUDE=-Iinclude/ -I../../include/ -I../../Scaffold/include/
LIBS=-L../../lib -L../../Scaffold/lib -lmason -lscaffold -lm -lraylib

SRC_DIR=src

SOURCES=$(wildcard ${SRC_DIR}/*.c)

OUTPUT=test

final: compile
debug: enable-debug final

enable-debug:
	$(eval CFLAGS := ${CFLAGS} ${DEBUG})

compile:
	@echo [compiling...]
	# compile source files
	${CC} ${CFLAGS} ${SOURCES} ${INCLUDE} ${LIBS} -o ${OUTPUT}

