CC = gcc

programs = callFileOp
dyLib = dyLib.so

all : $(programs) $(dyLib)

CST_FLAGS = -Wall -m64 -O0 -std=c99 -g -static
CDY_FLAGS = -g -Wall -m64 -std=c99

# LIB_ST_SFLAGS = -Wall -m64 -shared -fPIC -O0 -std=c99 -g 
LIB_DY_SFLAGS = -g -Wall -shared -fPIC

CSOURCE = callFileOp.c
COBJECT = $(CSOURCE:.c=.o)

LIBCSOURCE = dyLibFileOp.c

# forgot the -c to create the .o file 
$(programs): $(COBJECT)
	$(CC) $(CDY_FLAGS) -o $@ $^

dyLib.so: dyLibFileOp.c
	$(CC) $(LIB_DY_SFLAGS) -o $@ $^ -ldl

clean: 
	rm -rf *.o *.so *.txt $(programs)
