/*
* Name: AJ Wong
* CruzID: 1652596
* Class: CMPS 101
* Date: 29 May 2019
* Desc: Implementation file for Graph ADT
* File Name: Graph.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Graph.h"

// GraphObj
typedef struct GraphObj {
  List *adj;
  int order;
  int size;
  int *color; // white = 0, grey = 1, black = 2
  int *distance;
  int *parent;
  int source;
} GraphObj;

// newGraph()
// constructor for the Graph type
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
  G->adj = calloc(n + 1, sizeof(ListObj));
  G->color = calloc(n + 1, sizeof(int));
  G->distance = calloc(n + 1, sizeof(int));
  G->parent = calloc(n + 1, sizeof(int));
  assert(G != NULL);
  assert(G->adj != NULL);
  assert(G->color != NULL);
  assert(G->distance != NULL);
  assert(G->parent != NULL);
  for (int i = 1; i <= n; i++) {
    G->adj[i] = newList();
    G->color[i] = 0;
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  G->order = n;
  G->size = 0;
  G->source = NIL;
  return G;
}

// freeGraph()
// destructor for the Graph type
void freeGraph(Graph* pG) {
  if (pG != NULL && *pG != NULL) {
    for (int i = 1; i <= (*pG)->order; i++) {
      freeList(&((*pG)->adj[i]));
    }
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->distance);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
  }
}

/*** Access functions ***/
int getOrder(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: getOrder() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->order;
}

int getSize(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: getSize() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->size;
}

int getSource(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: getSource() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->source;
}

int getParent(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: getParent() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: getParent() called using invalid index u\n");
    exit(EXIT_FAILURE);
  }
  return G->parent[u];
}

int getDist(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: getDist() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: getDist() called using invalid index u\n");
    exit(EXIT_FAILURE);
  }
  return G->distance[u];
}

void getPath(List L, Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: getPath() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (getSource(G) == NIL) {
    fprintf(stderr, "Graph Error: getPath() called on Graph with source of NIL\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: getPath() called using invalid index u\n");
    exit(EXIT_FAILURE);
  }
  if (G->distance[u] == INF) {
    append(L, NIL);
  }
  else {
    if (u != G->source) {
      getPath(L, G, G->parent[u]);
    }
    append(L, u);
  }
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: makeNull() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= G->order; i++) {
    clear(G->adj[i]);
  }
  G->size = 0;
}

void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: addEdge() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: addEdge() called using invalid index u\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > G->order) {
    fprintf(stderr, "Graph Error: addEdge() called using invalid index v\n");
    exit(EXIT_FAILURE);
  }
  addArc(G, u, v);
  addArc(G, v, u);
  G->size--; // because we want to add one edge, not two arcs
}

void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: addArc() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: addArc() called using invalid index u\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > G->order) {
    fprintf(stderr, "Graph Error: addArc() called using invalid index v\n");
    exit(EXIT_FAILURE);
  }
  moveFront(G->adj[u]);
  while (index(G->adj[u]) != -1 && v > get(G->adj[u])) {
    moveNext(G->adj[u]);
  }
  if (index(G->adj[u]) != -1) { // index did not fall off list
    insertBefore(G->adj[u], v);
  }
  else {
    append(G->adj[u], v);
  }
  G->size++;

}

void BFS(Graph G, int s) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: BFS() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= G->order; i++) { // reset discovery states
    G->color[i] = 0;
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  int x;
  G->source = s;
  G->color[s] = 1;
  G->distance[s] = 0;
  G->parent[s] = NIL;
  List L = newList();
  append(L, s);
  while (length(L) != 0) {
    x = front(L);
    deleteFront(L);
    moveFront(G->adj[x]);
    while (index(G->adj[x]) != -1) {
      int y = get(G->adj[x]);
      if (G->color[y] == 0) {
        G->color[y] = 1;
        G->distance[y] = G->distance[x] + 1;
        G->parent[y] = x;
        append(L, y);
      }
      moveNext(G->adj[x]);
    }
    G->color[x] = 2;
  }
  freeList(&L);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: printGraph() called on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= G->order; i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
    fprintf(out, "\n");
  }
}
