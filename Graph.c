
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj {
    List* adj; //array of adjacent lists
    int *color; //array of color
    int *parent; // array of parent of vertex
    int *distance; // dist from vertex i
    int order; //num of vertices
    int size; // num of edges
    int src; //last used vertex

}GraphObj;

Graph newGraph(int n){
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->adj = calloc(n+1, sizeof(List));
    graph->color = calloc(n +1, sizeof(int));
    graph->parent = calloc(n +1, sizeof(int));
    graph->distance = calloc(n +1, sizeof(int));
    graph->order = n;
    graph->size = 0;
    graph->src = NIL;
    for (int i = 1; i <= n; i++) {
        graph->adj[i] = newList();
        graph->color[i] = WHITE; //setting up initial color
        graph->parent[i] = NIL; 
        graph->distance[i] = INF;
    }
    return graph;

}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL) {
        Graph clr = *pG;
        for(int i =1; i < (clr->order + 1); i++) {
            freeList(&(clr->adj[i]));
        }
        free(clr->adj);
        free(clr->parent);
        free(clr->distance);
        free(clr->color);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph error: cannot getOrder() on NULL Graph reference\n");
        exit(1);
    }
    else{
        return G->order;
    }
}

int getSize(Graph G){
    if(G == NULL){
        printf("Graph error: cannot getSize() on NULL Graph reference\n");
        exit(1);
    }
    else{
        return G->size;
    }
}

int getSource(Graph G){
    if(G == NULL){
        printf("Graph error: cannot getSource() on NULL Graph reference\n");
        exit(1);
    }
    else{
        return G->src;
    }
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph error: cannot getParent() on NULL Graph reference\n");
        exit(1);
    }
    else if( u < 1 || u > getOrder(G)){
        printf("Graph error: cannot getParent() if int u is not within bounds\n");
        exit(1);
    }
    else{
        return G->parent[u];
    }
}

int getDist(Graph G, int u){
    if(G == NULL){
        printf("Graph error: cannot getDist() on NULL Graph reference\n");
        exit(1);
    }
    else if(getSource(G) == NIL){
        return INF;
    }
    else if( u < 1 || u > getOrder(G)) {
        printf("Graph error: cannot getDist() if u is not within bounds\n");
        exit(1);
    }
    else{
        return G->distance[u];
    }
}


void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: cannot getPath() on NULL Graph reference\n");
        exit(1);
    }
    else if (u < 1 || u > getOrder(G) ) {
        printf("Graph error: cannot getPath() if u is out of bounds\n");
        exit(1);
    }
    else if (u == getSource(G)) {
        append(L, getSource(G));
    }
    else if (G->parent[u] == NIL)
    {
        append(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}


/*** Manipulation procedures ***/
void makeNull(Graph G){
    if(G == NULL){
        printf("Graph error: cannot getPath() on NULL Graph reference\n");
        exit(1);
    }
    else{
        for(int i=0; i < G->order; i++) {
            clear(G->adj[i]);
            G->distance[i] = INF;
            G->color[i] = WHITE;
            G->parent[i] = NIL;
        }
        G->size = 0;
    }
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph error: cannot addArc() on NULL Graph reference\n");
        exit(1);
    }
    else if ( u < 1 || v < 1){
        printf("Graph error: cannot addArc() if u or v is below the lower bound\n");
        exit(1);
    }
    else if ( u > getOrder(G) || v > getOrder(G) )  {
        printf("Graph error: cannot addArc() if u or v is above the upper bound\n");
        exit(1);
    }
    else{
        addArc(G, u, v);
        addArc(G, v, u);
        G->size--;
    }

}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph error: cannot addArc() on NULL Graph reference\n");
        exit(1);
    }
    else if ( u < 1 || v < 1){
        printf("Graph error: cannot addArc() if u or v is below the lower bound\n");
        exit(1);
    }
    else if ( u > getOrder(G) || v > getOrder(G) )  {
        printf("Graph error: cannot addArc() if u or v is above the upper bound\n");
        exit(1);
    }
    else{
        List L = G->adj[u];
        moveFront(L);
        while(index(L) != -1 && v > get(L)) {
            moveNext(L);
        }
        if(index(L) == -1){
            append(L,v);
            G->size++;
        }
        else{
            insertBefore(L,v);
            G->size++;
        }
    }
}

//utilizing breath for search algorithm given in textbook
void BFS(Graph G, int s) {
    if (G == NULL) {
        printf("Graph error: BFS() called on NULL Graph reference\n");
        exit(1);
    }
    else if(s < 1 || s > getOrder(G)) {
        printf("Graph error: can't call BFS() when variable s is not within bounds\n");
        exit(1);
    }
    else{
        for (int x = 1; x <= getOrder(G); x++) {
            G->color[x] = WHITE;
            G->distance[x] = INF;
            G->parent[x] = NIL;
        }
        G->src = s;
        G->color[s] = GRAY;
        G->distance[s] = 0;
        G->parent[s] = NIL;
        List L = newList();
        append(L, s);
        while(length(L) > 0) {
            int x = front(L);
            deleteFront(L);
            List K = G->adj[x];
            moveFront(K);
            while (index(K) != -1) {
                int y = get(K);
                if (G->color[y] == WHITE) {
                    G->color[y] = GRAY;
                    G->distance[y] = G->distance[x] + 1;
                    G->parent[y] = x;
                    append(L, y);
                }
                else{
                    moveNext(K);
                }
            }
        G->color[x] = BLACK;
        }
        freeList(&L);
    }
}


void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else {
        for(int i = 1; i <= getOrder(G); i++){
            fprintf(out, "%d: ", i);
            printList(out, G->adj[i]);
            fprintf(out, "\n");
        }
    }
}

