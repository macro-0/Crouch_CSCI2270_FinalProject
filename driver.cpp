#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "BinarySearchTree.h"

// todo: search either by scientific name or by common name

using namespace std;

void printMenu();
void readIn(BinarySearchTree *bst, char *filename);

int main(int argc, char* argv[]) {
	BinarySearchTree *bst = new BinarySearchTree();
	readIn(bst, argv[1]); 
	string str_choice = "";
	int choice = -1;
	bool quit = false;
	
	string commonName;
	while (!quit) {
		printMenu();
		getline(cin, str_choice);
		choice = stoi(str_choice);
		switch(choice) {
			case 1:
				bst->printTree();
				break;
			case 2:
				break;
			case 3:
				cout << "enter common name: " << endl;
				getline(cin, commonName);
				bst->findDataNode(commonName);
				break;
			case 4:
				quit = true;
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "invalid input, please try again" << endl;
				break;
		}
	}	
	return 0;
}

void printMenu() {
	cout << "*****Menu*****" << endl;
	cout << "1: print tree" << endl;
	cout << "2: add node" << endl;
	cout << "3: find node" << endl;
	cout << "4: quit" << endl;
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
				sciName = data[6] + " " + data[7];  // sciName = "genus" + " " + "species"
				if (atoi(data[13].c_str()) < 10) {  // format date
					in_date += "0";
				}
				in_date += data[13] + data[14] + data[12]; 
								
				//bst->addDataNode(commonName, sciName, phenophase, elevation, siteID, date, count);
				bst->addDataNode(data[8], sciName, data[11], atoi(data[3].c_str()), atoi(data[0].c_str()), in_date, 0);
				in_date = "";  // reset
			}
			
		}
		
		infile.close();
	} else {
		cout << "Error opening infile, please check CLA" << endl;
	}
}
