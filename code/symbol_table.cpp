#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct data_info{
    std::string value_name;
    int line_number;
    int refrence = 0;
    std::string general_type = "";
    std::string data_type = "";
    std::string function_param = ""; // holds the name of the function the variable was a parameter of. Ex: hello(int a) function_param = "hello"
};
int main(int argc, char **argv) {
    // handle input error
    if(argc < 2){
        std::cout << "Please specify an input file!" << std::endl;
        return 1; 
    }
    std::cout << "Reading in the file: " << argv[1] << std::endl;

    std::ifstream file(argv[1]); // input file stream
    std::ofstream out("identifiers.txt");
    std::string line;
    std::string token;
    std::vector<data_info> data_mappings;

    out << "Read in the file: " << argv[1] << "\n" "------ \n";

    // counters
    int line_counter = 0;
    int num_functions = 0;
    int num_variables = 0;
    int num_ifs = 0;
    int num_for = 0;
    int num_while = 0;


    while(getline(file, line)) {
        std::stringstream stream(line);

        line_counter++;

        while(stream >> token) {
            bool found = false; // have not seen the first token
            for(data_info& d : data_mappings){
                if(d.value_name == token){
                    d.refrence++; // we have found previous token, update the times seen 
                    found = true;
                    break;
                }
            }
            if(!found){
                if(token == "int" || token == "int*" || token == "long" || token == "long*" || token == "double" || token == "double*" || token == "char" || token == "char*" || token == "short" || token == "*short" || token == "float" || token == "*float") {
                    data_info new_data; // make new struct, to add to vector

                    // Holds temp vars
                    std::string data_type = token;
                    std::string name = "";
                    std::string func_token = "";

                    stream >> token; // Gets the next token (the identifier name)

                    // edge case "long long var_name" < thinks the var_name is long, should be the next token.
                    if(token != "long"){
                        name = token;
                    } else{
                        stream >> token; // move along one 
                        name = token; 
                        data_type = "long long";
                    }

                    std::cout << "token:" << token << std::endl;

                    //If the next token is a (, we have a function, else we have a variable
                    stream >> token;

                    if(token == "("){
                        // check what's inside params
                        while(func_token != ")"){
                            stream >> func_token; // func_token = the variable name 
                            if(func_token != "," && func_token != ")" && func_token != "int"){
                                num_variables++; // add to counter, we saw a variable inside the params. 
                                // for debugging:
                                /* std::cout << "func_token:" << func_token << std::endl; */
                                /* std::cout << "name:" << name << std::endl; */
                                new_data.value_name = func_token;
                                new_data.line_number = line_counter;
                                new_data.general_type = "variable";
                                new_data.data_type = data_type;
                                new_data.function_param = name; // this is the function name
                                data_mappings.push_back(new_data);
                            }
                        }
                        num_functions++; // we have a function

                        // updates the vector
                        new_data.value_name = name;
                        new_data.line_number = line_counter;
                        new_data.general_type = "function";
                        new_data.data_type = data_type;
                    }
                    else {
                        num_variables++; // we have a variable

                        // updates the vector
                        new_data.value_name = name;
                        new_data.line_number = line_counter;
                        new_data.general_type = "variable";
                        new_data.data_type = data_type;
                    }
                    data_mappings.push_back(new_data); // add to vector
                }
                else if(token == "if") {
                    num_ifs++;
                }
                else if(token == "while") {
                    num_while++;
                }
                else if(token == "for") {
                    num_for++;
                }
            }
        }
    }
    file.close();
    // for debugging the vector mappings
    for(data_info d : data_mappings){
        // out refers to output file
        out << d.value_name << "," << "line " << d.line_number << "," << d.general_type << "," << d.data_type << "," << "refrenced:" << d.refrence << std::endl;  
        std::cout << d.value_name <<  "(" << d.function_param << ")"
            <<  "," << "line " << d.line_number << "," << d.general_type << "," << d.data_type << "," << "refrenced:" << d.refrence << std::endl;  
    }
    std::cout << "Variables: " << num_variables << std::endl;
    std::cout << "Functions: " << num_functions << std::endl;
    std::cout << "If statements: " << num_ifs << std::endl;
    std::cout << "For loops: " << num_for << std::endl;
    std::cout << "While loops: " << num_while << std::endl;
    out.close();
    return 0; //Program ended succesfully
}
