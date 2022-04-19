#include <iostream>
#include <fstream>

using namespace std;

int N = 0;
long long int cnt = 0;

int main(){
	int T = 0;
	ifstream input("input.txt");
	ofstream output("output.txt");
	input >> T;
	for(int i = T; i > 0; i--){
		cnt = 0; N = 0;
		input >> N;
		long long int *seq = new long long int[N];
		for(int j = 0; j < N; j++){
			long long int num = 0;
			input >> num;
			seq[j] = num;
		}
		for(int i = 0; i < N - 1; i++){
        	for(int j = i + 1; j < N; j++){
            	if(seq[j] >= 2 * seq[i]){
                	cnt++;
            	}
     		}
    	}
		output << cnt << endl;
		delete[] seq;
	}
	input.close();
	output.close();
	return 0;
}