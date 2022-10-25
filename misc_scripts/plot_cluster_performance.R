library(tidyverse)

# plotting iris
iris <- read_csv('iris_cluster.csv')

ggplot(data = iris) +
  geom_point(aes(sepal.length,petal.length, color=factor(variety))) +
  xlab("Sepal Length") +
  ylab("Petal Length") + 
  theme_minimal() +
  ggtitle('Actual Variety Classification')

ggplot(data = iris) +
  geom_point(aes(sepal.length,petal.length, color=factor(cluster))) +
  xlab("Sepal Length") +
  ylab("Petal Length") + 
  theme_minimal() +
  ggtitle("Clustering Results")

# plotting moons
moons <- read_csv("moons_cluster.csv")

ggplot(data = moons) +
  geom_point(aes(x,y, color=factor(group))) +
  xlab("x") +
  ylab("y") + 
  theme_minimal() +
  ggtitle('Actual Group Classification')

ggplot(data = moons) +
  geom_point(aes(x,y, color=factor(cluster))) +
  xlab("x") +
  ylab("y") + 
  theme_minimal() +
  ggtitle("Clustering Results")

# plotting blobs
blobs <- read_csv("blobs_cluster.csv")

ggplot(data = blobs) +
  geom_point(aes(x,y, color=factor(group))) +
  xlab("x") +
  ylab("y") + 
  theme_minimal() +
  ggtitle('Actual Group Classification')

ggplot(data = blobs) +
  geom_point(aes(x,y, color=factor(cluster))) +
  xlab("x") +
  ylab("y") + 
  theme_minimal() +
  ggtitle("Clustering Results")

# generate multi-dimensional blobs
blob_data <- read_csv("data/blobs.csv")

for(i in 1:50){
  blob_data[[i]] <- runif(1)*blob_data$x
}

write_csv(blob_data[1:50,], file = "data/multi_blobs.csv")  
