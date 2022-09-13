#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
  int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*)malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
  Node* new=(Node*)malloc(sizeof(Node));
  *new= *n;
  return new;
}

Node* read_file (char* file_name){
  Node* n= createNode();
  FILE* file= fopen(file_name, "r");
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
      if(!fscanf (file, "%d", &n->sudo[i][j])) printf("failed to read data!");
    }
  }
  fclose(file);
  return n;
}

void print_node(Node* n){
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++) printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node* n){
  int fila[10];
  int columna[10];
  int submatriz[10];
  for (int i=0; i<9; i++){
    for (int a=0; a<10; a++) fila[a]= 0;
    for (int k=0; k<9; k++){
      if (n->sudo[i][k] != 0){
        if (fila[n->sudo[i][k]] == 1) return 0;
        else fila[n->sudo[i][k]]= 1;
      }
    }
  }
  for (int i=0; i<9; i++){
    for (int b=0; b<10; b++) columna[b]= 0;
    for (int k=0; k<9; k++){
      if (n->sudo[k][i] != 0){
      	if (columna[n->sudo[k][i]] == 1) return 0;
        else columna[n->sudo[k][i]]= 1;
      }
    }
  }

  for (int i=0; i< 9; i++){
        for (int c=0; c<10; c++) submatriz[c]= 0;
        for (int k= 0; k< 9; k++){
            int iSub = 3*(i/3) + (k/3);
            int kSub = 3*(i%3) + (k%3);
            if (n->sudo[iSub][kSub] != 0)
            {
              if (submatriz[n->sudo[iSub][kSub]] == 1) return 0;
              else submatriz[n->sudo[iSub][kSub]] = 1;
            }
          }
      }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, k;
    for (i = 0; i < 9; i++)
    {
      for (k = 0; k < 9; k++)
      {
        if (n->sudo[i][k] == 0)
        {
          for (int newValue = 1; newValue < 10; newValue++)
          {
            n->sudo[i][k] = newValue;
            if (is_valid(n))
            {
              Node* adjNode = copy(n);
              pushBack(list, adjNode);
            }
          }
          n->sudo[i][k] = 0;
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++)
    {
      for (int k = 0; k < 9; k++)
      {
        if (n->sudo[i][k] == 0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  int size = get_size(S);
  *cont = 0;
  while (size != 0)
  {
    Node* n = first(S);
    if (!n) return NULL;
    popFront(S);
    if (is_final(n)) return n;

    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);
    while (aux != NULL)
    {
      push(S, aux);
      aux = next(adj);
    }
    free(aux);
    (*cont)++;
  }
  return NULL;
}

/*int main( int argc, char *argv[] ){
  Node* initial= read_file("s12a.txt");;
  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);
  return 0;
}*/