#ifndef ASTAR_H
#define ASTAR_H

#include "../Data-structures-in-C/hashtable.h"
#include "../Data-structures-in-C/binaryTree.h"
#include "../Data-structures-in-C/linkedList.h"
#include <stdio.h>
typedef struct _bestFirstNode *bestFirstNode;
#include "bestFirst.c"

float getElem(bestFirstNode elem);

float getElemGen(void* elem);

bestFirstNode makeBestFirstNode(int* coords, float value, int* parent);

int checkPos(int* position, int matrix[][6]);

linkedList closest_path(int matrix[][6], hashtable ht,int* key, int* startPos);

float distance(int pointA[2], int pointB[2]);

linkedList bestFirst(int startPos[2], int finishPos[2], int matrix[][6]);
#endif // ASTAR_H
