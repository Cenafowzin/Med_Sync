#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//ÁREA DE RODRIGO:

// estruturas (serão transferidas para o funcs.h)
typedef struct areaNode{
    char *name;
    struct areaNode *next;
} areaNode;

typedef struct specNode{
    char *name;
    areaNode *area;
    struct specNode *next;
} specNode;

// ESPECIALIZACAO ---------------------------------------------------------------

specNode *selectSpec(areaNode *SelectedArea, specNode *SpecHead, specNode *PrevSelected){

    if(SelectedArea == NULL){
        printf("Nenhuma especialização selecionada");
        return NULL;
    }

    if (SpecHead == NULL){
        printf("Não existe nenhuma especialização\n-----------------\n");
        return NULL;

    }else{
        int area, count = 0;
        specNode *current = SpecHead;

        printf("(%d) voltar\n-----------------\n", count);
        count++;

        while(current != NULL){

            if(current->area == SelectedArea){
                printf("(%d) %s\n-----------------\n", (count), current->name);
                current = current->next;
                count++;
            }

            current = current->next;
        }

        printf("Digite o numero da especialização: ");
        scanf("%d", &area);

        if (area == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;

        }
        if(area > count || area < 0){
            printf("Opção inválida\n");
            return NULL;
        }

        current = SpecHead;
        count = 1;

        while(count != area){
            if(current->area == SelectedArea){
                current = current->next;
                count++;
            }
            current = current->next;
        }

        return current;
    }
}

void createSpec(areaNode *SelectedArea, specNode **SpecHead){

    if(SelectedArea == NULL){
        printf("Nenhuma especialização selecionada");
        return;
    }

    printf("Digite o nome da especialização que deseja criar:\n");
    char ch = getchar();

    if(ch == '\n'){
        printf("Você não pode criar uma especialização sem nome!\n");
        return;
    }

    if(*SpecHead == NULL){

        *SpecHead = (specNode *)malloc(sizeof(specNode));
        int size = 0;
        (*SpecHead)->name = (char *)malloc(sizeof(char));
        (*SpecHead)->name[size] = ch;

        while(ch != '\n'){
            (*SpecHead)->name = (char *)realloc(((*SpecHead)->name), (size + 2) * sizeof(char));
            (*SpecHead)->name[size] = ch;
            size++;

            ch = getchar();
        }
        (*SpecHead)->name[size] = '\0';
        (*SpecHead)->area = SelectedArea;
        (*SpecHead)->next = NULL;

    }else{

        specNode *current = *SpecHead;

        while(current->next != NULL){
            current = current->next;
        }

        current->next = (specNode *)malloc(sizeof(specNode));
        current = current->next;

        int size = 0;
        current->name = (char *)malloc(sizeof(char));
        current->name[size] = ch;

        while(ch != '\n'){
            current->name = (char *)realloc((current->name), (size + 2) * sizeof(char));
            current->name[size] = ch;
            size++;

            ch = getchar();
        }
        current->name[size] = '\0';
        current->area = SelectedArea;
        current->next = NULL;
    }
}

void editSpec(areaNode *SelectedArea, specNode **SpecHead){
    
    specNode *selectedSpec = NULL;

    selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);
    getchar();

    if(selectedSpec == NULL || *SpecHead == NULL){
        printf("Nenhuma especialização");
        return;

    }else{
        printf("Digite o novo nome da especialização:\n");
        char ch = getchar();

        if(ch == '\n'){
            printf("Você não deixar uma especialização sem nome!\n");
            return;
        }

        int size = 0;
        selectedSpec->name = (char *)realloc((selectedSpec->name), sizeof(char));
        selectedSpec->name[size] = ch;

        while(ch != '\n'){
            selectedSpec->name = (char *)realloc((selectedSpec->name), (size + 2) * sizeof(char));
            selectedSpec->name[size] = ch;
            size++;

            ch = getchar();
        }
        selectedSpec->name[size] = '\0';
        
    }
}

void deleteSpec(areaNode *SelectedArea, specNode **SpecHead){
    specNode *selectedSpec = NULL, *current = *SpecHead, *temp = NULL;

    selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);

    if(selectedSpec == NULL || *SpecHead == NULL){
        printf("Nenhuma área");
        return;

    }else if( *SpecHead == selectedSpec){
        temp = *SpecHead;
        *SpecHead = (*SpecHead)->next;
        free(temp);
        
    }else{
        while(current->next != selectedSpec){
            current = current->next;
        }

        temp = current->next;
        current->next = current->next->next;
        free(temp);
        
    }
}

void menuSpec(areaNode *SelectedArea, specNode *SpecHead){
    int command = -1;
    specNode *selectedSpec = NULL;

    while(command != 0){
        printf("Área: %s\n|----------------|\n", SelectedArea->name);
        
        if(SpecHead == NULL){
            printf("Não existe nenhuma área\n-----------------\n");
        }else{
            specNode *current = SpecHead;

            while(current != NULL){
                if(current->area == SelectedArea){
                    printf("%s\n-----------------\n", current->name);
                    current = current->next;

                }
                
                current = current->next;
            }
        }

        printf("Selecione uma ação para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar especialização\n");
        printf("(2) editar especialização\n");
        printf("(3) selecionar especialização\n");
        printf("(4) deletar especialização\n");
        scanf("%d", &command);

        switch(command){
        case 0:
            return;
            break;
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createSpec(SelectedArea, &SpecHead);
            printf("\033[H\033[2J");
            break;

        case 2:
            printf("\033[H\033[2J");
            editSpec(SelectedArea, &SpecHead);
            printf("\033[H\033[2J");

            break;

        case 3:
            printf("\033[H\033[2J");
            selectedSpec = selectSpec(SelectedArea, SpecHead, selectedSpec);
            printf("\033[H\033[2J");

            if(selectedSpec != NULL){
                printf("[%s]\n\n", selectedSpec->name);
            }
            break;

        case 4:
            printf("\033[H\033[2J");
            deleteSpec(SelectedArea, &SpecHead);
            printf("\033[H\033[2J");
        }
    }

}

