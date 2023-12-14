/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa3
*/
//-----------------------------------------------------------------------------
// GRAPH Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL 0                              //could be 0 instead
#include<stdbool.h>
#include"List.h"

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
//creates a newGraph that has n verticies and 0 edges
Graph newGraph(int n);

//frees the memory associated with graph pG
//Pre: G!= NULL
void freeGraph(Graph* pG);


/*** Access functions ***/

//returns the order (number of verticies) in G
//Pre: G!= NULL
int getOrder(Graph G);

//returns the size (number of edges) in G
//Pre: G!= NULL
int getSize(Graph G);

//returns the parent vertex of vertex u in BFS tree, or NIL if BFS hasn't been called yet
//Pre: G!= NULL, 1 <= u <= getOrder(G)
int getParent(Graph G, int u);


//Pre: 1<=u<=n=getOrder(G) 
//Returns the Discover time of u on Graph(G) or UNDEF if DFS has not been run yet
int getDiscover(Graph G, int u); 

//Pre: 1<=u<=n=getOrder(G)
//Returns the Finish time of u on Graph(G) or UNDEF if DFS has not been run yet
int getFinish(Graph G, int u); 


/*** Manipulation procedures ***/

//adds a directed edge {u,v} from vertex u to vertex v
//Pre: G!= NULL
void addArc(Graph G, int u, int v);


//adds an undirected edge {u,v} to Graph G
//Pre: G!= NULL, 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v);

//Pre: length(S)==getOrder(G)
//perform the depth first search algorithm on G 
//Before DFS, List S defines the order in which vertices are to be processed in DFS
//After DFS, List S will store the vertices by decreasing finish times
void DFS(Graph G, List S); 

/*** Other operations ***/

//Pre: G is not Null
//Returns a graph that is the transpose of G (same verticies but the adjacency matrix is transposed)
Graph transpose(Graph G);


//Pre: G is not Null
//Returns a new graph that is a copy of G (same verticies and Edges)
Graph copyGraph(Graph G);

//prints adjacency list of graph G to FILE* out
//Pre: G!= NULL
void printGraph(FILE* out, Graph G);

#endif