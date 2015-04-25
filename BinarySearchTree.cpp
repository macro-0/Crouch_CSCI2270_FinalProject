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
}

BinarySearchTree::~BinarySearchTree() {
	deleteAll(root);
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

void BinarySearchTree::findDataNode(std::string commonName) {
	dataNode* x = searchBSTTree(root, commonName);
	if (x == NULL) {
		cout << "data not found" << endl;
	} else {
		cout << "data information: " << endl;
		printNode(x);
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

void BinarySearchTree::printTree(dataNode *node) {
	if (node == NULL) {
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

dataNode* BinarySearchTree::searchBSTTree(dataNode *node, std::string in_commonName) {
	if (node == NULL) {
		return NULL;
	} else if (node->commonName == in_commonName) {
		return node;
	} else {
		if (in_commonName.compare(node->commonName) < 0) {
			return searchBSTTree(node->left, in_commonName);
		} else {
			return searchBSTTree(node->right, in_commonName);
		}
	}
}


