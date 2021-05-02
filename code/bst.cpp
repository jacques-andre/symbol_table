#include "bst.h"
#include "symbol_table.h"

BST::BST(){
	root = NULL;
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


void BST::inorder_print(){
	// public
	inorder_print(root);
	std::cout << "\n";
}

void BST::inorder_print(Node *leaf){
	// private
	if(leaf != NULL){
		inorder_print(leaf->left);
		std::cout << leaf-> symbol_data.token_name << "," << leaf -> symbol_data.times_seen << std::endl;
		inorder_print(leaf->right);
	}
}
