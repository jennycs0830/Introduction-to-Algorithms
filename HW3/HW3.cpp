#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<iostream>

using namespace std;

void printTable(char **Table, int n);
int Counts = 0;

bool checkqueen(int row, int column, char** Table, int N) {
	//左上
	for (int i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--) {
		if (Table[i][j])
			return false;
	}
	//左下
	for (int i = row + 1, j = column - 1; i < N && j >= 0; i++, j--) {
		if (Table[i][j])
			return false;
	}
	//右上
	for (int i = row - 1, j = column + 1; i >= 0 && j < N; i--, j++) {
		if (Table[i][j])
			return false;
	}
	//右下
	for (int i = row + 1, j = column + 1; i < N && j < N; i++, j++) {
		if (Table[i][j])
			return false;
	}
	//左
	for (int i = column -1; i >= 0; i--) {
		if (Table[row][i])
			return false;
	}
	//右
	for (int i = column + 1; i < N; i++) {
		if (Table[row][i])
			return false;
	}
	//cout << "true " ;
	return true;
}

void nqueen(int col, int n, char**Table)
{
	int row;
	if (col == n) {
		Counts++;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (Table[i][col]) {
			nqueen(col + 1, n, Table);
			return;
		}
	}
	for (row = 0; row < n; row++) {
		if (checkqueen(row, col, Table, n)) {
			Table[row][col] = 'Q';
			//printTable(Table, n);
			nqueen(col + 1, n, Table);
			Table[row][col]=0x00;
			//printTable(Table, n);
		}
	}
}
void printTable(char **Table, int n)
{
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!Table[i][j])
				printf(". ");
			else
				printf("%c ", (Table[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}

void freeTable(char **Table, int n)
{
	for (int i = 0; i < n; i++)
		free(Table[i]);
	free(Table);
}

int main() {
	ifstream Input;
	Input.open("input.txt");
	ofstream Output;
	Output.open("output.txt");

	int T=0;
	Input >> T;
	//cout << T <<endl;
	for (int i = T; i > 0; i--) {
		int N = 0, preData = 0;
		Input >> N >> preData;
		//cout << N << " "<<preData<<endl;
		char**Table = (char**)malloc(sizeof(char*)*N);
		for (int i = 0; i < N; i++) {
			Table[i] = (char*)calloc(N, sizeof(char));
		}
		//printTable(Table, N);
		for (int i = 0; i < preData; i++) {
			int row, column;
			Input >> row >> column;
			Table[row][column] = 'Q';
		}
		//printTable(Table, N);
		nqueen(0, N, Table);
		Output << Counts << endl;
		//printTable(Table, N);
		//cout << "Count=" << Counts << endl;
		Counts = 0;
		freeTable(Table, N);
	}
	/*while(!Input.eof()){
		int N,preData;
		Input>>N>>preData;
		char**Table=(char**)malloc(sizeof(char*)*N);
		for(int i=0;i<N;i++){
			Table[i]=(char*)calloc(N,sizeof(char));
		}
		for(int i=0;i<preData;i++){
			int row,column;
			Input>>row>>column;
			Table[row][column]='Q';
		}
		printTable(Table,N);
		nqueen(0,N,Table);

		cout<<"Count="<<Counts<<endl;
		Counts=0;
		freeTable(Table,N);
	}*/
	Input.close();
	Output.close();
	return 0;
}