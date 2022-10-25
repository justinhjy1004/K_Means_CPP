/**
 * 
 * Author: Justin Ho
 * Date : 03/07/2021
 * Main file for k-means clustering
 * Prompts user for input and executes kmeans
 * 
 */

#include <iostream>
#include <vector>
#include <fstream>

#include "kmeans.hpp"
#include "parser.hpp"
#include "writer.hpp"

using namespace std;

int main(int argc, char * argv[]){

    if(argc > 1){
        if(strcmp(argv[1], "cluster") == 0){
            string file_name = "data/blobs.csv";
            vector<vector<double>> input = parse_csv(file_name);
            vector<vector<double>> results = time_by_cluster(20, input);
            record_csv(results,argv[1]);
            return(0);
        }
        else if(strcmp(argv[1], "transactions") == 0){
            string file_name = "data/blobs.csv";
            vector<vector<double>> input = parse_csv(file_name);
            vector<vector<double>> results = time_by_transaction(input, 10);
            record_csv(results,argv[1]);
            return(0);
        }else if(strcmp(argv[1], "dimensions") == 0){
            string file_name = "data/multi_blobs.csv";
            vector<vector<double>> input = parse_csv(file_name);
            vector<vector<double>> results = time_by_dimensions(input);
            record_csv(results,argv[1]);
            return(0);
        } else if (strcmp(argv[1], "fit") == 0){
            string file_name = "data/blobs.csv";
            vector<vector<double>> input = parse_csv(file_name);
            vector<vector<double>> results = fit_by_cluster(20, input);
            record_csv(results,argv[1]);
            return(0);
        } else {
            cout << "Invalid flag!\n";
            exit(1);
        }
    }

    // input parameters
    string file_name;
    int k;
    double epsilon;
    int max_iterations;

    // prompt input from users
    cout << "Input file name: \n";
    while(!(cin >> file_name)){
        cout << "Bad value!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Input number of clusters k (int): \n";
    while(!(cin >> k)){
        cout << "Bad value!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Input minimum SSD threshold (double): \n";
    while(!(cin >> epsilon)){
        cout << "Bad value!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Maximum number of iterations (int): \n";
    while(!(cin >> max_iterations)){
        cout << "Bad value!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // parse file 
    vector<vector<double>> dataset = PARSER_HPP::parse_csv(file_name);

    // init kmeans
    kmeans_clustering k_means_implementation(k, epsilon, max_iterations, dataset);

    // run kmeans
    k_means_implementation.execute();

    // obtain cluster
    vector<int> clusters = k_means_implementation.get_clusters();

    // write csv file for clusters
    write_csv(file_name, clusters);

    return(0);

}