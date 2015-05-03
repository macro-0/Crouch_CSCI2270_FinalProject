#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// public

RedBlackTree::RedBlackTree() {
	nil = new rbNode("NIL", "NIL", "NIL", 0, 0, "NIL", 0);
	nil->isRed = false;
	nil->left = nil;
	nil->right = nil;
	root = nil;
}

RedBlackTree::~RedBlackTree() {
	deleteAll(root);
	delete nil;
}

void RedBlackTree::printTree() {
	printTree(root);
	return;
}

void RedBlackTree::addDataNode(string in_commonName, string in_sciName, string in_phenophase, int in_elevation, int in_siteID, string in_date, int count) {
	rbNode *newNode = new rbNode (in_commonName, in_sciName, in_phenophase, in_elevation, in_siteID, in_date, count);
	newNode->left = nil;
	newNode->right = nil;

	rbNode *x = root;
	rbNode *y = NULL;

	if (root == nil) {
		root = newNode;
		newNode->parent = NULL;
		newNode->count++;
	} else {
		while (x != nil) {
			y = x;
			if (newNode->commonName.compare(x->commonName) < 0) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		if (y != nil && y != NULL) {
			if (newNode->commonName != y->commonName) {
				newNode->parent = y;
				newNode->count = 1;
				if (newNode->commonName.compare(y->commonName) < 0) {
					y->left = newNode;
				} else {
					y->right = newNode;
				}
				rbAddFixup(newNode);  // tree is already balanced if animal/plant has been added before
			} else {  // sighting of same animal/plant
				y->count++;
				y->phenophase.push_back(in_phenophase);
				y->elevation.push_back(in_elevation);
				y->siteID.push_back(in_siteID);
				y->date.push_back(in_date);
			}
		}
	}

	return;
}

void RedBlackTree::findDataNode(string commonName) {
	rbNode* x = searchRBTree(root, commonName);
	if (x == nil) {
		cout << "data not found" << endl;
	} else {
		cout << "data information: " << endl;
		printNode(x, true);
	}
	return;
}

void RedBlackTree::deleteDataNode(string commonName) {
	rbNode *z = searchRBTree(root, commonName);
	rbNode *y = z;
	rbNode *x = nil;
	bool yOrigColor = y->isRed;

	if (z->left == nil) {
		x = z->right;
		rbTransplant(z, z->right);  // todo
	} else if (z->right == nil) {
		x = z->left;
		rbTransplant(z, z->right);
	} else {
		y = z->right;
		while (y->left != nil) {
			y = y->left;
		}
		yOrigColor = y->isRed;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		} else {
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rbTransplant(z,y);
		y->left = z->left;
		y->left->parent = y;
		y->isRed = z->isRed;
	}
	delete z;

	if (!yOrigColor) {
		rbDeleteFixup(x);
	}
}


// private

void RedBlackTree::deleteAll(rbNode *node) {
	if (node == nil) {
		return;
	} else {
		if (node->left != nil) {
			deleteAll(node->left);
		}
		if (node->right != nil) {
			deleteAll(node->right);
		}
		delete node;
	}
	return;
}

void RedBlackTree::printTree(rbNode *node) {
	cout << "print" << endl;
	if (node == nil) {
		cout << "no nodes in tree" << endl;
		return;
	} else {
		if (node->left != nil) {
			printTree(node->left);
		}
		printNode(node, false);
		if (node->right != nil) {
			printTree(node->right);
		}
		return;
	}
}

void RedBlackTree::printNode(rbNode *node, bool lookUp) {
	cout << "Common name: " << node->commonName << endl;
	cout << "Scientific name: " << node->sciName << endl;
	cout << "Number of records: " << node->count << endl;
	cout << "Site ID(s): ";
	for (unsigned int i = 0; i < (node->siteID).size()-1; i++) {
		cout << node->siteID[i]<<",";
	} cout << node->siteID[node->siteID.size()-1] << endl;


    if(lookUp){//only an option when the user has searched for a specimen by common name (not when printing entire tree)
        std::string input = "blah";
        while(input != "y" && input != "n"){//loop until user provides valid input
            cout<<"Would you like more information on a site ID? (y)es or (n)o" <<endl;
            std::getline(std::cin, input);
        }

        if(input =="y"){
            std::string ID = " ";

            while(ID.compare(" ") == 0){
                cout<<"What is the site ID?"<<endl;
                getline(std::cin, ID);
            }

            bool found = false;//indicates whether at least one with the same index has been found
            for(unsigned int i=0; i < (node->siteID).size(); i++){
               if(std::to_string(node->siteID[i]).compare(ID)== 0){//change to string to more easily handle invalid user input(e.g. string instead of int)
                    if(!found){//first instance in vector
                        cout<<"Site ID:" << node->siteID[i]<<endl;
                        cout<<"Elevation:" <<node->elevation[i]<<endl;
                        cout<<"----------"<<endl;
                        found = true;
                    }
                    if(node->date[i].length() ==8){
                        cout<<node->date[i].substr(0,2)<<"/"<<node->date[i].substr(2,2)<<"/"<<node->date[i].substr(4,4)<< ": " <<node->phenophase[i]<<endl;
                    }
                    else{
                        cout<<node->date[i].substr(0,2)<<"/"<<node->date[i].substr(2,1)<<"/"<<node->date[i].substr(3,4)<<": " <<node->phenophase[i]<<endl;
                        cout<<"Phenophase:"<<node->phenophase[i]<<endl;

                    }

                }
            }

            if(!found){
                cout<<"Sorry, that ID could not be found" <<endl;
            }

            }
        }
}

rbNode* RedBlackTree::searchRBTree(rbNode *node, std::string in_commonName) {
	if (node == nil) {
		return nil;
	} else if (node->commonName == in_commonName) {
		return node;
	} else {
		if (in_commonName.compare(node->commonName) < 0) {
			return searchRBTree(node->left, in_commonName);
		} else {
			return searchRBTree(node->right, in_commonName);
		}
	}
}

void RedBlackTree::rbAddFixup(rbNode *node) {
	rbNode *uncle = NULL;
	node->left = nil;
	node->right = nil;

	while (node != root && node->parent->isRed) {
			cout << "check" << endl;

		if (node->parent->parent->left == node->parent) {
			uncle = node->parent->parent->right;
			if (uncle->isRed) {
				node->parent->isRed = false;
				uncle->isRed = false;
				node->parent->parent->isRed = true;
				node = node->parent->parent;
			} else {
				if (node->parent->right == node) {
					node = node->parent;
					cout << "working before rotate left" << endl;
					leftRotate(node);
				}
				node->parent->isRed = false;
				node->parent->parent->isRed = true;
				cout << "working before rotate right" << endl;
				rightRotate(node->parent->parent);
			}
		} else {
			uncle = node->parent->parent->left;
			if (uncle->isRed) {
				node->parent->isRed = false;
				uncle->isRed = false;
				node->parent->parent->isRed = true;
				node = node->parent->parent;
			} else {
				if (node->parent->left == node) {
					node = node->parent;
					cout << "working before rotate right 2" << endl;
					rightRotate(node);
				}
				node->parent->isRed = false;
				node->parent->parent->isRed = true;
				cout << "working before left rotate 2" << endl;
				leftRotate(node->parent->parent);
			}
		}
	}
	root->isRed = false;
}

void RedBlackTree::rbDeleteFixup(rbNode *node) {
	rbNode *w = nil;
	while (node != root && node->isRed == false) {
		if (node->parent->left == node) {
			w = node->parent->right;
			if (w->isRed) {
				w->isRed = false;
				node->parent->isRed = true;
				leftRotate(node->parent);
				w = node->parent->right;
			}

			if (!w->left->isRed && !w->right->isRed) {
				w->isRed = true;
				node = node->parent;
			} else {
				if (!w->right->isRed) {
					w->left->isRed = false;
					w->isRed = true;
					rightRotate(w);
					w = node->parent->right;
				}
				w->isRed = node->parent->isRed;
				node->parent->isRed = false;
				w->right->isRed = false;
				leftRotate(node->parent);
				node = root;
			}
		}

		else {
			w = node->parent->right;
			if (w->isRed) {
				w->isRed = false;
				node->parent->isRed = true;
				rightRotate(node->parent);
				w = node->parent->left;
			}

			if (!w->left->isRed && !w->right->isRed) {
				w->isRed = true;
				node = node->parent;
			} else {
				if (!w->left->isRed) {
					w->right->isRed = false;
					w->isRed = true;
					leftRotate(w);
					w = node->parent->left;
				}
				w->isRed = node->parent->isRed;
				node->parent->isRed = false;
				w->left->isRed = false;
				rightRotate(node->parent);
				node = root;
			}
		}
	}
	node->isRed = false;
	return;
}

void RedBlackTree::rbTransplant(rbNode *u, rbNode *v) {
	if (u->parent == nil) {
		root = v;
	} else if (u->parent->left == u) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
	return;
}

void RedBlackTree::leftRotate(rbNode *x) {
	rbNode *y = x->right;
	x->right = y->left;
	if (y->left != nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil) {
		root = y;
	} else {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
	return;
}

void RedBlackTree::rightRotate(rbNode *x) {
	rbNode *y = x->left;
	x->left = y->right;
	if (y->right != nil) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nil) {
		root = y;
	} else {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	}
	y->right = x;
	x->parent = y;
}





