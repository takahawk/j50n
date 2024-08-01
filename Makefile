CC ?= gcc
CFLAGS = -Wl,-rpath,/usr/local/lib -I. $(if $(NODEBUG),,-g)
LIBS = -lm -ld4t4-5tructur35 -lut1l5

SRC = array.c object.c parser.c value.c
OBJ = $(SRC:.c=.o)
OBJ_PIC = $(OBJ:.o=_pic.o)
HEADER = json.h

INSTALL_INCLUDE_DIR ?= /usr/local/include/w/j50n
INSTALL_SRC_DIR ?= /usr/local/src/w/j50n
INSTALL_LIB_DIR ?= /usr/local/lib/

SHARED_LIB = bin/libj50n.so
STATIC_LIB = bin/libj50n.a
DESCRIBE_BIN = bin/describe

.PHONY: all check clean shared static install
.DEFAULT_GOAL = all

all: $(DESCRIBE_BIN) shared static

check:
	$(CC) -fsyntax-only $(SRC) $(HEADER)

shared: $(SHARED_LIB)

static: $(STATIC_LIB)

$(DESCRIBE_BIN): $(OBJ) cmd/describe.o
	mkdir -p bin
	$(CC) $(if $(USE_SHARED),,-static) -o $@ $^ $(CFLAGS) $(LIBS)


$(SHARED_LIB): $(OBJ_PIC)
	mkdir -p bin
	$(CC) -shared -o $@ $^ $(CFLAGS) -fPIC $(LIBS)

$(STATIC_LIB): $(OBJ)
	mkdir -p bin
	ar rcs $@ $^

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS) -fPIC

%_pic.o: %.c
	$(CC) -fPIC -c -o $@ $< $(CFLAGS) -fPIC


install:
	mkdir -p $(INSTALL_INCLUDE_DIR) 
	mkdir -p $(INSTALL_SRC_DIR) 
	mkdir -p $(INSTALL_LIB_DIR)
	for header in $(HEADERS); do \
	       cp $$header $(INSTALL_INCLUDE_DIR) ; \
	done
	
	for src in $(SRC); do \
		cp $$src $(INSTALL_SRC_DIR) ; \
	done
	
	cp $(SHARED_LIB) $(INSTALL_LIB_DIR)
	cp $(STATIC_LIB) $(INSTALL_LIB_DIR)

clean:
	rm -rf *.o
