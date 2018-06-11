#include "TextClassifier.h"
#include<iostream>
#include<cmath>

bool compare(pair<string, int> val1, pair<string, int> val2) {
	return val1.second > val2.second;
}

void TextClassifier::learn(istream& in) {
	const char* SEPARATORS = ".,!?*-+;";
	vector<string> nGrams;
	char wordChar[32];
	map<string, int> nGram_Key;
	while (in >> wordChar) {
		strcpy(wordChar, strtok(wordChar, SEPARATORS));
		string word(wordChar);
		nGrams = makeNGrams(word);

		for (auto it : nGrams) {
			if (nGram_Key.size() >= CATEGORY_LEN) {
				auto nGram = nGram_Key.find(it);
				if (nGram != nGram_Key.end())
					nGram_Key[it]++;
			}
			else
				nGram_Key[it]++;
				
		}
		word.clear();
	}

	for (auto it : nGram_Key) {
		_frequencyMap.push_back(it);
	}

	sort(_frequencyMap.begin(), _frequencyMap.end(), compare);

}
vector<string> TextClassifier::makeNGrams(const string& str) {
	string nGram = "_";
	vector<string> nGrams;
	for (int i = 0; i < str.length() ; i++) {
		for (int j = i ; j < str.length() + UPPER_NGRAM_LEN; j++) {

			if (j < str.length())
				nGram += str[j];
			else
				nGram += "_";

			int size = nGram.length();
			if (size < LOWER_NGRAM_LEN) 
				continue;
			if (size > UPPER_NGRAM_LEN)
				break;
			nGrams.push_back(nGram);	
		}
		nGram.clear();
	}
	return nGrams;
}
void TextClassifier::dumpProfile(ostream& out) const {
	out << _category<<endl;
	for (auto nGram : _frequencyMap) 
		out << nGram.first << " " << nGram.second << endl;
}
void TextClassifier::learnFromDump(istream& in) {
	char category[16];
	in >> category;
	_category = category;
	char nGram[6], nums[6];
	while (in >> nGram && in >> nums) {
		_frequencyMap.push_back(pair<string,int> (nGram,stoi(nums)));
	}
}
long int TextClassifier::score(const TextClassifier& classifier) const {
	bool found = false;
	int score = 0;
	for (int i = 0; i < _frequencyMap.size();i++) {
		for (int j = 0; j < classifier._frequencyMap.size() ; j++) {
			if (_frequencyMap[i].first == classifier._frequencyMap[j].first) {
				found = true;
				score += abs(i - j);
				break;
			}
		}
		if (found == false)
			score += MAX_SCORE;
		found = false;
	}
	return score;
}