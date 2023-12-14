/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa2
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"           //do I need to include this in Graph.h and Graph.c


typedef struct GraphObj{
    int order;
    int size;
    int s;                                              //should I use a Vertex struct?
    List* adj;
    char* color;
    int* p;
    int* d;
} GraphObj;

/*** Constructors-Destructors ***/
//creates a newGraph that has n verticies and 0 edges
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert( G!=NULL );
    G -> order = n;
    G -> size = 0;
    G -> s = NIL;
    G -> adj = (List *) malloc((n+1) * sizeof(List));
    G -> color = (char *) malloc( (n+1) * sizeof(char));
    G -> p = (int *) malloc( (n+1) * sizeof(int));
    G -> d = (int *) malloc( (n+1) * sizeof(int));

    for (int i = 1; i <= G->order; i++){
        G -> adj[i] = newList();
        G -> color[i] = 'w';
        G -> p[i] = NIL;
        G -> d[i] = INF;
    }

    return (G);
}

//frees the memory associated with graph pG
//Pre: G!= NULL
void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){              //if pG == NULL, we cannot access *pG
        for(int i = 1; i <= (*pG)->order; i++){
            freeList(&((*pG)->adj[i]));            //frees each List
        }                  
        free((*pG) -> adj);                       //frees the pointer to the first List
        free((*pG) -> color);
        free((*pG) -> p);
        free((*pG) -> d);
        //do we have to set all of these to NULL? Like (*pG)->adj = NULL;
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

//returns the order (number of verticies) in G
//Pre: G!= NULL
int getOrder(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    //all Graphs have an order, so no need to check if empty
    return (G->order);
}

//returns the size (number of edges) in G
//Pre: G!= NULL
int getSize(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    //if no size, should return 0, bc that is what newGraph is initialized to
    return (G->size);
}

//returns the source vertex most recently used by BFS, or nil if BFS hasn't been called yet
//Pre: G!= NULL
int getSource(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    return (G->s);
    //no need to check if BFS() has been called bc s is initialized to NIL
}

//returns the parent vertex of vertex u in BFS tree, or NIL if BFS hasn't been called yet
//Pre: G!= NULL, 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if (u <= 0 || u > G->order){
        printf("Graph Error: calling getParent() with Vertex %d which does not exist in Graph reference\n", u);
        exit(EXIT_FAILURE);
    }
    return (G->p[u]);
    //all elements in p should be initialized to NIL in case BFS hasn't been called yet
}

//returns the distance from the most recent BFS source to vertex u, or NIL if BFS hasn't been called yet
//Pre: G!= NULL, 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if (u <= 0 || u > G->order){
        printf("Graph Error: calling getDist() with Vertex %d which does not exist in Graph reference\n", u);
        exit(EXIT_FAILURE);
    }
    return (G->d[u]);
    //all elements in d should be initialized to NIL in case BFS hasn't been called yet
}

//appends to List L the shortest path from most recent BFS source to vertex u, or NIL if no such path exists
//Pre: G!= NULL, 1 <= u <= getOrder(G), getSource != NIL
void getPath(List L, Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if (u <= 0 || u > G->order){
        printf("Graph Error: calling getDist() with Vertex %d which does not exist in Graph reference\n", u);
        exit(EXIT_FAILURE);
    }
    if (G->s == NIL){
        printf("Graph Error: calling getPath() before calling BFS()\n");
        exit(EXIT_FAILURE);
    }
    if(G->d[u] == INF){                 //check if source and u are even connected at beginning
        append(L, NIL);
        return;                                     //NIL is 0, so source to source is 0 too
    }
    if (G->s == u){
        append(L, u);
    } else if (G->p[u] == NIL){
        return; //when would this case be met though, if I am checking for this at the beginning
    } else {
        getPath(L, G, G->p[u]);
        append(L, u);

    }
}



/*** Manipulation procedures ***/
//deletes all edges of G, restoring it to its original state
//Pre: G!= NULL
void makeNull(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    G -> size = 0;
    G -> s = NIL;
    for (int i = 1; i <= G->order; i++){
        for(int i = 1; i <= G->order; i++){
            clear(G->adj[i]);            //as long as it was initialized, it created a newList, meaning it can be cleared
        }                          
        G -> color[i] = 'w';
        G -> p[i] = NIL;
        G -> d[i] = INF;
    }
}


//helper function that inserts edge x in L = adj[y] in the appropriate spot
//called: addSorted(adj[y], x);
int addSorted(Graph G, List L, int x){
    if (length(L) == 0){
        append(L, x);
    } else {
        bool added = false;
        moveFront(L);
        while(index(L) >= 0 ){              //while cursor is defined
            if (x == get(L) ) { 
                added = true;
                return 1;
            }   
            if (x < get(L) ) { 
                insertBefore(L, x);
                added = true;
                break;
            }   
            moveNext(L);
        }
        if (!added){
            append(L, x);
        }
    }
    return 0;
}

//adds an undirected edge {u,v} to Graph G
//Pre: G!= NULL, 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
    if( G==NULL ){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if(addSorted(G, G -> adj[u], v) != 1 && addSorted(G, G -> adj[v], u) != 1) {
        G->size++;
    }
}

//adds a directed edge {u,v} from vertex u to vertex v
//Pre: G!= NULL
void addArc(Graph G, int u, int v){
    if( G==NULL ){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if(addSorted(G, G -> adj[u], v) != 1) {
        G->size++;
    }
}


//does BFS on Graph G, using vertex s as the source
//Pre: G!= NULL, 1 <= s <= getOrder(G)
void BFS(Graph G, int s){
    if( G==NULL ){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    //check for G is empty (G->size == 0 aka no edges)
    G->s = s;

    for(int i = 1; i <= G->order; i++){
        if (i == s){
            continue;
        }
        G -> color[i] = 'w';
        G -> p[i] = NIL;
        G -> d[i] = INF;
    }

    //DELETE LATER
    //printf("Source: %d\n", s);

    G -> color[s] = 'g';
    G -> d[s] = 0;
    G -> p[s] = NIL;
    List Q = newList();
    prepend(Q, s);
    int x;
    while (length(Q) > 0){
        moveBack(Q); 
        x = get(Q);
        deleteBack(Q);

        moveFront(G->adj[x]); 
        int y;
        while(index(G->adj[x]) >= 0){
            y = get(G->adj[x]);
            if (G->color[y] == 'w'){
                G->color[y] = 'g';
                G->d[y] = G->d[x]+1;
                G->p[y] = x;
                //DELETE LATER
                //printf("Parent: %d, Source: %d\n", x, y);
                prepend(Q, y);
            }
            moveNext(G->adj[x]);
        }
        G->color[x] = 'b';
    }
    freeList(&Q);
}


/*** Other operations ***/
//prints adjacency list of graph G to FILE* out
//Pre: G!= NULL
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}