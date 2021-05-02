output: symbol_table.o bst.o
	g++ --std=c++11 symbol_table.o bst.o -o symbol_table

symbol_table.o: symbol_table.cpp symbol_table.h
	g++ --std=c++11 -c symbol_table.cpp # compile to object file "-c"

bst.o: bst.cpp bst.h
	g++ --std=c++11 -c bst.cpp # compile to object file "-c"

clean: 
	rm *.o output
