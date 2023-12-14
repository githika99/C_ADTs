/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa2
*/
//-----------------------------------------------------------------------------
// GRAPH Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#define INF -1
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

//returns the source vertex most recently used by BFS, or nil if BFS hasn't been called yet
//Pre: G!= NULL
int getSource(Graph G);

//returns the parent vertex of vertex u in BFS tree, or NIL if BFS hasn't been called yet
//Pre: G!= NULL, 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

//returns the distance from the most recent BFS source to vertex u, or NIL if BFS hasn't been called yet
//Pre: G!= NULL, 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

//appends to List L the shortest path from most recent BFS source to vertex u, or NIL if no such path exists
//Pre: G!= NULL, 1 <= u <= getOrder(G), getSource != NIL
void getPath(List L, Graph G, int u);


/*** Manipulation procedures ***/
//deletes all edges of G, restoring it to its original state
void makeNull(Graph G);


//adds an undirected edge {u,v} to Graph G
//Pre: G!= NULL, 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v);


//adds a directed edge {u,v} from vertex u to vertex v
//Pre: G!= NULL
void addArc(Graph G, int u, int v);


//does BFS on Graph G, using vertex s as the source
//Pre: G!= NULL, 1 <= s <= getOrder(G)
void BFS(Graph G, int s);


/*** Other operations ***/
//prints adjacency list of graph G to FILE* out
//Pre: G!= NULL
void printGraph(FILE* out, Graph G);

#endif