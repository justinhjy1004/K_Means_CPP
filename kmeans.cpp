/**
 * 
 * Author: Justin HO
 * NUID 47438345
 * Implementation of K-means clustering
 * 
 */

#include <stdio.h>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// class definition
class kmeans_clustering
{
private:
    int k;                            // number of clusters
    double epsilon;                   // min change in SSE
    int max_iterations;               // max number of iterations until termination
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

// constructor for class kmeans_clustering
kmeans_clustering::kmeans_clustering(int k, double epsilon,
                                     int max_iterations, vector<vector<double>> points)
{
    this->k = k;
    this->epsilon = epsilon;
    this->max_iterations = max_iterations;
    this->points = points;
    this->dimensions = points[0].size();
    this->n = points.size();    

    // initialize centroids
    vector<int> random_assignments;
    // ensure no same points
    for (int i = 0; i < this->k; i++)
    {
        int random_assignment = rand() % this->points.size();
        if (count(random_assignments.begin(), random_assignments.end(), random_assignment))
        {
            i--;
        }
        else
        {
            random_assignments.push_back(random_assignment);
        }
    }

    // assign centroid to random init
    for (int i = 0; i < this->k; i++)
    {
        this->centroids.push_back(this->points[random_assignments[i]]);
    }

    // initialize distances to 0
    for (int i = 0; i < this->n; i++)
    {
        vector<double> entry;
        for (int j = 0; j < k; j++)
        {
            entry.push_back(0);
        }
        this->distances.push_back(entry);
    }

    
    // initialize clusters to NULL
    for (int i = 0; i < this->n; i++)
    {
        this->assigned_cluster.push_back(-1);
    }

     
}

// run kmeans
int kmeans_clustering::execute()
{

    for (int i = 0; i < this->max_iterations; i++)
    {
        double change_SSE = kmeans_clustering::compute_SSE();
        if(change_SSE < this->epsilon){
            break;
        }
        kmeans_clustering::assign_cluster();
        kmeans_clustering::update_centroids();
    }

    kmeans_clustering::calculate_within_cluster_SSE();

    return (0);
}

vector<vector<double>> kmeans_clustering::get_points()
{
    return this->points;
}

vector<vector<double>> kmeans_clustering::get_distance()
{
    return this->distances;
}

vector<int> kmeans_clustering::get_clusters()
{
    return this->assigned_cluster;
}

// computation of SSE using euclidean distance
double kmeans_clustering::compute_SSE()
{
    double change_SSE = 0;
    for (int i = 0; i < this->n; i++)
    { // for each point
        for (int j = 0; j < this->k; j++)
        { // for each centroid
            double calc_distance = 0;
            for (int k = 0; k < this->dimensions; k++)
            {
                calc_distance += pow(this->points[i][k] - this->centroids[j][k], 2);
            }
            calc_distance = sqrt(calc_distance);
            change_SSE += abs(calc_distance - this->distances[i][j]);
            this->distances[i][j] = calc_distance;
        }
    }

    return change_SSE;
}

// assign cluster based on the minimum SSE
void kmeans_clustering::assign_cluster()
{
    for (int i = 0; i < this->n; i++)
    { // for each point
        // get the minimum element
        auto min_distance = min_element(this->distances[i].begin(), this->distances[i].end());
        // get the index of the element, which corresponds to the centroid
        int index = distance(this->distances[i].begin(), min_distance);
        // assign to the closest centroid
        this->assigned_cluster[i] = index;
    }
}

// update centroid position
void kmeans_clustering::update_centroids()
{
    for (int i = 0; i < this->k; i++)
    { // for each centroid
        vector<double> new_spatial_location;

        for (int j = 0; j < this->dimensions; j++)
        {
            new_spatial_location.push_back(0);
        }

        int num_points = 0;

        for (int j = 0; j < this->n; j++)
        { // find the points

            if (this->assigned_cluster[j] == i)
            { // assigned to this cluster
                num_points++;
                for (int k = 0; k < this->dimensions; k++)
                { // add each assigned clusters' dimensions
                    new_spatial_location[k] += this->points[j][k];
                }
            }
        }

        if (num_points != 0)
        { // avoid division by 0
            for (int k = 0; k < this->dimensions; k++)
            {
                new_spatial_location[k] /= num_points;
            }
        }

        //check change of SSE

        // update centroid
        this->centroids[i] = new_spatial_location;
    }
}

void kmeans_clustering::set_clusters(int k){
    this->k = k;
    return;
}

void kmeans_clustering::calculate_within_cluster_SSE(){

    vector<vector<double>> distances = this->distances;
    vector<int> c = this->assigned_cluster;
    
    double dist = 0;
    for(int j = 0; j < n; j++){
        dist += distances[j][c[j]];
    }

    this->within_cluster_SSE = dist;
}

double kmeans_clustering::get_within_cluster_SSE(){

    return this->within_cluster_SSE;

}

// plotting time by cluster
vector<vector<double>> time_by_cluster(int k, vector<vector<double>> points){
    double epsilon = 0.001;
    int max_iterations = 1000;

    vector<vector<double>> time_set;

    for(int i = 0; i <= k; i++){
        vector<double> time;
        kmeans_clustering instance(i, epsilon, max_iterations, points);
        auto start = high_resolution_clock::now(); 
        instance.execute();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        time.push_back((double) i);
        time.push_back((double) duration.count());
        time_set.push_back(time);
    }

    return time_set;
}

// plotting time by transactions
vector<vector<double>> time_by_transaction(vector<vector<double>> points, int increments){
    double epsilon = 0.001;
    int max_iterations = 1000;
    int k = 5;

    vector<vector<double>> time_set;

    int max_transactions = points.size();

    for(int i = increments; i < max_transactions; i += increments){
        //subset vector based on index
        vector<vector<double>>::const_iterator first = points.begin();
        vector<vector<double>>::const_iterator last = points.begin() + i;
        vector<vector<double>> subset(first,last);

        vector<double> time;
        kmeans_clustering instance(k, epsilon, max_iterations, subset);
        auto start = high_resolution_clock::now(); 
        instance.execute();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        time.push_back((double) i);
        time.push_back((double) duration.count());
        time_set.push_back(time);
    }

    return time_set;
}

// plotting time by dimensions
vector<vector<double>> time_by_dimensions(vector<vector<double>> points){
    double epsilon = 0.001;
    int max_iterations = 1000;
    int k = 5;

    vector<vector<double>> time_set;

    int max_dimensions = points[0].size();
    int n = points.size();

    for(int i = 0; i < 40; i++){
        // remove last element 
        for(int j = 0; j < n ; j++){
            points[j].pop_back();
        }

        vector<double> time;
        kmeans_clustering instance(k, epsilon, max_iterations, points);
        auto start = high_resolution_clock::now(); 
        instance.execute();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        time.push_back((double) max_dimensions - i);
        time.push_back((double) duration.count());
        time_set.push_back(time);
    }

    return time_set;
}

// SSE by cluster
vector<vector<double>> fit_by_cluster(int k, vector<vector<double>> points){
    double epsilon = 0.001;
    int max_iterations = 1000;

    vector<vector<double>> average_SSE;

    int n = points.size();

    for(int i = 1; i <= k; i++){
        vector<double> sse;
        kmeans_clustering instance(i, epsilon, max_iterations, points);
        instance.execute();

        vector<vector<double>> distances = instance.get_distance();
        vector<int> c = instance.get_clusters();
        
        double dist = 0;
        for(int j = 0; j < n; j++){
            dist += distances[j][c[j]];
        }
        dist /= n;

        

        sse.push_back((double) i);
        sse.push_back((double) dist);
        average_SSE.push_back(sse);
    }

    return average_SSE;
}