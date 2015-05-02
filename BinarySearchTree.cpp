#include "BinarySearchTree.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// public

BinarySearchTree::BinarySearchTree() {
	root = NULL;
	//ctor
}

BinarySearchTree::~BinarySearchTree() {
	deleteAll(root);
	//dtor
}

void BinarySearchTree::printTree() {
	printTree(root);
	return;
}

void BinarySearchTree::addDataNode(string in_commonName, string in_sciName, string in_phenophase, int in_elevation, int in_siteID, string in_date, int count) {
	dataNode *newNode = new dataNode (in_commonName, in_sciName, in_phenophase, in_elevation, in_siteID, in_date, count);
	if (root == NULL) {
		root = newNode;
		newNode->parent = NULL;
		newNode->count++;
	} else {
		dataNode *x = root;
		dataNode *y = NULL;
		while (x != NULL) {
			y = x;
			if (newNode->commonName.compare(x->commonName) < 0) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		if (newNode->commonName != y->commonName) {
			newNode->parent = y;
			newNode->count = 1;
			if (newNode->commonName.compare(y->commonName) < 0) {
				y->left = newNode;
			} else {
				y->right = newNode;
			}
		} else {  // sighting of same animal/plant
			y->count++;
			y->phenophase.push_back(in_phenophase);
			y->elevation.push_back(in_elevation);
			y->siteID.push_back(in_siteID);
			y->date.push_back(in_date);
		}	
	}
	return;
}

void BinarySearchTree::findDataNode(string commonName) {
	dataNode* x = searchBSTree(root, commonName);
	if (x == NULL) {
		cout << "data not found" << endl;
	} else {
		cout << "data information: " << endl;
		printNode(x);
	}
}

void BinarySearchTree::deleteDataNode(string commonName) {
	dataNode *x = searchBSTree(root, commonName);
	if (x) {
		if (x->parent != NULL) {
			if ((x->left == NULL) && (x->right == NULL)) {  // no children
				if (x->parent->left == x) {
					x->parent->left = NULL;
				} else {
					x->parent->right = NULL;
				}
				delete x;
			} else if ((x->left != NULL) && (x->right == NULL)) {  // left child only
				if (x->parent->left == x) {
					x->parent->left = x->left;
				} else {
					x->parent->right = x->left;
				}
				x->left->parent = x->parent;
				delete x;
			} else if ((x->left == NULL) && (x->right == NULL)) {  // right child only
				if (x->parent->left == x) {
					x->parent->left = x->right;
				} else {
					x->parent->right = x->right;
				}
				x->right->parent = x->parent;
				delete x;
			} else {  // both left and right children
				dataNode *replace = x->right;
				while (replace->left != NULL) {
					replace = replace->left;
				}
				x->commonName = replace->commonName;
				x->sciName = replace->sciName;
				for (int i = 0; i < replace->count; i++) {
					 x->phenophase[i] = replace->phenophase[i];
					 x->elevation[i] = replace->elevation[i];
					 x->siteID[i] = replace->siteID[i];
					 x->date[i] = replace->date[i];
				}
				x->count = replace->count;
				if (replace->left != NULL) {
					replace->right->parent = replace->parent;
				}
				if (replace->parent->left == replace) {
					replace->parent->left = replace->right;
				} else {
					replace->parent->right = replace->right;
				}
			}
		} else {  // x->parent = NULL; x is the root
			if (x->right == NULL && x->left == NULL) {
				root = NULL;
				delete x;
			} else {
				dataNode *replace = x;
				if (x->left != NULL && x->right == NULL) {  // no nodes to right of root
					replace = x->left;
					if (replace->right == NULL) {
						replace->parent = NULL;
						root = replace;
					} else {
						while (replace->right != NULL) {
							replace = replace->right;  // maximum node in left subtree
						}
						if (replace->left == NULL) {
							replace->parent->right = NULL;
							replace->left = x->left;
							x->left->parent = replace;
							replace->parent = NULL;
							root = replace;
						} else {
							replace->parent->right = replace->left;
							replace->left->parent = replace->parent;
							replace->left = x->left;
							x->left->parent = replace;
							replace->parent = NULL;
							root = replace;
						}
					}
					delete x;
					
				} else if (x->right != NULL && x->left == NULL) {  // no nodes to left of root
					if (replace->left == NULL) {
						replace->parent = NULL;
						root = replace;
					} else {
						while (replace->left != NULL) {
							replace = replace->left;  // minimum node in left subtree
						}
						if (replace->right == NULL) {
							replace->parent->left = NULL;
							replace->right = x->right;
							x->right->parent = replace;
							replace->parent = NULL;
							root = replace;
						} else {
							replace->parent->left = replace->right;
							replace->right->parent = replace->parent;
							replace->right = x->right;
							x->right->parent = replace;
							replace->parent = NULL;
							root = replace;
						}
					}
					delete x;
					
				} else {  // nodes to both sides, replace w/ maximum node on left
					replace = x->left;
					if (replace->right == NULL) {
						replace->right = x->right;
						x->right->parent = replace;
						replace->parent = NULL;
						root = replace;
					} else {
						while (replace->right != NULL) {
							replace = replace->right;
						}
						if (replace->left == NULL) {
							replace->parent->right = NULL;
							replace->left = x->left;
							x->left->parent = replace;
							replace->right = x->right;
							x->right->parent = replace;
							replace->parent = NULL;
							root = replace;
						} else {
							replace->parent->right = replace->left;
							replace->left->parent = replace->parent;
							replace->left = x->left;
							x->left->parent = replace;
							replace->parent = NULL;
							replace->right = x->right;
							x->right->parent = replace;
							replace->parent = NULL;
							root = replace;
						}
					delete x;
					}
				}
			}
		}
	} else {
		cout << "data not found" << endl;
	}
}


// private

void BinarySearchTree::deleteAll(dataNode *node) {
	if (node == NULL) {
		return;
	} else {
		if (node->left != NULL) {
			deleteAll(node->left);
		}
		if (node->right != NULL) {
			deleteAll(node->right);
		}
		delete node;
	}
	return;
}

/*
 * Prototype: void BinarySearchTree::printTree(dataNode *node);
 * Description: This method does an in-order traversal of the tree in order
 * 		to print each node to the terminal. Handles empty-tree case (no data 
 * 		nodes).
*/

void BinarySearchTree::printTree(dataNode *node) {
	if (!node) {
		cout << "no nodes in tree" << endl;
		return;
	} else {
		if (node->left != NULL) {
			printTree(node->left);
		}
		printNode(node);
		if (node->right != NULL) {
			printTree(node->right);
		}
		return;
	}
}

void BinarySearchTree::printNode(dataNode *node) {
	cout << "Common name: " << node->commonName << endl;
	cout << "Scientific name: " << node->sciName << endl;
	cout << "Number of records: " << node->count << endl;
	cout << "Site ID(s): ";
	for (unsigned int i = 0; i < (node->siteID).size()-1; i++) {
		cout << node->siteID[i] << ", ";
	} cout << node->siteID[node->siteID.size()-1] << endl;
}

dataNode* BinarySearchTree::searchBSTree(dataNode *node, std::string in_commonName) {
	if (node == NULL) {
		return NULL;
	} else if (node->commonName == in_commonName) {
		return node;
	} else {
		if (in_commonName.compare(node->commonName) < 0) {
			return searchBSTree(node->left, in_commonName);
		} else {
			return searchBSTree(node->right, in_commonName);
		}
	}
}


