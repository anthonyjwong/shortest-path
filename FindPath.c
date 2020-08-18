/*
* Name: AJ Wong
* CruzID: 1652596
* Class: CMPS 101
* Date: 29 May 2019
* Desc: Finds shortest path and distance between two vertices in a Graph.
* File Name: FindPath.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 256

int main(int argc, char* argv[]) {

  int x,y;
  int graphFinished = 0;
  FILE *in, *out;
  char line[MAX_LEN];
  Graph G = NULL;


  // check command line for correct number of arguments
  if( argc != 3 ) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // open files for reading and writing
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if (in == NULL) {
    printf("Unable to read from file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if (out == NULL) {
    printf("Unable to write to file %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  fgets(line, MAX_LEN, in);
  sscanf(line, "%d", &x);
  G = newGraph(x);

  /* read each line of input file, then count and print tokens */
  while( fgets(line, MAX_LEN, in) != NULL)  {
    sscanf(line, "%d %d", &x, &y);
    if (x == 0 && y == 0 && graphFinished != 1) {
      printGraph(out, G);
      fprintf(out, "\n");
      graphFinished = 1;
    }
    else {
      if (graphFinished == 0) {
        addEdge(G, x, y);
      }
      else if (x != 0 && y != 0) {
        BFS(G, x);
        fprintf(out, "The distance from %d to %d is ", x, y);
        int distance = getDist(G, y);
        if (distance == INF) {
          fprintf(out, "infinity\n");
        }
        else {
          fprintf(out, "%d\n", distance);
        }
        List L = newList();
        getPath(L, G, y);
        if (front(L) == NIL) {
          fprintf(out, "No %d-%d path exists", x, y);
        }
        else {
          fprintf(out, "A shortest %d-%d path is: ", x, y);
          printList(out, L);
        }
        fprintf(out, "\n\n");
      }
    }
  }

  /* close input and output files */
  fclose(in);
  fclose(out);
  return(EXIT_SUCCESS);

}
