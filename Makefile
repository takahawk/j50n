CC=gcc
CFLAGS=-I. -I./d4t4-5tructur35 -I./ut1l5
LIBS=-lm
DEPS=json.h

DATA_STRUCTURES=array_list.o buffer.o skip_list_map.o 
UTILS=files.o
OBJ=array.o object.o value.o parser.o $(patsubst %,d4t4-5tructur35/%,$(DATA_STRUCTURES)) $(patsubst %,ut1l5/%,$(UTILS))

bin/describe: $(OBJ) cmd/describe.o
	mkdir -p bin/
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ut1l5/files.o: ut1l5/files.c
	$(MAKE) -C ut1l5 $(UTILS)

d4t4-5tructur35/%.o: d4t4-5tructur35/%.c
	$(MAKE) -C d4t4-5tructur35 $(DATA_STRUCTURES)


clean:
	rm -rf *.o
	$(MAKE) -C d4t4-5tructur35 clean
	$(MAKE) -C ut1l5 clean
