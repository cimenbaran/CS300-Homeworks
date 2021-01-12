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

template<class Obj>
void swap(Obj & a, Obj & b) {
	Obj temp = a;
	a=b;
	b=temp;
}

// InsertionSort
template<class Obj>
void InsertionSort(std::vector<Obj> & vec) {
	int i;
	
	for(unsigned int j=1; j < vec.size(); j++) {
		Obj temp = vec[j];
		for(i=j; i>0 && temp < vec[i-1]; i--) {
			vec[i] = vec[i-1];
		}
		vec[i] = temp;
	}
}

// QuickSort
template<class Obj>
void QuickSort(std::vector<Obj> & vec) {
	QuickSort(vec, 0, vec.size()-1);
}

template<class Obj>
const Obj & median3(std::vector<Obj> & vec, int left, int right) {
	int center = (left + right) / 2;
	if(vec[center] < vec[left]) {
		swap(vec[left], vec[center]);
	}
	if(vec[right] < vec[left]) {
		swap(vec[left], vec[right]);
	}
	if(vec[right] < vec[center]) {
		swap(vec[center], vec[right]);
	}
	swap(vec[center], vec[right-1]);
	return vec[right-1];
}

template<class Obj> 
void InsertionSortForQuick(std::vector<Obj> & vec, int left, int right) {
	for(int i=left+1; i<=right; i++) {
		Obj temp = vec[i];
		int j;
		for(j=i; j > left && temp < vec[j-1]; j--) 
			vec[j] = vec[j-1];
		vec[j] = temp;
	}
}

template<class Obj>
void QuickSort(std::vector<Obj> & vec,int left, int right) {
	if(left + 10 <= right) {
		
		Obj pivot = median3(vec, left, right);
		
		int i = left, j = right-1;
		while(true) {
			while(vec[++i] < pivot) {}
			while(pivot < vec[--j]) {}
			if(i<j) {
				swap(vec[i], vec[j]);
			}
			else {break;}
		}
		swap(vec[i], vec[right-1]);
		QuickSort(vec, left, i-1);
		QuickSort(vec, i+1, right);
	}
	else {
		InsertionSortForQuick(vec, left, right);
	}
}

template<class Obj>
void QuickSort(std::vector<Obj> & vec,int left, int right, int pivot) {
	if(left + 10 <= right) {
		
		int i = left, j = right-1;
		while(true) {
			while(vec[++i] < vec[pivot]) {}
			while(vec[pivot]< vec[--j]) {}
			if(i<j) {
				swap(vec[i], vec[j]);
			}
			else {break;}
		}
		swap(vec[i], vec[right-1]);
		QuickSort(vec, left, i-1);
		QuickSort(vec, i+1, right);
	}
	else {
		InsertionSortForQuick(vec, left, right);
	}
}

// HeapSort
inline int leftChild(int i) {
	return 2*i + 1;
}

template<class Obj>
void PercDown(std::vector<Obj> & vec, int i, int n) {
	int child;
	Obj tmp = vec[i];
	for(; leftChild(i) < n; i = child) {
		child = leftChild(i);
		if(child != n-1 && vec[child] < vec[child+1]) {
			child++;
		}
		if(vec[child] > tmp) {
			vec[i] = vec[child];
		}
		else {
			break;
		}
	}
	vec[i] = tmp;
}

template<class Obj>
void HeapSort(std::vector<Obj> & vec) {
	for(int i=vec.size()/2; i >= 0; i--) {
		PercDown(vec, i, vec.size());
	}

	for(int i=vec.size()-1; i > 0; i--) {
		swap(vec[0], vec[i]);
		PercDown(vec, 0, i);
	}
}

// MergeSort
template<class Obj>
void MergeSort(std::vector<Obj> & vec) {
	std::vector<Obj> tempArray(vec.size());
	MergeSort(vec,tempArray, 0, vec.size()-1);
}

template<class Obj>
void MergeSort(std::vector<Obj> & vec, std::vector<Obj> & tempArray, int left, int right) {
	if(left < right) {
		int center = (left + right )/ 2;
		MergeSort(vec, tempArray, left, center);
		MergeSort(vec, tempArray, center+1, right);
		Merge(vec, tempArray, left, center+1, right);
	}
}

template<class Obj>
void Merge(std::vector<Obj> & vec, std::vector<Obj> & tempArray, int LeftPos, int RightPos, int RightEnd) {
	int LeftEnd = RightPos-1;
	int tempPos = LeftPos;
	int numOfElements = RightEnd - LeftPos +1;

	while(LeftPos <= LeftEnd && RightPos <= RightEnd) {
		if(vec[LeftPos] <= vec[RightPos]) {
			tempArray[tempPos++] = vec[LeftPos++];
		}
		else {
			tempArray[tempPos++] = vec[RightPos++];
		}
	}

	while(LeftPos <= LeftEnd) {
		tempArray[tempPos++] = vec[LeftPos++];
	}
	while(RightPos <= RightEnd) {
		tempArray[tempPos++] = vec[RightPos++];
	}
	
	for(int i=0; i < numOfElements; i++, RightEnd--) {
		vec[RightEnd] = tempArray[RightEnd];
	}
}

