#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct data_info{
    std::string value_name;
    int line_number;
    int refrence;
    std::string general_type = "";
    std::string data_type = "";
};
int main(int argc, char **argv) {
    // handle input error
    if(argc < 2){
        std::cout << "Please specify an input file!" << std::endl;
        return 1; 
    }
    std::cout << "Reading in the file: " << argv[1] << std::endl;

    std::ifstream file(argv[1]);
    std::string line;
    std::string token;
    std::vector<data_info> data_mappings;

    // counters
    int line_counter = 0;
    int num_functions = 0;
    int num_variables = 0;
    int num_ifs = 0;
    int num_for = 0;
    int num_while = 0;


    while(getline(file, line) != NULL) {
        std::stringstream stream(line);

        line_counter++;

        while(stream >> token) {
            if(token == "int" || token == "int*" || token == "long" || token == "long*" || token == "double" || token == "double*" || token == "char" || token == "char*" || token == "short" || token == "*short" || token == "float" || token == "*float") {

                bool found = false; // have not seen the first token

                //We have an int identifier (variable or function)
                std::string data_type = token;
                stream >> token; // Gets the next token (the identifier name)
                std::string name = token;

                // the problem is here, it is not updating the refrence***
                for(data_info d : data_mappings){
                    if(d.value_name == name){
                        std::cout << "am here!" << std::endl;
                        d.refrence++;
                        found = true;
                        break;
                    }
                }

                //If the next token is a (, we have a function, else we have a variable
                stream >> token;

                if(token == "("){
                    num_functions++; // we have a function

                    // updates the vector
                    if(!found){
                        data_info new_data;
                        new_data.value_name = name;
                        new_data.line_number = line_counter;
                        new_data.refrence = 1; // first time we have seen the function
                        new_data.general_type = "function";
                        new_data.data_type = data_type;
                        data_mappings.push_back(new_data);
                    } 
                }
                else {
                    num_variables++; // we have a variable

                    // updates the vector
                    if(!found){
                        data_info new_data;
                        new_data.value_name = name;
                        new_data.line_number = line_counter;
                        new_data.refrence = 1; // first time we have seen the function
                        new_data.general_type = "variable";
                        new_data.data_type = data_type;
                        data_mappings.push_back(new_data);
                    } 
                }
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
    file.close();
    for(auto &w : data_mappings){
        std::cout << "\n";
        std::cout << w.value_name << "," << "line " << w.line_number << "," << w.general_type << "," << w.data_type << "," << "refrenced:" << w.refrence << std::endl;  
    }
    std::cout << "Variables: " << num_variables << std::endl;
    std::cout << "Functions: " << num_functions << std::endl;
    std::cout << "If statements: " << num_ifs << std::endl;
    std::cout << "For loops: " << num_for << std::endl;
    std::cout << "While loops: " << num_while << std::endl;
    return 0; //Program ended succesfully
}
