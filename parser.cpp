/**
 * 
 * Author: Justin Ho
 * Date: 03/07/2021
 * Parses csv file, ignores attributes that are non-continuous
 * Default max dimension is 1000;
 * 
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

vector<vector<double>> parse_csv(string file_name){

    vector<vector<double>> parsed_file;

    ifstream input_file(file_name);

    if(!input_file){
        cout << "Input file is invalid!\n";
        exit(1);
    }

    string header;

    getline(input_file, header);

    string values;

    regex e("^-?\\d*\\.?\\d+"); // check if item is decimal

    while(getline(input_file, values)){

        string delimiter = ",";
        vector<double> instance;
        size_t pos = 0;
        string token;
        while ((pos = values.find(delimiter)) != string::npos) {

            token = values.substr(0, pos);
            // only obtain continuous variables
            if(regex_match(token, e)){
                instance.push_back(stod(token));
            }
            values.erase(0, pos + delimiter.length());
        }

        if(regex_match(values, e)){
                instance.push_back(stod(token));
        }

        parsed_file.push_back(instance);

    }

    return parsed_file;
}