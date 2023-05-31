#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//ÁREA DE RODRIGO:

//estruturas (serão transferidas para o funcs.h)
typedef struct areaNode {
  char *name;
  struct areaNode *next;
} areaNode;

typedef struct specNode {
  char *name;
  areaNode *area;
  struct specNode *next;
} specNode;

void saveArea(areaNode *AreaHead){
  
}

areaNode* selectArea(areaNode *AreaHead){

  if(AreaHead == NULL){
    printf("Não existe nenhuma área");

    return NULL;
  }else{
    int area, count = 0;
    areaNode* current = AreaHead;

    while(current->next != NULL){
      printf("(%d) %s\n", (count+1), current->name);
      current = current->next;
      count++;
    }
    printf("(%d) %s\n", (count+1), current->name);

    printf("Digite o numero da área: ");
    scanf("%d", &area);

    current = AreaHead;
    count = 0;

    while(count != (area-1)){
      current = current->next;
      count++;
    }
    
    return current;
  }
  
}

void createArea(areaNode **AreaHead){

  char ch = getchar();

  if(ch == '\n'){
    printf("Você não pode criar uma área sem nome!");
    return;
  }

  if(*AreaHead == NULL){

    *AreaHead = (areaNode *)malloc(sizeof(areaNode));
    int size = 0;
    (*AreaHead)->name = (char *)malloc(sizeof(char));
    (*AreaHead)->name[size] = ch;

    while(ch != '\n'){
      (*AreaHead)->name =
          (char *)realloc(((*AreaHead)->name), (size + 2) * sizeof(char));
      (*AreaHead)->name[size] = ch;
      size++;

      ch = getchar();
    }
    (*AreaHead)->name[size] = '\0';
    (*AreaHead)->next = NULL;
    
  }else{

    areaNode *current = *AreaHead;

    while(current->next != NULL){
      current = current->next;
    }

    current->next = (areaNode *)malloc(sizeof(areaNode));
    current = current->next;

    int size = 0;
    current->name = (char *)malloc(sizeof(char));
    current->name[size] = ch;

    while(ch != '\n'){
      current->name =
          (char *)realloc((current->name), (size + 2) * sizeof(char));
      current->name[size] = ch;
      size++;

      ch = getchar();
    }
    current->name[size] = '\0';
    current->next = NULL;
  }
  
}


//testes (será apagado no fim)
int main(){

  areaNode *current, *AreaHead = NULL, *selectedArea = NULL;

  createArea(&AreaHead);
  createArea(&AreaHead);
  createArea(&AreaHead);
  createArea(&AreaHead);

  current = AreaHead;

  selectedArea = selectArea(AreaHead);

  printf("[%s]\n", selectedArea->name);

  return 0;
}

//ÁREA DE FLÁVIO:

//ÁREA DE VICTOR:

//ÁREA DE JOÃO:

//ÁREA DE HENRIQUE:

//ÁREA DE DIEGO:

