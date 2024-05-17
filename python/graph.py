# Python program for the above approach
import heapq

# This class represents a directed graph using
# adjacency list representation
class Graph:
    def __init__(self, V):
        self.V = V  # No. of vertices
        self.adj = [[] for _ in range(V)]  # In a weighted graph, store vertex and weight pair for every edge

    # Function to add an edge to the graph
    def add_edge(self, u, v, w):
        self.adj[u].append((v, w))
        self.adj[v].append((u, w))

# Driver program to test methods of the graph class
if __name__ == "__main__":
    # Create the graph given in the above figure
    V = 9
    g = Graph(V)

    # Making the above-shown graph
    g.add_edge(0, 1, 4)
    g.add_edge(0, 7, 8)
    g.add_edge(1, 2, 8)
    g.add_edge(1, 7, 11)
    g.add_edge(2, 3, 7)
    g.add_edge(2, 8, 2)
    g.add_edge(2, 5, 4)
    g.add_edge(3, 4, 9)
    g.add_edge(3, 5, 14)
    g.add_edge(4, 5, 10)
    g.add_edge(5, 6, 2)
    g.add_edge(6, 7, 1)
    g.add_edge(6, 8, 6)
    g.add_edge(7, 8, 7)
