# K-Means Clustering Implementation in C++
## Group 8 (Justin Ho and Kolby Johnson)

## Description of Algorithm
This is an implementation of k-means clustering using the Euclidean Distance and accepts the following parameters:
1. Input file (this is designed to read csv files, all non-continuous variables are dropped)
1. Number of clusters
1. Epsilon (Change in the sum of the distnaces from the cluster centers) 
1. Maximum Number of Iterations

## Usage
In the CSE terminal execute the following in this directory
```CSE Terminal
make
./main
```
The program will prompt you for the inputs described above.

## Miscellaneous
* The output will be rendered in the same directory of the input file with "_cluster" appended to its name
* Datasets used can be found in the "data/" directory, with its corresponding "_cluster" results
* The images generated based on the clusters of the clustering algorithm and the "actual" groups based on the source of the data are in the "Clustering Images/" directory
* Plots for time vs dimension, transactions and clusters as well as the graph for goodness of fit are in the "plots/" directory
* Miscellaneous scripts for data generation and plotting are included in the directory "misc_scripts/"
