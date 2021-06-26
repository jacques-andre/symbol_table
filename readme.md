# symbol_table 

**Jacques Andre, 40485967**


## How to build:

During development, my program was compiled using `g++`. It also uses `--std=c++11`, using the *"newer"* features of
c++.

### MakeFile:

```make
output: symbol_table.o bst.o
	g++ --std=c++11 symbol_table.o bst.o -o symbol_table

symbol_table.o: symbol_table.cpp symbol_table.h
	g++ --std=c++11 -c symbol_table.cpp # compile to object file "-c"

bst.o: bst.cpp bst.h
	g++ --std=c++11 -c bst.cpp # compile to object file "-c"

clean: 
	rm *.o output
```

Both files (`bst.cpp` & `symbol_table.cpp`) are included in my output, with the heart of my program in `symbol_table.cpp` and the binary search tree in `bst.cpp`. 

## Header files:

I have 2 header files used in my program. `bst.h`: holds information surrounding the Binary Search Tree class. Makes it easier to use from `symbol_token.cpp`. 

`symbol_table.h`: holds information surrounding the `sturct token_info`, this means I can use my `struct` from other
files such as `bst.cpp`

## Running:
```
make
./symbol_table test-files/test3.c
```

