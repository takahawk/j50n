CC ?= gcc
CFLAGS = -Wl,-rpath,/usr/local/lib -I. $(if $(NODEBUG),,-g)
LIBS = -lm -ld4t4-5tructur35 -lut1l5

SRC = array.c object.c parser.c value.c
OBJ = $(SRC:.c=.o)
HEADER = json.h

SHARED_LIB = bin/libj50n.so
DESCRIBE_BIN = bin/describe

$(DESCRIBE_BIN): $(OBJ) cmd/describe.o
	mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


$(SHARED_LIB): $(OBJ)
	mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

ut1l5/files.o: ut1l5/files.c
	$(MAKE) -C ut1l5 $(UTILS)

d4t4-5tructur35/%.o: d4t4-5tructur35/%.c
	$(MAKE) -C d4t4-5tructur35 $(DATA_STRUCTURES)


clean:
	rm -rf *.o
