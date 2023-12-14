/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa3
This version is in git
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
    List* adj;
    char* color;
    int* p;
    int* d;
    int* f;
} GraphObj;

/*** Constructors-Destructors ***/
//creates a newGraph that has n verticies and 0 edges
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert( G!=NULL );
    G -> order = n;
    G -> size = 0;
    G -> adj = (List *) malloc((n+1) * sizeof(List));
    G -> color = (char *) malloc( (n+1) * sizeof(char));
    G -> p = (int *) malloc( (n+1) * sizeof(int));
    G -> d = (int *) malloc( (n+1) * sizeof(int));
    G -> f = (int *) malloc( (n+1) * sizeof(int));

    for (int i = 1; i <= G->order; i++){
        G -> adj[i] = newList();
        G -> color[i] = 'w';
        G -> p[i] = NIL;
        G -> d[i] = UNDEF;
        G -> f[i] = UNDEF;
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
        free((*pG) -> f);
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

//CHANGE FOR DFS
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

//WRITE
//Pre: 1<=u<=n=getOrder(G) 
//Returns the Discover time of u on Graph(G) or UNDEF if DFS has not been run yet
int getDiscover(Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if (u <= 0 || u > G->order){
        printf("Graph Error: calling getParent() with Vertex %d which does not exist in Graph reference\n", u);
        exit(EXIT_FAILURE);
    }
    return (G->d[u]);
    
}


//WRITE
//Pre: 1<=u<=n=getOrder(G) 
//Returns the Finish time of u on Graph(G) or UNDEF if DFS has not been run yet
int getFinish(Graph G, int u){
    if( G==NULL ){
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if (u <= 0 || u > G->order){
        printf("Graph Error: calling getParent() with Vertex %d which does not exist in Graph reference\n", u);
        exit(EXIT_FAILURE);
    }
    return (G->f[u]);
    
}

/*** Manipulation procedures ***/


//helper function that inserts edge x in L = adj[y] in the appropriate spot
//called: addSorted(adj[y], x);
//Potential Probelm: this changes the position of cursor, which for List S, needs to remain in the same place
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

//DFS helper function, not included in header file
void visit(Graph G, List S, int x, int *time){
    G->d[x] = ++(*time);
    G->color[x] = 'g';

    //iterate through List G->adj[x]
    moveFront(G->adj[x]);
    while(index(G->adj[x]) != -1){
        //printf("adj[x] is \n", x);
        int y = get(G->adj[x]);
        if (G->color[y] == 'w'){
            G->p[y] = x;
            visit(G, S, y, time);
        }
        moveNext(G->adj[x]);
    }

    G->color[x] = 'b';
    G->f[x] = ++(*time);
    //finish x
    insertAfter(S, x);                                  //appending in decreasing finish time order
    
}


//Pre: length(S)==getOrder(G)
//perform the depth first search algorithm on G 
//Before DFS, List S defines the order in which vertices are to be processed in DFS
//After DFS, List S will store the vertices by decreasing finish times
void DFS(Graph G, List S){
    if( G==NULL ){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(S) != G->order ){
      printf("Graph Error: calling DFS() with input List not including every vertex in G\n");
      exit(EXIT_FAILURE);
    }
    //check for other condition right now
    for(int x = 1; x <= G->order; x++){
        G->color[x] = 'w';
        G->p[x] = NIL;
    }
    int time = 0;

    //sets cursor at end so that new order can be appended after S
    //from front of S, process an element and then pop it from S (S is stack ---->) (so leftmost side is top)
    moveBack(S);  
    while(true){
        int x = front(S);
        if (G->color[x] == 'w'){
            //printf("\nvisit was called with %d from DFS loop\n", x);
            visit(G, S, x, &time);
        }
        if(x == get(S)){                //this is true loop terminator, condition in while loop is just placeholder
            //printf("loop terminated because front(%d) == cursor(%d)", x, get(S));
            deleteFront(S);
            break;
        }
        deleteFront(S);
    }

}

/*** Other operations ***/

//WRITE
//Pre: G is not Null
//Returns a graph that is the transpose of G (same verticies but the adjacency matrix is transposed)
Graph transpose(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    Graph cpy = newGraph(G->order);
    List temp;
    int curr;
    for(int i = 1; i<= G->order; i++){
        //iterate through each adjacency list
        temp = G->adj[i];
        moveFront(temp);
        while(index(temp) != -1){
            curr = get(temp);
            addArc(cpy, curr, i);
            moveNext(temp);
        }
    }
    return cpy;
}

//Pre: G is not Null
//Returns a new graph that is a copy of G (same verticies and Edges)

//actually you should use newGraph() for this because adj is an array of Lists
//but color, d, p, f are all arrays
//you can use one loop for all of these, and copy G->thatlist[i]
//then you can have one loop to iterate through 
Graph copyGraph(Graph G){
    if( G==NULL ){
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    Graph cpy = malloc(sizeof(GraphObj));
    assert( cpy!=NULL );
    int n = G->order;
    cpy -> order = n;
    cpy -> size = G -> size;
    cpy -> adj = (List *) malloc((n+1) * sizeof(List));
    cpy -> color = (char *) malloc( (n+1) * sizeof(char));
    cpy -> p = (int *) malloc( (n+1) * sizeof(int));
    cpy -> d = (int *) malloc( (n+1) * sizeof(int));
    cpy-> f = (int *) malloc( (n+1) * sizeof(int));

    for (int i = 1; i <= n; i++){
        cpy -> adj[i] = copyList(G -> adj[i]);          //instead of newList in newGraph(), we use copyList, which also returns a new list
        cpy-> color[i] = G->color[i];
        cpy -> p[i] = G->p[i];
        cpy -> d[i] = G->d[i];
        cpy -> f[i] = G->f[i];
    }

    return (cpy);
}


//prints adjacency list of graph G to FILE* out
//Pre: G!= NULL
void printGraph(FILE* out, Graph G){
    if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
    }
    fprintf(out, "\n");
}
