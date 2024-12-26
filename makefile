CC=clang
CFLAGS ?= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-but-set-variable -O2
DEBUG=-fsanitize=address,undefined -g3

RAYLIB_LIBTYPE ?= STATIC
RAYLIB_INCLUDE_DIR ?= raylib/src/

INCLUDE=-Iinclude/ -IScaffold/include/ -I${RAYLIB_INCLUDE_DIR}

SRC_DIR=src
OBJ_DIR=build
OUT_DIR=lib

SOURCES=$(wildcard ${SRC_DIR}/*.c) $(wildcard ${SRC_DIR}/*/*.c)

OUTPUT=libmason.a

.PHONY: final debug enable-debug raylib compile move assemble clean

final: raylib compile move assemble
debug: enable-debug final

enable-debug:
	$(eval CFLAGS := ${CFLAGS} ${DEBUG})

raylib:
ifeq (${RAYLIB_LIBTYPE},STATIC)
	@echo [building raylib...]
	$(MAKE) -C ${RAYLIB_INCLUDE_DIR}
endif

compile:
	@echo [compiling...]
	# compile source files
	${CC} -c ${CFLAGS} ${SOURCES} ${INCLUDE}

move:
	@echo [moving files...]
	#create necessary dir if it doesn't exist
	test -d ${OBJ_DIR} || mkdir ${OBJ_DIR}

	# move generated object files to obj_dir
	$(eval objs := $(wildcard *.o))
	mv ${objs} ${OBJ_DIR}

assemble:
	@echo [creating static library...]
	#create necessary dir if it doesn't exist
	test -d ${OUT_DIR} || mkdir ${OUT_DIR}

	# assemble object files and raylib into final static library file
	$(eval objs := $(wildcard ${OBJ_DIR}/*.o))
ifeq (${RAYLIB_LIBTYPE},STATIC)
	$(eval objs += $(wildcard ${RAYLIB_INCLUDE_DIR}/*.o))
endif
	ar -rcs ${OUT_DIR}/${OUTPUT} ${objs}

clean:
ifneq ($(wildcard ${OBJ_DIR}/*.o),)
	rm $(wildcard ${OBJ_DIR}/*.o)
endif
ifeq (${RAYLIB_LIBTYPE}, STATIC)
	$(MAKE) clean -C raylib/src/
endif

