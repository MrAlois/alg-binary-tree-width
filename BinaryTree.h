#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include <Windows.h>
#include <iomanip>
#include <random>

using namespace std;

//! Elementarni prvek stromu
/*! Struktura node reprezentuje "list" stromu, neboli jeho prvek.  */
struct node {
	int value;		//! Data prvku	
	int depth;		//! Hloubka prvku vuci korenu
	node* left;		//! Odkaz na potomka na levé strane
	node* right;	//! Odkaz na potomka na pravé strane
};


//! Upraveny binarni strom (nevyvazena varianta)
/*! Upraveny binarni strom dle vzoru ze stranky https://gist.github.com/toboqus/def6a6915e4abd66e922. Z puvodni
*	implemenace byly odstraneny metody pro postorder a preoder print. Pridany naopak byly metody create_treeTable(), traverse_inorder(),
*	print_treeTable(), insert_fromFile() a insert_random().
*/
class BinaryTree {
private:
	//! Koren stromu
	node* root;

	//! Dynamicka promenna, ktera obsahuje prvky podle pater. 
	/*!	Vektor (patro) vektoru (prvky v patre), ktery se rozsiruje a vyplnuje daty pomoci metody create_table(). 
	*	Tato vektorova struktura se pouziva jako databaze prvku rozdelenych podle pater.
	*/
	vector<vector<int>> table;

	
	int treeDepth;	//!< Hloubka stromu
	int	treeWidth;	//!< Sirka stromu

	
	void destroy_tree(node* leaf);		//!< Rekurzivni cast metody pro korektni mazani prvku
	void insert(int key, node* leaf);	//!< Rekurzivni cast metody vkládání prvku do stromu
	void traverse_inorder(node* leaf);	//!< Rekurzivnì projde strom metodou inorder a zaroven prida prvky do databaze pater (table)

	//! Aktualizuje patrovou tabulku (databaze pozic)
	/*!	Pri zavolani upravi velikosti tabulkových vektoru podle nejaktualnejsiho velikosti, a postupne 
	*	se pomoci rekurze nasklada do kazdeho patra prvky. Algoritmus zaroven pøepocitava maximalní sirku stromu. 
	*	Tato metoda MUSI byt manualne volana kdykoliv bude program chtit vyuzit nejaktualnejsi atributy stromu treeWidth.
	*/
	void create_treeTable();			

public:
	BinaryTree();
	~BinaryTree();

	void insert(int key);		//!< Verejna spousteci metoda pro privatni metodu insert()
	void destroy_tree();		//!< Verejna spousteci metoda pro privatni metodu destroy_tree()
	void traverse_inorder();	//!< Verejna spousteci metoda pro privatni metodu traverse_inorder()

	void print_treeTable();				//!< Vykresli tabulku s jednotlivymi patry, a jejich prvky. Rudou barvou oznacuje nejsirsi patra
	void insert_fromFile(string path);	//!< Vola insert() pro každý prvek z nacteneho souboru
	void insert_random(int n, int max);	//!< Debugovaci pomocna funkce, ktera generuje 'n'-pocet nahodnych cisel v intervalu 0 - 'max'
};


