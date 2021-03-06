// Jacques Andre, 40485967
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// local includes
#include "symbol_table.h" 
#include "bst.h"

void pretty_console(int& num_functions, int& num_variables, int& num_ifs, int& num_for, int& num_while){
    // this function will output variables "nicely" to the console. 
    std::cout << "Variables: " << num_variables << "\n";
    std::cout << "Functions: " << num_functions << "\n";
    std::cout << "If statements: " << num_ifs << "\n";
    std::cout << "For loops: " << num_for << "\n";
    std::cout << "While loops: " << num_while;
}

int main(int argc, char **argv) {
    BST* tree = new BST; // create a new instance of the "binary search tree"

    // handle input error
    if(argc < 2) {
        std::cout << "Please specify an input file!" << std::endl;
        return 1;
    } else if(argv[1] == NULL) {
        std::cout << "Error! Couldn't read " << argv[1] << std::endl;
    } else {
        std::cout << "Reading in the file: " << argv[1] << std::endl;
    }

    std::ifstream file(argv[1]); // input file stream
    std::ofstream out("identifiers.txt"); // output file stream
    std::string line;

    out << "Read in the file: " << argv[1] << "\n" "------ \n";

    // counters
    int line_counter= 0;
    int num_functions = 0;
    int num_variables = 0;
    int num_ifs = 0;
    int num_for = 0;
    int num_while = 0;

    std::string last_function;
    while(getline(file, line)) {
        // go through file line by line
        line_counter++;
        std::istringstream ss(line); // tokenize

        std::string word; // constantly updating

        while (ss >> word) {
            bool found = 0;
            if(tree -> update_symbol(word,last_function,"variable")) {
                found = 1;
            } else if(tree -> update_function(word,"function")){
                found = 1;
            }
            if(!found){
                token_info new_insertion; // make a new struct

                if(word == "int" || word == "int*" || word == "long" || word == "long*" || word == "double" || word == "double*" || word == "char[]" || word == "char" || word == "char*" || word == "short" || word == "*short" || word == "float" || word == "*float" || word == "void"){

                    // hold vars
                    std::string data_name;
                    std::string data_type;

                    data_type = word; // int,char,etc
                    ss >> word; // move along one more 

                    // edge case, things var name is "long" when type is "long long", need to move one more
                    if(word == "long"){
                        ss >> word;
                        data_name = word;
                        data_type = "long long";
                    } else{
                        data_name = word; // variable/func name
                        ss >> word; // move along one more
                    }

                    // if we see "(" will be function.
                    if(word == "("){
                        num_functions++;
                        new_insertion.general_type = "function";
                        last_function = data_name;
                    } else if(word == "[]"){
                        data_type = "char[]";
                        new_insertion.general_type = "variable";
                        num_variables++;
                    } 
                    else {
                        new_insertion.general_type = "variable";
                        num_variables++;
                    }

                    // make a new insertion to the tree
                    new_insertion.token_name = data_name;
                    new_insertion.line_number = line_counter;
                    new_insertion.times_seen = 0;
                    new_insertion.data_type = data_type;
                    new_insertion.last_function = last_function;
                    tree -> insert(new_insertion); // add a leaf to the tree

                }
                else if(word == "if"){
                    num_ifs++;
                } else if(word == "for"){
                    num_for++;
                } else if(word == "while"){
                    num_while++;
                }
            }
        }
    }
    pretty_console(num_functions,num_variables,num_ifs,num_for,num_while); 
    tree -> write_file(out); 
    out.close();
    delete tree; // defrence memory
    return 0;
}
