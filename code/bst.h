#pragma once

#include "symbol_table.h"

class BST{
    private:
        struct Node{
            token_info symbol_data;
            Node* left;
            Node* right;
        };
        Node* root;
        void insert(token_info symbol_data, Node* leaf);
        void inorder_print(std::ofstream& file,Node* leaf);
        bool update_symbol(std::string word, std::string last_function, std::string general_type,Node* leaf);
        bool update_function(std::string word, std::string general_type,Node* leaf);
        void clear_tree();
    public:
        BST();
        ~BST();
        void insert(token_info symbol_data);
        void print();
        void inorder_print(std::ofstream& file);
        bool update_symbol(std::string word, std::string last_function, std::string general_type);
        bool update_function(std::string word, std::string general_type);
        void clear_tree(Node* leaf);
};
