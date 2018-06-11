#include<iostream>
#include<fstream>

#include "TextClassifier.h"

using namespace std;

void initClassifier(TextClassifier& classifier) {
	string name = "learn/" + classifier.getCategory() + ".txt";
	string dump = "dump/dump " + classifier.getCategory() + ".txt";

	ifstream fileIn(dump);
	if (fileIn.is_open())
		classifier.learnFromDump(fileIn);
	else {
		fileIn.open(name);
		classifier.learn(fileIn);
		ofstream fileOut(dump);
		classifier.dumpProfile(fileOut);
		fileOut.close();
	}
	fileIn.close();
}

void analyze(TextClassifier& text, vector<TextClassifier>& classifiers) {
	vector<long int> scores;
	
	for (auto it : classifiers)
		scores.push_back(it.score(text));
	
	int min = 0;
	for (int i = 1; i < scores.size(); i++)
		if (scores[i] < scores[min])
			min = i;
	text.setCategory(classifiers[min].getCategory());
}

int main()
{
	vector<TextClassifier> classifiers;
	classifiers.push_back(TextClassifier("english"));
	classifiers.push_back(TextClassifier("italian"));
	classifiers.push_back(TextClassifier("spain"));
	classifiers.push_back(TextClassifier("french"));
	TextClassifier myText("unknown");

	for (auto &it : classifiers)
		initClassifier(it);
	
	string fileName;
	cout << "ENTER THE FILE'S NAME FOR CLASSIFICATION :";
	cin >> fileName;
	ifstream file(fileName);
	
	if (!file.is_open()) {
		cout << "FILE DOESNT EXIST\n";
	}
	else {
		myText.learn(file);
		analyze(myText, classifiers);
		cout << "FILE IS : " << myText.getCategory();
	}	
	getchar();
	getchar();
	return 0;
}

