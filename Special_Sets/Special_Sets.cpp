// Special_Sets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cstdlib>

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

int main()
{
	matrix = Load_Data("input.txt");
    return 0;
}

