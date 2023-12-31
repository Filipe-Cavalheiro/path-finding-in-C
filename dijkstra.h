#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../Data-structures-in-C/hashtable.h"
#include "../Data-structures-in-C/binaryTree.h"
#include "../Data-structures-in-C/linkedList.h"
typedef struct _dijkstraNode *dijkstraNode;
#include "dijkstra.c"

int getElem(dijkstraNode elem);

int getElemGen(void* elem);

dijkstraNode makeDijkstraNode(int* coords, int value, int* parent);

int checkPos(int* position, int matrix[][6]);

linkedList closest_path(int matrix[][6], hashtable ht,int* key, int* startPos);

linkedList dijkstra(int startPos[2], int finishPos[2], int matrix[][6], int* costMatrix);
#endif // DIJKSTRA_H
