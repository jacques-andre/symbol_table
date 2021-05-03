#include "bst.h"
#include "symbol_table.h"
#include <fstream> 
#include <iostream> 

BST::BST(){
	root = NULL;
}

BST::~BST(){
	clear_tree(); // remove all nodes
}

void BST::insert(token_info symbol_data, Node* leaf){
	if(symbol_data.token_name.at(0) <= leaf -> symbol_data.token_name.at(0)){
		if(leaf -> left != NULL){
			// recursive, found a node on the left side, keep going 
			insert(symbol_data,leaf->left);
		} else{
			// make a new left node "smaller"
			leaf -> left = new Node;
			leaf -> left -> symbol_data = symbol_data;
			leaf -> left -> left = NULL;
			leaf -> left -> right = NULL;
		} 
	}
	else if(symbol_data.token_name.at(0) >= leaf -> symbol_data.token_name.at(0)){
		// bigger than
		if(leaf -> right != NULL){
			insert(symbol_data,leaf -> right);
		} else{
			leaf -> right = new Node;
			leaf -> right -> symbol_data = symbol_data;
			leaf -> right -> right = NULL;
			leaf -> right -> left = NULL;
		}
	}
}
void BST::insert(token_info symbol_data){
	if(root != NULL){
		insert(symbol_data,root);
	} else{
		root = new Node;
		root -> symbol_data = symbol_data;
		root -> left = NULL;
		root -> right = NULL;
	}
}

bool BST::update_function(std::string word, std::string general_type){
	// public
	return update_function(word,general_type,root);
}

bool BST::update_function(std::string word,std::string general_type, Node* leaf){
	// check if the word is the same as a token
	if(leaf != NULL){
		if(leaf -> symbol_data.token_name == word && leaf -> symbol_data.general_type == general_type){
			leaf -> symbol_data.times_seen++;
			return true;
		} else{
			update_function(word,general_type,leaf->left);
			update_function(word,general_type,leaf->right);
		}
	}
	return false;
}

bool BST::update_symbol(std::string word,std::string last_function, std::string general_type){
	// public
	return update_symbol(word,last_function,general_type,root);
}

bool BST::update_symbol(std::string word,std::string last_function, std::string general_type, Node* leaf){
	// check if the word is the same as a token
	if(leaf != NULL){
		if(leaf -> symbol_data.token_name == word && leaf -> symbol_data.last_function == last_function && leaf -> symbol_data.general_type == general_type){
			leaf -> symbol_data.times_seen++;
			return true;
		} else{
			update_symbol(word,last_function,general_type,leaf->left);
			update_symbol(word,last_function,general_type,leaf->right);
		}
	}
	return false;
}


void BST::inorder_print(std::ofstream& file){
	// public
	inorder_print(file,root);
	std::cout << "\n";
}

void BST::inorder_print(std::ofstream& file, Node *leaf){
	// private
	if(leaf != NULL){
		inorder_print(file,leaf->left);
		// using file writing here
		if(leaf -> symbol_data.general_type == "function"){
			file << leaf -> symbol_data.token_name << "," << "line " << leaf -> symbol_data.line_number << "," << leaf -> symbol_data.general_type << "," << leaf -> symbol_data.data_type << ",refrenced " << leaf -> symbol_data.times_seen << "\n";
		} else if(leaf -> symbol_data.general_type == "variable" && leaf -> symbol_data.last_function != "main"){
			file << leaf -> symbol_data.token_name << " " << "(" << leaf -> symbol_data.last_function << ")" << "," << "line " << leaf -> symbol_data.line_number << "," << leaf -> symbol_data.general_type << "," << leaf -> symbol_data.data_type << ",refrenced " << leaf -> symbol_data.times_seen << "\n";
		} else{
			file << leaf -> symbol_data.token_name << "," << "line " << leaf -> symbol_data.line_number << "," << leaf -> symbol_data.general_type << "," << leaf -> symbol_data.data_type << ",refrenced " << leaf -> symbol_data.times_seen << "\n";
		}
		inorder_print(file,leaf->right);
	}
}

void BST::clear_tree(){
	clear_tree(root);
}

void BST::clear_tree(Node* leaf){
	// private
	if(leaf != NULL){
		clear_tree(leaf->left);
		clear_tree(leaf->right);
		delete leaf;
	}
}

