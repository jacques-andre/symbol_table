//Author: Simon Powers
//A program to count the number of times each word occurs in a file

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct word_info
{
    string word; //The word;
    int count; //The number times the word occurs in the file
};

int main(int argc, char **argv)
{
    ifstream file("doc.txt");
    string line;
    string token;
    vector<word_info> word_list;

    while(getline(file, line))
    {
        stringstream stream(line);

        while(stream >> token) 
        {
           //Check if we have already seen the current word (token)
           //if yes, add one to its count
           bool found = false;
           for(auto &w : word_list)
           {
               if(w.word == token)
               {
                   //We have seen the word so add one to its count
                   w.count++;
                   found = true;
                   break;
               }
           }
           if(!found)
           {
               //We have seen a new word, so add it to word_list;
               word_info new_word;
               new_word.word = token;
               new_word.count = 0;
               word_list.push_back(new_word);
           }
        }
    }
    file.close();
    //Print the words and their counts
    for(auto &w : word_list)
    {
        cout << w.word << "\t\t\t" << w.count << endl;
    }
    return 0; //Program ended succesfully
}
