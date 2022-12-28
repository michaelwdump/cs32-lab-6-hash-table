// WordCount.cpp
#include <sstream>

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {
	// for (int i=0; i < CAPACITY; ++i) {
	// 	table[i] = vector<pair<"EMPTY", 0>>;
	// }
}

// Simple hash function. Do not modify.
size_t WordCount::hash(const std::string & word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i); //adds ascii value of char
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	//for every elem, for every vector int, sum up the ints and then sum up those sums
	int sum = 0;

	for (unsigned int i=0; i < CAPACITY; ++i) {
		int subSum = 0;
		//iterating inside vector to increment subSum
		for (unsigned int j=0; j<table[i].size(); ++j) {
			subSum += table[i].at(j).second;
		}
		sum += subSum;
	}
	return sum;
}

int WordCount::getNumUniqueWords() const {
	int sum = 0;
	for (unsigned int i=0; i < CAPACITY; ++i) {
		sum += table[i].size();
	}
	return sum;
}

int WordCount::getWordCount(const std::string & word) const {
	string word1 = this->makeValidWord(word);


	//TODO: is chained hashing supposed to have a runtime of O(n)?
	for (unsigned int i=0; i < table[hash(word1)].size(); ++i) {
		if (table[hash(word1)].at(i).first == word1) {
			return table[hash(word1)].at(i).second;
		}
	}

	
	return 0;
}
	
int WordCount::incrWordCount(const std::string & word) {
	string word1 = this->makeValidWord(word); 
	if (word1 == "") return 0;
	//if valid word

	//valid, new word
	if (table[hash(word1)].size() == 0) {
			//empyt vector at hash
			std::pair<std::string, int> newWord (word1, 1);
			table[hash(word1)].push_back(newWord);
			return table[hash(word1)].at(0).second;
	}
	//valid word with existing hash
	else {
		//cout << "size: " << table[hash(word1)].size() << endl;
		for (unsigned int i=0; i < table[hash(word1)].size(); ++i) {
			//existing vector at hash
			if (table[hash(word1)].at(i).first == word1) {

				table[hash(word1)].at(i).second +=1;
				return table[hash(word1)].at(i).second;
			}
			//same hash, but diff new word

		}
			std::pair<std::string, int> newWord (word1, 1);
			table[hash(word1)].push_back(newWord);
			//cout << table[hash(word1)].at(i).second << endl; //DELE
			return table[hash(word1)].back().second;
	}
	return 0;
}

int WordCount::decrWordCount(const std::string & word) {
	string word1 = this->makeValidWord(word); 

	if (table[hash(word1)].size() <= 0) {
			//new word
			return -1;
	}
	else {
		for (unsigned int i=0; i < table[hash(word1)].size(); ++i) {
			//exisiting word
			if (table[hash(word1)].at(i).first == word1) {
				table[hash(word1)].at(i).second -=1;
				if (table[hash(word1)].at(i).second == 0) {
					table[hash(word1)].erase(table[hash(word1)].begin()+i);
					return 0;
				}
				return table[hash(word1)].at(i).second;
			}
		}
	}
	return 0;

}

bool WordCount::isWordChar(char c) {

	char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	vector<char> alphabet( alpha, alpha+sizeof(alpha)-1 );

	for (unsigned int i=0; i < alphabet.size(); ++i) {
		if (c == alphabet.at(i)) { 
			return true;
		}
	}
	return false;
}

std::string WordCount::makeValidWord(const std::string & word) {
	string word1 = "";
	//use true/false statements and don't erase from input word; it
	for (unsigned int i=0; i < word.size(); ++i) {
		char charWord = word[i];
		if (isWordChar(charWord)) {
			word1 += tolower(charWord);
			}
		//delete edge specials, keep specials between letters
	 	if (charWord == '\'' || charWord == '-') {
			//cout << "special char dectected at index: " << i << endl;
			bool before = false;
			bool after = false;
			for (unsigned int j =i; j < word.size(); ++j) {
				char charWordAfter = word[j];
				// cout << "word after: " << charWordAfter << endl;
				if (isWordChar(charWordAfter)) {
					// cout << "WORDAFTER TRUE!" << endl;
					after = true;
					break;
				}
			}
			for (int k=i; k > -1; --k) { //REMEMBER: if you're checkign all letters in a string, make sure the lowest limit >= 0
				char charWordBefore = word[k];
				// cout << "word before: " << charWordBefore << endl;
				if (isWordChar(charWordBefore)) {
					// cout << "WORDBEFORE TRUE!" << endl;
					before = true;
					break;
				}
			}

			if (after == true && before == true) {
				word1 += charWord;
			}

			}
		}
	return word1;
}












void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	vector<pair<string,int>> temp;
	//is the &out arg a ostream fileld with CSV's in number (alpha if same) order?
	//how do you get get the &out object? do u get a huge paragraph and sort it?
	for (unsigned int i=0; i < CAPACITY; ++i) {
		for (unsigned int j=0; j<table[i].size(); ++j) {
			//cout << "Tyu" << endl;
			temp.push_back(table[i].at(j));
		}
	}

	//sort vector alphabetically in descending order
	size_t largestIndex;
    //Search through array from start for value larger than current max
	// Going from right-to-left because we are finding the largest index first
	for (size_t i = temp.size() - 1; i > 0; i--) {
		largestIndex = 0;
		for (size_t j = 1; j <= i; j++) {
			//cout << "i = " << i << ", j = " << j << endl;
			if (temp[j].first > temp[largestIndex].first) {
				largestIndex = j;
			}
		}
		swap(temp[i], temp[largestIndex]);
	}
	reverse(temp.begin(), temp.end());

	//cout every elem
	for (unsigned int i=0; i<temp.size(); ++i) {
		out << temp[i].first << "," << temp[i].second << endl;
	}

}


void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	vector<pair<string,int>> temp;

	//adding all hash table elems to the temp vector
	for (unsigned int i=0; i < CAPACITY; ++i) {
		for (unsigned int j=0; j<table[i].size(); ++j) {
			//cout << "Tyu" << endl;
			temp.push_back(table[i].at(j));
		}
	}

	//sort vector alphabetically in descending order
	size_t largestIndex;
    //Search through array from start for value larger than current max
	// Going from right-to-left because we are finding the largest index first
	for (size_t i = temp.size() - 1; i > 0; i--) {
		largestIndex = 0;
		for (size_t j = 1; j <= i; j++) {
			//cout << "i = " << i << ", j = " << j << endl;
			if (temp[j].second > temp[largestIndex].second) {
				largestIndex = j;
			}
			//same occurances case
			if (temp[j].second == temp[largestIndex].second) {
				if (temp[j].first > temp[largestIndex].first) {
					largestIndex = j;
				}
			}
		}
		swap(temp[i], temp[largestIndex]);
	}
	//reverse(temp.begin(), temp.end());

	//cout every elem in vector
	for (unsigned int i=0; i<temp.size(); ++i) {
		out << temp[i].first << "," << temp[i].second << endl;
	}
}

void WordCount::addAllWords(const std::string& text) {
	istringstream iss(text);
	while (iss) {
		string word;
		iss >> word;
		incrWordCount(word);
	}
}