template<class Obj>
int BinarySearch(std::vector<Obj> & vec, int left, int right, Obj x, std::string fileName) {
	// returns the number of occurunces
	while(left <= right) {
		int middle = (left + right +1) /2;


		if(vec[middle] == x) {
			int count;
			for(unsigned int j=0; j < vec[middle].store.size(); j++) {
				if(vec[middle].store[j].documentName == fileName) {
					count = vec[middle].store[j].count; 
					return count;
				}
			}

			return 0; // word exist but not in this document
		};


		if(vec[middle] < x) {
			left = middle + 1;
		}
		else {
			right = middle -1;
		}
	}
	return -1;
}

int main() {
	
	HashTable<WordItem> table(WordItem(""));
	BinaryTree<std::string, WordItem *> myTree(NULL);
	
	int numOfFiles;
	std::cout << "Enter number of input files: ";
	std::cin >> numOfFiles;
	std::vector<std::string> fileNames(numOfFiles);
	std::string fileName;

	std::vector<WordItem> mainVector;


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
					// Sorting Vectors
					bool isFound = false;
					for(unsigned int j=0; j < mainVector.size(); j++) {
						if(mainVector[j].word == tempWord) {
							isFound = true;
							bool checkIfExists = false;
							for(unsigned int k=0; k < mainVector[j].store.size(); k++) {
								if(mainVector[j].store[k].documentName == fileName) {
									mainVector[j].store[k].count++;
									checkIfExists = true;
									break;
								}
							}
							if(!checkIfExists) {
								mainVector[j].store.push_back(DocumentItem(fileName, 1));
							}
							isFound = true;
							break;
						}
					}
					if(!isFound) { // If it is the first unique word
						WordItem tempWordItem = WordItem(tempWord);
						tempWordItem.store.push_back(DocumentItem(fileName, 1));
						mainVector.push_back(tempWordItem);
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

				// Sorting Vectors
				bool isFound = false;
				for(unsigned int j=0; j < mainVector.size(); j++) {
					if(mainVector[j].word == tempWord) {
						bool checkIfExists = false;
						for(unsigned int k=0; k < mainVector[j].store.size(); k++) {
							if(mainVector[j].store[k].documentName == fileName) {
								mainVector[j].store[k].count++;
								checkIfExists = true;
								break;
							}
						}
						if(!checkIfExists) {
							mainVector[j].store.push_back(DocumentItem(fileName, 1));
						}
						isFound = true;
						break;

					}
				}
				if(!isFound) { // If it is the first unique word
					WordItem tempWordItem = WordItem(tempWord);
					tempWordItem.store.push_back(DocumentItem(fileName, 1));
					mainVector.push_back(tempWordItem);
				}

				tempWord = "";
			}
		}
		file.close();
	}




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

	



	
	
	// ************************************************************************************************************************************************************************************************************************************************************************************************************
	
	int k = 10; // changed to 10 since 100 takes too long
	clock_t begin_time = clock();
	bool isAllFound = true;
	for (int i = 0; i < k; i++) {
	

	// QueryDocuments with Binary Search Tree

		std::vector<std::string> outputs;
		for(int j=0; j < numOfFiles; j++) {
			outputs.push_back("in Document " + fileNames[j]);
		}
		std::vector<int> countedWords(outputs.size(),0);

		for(unsigned int j=0; j < inputsLength; j++) {


			WordItem * temp = myTree.find(inputs[j]);
			if(temp != NULL ) {
				for(unsigned int k=0; k < temp->store.size(); k++) {
					for(int l=0; l < numOfFiles; l++) {
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
			for(int j=0; j < numOfFiles; j++) {
				if(countedWords[j] == inputsLength) {
					ShouldPrint = false;
				}
			}
			if(!isAllFound || ShouldPrint) {
				std::cout << "No document contains the given query" << std::endl;
			}
			else {
				for(int j=0; j < numOfFiles; j++) {
					outputs[j] += ".";
					if(outputs[j].substr(outputs[j].length()-6,6) == "times." && countedWords[j] == inputsLength) {
						std::cout << outputs[j] << std::endl;
					}
				}
			}
		}
	}
	double endBST = double(clock() - begin_time);
	
	begin_time = clock();

	
	bool isAllFound2 = true;
	for (int i = 0; i < k; i++) {
	// QueryDocuments with Hash Table


		std::vector<std::string> outputs;
		for(int j=0; j < numOfFiles; j++) {
			outputs.push_back("in Document " + fileNames[j]);
		}
		
		std::vector<int> countedWords(outputs.size(),0);

		for(unsigned int j=0; j < inputsLength; j++) {
			WordItem * temp = table.find(inputs[j]);
			if(temp->word != "") {
				for(unsigned int k=0; k < temp->store.size(); k++) {
					for(int l=0; l < numOfFiles; l++) {
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
			for(int j=0; j < numOfFiles; j++) {
				if(countedWords[j] == inputsLength) {
					ShouldPrint = false;
				}
			}
			if(!isAllFound2 || ShouldPrint) {
				std::cout << "No document contains the given query" << std::endl;
			}
			else {
				for(int j=0; j < numOfFiles; j++) {
					outputs[j] += ".";
					if(outputs[j].substr(outputs[j].length()-6,6) == "times." && countedWords[j] == inputsLength) {
						std::cout << outputs[j] << std::endl;
					}
				}
			}
		}
	}
	double endHT = double(clock() - begin_time);


	std::vector<WordItem> tempVec = mainVector;
	QuickSort(tempVec); // We can use any sorting algorithm, doesn't matter

	begin_time = clock();
	bool isAllFound3 = true;
	for (int i = 0; i < k; i++) {
	// QueryDocuments with Binary Search
		std::vector<std::string> outputs;
		for(int j=0; j < numOfFiles; j++) {
			outputs.push_back("in Document " + fileNames[j]);
		}
		
		
		std::vector<int> countedWords(outputs.size(),0);
		for(unsigned int j=0; j < inputsLength; j++) {
			for(int l=0; l < numOfFiles; l++) {
				int count = BinarySearch(tempVec, 0, tempVec.size()-1, WordItem(inputs[j]), fileNames[l]);
				if(count != 0 && count != -1) {
					countedWords[l]++;
					outputs[l] += ( ", " + inputs[j] + " found " + std::to_string(count) + " times");
				}
				else if (count == -1) { // word not found
					isAllFound3 = false;
				}
			}
		}

		if(k==i+1) {
			bool ShouldPrint = true;
			for(int j=0; j < numOfFiles; j++) {
				if(countedWords[j] == inputsLength) {
					ShouldPrint = false;
				}
			}
			if(!isAllFound3 || ShouldPrint) {
				std::cout << "No document contains the given query" << std::endl;
			}
			else{
				for(int j=0; j < numOfFiles; j++) {
					outputs[j] += ".";
					if(outputs[j].substr(outputs[j].length()-6,6) == "times." && countedWords[j] == inputsLength) {
						std::cout << outputs[j] << std::endl;
					}
				}
			}
		}
	}
	double endBS = double(clock() - begin_time);
	
	//

	std::vector<WordItem> quickFirst;
	std::vector<WordItem> quickRandom;
	std::vector<WordItem> quickMedian;
	std::vector<WordItem> insertion;
	std::vector<WordItem> merge;
	std::vector<WordItem> heap;

	std::cout << "\nBinary Search Tree Time: " << endBST / k << "\n";
	std::cout << "\nHash Table Time: " << endHT / k << "\n";
	std::cout << "\nBinary Search Time: " << endBS / k << "\n\n";

	begin_time = clock();
	for (int i = 0; i < k; i++) {
		std::vector<WordItem> temp = mainVector;
		QuickSort(temp);
	}
	double endQuickMed = double(clock() - begin_time);
	
	begin_time = clock();
	for (int i = 0; i < k; i++) {
		std::vector<WordItem> temp = mainVector;
		QuickSort(temp, 0,temp.size()-1, rand() % temp.size());
	}
	double endQuickRand = double(clock() - begin_time);

	begin_time = clock();
	for (int i = 0; i < k; i++) {
		std::vector<WordItem> temp = mainVector;
		QuickSort(temp, 0,temp.size()-1, 0);
	}
	double endQuickFirst = double(clock() - begin_time);

	begin_time = clock();
	for (int i = 0; i < k; i++) {
		std::vector<WordItem> temp = mainVector;
		MergeSort(temp);
	}
	double endMerge = double(clock() - begin_time);

	begin_time = clock();
	for (int i = 0; i < k; i++) {
		std::vector<WordItem> temp = mainVector;
		HeapSort(temp);
	}
	double endHeap = double(clock() - begin_time);
	
	begin_time = clock();
	for (int i = 0; i < k; i++) {
		std::vector<WordItem> temp = mainVector;
		InsertionSort(temp);
	}
	double endInsertion = double(clock() - begin_time);

	std::cout << "Quick Sort(median) Time: " << endQuickMed / k << std::endl;
	std::cout << "Quick Sort(random) Time: " << endQuickRand / k<< std::endl;
	std::cout << "Quick Sort(first) Time: " << endQuickFirst / k << std::endl;
	std::cout << "Merge Sort Time: " << endMerge / k << std::endl;
	std::cout << "Heap Sort Time: " << endHeap / k << std::endl;
	std::cout << "Insertion Sort Time: " << endInsertion / k << std::endl << std::endl;

	std::cout << "Speed Up BST/HST: " << endBST/endHT << std::endl;
	std::cout << "Speed Up Merge Sort/Quick Sort(Median): " << endMerge/endQuickMed << std::endl;
	std::cout << "Speed Up Heap Sort/Quick Sort(Median): " << endHeap/endQuickMed << std::endl;
	std::cout << "Speed Up Insertion Sort/Quick Sort(Median): " << endInsertion/endQuickMed << std::endl << std::endl;

	std::cout << "Speed Up Binary Search Tree Time / Binary Search:" << endBST/ endBS << std::endl;
	std::cout << "Speed Up Binary Search / Hash Table Time: " << endBS / endHT << std:: endl << std:: endl;

	return 0;
};