#ifndef ASTAR_H
#define ASTAR_H

#include "../Data-structures-in-C/hashtable.h"
#include "../Data-structures-in-C/binaryTree.h"
#include "../Data-structures-in-C/linkedList.h"
#include <stdio.h>
typedef struct _aStarNode *aStarNode;
#include "aStar.c"

int getElem(aStarNode elem);

int getElemGen(void* elem);

aStarNode makeDijkstraNode(int* coords, float value, int* parent);

int checkPos(int* position, int matrix[][6]);

linkedList closest_path(int matrix[][6], hashtable ht,int* key, int* startPos);

float distance(int pointA[2], int pointB[2]);

linkedList dijkstra(int startPos[2], int finishPos[2], int matrix[][6], int* costMatrix);
#endif // ASTAR_H
