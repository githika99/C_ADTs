/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa2
*/
//This is a test file for the Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){

    
   Graph N = newGraph(4);              //Verticies of graph are 1, 2, 3, 4
    addEdge(N, 1, 4);
    addEdge(N, 1, 3);
    addArc(N, 2, 3);
    printf("Size of N is: %d\n", getSize(N));
    addEdge(N, 2, 4);
    printGraph(stdout, N);
    printf("Order of N is: %d\n", getOrder(N)); 
    printf("Size of N is: %d\n", getSize(N)); 
    printf("Soruce of N is: %d\n", getSource(N)); 
    printf("Parent of %d is: %d\n", 3, getParent(N, 3));
    printf("getDist of %d is: %d\n", 3, getDist(N, 3));
    printf("\n");
    
    BFS(N,1);
    printf("Soruce of N is: %d\n", getSource(N)); 
    printf("Parent of %d is: %d\n", 3, getParent(N, 3));
    printf("Parent of %d is: %d\n", 4, getParent(N, 4));
    printf("Parent of %d is: %d\n", 2, getParent(N, 2));
    printf("getDist of %d is: %d\n", 3, getDist(N, 3));
    printf("getDist of %d is: %d\n", 4, getDist(N, 4));
    printf("getDist of %d is: %d\n", 2, getDist(N, 2));
    
    List L = newList();
    getPath(L,N,3);
    printf("getPath for %d is: ", 3);
    printList(stdout, L);
    clear(L);

    getPath(L,N,4);
    printf("getPath for %d is: ", 4);
    printList(stdout, L);
    clear(L);

    getPath(L,N,2);
    printf("getPath for %d is: ", 2);
    printList(stdout, L);
    clear(L);
    

    printf("\n");

    makeNull(N);
    printf("Size of N is: %d\n", getSize(N));
    printf("Order of N is: %d\n", getOrder(N)); 
    freeList(&L);
    freeGraph(&N);
    
    printf("\n\nTantalo Tests\n\n");

    
   //Tantalo Tests
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

    return 0;
}

/*  Output should look like:
Size of G is: 3
1: 3 4
2: 3 4
3: 1
4: 1 2
Order of G is: 4
Size of G is: 4
Source of G is: NIL
Parent of 3 is: NIL
getDist of 3 is: NIL

Source of G is: 1
Parent of 3 is: 1
Parent of 4 is: 1
Parent of 2 is: 4
getDist of 3 is: 1
getDist of 4 is: 1
getDist of 2 is: 2
getPath of 3 is: 1 3
getPath of 4 is: 1 4
getPath of 2 is: 1 3 2

Size of G is: 0
Order of G is: 4

Tantalo Tests


1: 2 8
2: 1 3 9
3: 2 4 10
4: 3 5 11
5: 4 6 12
6: 5 7 13
7: 6 14
8: 1 9 15
9: 2 8 10 16 31
10: 3 9 11 17
11: 4 10 12 18
12: 5 11 13 19
13: 6 12 14 17 20
14: 7 13 21 33
15: 8 16 22
16: 9 15 17 23
17: 10 13 16 18 24
18: 11 17 19 25
19: 12 18 20 26
20: 13 19 21 27
21: 14 20 28
22: 15 23 29
23: 16 22 24 30
24: 17 23 25 31
25: 18 24 26 32
26: 19 25 27 33
27: 20 26 28 34
28: 21 27 35
29: 22 30
30: 23 29 31
31: 9 24 30 32
32: 25 31 33
33: 14 26 32 34
34: 27 33 35
35: 28 34

Radius = 5
Central vertices: 13 17 18 24 25 31 32 33
Diameter = 8
Peripheral vertices: 1 28
*/

