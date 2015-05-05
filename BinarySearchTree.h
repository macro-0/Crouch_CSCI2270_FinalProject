#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <vector>

struct dataNode {
	std::string commonName;
	std::string sciName;
	std::vector<std::string> phenophase;
	std::vector<int> elevation;
	std::vector<int> siteID;
	std::vector<std::string> date;
	int count;  // number of times animal/plant has an entry in database

	dataNode *left;
	dataNode *right;
	dataNode *parent;

	dataNode(){};

	dataNode (std::string in_commonName, std::string in_sciName, std::string in_phenophase, int in_elevation, int in_siteID, std::string in_date, int count) {
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

class BinarySearchTree {
	public:
		BinarySearchTree();
		virtual ~BinarySearchTree();
		void printTree();
		void addDataNode(std::string in_commonName, std::string in_sciName, std::string in_phenophase, int in_elevation, int in_siteID, std::string in_date, int count);
		void findDataNode(std::string commonName);
		void deleteDataNode(std::string commonName);

	protected:

	private:
		void deleteAll(dataNode *node);  // postorder
		void printTree(dataNode *node);
		void printNode(dataNode *node, bool lookUp);
		dataNode* searchBSTree(dataNode *node, std::string commonName);
		dataNode *root;
};

#endif  // BINARYSEARCHTREE_H