// AREA -------------------------------------------------------------------------

areaNode *selectArea(areaNode *AreaHead, areaNode *PrevSelected){

    if (AreaHead == NULL){
        printf("Não existe nenhuma área\n-----------------\n");

        return NULL;
    }else{
        int area, count = 0;
        areaNode *current = AreaHead;

        printf("(%d) voltar\n-----------------\n", count);
        count++;

        while(current != NULL){
            printf("(%d) %s\n-----------------\n", (count), current->name);
            current = current->next;
            count++;
        }

        printf("Digite o numero da área: ");
        scanf("%d", &area);

        if (area == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;
        }
        if(area > count || area < 0){
            printf("Opção inválida\n");
            return NULL;
        }

        current = AreaHead;
        count = 1;

        while(count != area){
            current = current->next;
            count++;
        }

        return current;
    }
}

void createArea(areaNode **AreaHead){
    printf("Digite o nome da área que deseja criar:\n");
    char ch = getchar();

    if(ch == '\n'){
        printf("Você não pode criar uma área sem nome!\n");
        return;
    }

    if(*AreaHead == NULL){

        *AreaHead = (areaNode *)malloc(sizeof(areaNode));
        int size = 0;
        (*AreaHead)->name = (char *)malloc(sizeof(char));
        (*AreaHead)->name[size] = ch;

        while(ch != '\n'){
            (*AreaHead)->name = (char *)realloc(((*AreaHead)->name), (size + 2) * sizeof(char));
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
            current->name = (char *)realloc((current->name), (size + 2) * sizeof(char));
            current->name[size] = ch;
            size++;

            ch = getchar();
        }
        current->name[size] = '\0';
        current->next = NULL;
    }
}

void editArea(areaNode **AreaHead){
    
    areaNode *selectedArea = NULL;

    selectedArea = selectArea(*AreaHead, selectedArea);
    getchar();
    if(selectedArea == NULL || *AreaHead == NULL){
        printf("Nenhuma área");
        return;
    }else{
        printf("Digite o novo nome da área:\n");
        char ch = getchar();

        if(ch == '\n'){
            printf("Você não deixar uma área sem nome!\n");
            return;
        }

        int size = 0;
        selectedArea->name = (char *)realloc((selectedArea->name), sizeof(char));
        selectedArea->name[size] = ch;

        while(ch != '\n'){
            selectedArea->name = (char *)realloc((selectedArea->name), (size + 2) * sizeof(char));
            selectedArea->name[size] = ch;
            size++;

            ch = getchar();
        }
        selectedArea->name[size] = '\0';
        
    }
}

void deleteArea(areaNode **AreaHead){
    areaNode *selectedArea = NULL, *current = *AreaHead, *temp = NULL;

    selectedArea = selectArea(*AreaHead, selectedArea);

    if(selectedArea == NULL || *AreaHead == NULL){
        printf("Nenhuma área");
        return;

    }else if( *AreaHead == selectedArea){
        temp = *AreaHead;
        *AreaHead = (*AreaHead)->next;
        free(temp);
        
    }else{
        while(current->next != selectedArea){
            current = current->next;
        }

        temp = current->next;
        current->next = current->next->next;
        free(temp);
        
    }
}

void menuArea(areaNode *AreaHead, specNode *SpecHead){
    int command = -1;
    areaNode *selectedArea = NULL;

    while(command != 0){
        if(AreaHead == NULL){
            printf("Não existe nenhuma área\n-----------------\n");
        }else{
            areaNode *current = AreaHead;

            while(current != NULL){
                printf("%s\n-----------------\n", current->name);
                current = current->next;
            }
        }

        printf("Selecione uma ação para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar área\n");
        printf("(2) editar área\n");
        printf("(3) selecionar área\n");
        printf("(4) deletar área\n");
        printf("(5) ver especializações de uma área\n");
        scanf("%d", &command);

        switch(command){
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createArea(&AreaHead);
            printf("\033[H\033[2J");
            break;

        case 2:
            printf("\033[H\033[2J");
            editArea(&AreaHead);
            printf("\033[H\033[2J");

            break;

        case 3:
            printf("\033[H\033[2J");
            selectedArea = selectArea(AreaHead, selectedArea);
            printf("\033[H\033[2J");

            if(selectedArea != NULL){
                printf("[%s]\n\n", selectedArea->name);
            }
            break;

        case 4:
            printf("\033[H\033[2J");
            deleteArea(&AreaHead);
            printf("\033[H\033[2J");

        case 5:
            printf("\033[H\033[2J");
            selectedArea = selectArea(AreaHead, selectedArea);
            printf("\033[H\033[2J");
            menuSpec(selectedArea, SpecHead);
            printf("\033[H\033[2J");
        }
    }

}

// testes (será apagado no fim)
int main()
{

    areaNode *currentArea, *AreaHead = NULL, *selectedArea = NULL;
    specNode *currentSpec, *SpecHead = NULL, *selectedSpec = NULL;

    menuArea(AreaHead, SpecHead);

    return 0;
}

//ÁREA DE FLÁVIO:

//ÁREA DE VICTOR:

//ÁREA DE JOÃO:

//ÁREA DE HENRIQUE:

//ÁREA DE DIEGO:

