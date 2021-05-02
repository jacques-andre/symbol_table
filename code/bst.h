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
        void inorder_print(Node* leaf);
        bool update_symbol(std::string word, std::string last_function, std::string general_type,Node* leaf);
        bool update_function(std::string word, std::string general_type,Node* leaf);
    public:
        BST();
        void insert(token_info symbol_data);
        void print();
        void inorder_print();
        bool update_symbol(std::string word, std::string last_function, std::string general_type);
        bool update_function(std::string word, std::string general_type);
};
