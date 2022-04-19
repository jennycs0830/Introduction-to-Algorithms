#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<unordered_set>
#include<algorithm>

using namespace std;

int wordBreak(string s, vector<string> wordDict) {
	unordered_set<string> dict(begin(wordDict), end(wordDict));
	if (dict.size() == 0) {
		return -1;
	}

	int longestWord = 0;
	for (string word : dict) {
		longestWord = max(longestWord, (int)word.size());
	}

	int n = s.size();
	vector<int> dp(n + 1, -1);
	dp[0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = i - 1; j >= max(i - longestWord, 0); j--) {
			if (dp[j] != -1) {
				string word = s.substr(j,i - j);
				if (dict.find(word) != dict.end()) {
					dp[i] = dp[j] + 1;
				}
			}
		}
	}
	return dp[n];
}

int main() {
	ifstream Input;
	ofstream Output;
	Input.open("input.txt");
	Output.open("output.txt");

	int N;
	Input >> N;
	for (int i = 0; i < N; i++) {
		int M;
		Input >> M;
		//construct dictionary
		vector<string> wordDict;
		for (int i = 0; i < M; i++) {
			string word;
			Input >> word;
			wordDict.push_back(word);
		}
		string text;
		Input >> text;
		Output << wordBreak(text, wordDict) << endl;
	}
	return 0;
}