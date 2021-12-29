#include "BinaryTree.h"

BinaryTree::BinaryTree() {
	root = NULL;
	treeDepth = 0;
	treeWidth = 0;
}

BinaryTree::~BinaryTree() {
	destroy_tree();
	table.clear();
}

void BinaryTree::destroy_tree() {
	destroy_tree(root);
}

void BinaryTree::destroy_tree(node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void BinaryTree::insert(int key) {
	if (root != NULL) {
		insert(key, root);
	}
	else {
		root = new node;
		root->depth = 0;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

void BinaryTree::insert(int key, node* leaf){
	if (key < leaf->value) {
		if (leaf->left != NULL) {
			insert(key, leaf->left);
		}
		else {
			leaf->left = new node;
			leaf->left->depth = leaf->depth + 1;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;

			// Proceduralni vypocet maximalni hloubky stromu (resp. neni treba volat create_treeTable())
			if (treeDepth < leaf->left->depth)
				treeDepth = leaf->left->depth;
		}
	} 
	else if (key >= leaf->value) {
		if (leaf->right != NULL) {
			insert(key, leaf->right);
		}
		else {
			leaf->right = new node;
			leaf->right->depth = leaf->depth + 1;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;

			// Proceduralni vypocet maximalni hloubky stromu
			if (treeDepth < leaf->right->depth)
				treeDepth = leaf->right->depth;
		}
	}
}

void BinaryTree::traverse_inorder() {
	traverse_inorder(root);
}

void BinaryTree::traverse_inorder(node* leaf) {
	if (leaf != NULL) {
		traverse_inorder(leaf->left);
		table[leaf->depth].push_back(leaf->value);
		traverse_inorder(leaf->right);
	}
}


void BinaryTree::create_treeTable(){
	table.resize(this->treeDepth + 1);
	traverse_inorder();

	for (int i = 0; i != treeDepth + 1; i++)
		if (table[i].size() > treeWidth)
			treeWidth = table[i].size();
}

void BinaryTree::print_treeTable(){	
	if (this->root == NULL) {
		printf("\n[ERROR] <PRINT> Strom neobsahuje zadne prvky!");
		return;
	}

	// Pred vykreslenim tabulky je treba ji mit co nejaktualnejsi
	this->create_treeTable();

	// Vyuziti knihovny <iomanip> pro vetsi prehled 
	cout << "Tree WIDTH table (inorder traversing):" << endl << endl;
	cout << left << setw(7) << setfill(' ') << "Depth";
	cout << left << setw(7) << setfill(' ') << "Width";
	cout << left << setw(10) << setfill(' ') << "Keys" << endl;
	cout << left << setw(treeWidth + 25) << setfill('-') << "-" << endl;

	for(int d = 0; d != treeDepth + 1; d++){
		cout << left << setw(7) << setfill(' ') << d;

		// Vyuziti knihovny <Windows.h> pro zabarveni konzoly. Konkretne tato podminka vykresli cervenou barvou nejsirsi patra.
		if (table[d].size() == treeWidth)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);

		cout << left << setw(7) << setfill(' ') << table[d].size();
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
	
		for (int i = 0; i != table[d].size(); i++)
			cout << table[d].at(i) << " ";
		
		printf("\n");
	}

	printf("\n TREE_WIDTH: %d    THREE_DEPTH: %d", this->treeWidth, this->treeDepth + 1);
}

void BinaryTree::insert_fromFile(string path){
	ifstream file(path, ifstream::in);

	if (file.is_open()) {
		int n;

		while (file >> n) {
			this->insert(n);
		}
	}
	else {
		printf("\n[ERROR] <FILE> Soubor se nepodarilo otevrit! \"%s\"", path.c_str());
	}

	file.close();
}

//! Pùvodní kód: https://en.cppreference.com/w/cpp/numeric/random/random_device
void BinaryTree::insert_random(int n, int max){
	std::random_device rd;							// obtain a random number from hardware
	std::mt19937 gen(rd());							// seed the generator
	std::uniform_int_distribution<> distr(0, max);	// define the range

	for (int i = 0; i != n; i++)
		this->insert(distr(gen));
}
