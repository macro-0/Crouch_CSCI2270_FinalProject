#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>  // stringstream
#include <string.h>  // compare
#include <algorithm>  // transform
#include "BinarySearchTree.h"
#include "RedBlackTree.h"

// todo: search either by scientific name or by common name
// todo: add functions to allow user to completely clear current tree
// todo: typecheck/other solution to stop menu crash
// todo: enable user to delete specific records of a sighting without deleting the node
// todo: enable user to add multiple records at once, ex. more than one sighting of common lilac at different elevations and sites

using namespace std;

void printMenu();
void readIn(BinarySearchTree *bst, char *filename);
void readIn(RedBlackTree *rb, char *filename);

int main(int argc, char* argv[]) {
	
	string tree_choice = "";
	string str_choice = "";
	int choice = -1;
	bool quit = false;
	
	string commonName = "";
	string sciName = "";
	string phenophase = "";
	string str_elevation = "";
	int elevation = 0;
	string str_siteID = "";
	int siteID = 0;
	string date = "";
	
	while (!quit) {
		cout << "Please enter which type of tree you would like to build: (u)nbalanced or (r)ed-black, or (q)uit: " << endl;
		getline(cin, tree_choice);
		if (tree_choice == "u") {
			bool bstQuit = false;
			cout << "You have chosen: unbalanced BST" << endl;
			BinarySearchTree *bst = new BinarySearchTree();
			readIn(bst, argv[1]); 
			while (!bstQuit) {
				printMenu();
				getline(cin, str_choice);
				choice = stoi(str_choice);
				switch(choice) {
					case 1:
						bst->printTree();
						break;
					case 2:
						cout << "enter common name: " << endl;
						getline(cin, commonName);
						transform(commonName.begin(), commonName.end(), commonName.begin(), ::tolower);  // method from http://blog.fourthwoods.com/2013/12/10/convert-c-string-to-lower-case-or-upper-case/
						cout << "enter scientific name: " << endl;
						getline(cin, sciName);
						cout << "enter phenophase: " << endl;
						getline(cin, phenophase);
						cout << "enter elevation in meters: " << endl;
						getline(cin, str_elevation);
						elevation = atoi(str_elevation.c_str());
						cout << "enter site ID: " << endl;
						getline(cin, str_siteID);
						siteID = atoi(str_siteID.c_str());
						cout << "enter date as MMDDYYYY: " << endl;
						getline(cin, date);
						bst->addDataNode(commonName, sciName, phenophase, elevation, siteID, date, 1);
						break;
					case 3:
						cout << "enter common name: " << endl;
						getline(cin, commonName);
						bst->findDataNode(commonName);
						break;
					case 4:
						cout << "enter common name: " << endl;
						getline(cin, commonName);
						bst->deleteDataNode(commonName);
						break;
					case 5:
						bstQuit = true;
						break;
					default:
						cout << "invalid input, please try again" << endl;
						break;
				}
			}
		} else if (tree_choice == "r") { 
			bool rbQuit = false;
			cout << "You have chosen: red-black BST" << endl;
			RedBlackTree *rb = new RedBlackTree();
			readIn(rb, argv[1]);
			 
			while (!rbQuit) {
				printMenu();
				getline(cin, str_choice);
				choice = stoi(str_choice);
				switch(choice) {
					case 1:
						rb->printTree();
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						rbQuit = true;
						break;
					default:
						cout << "invalid input, please try again" << endl;
						break;
				}
			}
				
		//} else if (tree_choice == "a") {
		} else if (tree_choice == "q") {
			cout << "Goodbye!" << endl;
			quit = true;
		} else {
			cout << "invalid input, please try again" << endl;
		}
	}	
	return 0;
}

void printMenu() {
	cout << "*****Menu*****" << endl;
	cout << "1: print tree" << endl;
	cout << "2: add data" << endl;
	cout << "3: find data" << endl;
	cout << "4. delete data" << endl;
	cout << "5: exit to main menu" << endl;
}

void readIn(BinarySearchTree *bst, char *filename) {
	ifstream infile(filename);
	cout << filename << endl;
	
	if (infile.is_open()) {
		vector<string> attributes;  // pull attributes from first line
		string line;
		string attribute;
		getline(infile, line);
		stringstream ss(line);
		while (getline(ss, attribute, ',')) {
			attributes.push_back(attribute);  // vector of record types 
		}
		
		string commonName = "";
		string sciName = "";
		string in_date = "";
		
		while (infile) {
			vector<string> data;  // pull attributes from first line
			getline(infile, line);
			if (line != "") {  // last line from txt file is blank
				stringstream ss(line);
				string datum;
				while (getline(ss, datum, ',')) {
					data.push_back(datum);  // vector of animal/plant data
				}
				
				commonName = data[8];
				transform(commonName.begin(), commonName.end(), commonName.begin(), ::tolower);
				
				sciName = data[6] + " " + data[7];  // sciName = "genus" + " " + "species"
				if (atoi(data[13].c_str()) < 10) {  // format date
					in_date += "0";
				}
				in_date += data[13] + data[14] + data[12]; 
								
				//bst->addDataNode(commonName, sciName, phenophase, elevation, siteID, date, count);
				bst->addDataNode(commonName, sciName, data[11], atoi(data[3].c_str()), atoi(data[0].c_str()), in_date, 0);
				in_date = "";  // reset
			}	
		}
		infile.close();
		
	} else {
		cout << "Error opening infile, please check CLA" << endl;
	}
}


void readIn(RedBlackTree *rb, char *filename) {
	ifstream infile(filename);
	cout << filename << endl;
	
	if (infile.is_open()) {
		vector<string> attributes;  // pull attributes from first line
		string line;
		string attribute;
		getline(infile, line);
		stringstream ss(line);
		while (getline(ss, attribute, ',')) {
			attributes.push_back(attribute);  // vector of record types 
		}
		
		string commonName = "";
		string sciName = "";
		string in_date = "";
		
		while (infile) {
			vector<string> data;  // pull attributes from first line
			getline(infile, line);
			if (line != "") {  // last line from txt file is blank
				stringstream ss(line);
				string datum;
				while (getline(ss, datum, ',')) {
					data.push_back(datum);  // vector of animal/plant data
				}
				
				commonName = data[8];
				transform(commonName.begin(), commonName.end(), commonName.begin(), ::tolower);
				
				sciName = data[6] + " " + data[7];  // sciName = "genus" + " " + "species"
				if (atoi(data[13].c_str()) < 10) {  // format date
					in_date += "0";
				}
				in_date += data[13] + data[14] + data[12]; 
				//bst->addDataNode(commonName, sciName, phenophase, elevation, siteID, date, count);
				rb->addDataNode(commonName, sciName, data[11], atoi(data[3].c_str()), atoi(data[0].c_str()), in_date, 0);
				in_date = "";  // reset
			}	
		}
		infile.close();
		
	} else {
		cout << "Error opening infile, please check CLA" << endl;
	}
}
