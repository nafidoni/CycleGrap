# CycleGrap
For a given graph determine all possible cycles of the graph 

It is a question of determining the cycles without strings in an undirected graph.
For this, we used that of vertex labeling. It introduces the concepts of vertex labeling and validation of three-vertex triples.
To ensure that the expansion of a given layoutless path always leads to a stringless cycle,
a breadth-search is used in a subgraph obtained by eliminating several vertices from the original graph.
It has the advantage of finding each ropeless cycle only once.
The resulting algorithm has time complexity O(n+m) where n is the number of vertices and m is the number of edges in the graph. 
