#pragma  once
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>

using namespace std;

#define MAX_SCORE 150

#define LOWER_NGRAM_LEN	2
#define UPPER_NGRAM_LEN	5
//Довжина профілів категорій текстів, що розпізнаються
#define CATEGORY_LEN 1000

using frequency_map = vector<pair<string, int>>;

class TextClassifier
{
public:
	/* Nameof category defaults to 'Unknown.' */
	TextClassifier() { _category = "unknown"; };
	~TextClassifier() {};
	/*Param classification – name of the category (e.g., "English").    */
	TextClassifier(const string category) { _category = category; };
	/* returns the map N-grams and their frequencies.     */
	frequency_map freqs() const { return _frequencyMap; }
	/* returns the name of the classifier.*/
	string getCategory() const { return _category; }
	/*Param classification – name of the category.*/
	void setCategory(const string& cat) { _category = cat; }
	/*learns the frequencies of N-grams in a corpus.*/
	void learn(istream& in);
	/*dumps the frequencies of N-grams in a corpus.
	File structure is as follows:
	* line which starts with s - classification
	* lines with N-grams start with n  and contain
	* N-gram and it squantity separated with space or tab*/
	void dumpProfile(ostream& out) const;
	/*learns the frequencies of N-grams from a file createdby.
	dumpProfile() function */
	void learnFromDump(istream& in);
	/*returns distance measure between 2 TextСlassifiers*/
	long int score(const TextClassifier& classifier) const;

private:
	vector<string> makeNGrams(const string& str);
	string _category;
	frequency_map _frequencyMap;
};

