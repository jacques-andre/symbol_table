//Author: Simon Powers
//A program to count the number of int identifiers in a .c file

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char **argv)
{
    ifstream file("test1.c");
    string line;
    string token;
    int line_counter = 0;
    int num_functions = 0;
    int num_variables = 0;

    while(getline(file, line))
    {
        stringstream stream(line);

        line_counter++;


        while(stream >> token)
        {
            if(token == "int")
            {
                //We have an int identifier (variable or function)
                //The next token is the name
                stream >> token; //Gets the next token (the identifier name)
                string name = token;
                cout << "The name of the identifier is: " << name << endl;
                cout << "The line number it is declared on is " << line_counter << endl;
                //If the next token is a (, we have a function, else we have
                //a variable
                stream >> token; //Get the next token
                if(token == "(")
                {
                    //We have a function
                    num_functions++;
                }
                else
                {
                    //We have a variable
                    num_variables++;
                }
            }
        }
    }
    file.close();
    cout << "The number of variables is: " << num_variables << endl;
    cout << "The number of functions is: " << num_functions << endl;
    return 0; //Program ended succesfully
}
