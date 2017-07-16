# glabel
Probabilistic graph labeling. For example, suppose you have a bipartite graph which connects users
and companies; you know the industry for many of the companies and some of the people, but want to
estimate the industry for the rest of the nodes.

> ./glabel graph.txt label.txt

# example 1
Our first example is a graph with 3 nodes, each of which is connected to the other; we know the node
labels for 2 of the nodes.

```
# graph.txt
1 2
2 3
3 1
```

```
# label.txt
1 cryptocurrency
2 machine-learning
```

Since we have no information on node 3 other than it's connected to 1 cryptocurrency and 1 machine learning
node, we would expect the output to be close to 50-50.

```
# inferred.txt
1 cryptocurrency 0.995025
1 machine-learning 0.00497512
2 cryptocurrency 0.00497512
2 machine-learning 0.995025
3 cryptocurrency 0.499643
3 machine-learning 0.500357
```

# example 2
Now suppose we introduce a new node which is connected to node 3 and node 1. This creates a new indirect link
between node 3 and the cryptocurrency industry.

```
# graph.txt
1 2
2 3
3 1
4 1
3 4
```

```
# label.txt
1 cryptocurrency
2 machine-learning
```

As expected, we see that the probability of `cryptocurrency` for both nodes 3 and 4 has increased.

```
# inferred.txt
1 cryptocurrency 0.995025
1 machine-learning 0.00497512
2 cryptocurrency 0.00497512
2 machine-learning 0.995025
3 cryptocurrency 0.560865
3 machine-learning 0.439135
4 cryptocurrency 0.731296
4 machine-learning 0.268704
```
