# LD_PRELOAD
testing LD_PRELOAD functionality in the host OS
callFileOp.c is the c file calling the open, read, write, lseek, and close file operations
to create a test.txt file with a hello world string inside.

dyLibFileOp.c is the c file for the LD_PRELOAD library. Within the library, we have 
open, read, write, lseek, and close functions that forward the call to the original
ones in the c library.

Makefile will generate dyLib.so and callFileOp.

tmpLd_CRW is the script file to temporarily set the LD_PRELOAD with dyLib.so and run the callFileOp.