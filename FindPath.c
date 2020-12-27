
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]) {

    int order=0; //number of vertices
    Graph G = NULL;
    int v1, v2, src, dest = 0; //v1 first
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    else if (out == NULL) {
        printf("Unable to open file %s for writingn\n", argv[2]);
        exit(1);
    }
    else { //first part of program: prints out adj list representation
        fscanf(in, "%d", &order); 
        G = newGraph(order); 
        while (fgetc(in) != EOF) {
            fscanf(in, "%d %d", &v1, &v2); 
            if (v1 == 0 || v2 == 0) {
                break;
            }
            else{
                addEdge(G, v1, v2);
            }
    }
    printGraph(out, G); 
    fprintf(out, "\n");


    //second part of program
    //entering a loop that prints out a pair of vertices
    while (fgetc(in) != EOF) {
        fscanf(in, "%d %d", &src, &dest);
        if (src == 0 && dest == 0) {
            break;
        }
        List L = newList();
        BFS(G, src);
        getPath(L, G, dest);

        if (getDist(G, dest) != INF) { //when the destination is not infinity
            fprintf(out, "The distance from %d to %d is %d\n", src, dest, length(L) - 1);
            fprintf(out, "A shortest %d-%d path is: ", src, dest);
            printList(out, L); 
            fprintf(out, "\n\n");
        }
        else if(dest == -1){ //cases that the destination is -1
            fprintf(out, "The distance from %d to %d is infinity\n", src, dest);
            fprintf(out, "No %d-%d path exists\n\n", src, dest);
        }
        else{ //the rest of the cases where the distance is infinity
            fprintf(out, "The distance from %d to %d is infinity\n", src, dest);
            fprintf(out, "No %d-%d path exists\n\n", src, dest);
        }
        freeList(&L);
    }

        freeGraph(&G);

}
    fclose(in); 
    fclose(out);
    return(0);
}