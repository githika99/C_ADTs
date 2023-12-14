/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa3
*/
//This is a test file for the Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
   
   Graph G = newGraph(8);
   addArc(G, 1, 2);
   addArc(G, 2, 3);
   addArc(G, 2, 5);
   addArc(G, 2, 6);
   addArc(G, 3, 4);
   addArc(G, 3, 7);
   addArc(G, 4, 3);
   addArc(G, 4, 8);
   addArc(G, 5, 1);
   addArc(G, 5, 6);
   addArc(G, 6, 7);
   addArc(G, 7, 6);
   addArc(G, 7, 8);
   addArc(G, 8, 8);

   List S = newList();
   for(int i=1; i<=8;i++){
      append(S,i);
   }

   DFS(G,S);
   //test DFS more intensely
   printf("\nFinal output of DFS is\n");
   printList(stdout, S);


   //test transpose(G) and copy(G)
   Graph cpy = copyGraph(G);
   Graph GT = transpose(G);

   printf("Graph G is:\n");
   printGraph(stdout, G);

   printf("\nGraph cpy is:\n");
   printGraph(stdout, cpy);

   printf("\nGraph GT is:\n");
   printGraph(stdout, GT);

   freeGraph(&cpy);
   freeGraph(&GT);
   freeGraph(&G);
   freeList(&S);
   

    return 0;
}
