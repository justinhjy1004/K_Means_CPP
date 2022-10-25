#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <stdio.h>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>

using namespace std;

class kmeans_clustering
{
private:
    int k;                            //number of clusters
    double epsilon;                   //min change in SSE
    int max_iterations;               //max number of iterations until termination
    int dimensions;                   // dimension of features
    int n;                            // number of points
    vector<vector<double>> points;    // vector of points, which itself is a vector of values
    vector<int> assigned_cluster;     // map for each point to the assigned cluster
    vector<vector<double>> centroids; // vector of centroids
    vector<vector<double>> distances; // distance of each point from cluster distances[point][centroid]
    double compute_SSE();
    void assign_cluster();
    void update_centroids();
    void calculate_within_cluster_SSE();
    double within_cluster_SSE; // within cluster SSE

public:
    kmeans_clustering(int k, double epsilon, int max_iterations, vector<vector<double>> points);
    int execute();
    vector<vector<double>> get_points();
    vector<int> get_clusters();
    void set_clusters(int k);
    vector<vector<double>> get_distance();
    double get_within_cluster_SSE();

};

vector<vector<double>> time_by_cluster(int k, vector<vector<double>> points);
vector<vector<double>> time_by_transaction(vector<vector<double>> points, int increments);
vector<vector<double>> time_by_dimensions(vector<vector<double>> points);
vector<vector<double>> fit_by_cluster(int k, vector<vector<double>> points);

#endif