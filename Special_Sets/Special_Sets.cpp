// Special_Sets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

vector<vector<int>> Load_Data(string filename) {
	vector<vector<int>> data;
	data.resize(100, vector<int>(100));
	ifstream input;
	input.open(filename);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			input >> data[i][j];
		}
	}
	return data;
};

int Check_Set(const vector<vector<int>>& matrix, const vector<int>& vec) {
	int n = matrix.size();
	//vector<int> out(n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int match = 0;
		for (int j = 0; j < n; j++) {
			if (matrix[i][vec[j]] == 1) match++;
		}

	}
/*	int out = 0;
	for (int i = 0; i < n; i++) {
		if (sum == tier) out++;
	}*/
	return sum;
};

vector<vector<int>> Find_Sets(vector<vector<int>>& Data, vector<vector<int>>& Lattice, vector<int>& LatticeCount, int tier, int k) {
	int count = LatticeCount[tier];
	vector<vector<int>> out;
	int new_count = 0;
	vector<int> index;
	for (int i = 0; i < count; i++) {
		if (MV_Product(Data, Lattice[i], tier) >= k) {
			new_count++;
			index.push_back(i);
		}
	}
	out.resize(new_count, vector<int>(100));
	for (int i = 0; i < new_count; i++) {
		out[i] = Lattice[index[i]];
	}
	LatticeCount.push_back(new_count);
	return out;
};


int main()
{
	vector<vector<int>> Data = Load_Data("input.txt");
/*	for (int i = 0; i < 10; i++) {
		cout << Data[i][1] << '\t';
	}*/
	vector<int> LatticeCount;
	LatticeCount.push_back(100);
	int tier = 1;
	int k = 5;
	int step = 0;
	vector<vector<int>> Lattice;
	Lattice.resize(100, vector<int>(100,0));
	for (int i = 0; i < 100; i++) {
		Lattice[i][i] = 1;
	}
	while (LatticeCount[tier-1] > 0) {
		vector<vector<int>> New = Find_Sets(Data, Lattice, LatticeCount, tier, 5);
		cout << LatticeCount[step] << '\t';
		tier++;
		step++;
	}
	cout << "Press any key to exit" << endl;
	char tmp;
	cin >> tmp;
    return 0;
}

