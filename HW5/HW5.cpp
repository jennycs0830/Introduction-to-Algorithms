#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include<set>

using namespace std;

void printtable(map<int, vector<int>>table) {
	cout << "table" << endl;
	for (auto iter = table.begin(); iter != table.end(); iter++) {
		cout << iter->first << " : ";
		for (int i = 0; i < iter->second.size(); i++) {
			cout << iter->second[i] << "　";
		}
		cout << endl;
	}
}

int main() {
	ifstream Input;
	ofstream Output;
	Input.open("input.txt");
	Output.open("output.txt");
	int T;
	Input >> T;

	for (int i = 0; i < T; i++) {
		int N, I;
		Input >> N >> I;

		map<int, vector<int>> table;
		for (int j = 0; j < N - 1; j++) {
			int num1, num2;
			Input >> num1 >> num2;
			if (table[num1].size() == NULL) {
				vector<int> adj;
				adj.push_back(num2);
				table[num1] = adj;
			}
			else {
				table[num1].push_back(num2);
			}
			if (table[num2].size() == NULL) {
				vector<int> adj;
				adj.push_back(num1);
				table[num2] = adj;
			}
			else {
				table[num2].push_back(num1);
			}
		}
		//printtable(table);

		vector<int> endpoint;
		for (auto iter = table.begin(); iter != table.end(); iter++) {
			if (iter->second.size() == 1) {
				endpoint.push_back(iter->first);
			}
		}
		int head, tail;
		if (endpoint[0] > endpoint[1]) {
			head = endpoint[0];
			tail = endpoint[1];
		}
		else {
			head = endpoint[1];
			tail = endpoint[0];
		}
		//cout << "head : " << head << endl;
		//cout << "tail : " << tail << endl;

		vector<int> graph;
		graph.push_back(head);
		graph.push_back(table[head][0]);
		for (int i = 1; i < N - 1; i++) {
			for (int j = 0; j < 2; j++) {
				if (table[graph[i]][j] != graph[i - 1]) {
					graph.push_back(table[graph[i]][j]);
					break;
				}
			}
		}
		graph.push_back(tail);

		Output << graph[I] << endl;
	}
	return 0;
}

