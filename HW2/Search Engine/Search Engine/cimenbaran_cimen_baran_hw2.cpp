// Baran Çimen CS300 HW2

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#ifndef AVLTREE
#include "AVLTree_by_Baran_Cimen.h"
#endif


using namespace std;

void ToLower(string & s)
// postcondition: s all lower case     
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = tolower(s[k]);
    }
}




int main() {
	int numOfFiles;
	cout << "Enter number of input files: ";
	cin >> numOfFiles;
	vector<string> fileNames(numOfFiles);
	string fileName;
	AVLTree<string, WordItem *> myTree(NULL);
	for(int i=1; i<numOfFiles+1; i++) {
		cout << "Enter " << i << ". file name: "; 
		cin >> fileName;
		fileNames[i-1] = fileName;
		ifstream file;
		file.open(fileName.c_str());
		string word;
		while(file >> word) {

			ToLower(word);
			bool check = (true && (word.length() != 0)); // check if all alphabetic
			for(unsigned int j=0; j< word.length(); j++) {
				if('a' > word.at(j) || 'z' < word.at(j)) { //!isalpha(word.at(j))
					check = false;
					break;
				}
			}
			if(check) { // if all word is alphabetic
				
				WordItem * temp = myTree.find(word);
				if(temp == NULL) { // if word doesn't exist
					myTree.insert(word); // add the word to the tree
					temp = myTree.find(word);
				} 
				else { // if word exists
					// do nothing
				}
				bool check2 = false; // is found
				for(int j=0; j < temp->store.size(); j++) {
					if(temp->store.at(j).documentName == fileName) {
						temp->store.at(j).count++;
						check2 = true;
						break;
					}
				}
				if(!check2) { // if not found
					temp->store.push_back( DocumentItem(fileName, 1));
				}
			}
			
		}
		file.close();
	}

	string line, word;
	cout << "Enter queried words in one line: ";
	cin.ignore();
	getline(cin, line);
	bool isFoundAny = false;
	for(int i=1; i<numOfFiles+1; i++) {
		fileName = fileNames[i-1];
		istringstream input(line);
		string output = "in Document " + fileName ;
		bool isFound = false;
		while(input >> word) {
			ToLower(word);
			WordItem * temp = myTree.find(word);
			
			if(temp != NULL) { // if such word is in the tree
				for(int j=0; j < temp->store.size(); j++) {
					if(temp->store.at(j).documentName == fileName) {
						output = output + ", " + word + " found " + to_string(temp->store.at(j).count) + " times";
						isFoundAny = true;
						isFound = true;
						break;
					}
				}
			}
		}
		output = output + ".";
		if(isFound) {
			cout << output << endl;
		}
	}
	if(!isFoundAny) {
		cout << "No document contains the given query" << endl;		
	}	
	return 0;
}