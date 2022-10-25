# -*- coding: utf-8 -*-
"""
Author: Justin Ho
Generate test data to observe clustering performance
"""

from sklearn import datasets
import numpy as np
import csv

# init fields
fields = ["x", "y", "group"]

# making of the moon dataset
moons = datasets.make_moons(n_samples=1000, noise=.05)
moon_array = moons[0]
moon_list = moon_array.tolist()
moon_group = moons[1]
moon_group_list = moon_group.tolist()

moon_list[1]

for i in range(len(moon_group_list)):
    moon_list[i].append(moon_group_list[i])
    
with open('moons.csv', 'w', newline="") as f: 
      
    # using csv.writer method from CSV package 
    write = csv.writer(f) 
      
    write.writerow(fields) 
    write.writerows(moon_list)     
    
# making of the blob dataset
    
blobs = datasets.make_blobs(n_samples=1000, random_state=8, centers=5)

blob_list = blobs[0].tolist()
blob_group_list = blobs[1].tolist()

for i in range(len(blob_group_list)):
    blob_list[i].append(blob_group_list[i])
    
with open('blobs.csv', 'w', newline="") as f: 
      
    # using csv.writer method from CSV package 
    write = csv.writer(f) 
      
    write.writerow(fields) 
    write.writerows(blob_list) 

