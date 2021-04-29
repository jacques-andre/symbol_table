#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct data_info{
    std::string value;
    int variable;
    int func;
    int count;
    int line_count;
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
    std::vector<data_info> dataMappings;

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
                //We have an int identifier (variable or function)
                //The next token is the name
                stream >> token; //Gets the next token (the identifier name)
                std::string name = token;
                std::cout << "The name of the identifier is: " << name << std::endl;
                std::cout << "The line number it is declared on is " << line_counter << std::endl;
                //If the next token is a (, we have a function, else we have
                //a variable
                stream >> token; //Get the next token
                if(token == "(")
                {
                    //Have a function
                    num_functions++;
                }
                else {
                    //Have a variable
                    num_variables++;
                }
            }
            else if(token == "if") {
                stream >> token;
                num_ifs++;
            }
            else if(token == "while") {
                stream >> token;
                num_while++;
            }
            else if(token == "for") {
                stream >> token;
                num_for++;
            }
            bool found = false;
            for(auto &w : dataMappings){
                if(w.value == token){
                    w.count++;
                    found = true;
                    break;
                }
            }
            if(!found){
                data_info new_data;
                new_data.value = token;
                new_data.line_count = line_counter - 1;
                new_data.count = 1;
                dataMappings.push_back(new_data);
            }
        }
    }
    file.close();
    for(auto &w : dataMappings){
        std::cout << w.value << "\t\t\t" << w.count << "\t\t\t" << w.line_count << std::endl;
    }
    std::cout << "Variables: " << num_variables << std::endl;
    std::cout << "Functions: " << num_functions << std::endl;
    std::cout << "If statements: " << num_ifs << std::endl;
    std::cout << "For loops: " << num_for << std::endl;
    std::cout << "While loops: " << num_while << std::endl;
    return 0; //Program ended succesfully
}
