library(tidyverse)

fit <- read_csv("plots/fit.csv")

ggplot(data = fit, aes(k,fit)) +
  geom_point() +
  geom_line() +
  xlab("Number of Clusters") +
  ylab("Mean Squared Error") +
  ggtitle("Goodness of fit and number of clusters") +
  theme_minimal()

clusters <- read_csv("plots/cluster.csv")

ggplot(data = clusters, aes(cluster,time)) +
  geom_point() +
  geom_line() +
  xlab("Clusters") +
  ylab("time in microseconds") +
  ggtitle("Number of clusters vs time") +
  theme_minimal()

dimensions <- read_csv("plots/dimensions.csv")

ggplot(data = dimensions, aes(dimensions,time)) +
  geom_point() +
  xlab("Dimensions") +
  ylab("time in microseconds") +
  ggtitle("Number of dimensions vs time") +
  theme_minimal()

transactions <- read_csv("plots/transactions.csv")

ggplot(data = transactions, aes(transactions,time)) +
  geom_point() +
  xlab("Transactions") +
  ylab("time in microseconds") +
  ggtitle("Number of transactions vs time") +
  theme_minimal()
