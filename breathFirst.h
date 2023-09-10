#ifndef BREATHFIRST_H
#define BREATHFIRST_H 

#include "../Data-structures-in-C/hashtable.h"
#include "../Data-structures-in-C/linkedList.h"
#include "breathFirst.c"

int checkPos(int* pos,int matrix[][6]);
linkedList closest_path(int matrix[][6], hashtable ht,int* key, int* startPos);
linkedList breathFirstSearch(int startPos[2], int finishPos[2], int matrix[][6]);

#endif /* BREATHFIRST_H */
