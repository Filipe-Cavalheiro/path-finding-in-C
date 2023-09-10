#include "breathFirst.h"

typedef struct {
    int coords[2];
}_BFNode, *BFNode;

BFNode makeBFNode(int* coords){
    BFNode elem = (BFNode)malloc(sizeof(_BFNode));
    if(elem == NULL){
        perror("Failed to allocate memory for the breath first Node\n");
        return NULL;
    }
    elem->coords[0] = coords[0];
    elem->coords[1] = coords[1];
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
        tmp = getElem_ht(ht, key);
        key[0] = tmp[0];
        key[1] = tmp[1];
        matrix[key[0]][key[1]] = 5;
        append(path, key);
    }
    return path;
}

linkedList breathFirstSearch(int startPos[2], int finishPos[2], int matrix[][6]){
    linkedList queue = makeLinkedList();
    hashtable table = makeHashtable();
    BFNode currentNode = makeBFNode(startPos);
    append(queue, currentNode);
    insert_ht(table, startPos, startPos);

    int* pos;
    while(sizeList(queue) != 0){
        pos = ((BFNode)popList(queue))->coords;

        for(int i = -1; i < 2; ++i){
            for(int j = -1; j < 2; ++j){
                int chekingPos[2] = {pos[0] + i, pos[1] + j};
                int typePos = checkPos(chekingPos, matrix);
                if((typePos == 0) || (typePos == 3)){
                    matrix[chekingPos[0]][chekingPos[1]] = 4;
                    currentNode = makeBFNode(chekingPos);
                    append(queue, currentNode);
                    insert_ht(table, chekingPos, pos);
                    if((chekingPos[0] == finishPos[0]) && (chekingPos[1] == finishPos[1])){
                        linkedList path = closest_path(matrix, table, chekingPos, startPos);
                        matrix[startPos[0]][startPos[1]] = 2;
                        matrix[finishPos[0]][finishPos[1]] = 3;
                        return path;
                    }
                }
            }
        }
    }
    matrix[startPos[0]][startPos[1]] = 2;
    matrix[finishPos[0]][finishPos[1]] = 3;
    return NULL;
}
