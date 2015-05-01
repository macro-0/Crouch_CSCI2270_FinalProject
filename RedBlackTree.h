#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
#include <vector>

struct rbNode {
	std::string commonName;
	std::string sciName;
	std::vector<std::string> phenophase;
	std::vector<int> elevation;
	std::vector<int> siteID;
	std::vector<std::string> date;
	int count;  // number of times animal/plant has an entry in database
	
	bool isRed;
	rbNode *left;
	rbNode *right;
	rbNode *parent;
	
	rbNode(){};
	
	rbNode (std::string in_commonName, std::string in_sciName, std::string in_phenophase, int in_elevation, int in_siteID, std::string in_date, int count) {
		commonName = in_commonName;
		sciName = in_sciName;
		phenophase.push_back(in_phenophase);
		elevation.push_back(in_elevation);
		siteID.push_back(in_siteID);
		date.push_back(in_date);
		count = 0;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};

class RedBlackTree {
	public:
		RedBlackTree();
		virtual ~RedBlackTree();
		void printTree();
		void addDataNode(std::string in_commonName, std::string in_sciName, std::string in_phenophase, int in_elevation, int in_siteID, std::string in_date, int count);
		void findDataNode(std::string commonName);
		void deleteDataNode(std::string commonName);
		
		
	protected:
	
	private:
		void deleteAll(rbNode *node);  // postorder
		void printTree(rbNode *node);
		void printNode(rbNode *node);
		rbNode* searchRBTree(rbNode *node, std::string commonName);
		void rbAddFixup(rbNode *node);
		void rbDeleteFixup(rbNode *node);
		void rbTransplant(rbNode *u, rbNode *v);
		void leftRotate(rbNode *x);
		void rightRotate(rbNode *x);
		rbNode *root;
		rbNode *nil;
};

#endif  // REDBLACKTREE_H
