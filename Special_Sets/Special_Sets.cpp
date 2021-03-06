// Student names: Nathan Soule and Julia Newting
// Date: 5/15/2018
// Homework #: 3980-1
// Lower bound on number of maximal special sets:
// The source code in this program is the work of people in my group
// and not the work of anyone else
// Signatures:
//
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <algorithm>

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

int Is_Special(const vector<vector<int>>& matrix, const vector<int>& vec) {
	int n = matrix.size();
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int match = 0;
		for (size_t j = 0; j < vec.size(); j++) {
			if (matrix[i][vec[j]] == 1) match++;
		}
		if (match == vec.size()) sum++;
	}
	return sum;
};

void RecursiveSolve(vector<int> available, vector<int> build, vector<vector<int>>* output, const vector<vector<int>>* data, const int k) {
	//initial trim (remove things from available)
	for (size_t i = 0; i < available.size();) {
		vector<int> temp = build;
		temp.push_back(available[i]);
		if (Is_Special(*data, temp) >= k)
			available.erase(available.begin() + i);
		else
			i++;
	}
	
	//if available is empty (check if we can add)
	if (available.size() == 0) {
		bool status = true;
		for (size_t i = 0; i < output->size(); i++) {
			if (includes(output->at(i).begin(), output->at(i).end(), build.begin(), build.end())) {
				status = false;
				break;
			}
		}
		if (status)
			output->push_back(build);
	}
	else {
		vector<int> Union = build;

		for (size_t i = 0; i < available.size(); i++) {
			Union.push_back(available[i]);
		}
		bool status = true;
		for (size_t i = 0; i < output->size(); i++) {
			if (includes(output->at(i).begin(), output->at(i).end(), Union.begin(), Union.end())) {
				status = false;
				break;
			}
		}
		if (status) {
			while (available.size() != 0) {
				build.push_back(available[0]);
				available.erase(available.begin());
				RecursiveSolve(available, build,output,data,k);
				build.pop_back();
			}
		}
	}
	//if available is not empty and build union available is not a subset of some element of output (iterate)
}

vector<vector<int>> Solve(const vector<vector<int>> &Data, int k, vector<vector<int>>& output) {
	vector<int> available;
	for (size_t i = 0; i < Data[0].size(); i++) {
		available.push_back(i);
	}
	vector<int> build;
	//vector<vector<int>> output;
	RecursiveSolve(available, build, &output, &Data, k);
	return output;
}



int main()
{
	vector<vector<int>> Data = Load_Data("input.txt");
/*	for (int i = 0; i < 10; i++) { // uncomment to check data loading
		cout << Data[i][1] << '\t';
	}*/
	vector<vector<int>> output;
	Solve(Data, 5, output);

	ofstream outfile;
	outfile.open("output.txt");
	bool done = false;
	while (!done) {
		size_t i = output[0].size();
		for (size_t j = 0; j < i; j++) {
			outfile << output[0][j] << '\t';
		}
		outfile << '\n';
		output.erase(output.begin());
		if (output.size() == 0)
			done = true;
	}
	cout << "Press any key to exit" << endl;
	char tmp;
	cin >> tmp;
    return 0;
}