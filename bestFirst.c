#include "bestFirst.h"

struct _bestFirstNode{
    int coords[2];
    float value;
    int parent[2];
};

float getElem(bestFirstNode elem){
    return elem->value;
}

float getElemGen(void* elem){
    return getElem((bestFirstNode)elem);
}

bestFirstNode makeBestFirstNode(int* coords, float value, int* parent){
    bestFirstNode elem = (bestFirstNode)malloc(sizeof(struct _bestFirstNode));
    if(elem == NULL){
        perror("could not create dijkstra Node\n");
        return NULL;
    }
    elem->coords[0] = coords[0];
    elem->coords[1] = coords[1];
    elem->value = value;
    elem->parent[0] = parent[0];
    elem->parent[1] = parent[1];
    return elem;
}

int checkPos(int* position, int matrix[][6]){
    if(position[0] < 0 || position[1] < 0)
        return 1;
    if(position[0] > 5 || position[1] > 5)
        return 1;
    return matrix[position[0]][position[1]];
}

linkedList closest_path(int matrix[][6], hashtable ht,int* key, int* startPos){
    linkedList path = makeLinkedList();
    int* tmp;
    while((key[0] != startPos[0]) || (key[1] != startPos[1])){
        tmp = ((bestFirstNode)getElem_ht(ht, key))->parent;
        key[0] = tmp[0];
        key[1] = tmp[1];
        matrix[key[0]][key[1]] = 5;
        append(path, key);
    }
    return path;
}

float distance(int pointA[2], int pointB[2]){
    return sqrt((((float)pointA[0] + (float)pointB[0])*((float)pointA[0] + (float)pointB[0])) + (((float)pointA[1] + (float)pointB[1]) * ((float)pointA[1] + (float)pointB[1])));
}

linkedList bestFirst(int startPos[2], int finishPos[2], int matrix[][6]){
    hashtable table = makeHashtable();
    bestFirstNode elem = makeBestFirstNode(startPos, 0, startPos);
    printf("created a Node: {%d, %d}, %f\n", elem->coords[0], elem->coords[1], elem->value);
    insert_ht(table, elem->coords, elem);
    binaryTree tree = makeBinaryTree(elem);

    int* pos;
    bestFirstNode currentNode;
    bestFirstNode oldNode;
    while(tree != NULL){
        currentNode = (bestFirstNode)getElem_bt(removeMinNode(&tree));
        printf("Removed a Node: {%d, %d}, %f\n", currentNode->coords[0], currentNode->coords[1], currentNode->value);
        if((currentNode->coords[0] == finishPos[0]) && (currentNode->coords[1] == finishPos[1])){
            linkedList path = closest_path(matrix, table, currentNode->coords, startPos);
            matrix[startPos[0]][startPos[1]] = 2;
            matrix[finishPos[0]][finishPos[1]] = 3;
            return path; 
        }
        matrix[(currentNode->coords)[0]][(currentNode->coords)[1]] = 4; 
        pos = currentNode->coords;
        oldNode = (bestFirstNode)getElem_ht(table, pos);
        if(oldNode != NULL){
            if(oldNode->value < currentNode->value)
                continue;
        }
        for(int i = -1; i < 2; ++i){
            for(int j = -1; j < 2; ++j){
                int chekingPos[2] = {pos[0] + i, pos[1] + j};
                int typePos = checkPos(chekingPos, matrix);
                if((typePos != 0) && (typePos != 3)){continue;}        
                oldNode = (bestFirstNode)getElem_ht(table, chekingPos);
                if(oldNode != NULL){
                    if(oldNode->value > currentNode->value + 1){
                        oldNode->value = currentNode->value + 1;
                        oldNode->parent[0] = currentNode->coords[0];
                        oldNode->parent[1] = currentNode->coords[1];
                        tree = insert_bt(tree, oldNode, getElemGen);
                        printf("changed a Node: {%d, %d}, %f\n", oldNode->coords[0], oldNode->coords[1], oldNode->value);
                    }
                    continue;
                }
                float cost = currentNode->value + distance(chekingPos, finishPos);
                bestFirstNode newNode = makeBestFirstNode(chekingPos, cost, currentNode->coords);
                printf("created a Node: {%d, %d}, %f\n", newNode->coords[0], newNode->coords[1], newNode->value);
                insert_ht(table, newNode->coords, newNode);
                tree = insert_bt(tree, newNode, getElemGen);
                continue;
            }
        }
    }
    freeTree(tree);
    matrix[startPos[0]][startPos[1]] = 2;
    matrix[finishPos[0]][finishPos[1]] = 3;
    return NULL;
}
