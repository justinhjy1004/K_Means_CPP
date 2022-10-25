/**
 * 
 * Author: Justin Ho
 * Date: 03/07/2021
 * Write csv file with output from the cluster 
 * 
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int write_csv(string input_file, vector<int> clusters){

    ifstream input(input_file); //input file

    string output_file; // output file with cluster
    string::size_type pos = input_file.find('.');
    if (pos != std::string::npos)
    {
        output_file = input_file.substr(0, pos);
    } else {
        exit(1);
    }

    ofstream output(output_file + "_cluster.csv");

    // append csv header with cluster column
    string header;
    string header_append;

    getline(input, header);
    header_append = header + ",\"cluster\"\n";
    output << header_append;

    // adding a column with the cluster results
    int i = 0;
    string instance;
    string instance_append;
    while(getline(input, instance)){
        string val = to_string(clusters[i]);
        instance_append = instance + "," + val + "\n";
        output << instance_append;
        i++;
    }

    return(0);

}

int record_csv(vector<vector<double>> results, string field){
    ofstream output(field + ".csv");
    output << field + ",time\n";
    for(const auto& instance: results){
        int n = instance.size();
        for(int i = 0; i < n; i++){
            output << instance[i];
            if(i == 0){
                output << ",";
            }
        }
        output << "\n";
    }

    return(0);
}