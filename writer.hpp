#ifndef WRITER_HPP
#define WRITER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int write_csv(string input_file, vector<int> clusters);
int record_csv(vector<vector<double>> results, string field);

#endif