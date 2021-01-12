#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>

// Other cpp files needs to be excluded from the project

#ifndef BINARY_TREE
#include "Binary_Tree_by_Baran_Cimen.h"
#endif


#ifndef HASH_TABLE
#include "Hash_Table_by_Baran_Cimen.h"
#endif


void ToLower(std::string & s)
// postcondition: s all lower case     
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = tolower(s[k]);
    }
}



int main() {
	
	HashTable<WordItem> table(WordItem(""));
	BinaryTree<std::string, WordItem *> myTree(NULL);

	int numOfFiles;
	std::cout << "Enter number of input files: ";
	std::cin >> numOfFiles;
	std::vector<std::string> fileNames(numOfFiles);
	std::string fileName;




	for(int i=1; i<numOfFiles+1; i++) {
		std::cout << "Enter " << i << ". file name: "; 
		std::cin >> fileName;
		fileNames[i-1] = fileName;
	}


	// PreProcess Files
	for(int i=0; i<numOfFiles; i++) {
		fileName = fileNames[i];
	
		std::ifstream file;
		file.open(fileName.c_str());
		std::string word;
		std::string tempWord = "";
		while(file >> word) { 
			ToLower(word);
			bool check = (true && (word.length() != 0)); // check if all alphabetic
			for(unsigned int j=0; j< word.length(); j++) {
				if('a' > word.at(j) || 'z' < word.at(j)) { //!isalpha(word.at(j))
					// A word is complete

					// BST
					WordItem * temp = myTree.find(tempWord);
					if(temp == NULL) { // if word doesn't exist
						myTree.insert(tempWord); // add the word to the tree
						temp = myTree.find(tempWord);
					} 

					bool check2 = false; // is found
					for(unsigned int j=0; j < temp->store.size(); j++) {
						if(temp->store.at(j).documentName == fileName) {
							temp->store.at(j).count++;
							check2 = true;
							break;
						}
					}
					if(!check2) { // if not found
						temp->store.push_back( DocumentItem(fileName, 1));
					}

					// Hashtable

					WordItem * temp2 = table.find(WordItem(tempWord));
					if(temp2->word == "") { // Doesn't exist
						table.insert(WordItem(tempWord));
						temp2 = table.find(WordItem(tempWord));
					}


					bool check3 = false; // is found
					for(unsigned int j=0; j < temp2->store.size(); j++) {
						if(temp2->store.at(j).documentName == fileName) {
							temp2->store.at(j).count++;
							check3 = true;
							break;
						}
					}
					if(!check3) { // if not found
						temp2->store.push_back( DocumentItem(fileName, 1));
					}



					tempWord = "";
				}
				else {
					tempWord += word.at(j);
				}
			}
			if(tempWord.length() != 0) { // last word at the line

				// BST

				WordItem * temp = myTree.find(tempWord);
				if(temp == NULL) { // if word doesn't exist
					myTree.insert(tempWord); // add the word to the tree
					temp = myTree.find(tempWord);
				} 
				bool check2 = false; // is found
				for(unsigned int j=0; j < temp->store.size(); j++) {
					if(temp->store.at(j).documentName == fileName) {
						temp->store.at(j).count++;
						check2 = true;
						break;
					}
				}
				if(!check2) { // if not found
					temp->store.push_back( DocumentItem(fileName, 1));
				}

				// Hashtable

				WordItem * temp2 = table.find(WordItem(tempWord));
				if(temp2->word == "") { // Doesn't exist
					table.insert(WordItem(tempWord));
					temp2 = table.find(WordItem(tempWord));
				}


				bool check3 = false; // is found
				for(unsigned int j=0; j < temp2->store.size(); j++) {
					if(temp2->store.at(j).documentName == fileName) {
						temp2->store.at(j).count++;
						check3 = true;
						break;
					}
				}
				if(!check3) { // if not found
					temp2->store.push_back( DocumentItem(fileName, 1));
				}

				tempWord = "";
			}
		}
		file.close();
	}




	//// HASHTABLE
	//for(int i=0; i<numOfFiles; i++) {
	//	fileName = fileNames[0];

	//	std::ifstream file;
	//	file.open(fileName.c_str());
	//	std::string word;
	//	std::string tempWord = "";
	//	while(file >> word) { 
	//		ToLower(word);
	//		bool check = (true && (word.length() != 0)); // check if all alphabetic
	//		for(unsigned int j=0; j< word.length(); j++) {
	//			if('a' > word.at(j) || 'z' < word.at(j))  { //!isalpha(word.at(j))
	//				
	//				WordItem temp2 = table.find(WordItem(tempWord));
	//				if(temp2->word == "") { // Doesn't exist
	//					table.insert(WordItem(tempWord, fileName));
	//					temp2 = table.find(WordItem(tempWord));
	//				}


	//				bool check3 = false; // is found
	//				for(unsigned int j=0; j < temp2->store.size(); j++) {
	//					if(temp2->store.at(j).documentName == fileName) {
	//						temp2->store.at(j).count++;
	//						check3 = true;
	//						break;
	//					}
	//				}
	//				if(!check3) { // if not found
	//					temp2->store.push_back( DocumentItem(fileName, 1));
	//				}
	//				tempWord = "";
	//			}
	//			else {
	//				tempWord += word.at(j);
	//			}
	//		}
	//	}
	//	file.close();
	//}

	table.preprocessPrint();
	
	std::cout << "Enter queried words in one line: "; 
	std::string line;
	std::vector<std::string> inputs;
	std::cin.ignore();
	std::getline(std::cin,line);
	ToLower(line);
	unsigned int length = line.length();
	std::string tempWord = "";
	for(unsigned int i=0; i<length; i++) {
		if('a' > line.at(i) || 'z' < line.at(i)) {
			if(tempWord.length() != 0) {
				inputs.push_back(tempWord);
				tempWord = "";
			}
		}
		else {
			tempWord += line.at(i);
		}
	}
	if(tempWord.length() != 0) {
		inputs.push_back(tempWord);
	}

	unsigned int inputsLength = inputs.size();

	bool isAllFound = true;

	int k = 20;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
	// QueryDocuments(with BST);
		std::vector<std::string> outputs;
		for(unsigned int j=0; j < numOfFiles; j++) {
			outputs.push_back("in Document " + fileNames[j]);
		}
		std::vector<int> countedWords(outputs.size(),0);

		for(unsigned int j=0; j < inputsLength; j++) {


			WordItem * temp = myTree.find(inputs[j]);
			if(temp != NULL ) {
				for(unsigned int k=0; k < temp->store.size(); k++) {
					for(unsigned int l=0; l < numOfFiles; l++) {
						if(temp->store[k].documentName == fileNames[l]) {
							outputs[l] += ( ", " + temp->word + " found " + std::to_string(temp->store[k].count) + " times");
							countedWords[l]++;
							break;
						}
					}	
				}
			}
			else { // a word is not found in any file
				isAllFound = false;
			}
		}
		if(k==i+1) { 
			bool ShouldPrint = true;
			for(unsigned int j=0; j < numOfFiles; j++) {
				if(countedWords[j] == inputsLength) {
					ShouldPrint = false;
				}
			}
			if(!isAllFound || ShouldPrint) {
				std::cout << "No document contains the given query" << std::endl;
			}
			else {
				for(unsigned int j=0; j < numOfFiles; j++) {
					outputs[j] += ".";
					if(outputs[j].substr(outputs[j].length()-6,6) == "times." && countedWords[j] == inputsLength) {
						std::cout << outputs[j] << std::endl;
					}
				}
			}
		}
		
	}

	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	(std::chrono::high_resolution_clock::now() - start);
	std::cout << "\nTime: " << BSTTime.count() / k << "\n";
	start = std::chrono::high_resolution_clock::now();

	bool isAllFound2 = true;


	for (int i = 0; i < k; i++)
	{
	// QueryDocuments (with hashtable);
		std::vector<std::string> outputs;
		for(unsigned int j=0; j < numOfFiles; j++) {
			outputs.push_back("in Document " + fileNames[j]);
		}
		
		std::vector<int> countedWords(outputs.size(),0);

		for(unsigned int j=0; j < inputsLength; j++) {
			WordItem * temp = table.find(inputs[j]);
			if(temp->word != "") {
				for(unsigned int k=0; k < temp->store.size(); k++) {
					for(unsigned int l=0; l < numOfFiles; l++) {
						if(temp->store[k].documentName == fileNames[l]) {
							outputs[l] += ( ", " + temp->word + " found " + std::to_string(temp->store[k].count) + " times");
							countedWords[l]++;
							break;
						}
					}	
				}
			}
			else {
				isAllFound2 = false;
			}
		}
		if(k==i+1) {
			bool ShouldPrint = true;
			for(unsigned int j=0; j < numOfFiles; j++) {
				if(countedWords[j] == inputsLength) {
					ShouldPrint = false;
				}
			}
			if(!isAllFound2 || ShouldPrint) {
				std::cout << "No document contains the given query" << std::endl;
			}
			else {
				for(unsigned int j=0; j < numOfFiles; j++) {
					outputs[j] += ".";
					if(outputs[j].substr(outputs[j].length()-6,6) == "times." && countedWords[j] == inputsLength) {
						std::cout << outputs[j] << std::endl;
					}
				}
			}
		}
		
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	(std::chrono::high_resolution_clock::now() - start);
	std::cout << "\nTime: " << HTTime.count() / k << "\n";

	double speed = (double)BSTTime.count() / (double)HTTime.count();
	std::cout << "Speed Up: " << speed << std::endl;


	return 0;
};