#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct token_info{
    // this holds information about the current token.
    int line_number; // line number token is on.
    int times_seen; // refrences
    std::string token_name;
    std::string general_type; // func or var
    std::string data_type; // int,string,etc
    std::string last_function; // last function
};

void pretty_printer(std::vector<token_info> const &token_vector){
    for(auto &t : token_vector){
        // check if it's a variable or function
        if(t.general_type == "function"){
            std::cout << t.token_name << ", " << "line " << t.line_number << ", " << t.general_type << ", " << t.data_type << ", " << "refrenced " << t.times_seen << std::endl;
        } else if(t.general_type == "variable" && t.last_function != "main"){
            // stops us putting (main) 
            std::cout << t.token_name << " " << "(" << t.last_function << ")" << "," << " line " << t.line_number << ", " << t.general_type << ", " << t.data_type << ", " << "refrenced " << t.times_seen << std::endl;
        } else{
            std::cout << t.token_name << "," << "line " << t.line_number << "," << t.general_type << "," << t.data_type << "," << t.times_seen << std::endl;
        }

    }
}

int main(int argc, char **argv) {

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
    std::ofstream out("identifiers.txt");
    std::string line;
    std::vector<token_info> token_vector;

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
            for(auto& t : token_vector){
                if(t.general_type == "variable" && word == t.token_name && t.last_function == last_function){
                    t.times_seen++;
                    found = 1;
                    break;
                } else if(t.general_type == "function" && word == t.token_name){
                    t.times_seen++;
                    found = 1;
                    break;
                }
            }

            if(!found){
                token_info new_insertion; // make a new struct

                if(word == "int" || word == "int*" || word == "long" || word == "long*" || word == "double" || word == "double*" || word == "char[]" || word == "char" || word == "char*" || word == "short" || word == "*short" || word == "float" || word == "*float" || word == "void"){

                    // hold vars
                    std::string data_name;
                    std::string data_type;

                    data_type = word; // int,char,etc
                    ss >> word; // move along one more 

                    data_name = word; // variable/func name
                    ss >> word; // move along one more

                    if(word == "("){
                        // if we see "(" will be function.
                        new_insertion.general_type = "function";
                        last_function = data_name;
                    } 
                    else {
                        new_insertion.general_type = "variable";
                    }


                    // make a new insertion to the vector
                    new_insertion.token_name = data_name;
                    new_insertion.line_number = line_counter;
                    new_insertion.times_seen = 0;
                    new_insertion.data_type = data_type;
                    new_insertion.last_function = last_function;
                    token_vector.push_back(new_insertion);

                }
            }
        }
    }
    pretty_printer(token_vector);
    out.close();
    return 0;
}
