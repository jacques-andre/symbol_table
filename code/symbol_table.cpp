#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
    ifstream file("test-files/test3.c");
    string line;
    string token;

    // counters
    int line_counter = 0;
    int num_functions = 0;
    int num_variables = 0;
    int num_ifs = 0;
    int num_for = 0;
    int num_while = 0;

    while(getline(file, line)) {
        stringstream stream(line);

        line_counter++;

        while(stream >> token) {
            if(token == "int" || token == "int*" || token == "long" || token == "long*" || token == "double" || token == "double*" || token == "char" || token == "char*" || token == "short" || token == "*short" || token == "float" || token == "*float") {
                //We have an int identifier (variable or function)
                //The next token is the name
                stream >> token; //Gets the next token (the identifier name)
                string name = token;
                /* cout << "The name of the identifier is: " << name << endl; */
                /* cout << "The line number it is declared on is " << line_counter << endl; */
                //If the next token is a (, we have a function, else we have
                //a variable
                stream >> token; //Get the next token
                if(token == "(")
                {
                    //We have a function
                    num_functions++;
                }
                else {
                    //We have a variable
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
        }
    }
    file.close();
    cout << "Variables: " << num_variables << endl;
    cout << "Functions: " << num_functions << endl;
    cout << "If statements: " << num_ifs << endl;
    cout << "For loops: " << num_for << endl;
    cout << "While loops: " << num_while << endl;
    return 0; //Program ended succesfully
}
