#include <iostream>

#include "BinaryTree.h"

int main(){
	BinaryTree* tree = new BinaryTree();

	// Nacteni prvku do stromu skrz textovy soubor
	//tree->insert_fromFile("Tree1.txt");
	tree->insert_fromFile("Tree2.txt");
	//tree->insert_random(150, 600);

	// Vykreslení generované tabulky
	tree->print_treeTable();

	std::getchar();
	delete tree;
}
