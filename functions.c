#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//aREA DE RODRIGO:

// estruturas (serao transferidas para o funcs.h)
typedef struct areaNode{
    char *name;
    struct areaNode *next;
} areaNode;

typedef struct specNode{
    char *name;
    char *area;
    struct specNode *next;
} specNode;

typedef struct actvNode{
    char *name;
    int mod;
    char *spec;
    struct actvNode *next;
} actvNode;

typedef struct questForm{
    int type;
    char *activity;//FAZ A LIGAÇÃO ENTRE PERGUNTA E ATIVIDADE
    char *quest;
    int nAlts;
    char **alternatives;
    struct questForm *next;
} questForm;

typedef struct questFormResp{
    char *activity;
    char *quest;
    char *answer;
    int *alternative;
    struct questFormResp *next;
} questFormResp;

// ATIVIDADE ---------------------------------------------------------------

actvNode *selectActv(specNode *SelectedSpec, actvNode *ActvHead, actvNode *PrevSelected){

    if(SelectedSpec == NULL){
        printf("Nenhuma especializacao selecionada");
        return NULL;
    }

    if (ActvHead == NULL){
        printf("Nao existe nenhuma atividade\n-----------------\n");
        return NULL;

    }else{
        int atcv, count = 0;
        actvNode *current = ActvHead;

        printf("(%d) voltar\n-----------------\n", count);
        count++;

        while(current != NULL){
            if(strcmp(current->spec, SelectedSpec->name) == 0){
                printf("(%d) %s\n-----------------\n", count, current->name);
                current = current->next;
                count++;
            }else{
                current = current->next;

            }
        }

        printf("Digite o numero da atividade: ");
        scanf("%d", &atcv);

        if (atcv == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;

        }

        if(atcv > count || atcv < 0){
            printf("Opcao invalida\n");
            return NULL;
        }

        current = ActvHead;
        count = 1;

        while(count <= atcv){
            if(count == atcv && strcmp(current->spec, SelectedSpec->name) == 0){
                return current;

            }else if(strcmp(current->spec, SelectedSpec->name) == 0){
                current = current->next;
                count++;
            }else{
                current = current->next;
            }
        }

        return current;
    }
}

void createActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail){
    char ch;
    int mod;

    if(SelectedSpec == NULL){
        printf("Nenhuma especializacao selecionada");
        return;
    }

    printf("(0) Teorica\n");
    printf("(1) Pratica\n");
    printf("Digite a modalidade da atividade:\n");
    scanf("%d", &mod);

    if(mod < 0 && mod > 1){
        printf("Opcao invalida");
        return;
    }
    
    getchar();
    printf("Digite o nome da atividade que deseja criar:\n");
    ch = getchar();

    if(ch == '\n'){
        printf("Voce nao pode criar uma atividade sem nome!\n");
        return;
    }

    if(*ActvHead == NULL){

        int size = 0;

        *ActvHead = (actvNode *)malloc(sizeof(actvNode));
        (*ActvHead)->name = (char *)malloc(sizeof(char));
        (*ActvHead)->name[size] = ch;

        while(ch != '\n'){
            (*ActvHead)->name = (char *)realloc(((*ActvHead)->name), (size + 2) * sizeof(char));
            (*ActvHead)->name[size] = ch;
            size++;

            ch = getchar();
        }

        (*ActvHead)->name[size] = '\0';
        (*ActvHead)->spec = (char *)malloc(sizeof(SelectedSpec->name));
        strcpy((*ActvHead)->spec, SelectedSpec->name);
        (*ActvHead)->mod = mod;
        (*ActvHead)->next = NULL;
        *ActvTail = *ActvHead;

    }else{
        (*ActvTail)->next = (actvNode *)malloc(sizeof(actvNode));
        (*ActvTail) = (*ActvTail)->next;

        int size = 0;
        (*ActvTail)->name = (char *)malloc(sizeof(char));
        (*ActvTail)->name[size] = ch;

        while(ch != '\n'){
            (*ActvTail)->name = (char *)realloc(((*ActvTail)->name), (size + 2) * sizeof(char));
            (*ActvTail)->name[size] = ch;
            size++;

            ch = getchar();
        }

        (*ActvTail)->name[size] = '\0';
        (*ActvTail)->spec = (char *)malloc(sizeof(SelectedSpec->name));
        strcpy((*ActvTail)->spec, SelectedSpec->name);
        (*ActvTail)->mod = mod;
        (*ActvTail)->next = NULL;
    }
}

void editActv(specNode *SelectedSpec, actvNode **ActvHead){
    
    actvNode *selectedActiv = NULL;

    selectedActiv = selectActv(SelectedSpec, *ActvHead, selectedActiv);
    getchar();

    if(selectedActiv == NULL || *ActvHead == NULL){
        printf("Nenhuma atividade");
        return;

    }else{
        printf("Digite o novo nome da atividade:\n");
        char ch = getchar();

        if(ch == '\n'){
            printf("Voce nao deixar uma atividade sem nome!\n");
            return;
        }

        int size = 0;
        selectedActiv->name = (char *)realloc(selectedActiv->name, sizeof(char));
        selectedActiv->name[size] = ch;

        while(ch != '\n'){
            selectedActiv->name = (char *)realloc(selectedActiv->name, (size + 2) * sizeof(char));
            selectedActiv->name[size] = ch;
            size++;

            ch = getchar();
        }
        selectedActiv->name[size] = '\0';
        
    }
}

void deleteActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail){
    actvNode *selectedActiv = NULL, *current = *ActvHead, *temp = NULL;

    selectedActiv = selectActv(SelectedSpec, *ActvHead, selectedActiv);

    if(selectedActiv == NULL || *ActvHead == NULL){
        printf("Nenhuma atividade");
        return;

    }else if( *ActvHead == selectedActiv){
        temp = *ActvHead;
        *ActvHead = (*ActvHead)->next;
        free(temp->name);
        free(temp->spec);
        free(temp);
        
    }else{
        while(current->next != selectedActiv){
            current = current->next;
        }

        temp = current->next;
        current->next = current->next->next;
        free(temp->name);
        free(temp->spec);
        free(temp);
        
    }

    if(*ActvHead == NULL){
        *ActvTail = NULL;
    }
}

//FORMULARIO ---------------------------------------------------------------

void createQuestForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail){
    char ch;
    int type, alts;

    if(SelectedActiv == NULL){
        printf("Nenhuma atividade selecionada");
        return;
    }
    
    printf("(0) Aberta\n");
    printf("(1) Fechada\n");
    printf("Selecione o tipo de pergunta:\n");
    scanf("%d", &type);

    if(type < 0 || type > 1){
        printf("Opcao invalida");
        return;
    }

    getchar();
    printf("Digite o que quer escrever na pergunta:\n");
    ch = getchar();

    if(ch == '\n'){
        printf("Voce nao pode criar uma pergunta sem nome!\n");
        return;
    }

    if(*FormHead == NULL){
        int size = 0;

        *FormHead = (questForm*)malloc(sizeof(questForm));
        (*FormHead)->quest = (char *)malloc(sizeof(char));
        (*FormHead)->quest[size] = ch;

        while(ch != '\n'){
            (*FormHead)->quest = (char *)realloc(((*FormHead)->quest), (size + 2) * sizeof(char));
            (*FormHead)->quest[size] = ch;
            size++;

            ch = getchar();
        }
        (*FormHead)->quest[size] = '\0';

        (*FormHead)->activity = (char *)malloc(sizeof(SelectedActiv->name));
        strcpy((*FormHead)->activity, SelectedActiv->name);
        (*FormHead)->type = type;
        (*FormHead)->next = NULL;
        *FormTail = *FormHead;

        if(type == 0){
            (*FormHead)->alternatives = NULL;
            (*FormHead)->nAlts = 0;
            return;
        
        }else{
            printf("Digite o numero de alternativas:\n");
            scanf("%d", &alts);
            getchar();

            (*FormHead)->alternatives = (char**)calloc(alts, sizeof(char*));


            for(int i=0; i<alts; i++){
                size = 0;

                printf("Digite a alternativa %d:\n", i+1);
                ch = getchar();

                (*FormHead)->alternatives[i] = (char *)malloc(sizeof(char));
                (*FormHead)->alternatives[i][size] = ch;

                while(ch != '\n'){
                    (*FormHead)->alternatives[i] = (char *)realloc(((*FormHead)->alternatives[i]), (size + 2) * sizeof(char));
                    (*FormHead)->alternatives[i][size] = ch;
                    size++;

                    ch = getchar();
                }
                (*FormHead)->alternatives[i][size] = '\0';

                (*FormHead)->nAlts = alts;
            }
        }

    }else{
        (*FormTail)->next = (questForm*)malloc(sizeof(questForm));
        (*FormTail) = (*FormTail)->next;

        int size = 0;
        (*FormTail)->quest = (char *)malloc(sizeof(char));
        (*FormTail)->quest[size] = ch;

        while(ch != '\n'){
            (*FormTail)->quest = (char *)realloc(((*FormTail)->quest), (size + 2) * sizeof(char));
            (*FormTail)->quest[size] = ch;
            size++;

            ch = getchar();
        }
        (*FormTail)->quest[size] = '\0';

        (*FormTail)->activity = (char *)malloc(sizeof(SelectedActiv->name));
        strcpy((*FormTail)->activity, SelectedActiv->name);
        (*FormTail)->type = type;
        (*FormTail)->next = NULL;

        if(type == 0){
            (*FormTail)->alternatives = NULL;
            (*FormTail)->nAlts = 0;
            return;
        
        }else{
            printf("Digite o número de alternativas:\n");
            scanf("%d", &alts);
            getchar();

            (*FormTail)->alternatives = (char**)calloc(alts, sizeof(char*));


            for(int i=0; i<alts; i++){
                size = 0;

                printf("Digite a alternativa %d:\n", i+1);
                ch = getchar();

                (*FormTail)->alternatives[i] = (char *)malloc(sizeof(char));
                (*FormTail)->alternatives[i][size] = ch;

                while(ch != '\n'){
                    (*FormTail)->alternatives[i] = (char *)realloc(((*FormTail)->alternatives[i]), (size + 2) * sizeof(char));
                    (*FormTail)->alternatives[i][size] = ch;
                    size++;

                    ch = getchar();
                }
                (*FormTail)->alternatives[i][size] = '\0';

                (*FormTail)->nAlts = alts;
            }
        }
    }
}

void editQuestForm(){

}

void menuForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail){
    int command = -1;
    questForm *selectedQuest = NULL;

    while(command != 0){
        printf("[%s]\n", *FormHead);
        printf("Atividade: %s\n|----------------|\n", SelectedActiv->name);
        
        if(*FormHead == NULL){
            printf("Nao existe nenhuma pergunta\n-----------------\n");
        }else{
            questForm *current = *FormHead;

            while(current != NULL){
                if(strcmp(current->activity, SelectedActiv->name) == 0){
                    printf("%s\n", current->quest);
                    if(current->type == 1){
                        for(int i=1; i< current->nAlts+1; i++){
                            printf("[%d/ %s]\n", i, current->alternatives[i-1]);
                        }
                    }
                    printf("-----------------\n");

                    current = current->next;

                }else{
                    current = current->next;

                }
                
            }
        }


        printf("Selecione uma acao para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar pergunta\n");
        scanf("%d", &command);

        switch(command){
        case 0:
            return;
            break;
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createQuestForm(SelectedActiv, FormHead, FormTail);
            printf("\033[H\033[2J");
            break;
        }
    }

}

void menuActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail, questForm *FormHead, questForm *FormTail){
    int command = -1;
    actvNode *selectedActv = NULL;

    while(command != 0){
        printf("[%s]\n", *ActvHead);
        printf("Especializacao: %s\n|----------------|\n", SelectedSpec->name);
        
        if(*ActvHead == NULL){
            printf("Nao existe nenhuma atividade\n-----------------\n");
        }else{
            actvNode *current = *ActvHead;

            while(current != NULL){
                if(strcmp(current->spec, SelectedSpec->name) == 0){
                    printf("%s\n-----------------\n", current->name);
                    current = current->next;

                }else{
                    current = current->next;

                }
                
            }
        }


        printf("Selecione uma acao para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar atividade\n");
        printf("(2) editar atividade\n");
        printf("(3) selecionar atividade\n");
        printf("(4) deletar atividade\n");
        scanf("%d", &command);

        switch(command){
        case 0:
            return;
            break;
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createActv(SelectedSpec, ActvHead, ActvTail);
            printf("\033[H\033[2J");
            break;

        case 2:
            printf("\033[H\033[2J");
            editActv(SelectedSpec, ActvHead);
            printf("\033[H\033[2J");
            break;

        case 3:
            printf("\033[H\033[2J");
            selectedActv = selectActv(SelectedSpec, *ActvHead, selectedActv);
            printf("\033[H\033[2J");

            if(selectedActv != NULL){
                printf("[%s]\n\n", selectedActv->name);
            }
            break;

        case 4:
            printf("\033[H\033[2J");
            deleteActv(SelectedSpec, ActvHead, ActvTail);
            printf("\033[H\033[2J");
            break;

        case 5:
            selectedActv = selectActv(SelectedSpec, *ActvHead, selectedActv);
            printf("\033[H\033[2J");
            menuForm(selectedActv, &FormHead, &FormTail);
            printf("\033[H\033[2J");
            break;
        }
    }

}



// ESPECIALIZACAO ---------------------------------------------------------------

specNode *selectSpec(areaNode *SelectedArea, specNode *SpecHead, specNode *PrevSelected){

    if(SelectedArea == NULL){
        printf("Nenhuma area selecionada");
        return NULL;
    }

    if (SpecHead == NULL){
        printf("Nao existe nenhuma especializacao\n-----------------\n");
        return NULL;

    }else{
        int spec, count = 0;
        specNode *current = SpecHead;

        printf("(%d) voltar\n-----------------\n", count);
        count++;

        while(current != NULL){

            if(strcmp(current->area, SelectedArea->name) == 0){
                printf("(%d) %s\n-----------------\n", count, current->name);
                current = current->next;
                count++;
            }else{
                current = current->next;

            }
        }

        printf("Digite o numero da especializacao: ");
        scanf("%d", &spec);

        if (spec == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;

        }

        if(spec > count || spec < 0){
            printf("Opcao invalida\n");
            return NULL;
        }

        current = SpecHead;
        count = 1;

        while(count <= spec){
            if(count == spec && strcmp(current->area, SelectedArea->name) == 0){
                return current;

            }else if(strcmp(current->area, SelectedArea->name) == 0){
                current = current->next;
                count++;
            }else{
                current = current->next;
            }
        }

        return current;
    }
}

void createSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail){

    char ch;
    int mod;

    if(SelectedArea == NULL){
        printf("Nenhuma especializacao selecionada");
        return;
    }

    printf("Digite o nome da especializacao que deseja criar:\n");
    ch = getchar();

    if(ch == '\n'){
        printf("Voce nao pode criar uma especializacao sem nome!\n");
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
        (*SpecHead)->area = (char *)malloc(sizeof(SelectedArea->name));
        strcpy((*SpecHead)->area, SelectedArea->name);
        (*SpecHead)->next = NULL;
        (*SpecTail) = (*SpecHead);

    }else{
        (*SpecTail)->next = (specNode *)malloc(sizeof(specNode));
        (*SpecTail) = (*SpecTail)->next;

        int size = 0;
        (*SpecTail)->name = (char *)malloc(sizeof(char));
        (*SpecTail)->name[size] = ch;

        while(ch != '\n'){
            (*SpecTail)->name = (char *)realloc(((*SpecTail)->name), (size + 2) * sizeof(char));
            (*SpecTail)->name[size] = ch;
            size++;

            ch = getchar();
        }
        (*SpecTail)->name[size] = '\0';
        (*SpecTail)->area = (char *)malloc(sizeof(SelectedArea->name));
        strcpy((*SpecTail)->area, SelectedArea->name);
        (*SpecTail)->next = NULL;
    }
}

void editSpec(areaNode *SelectedArea, specNode **SpecHead){
    
    specNode *selectedSpec = NULL;

    selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);
    getchar();

    if(selectedSpec == NULL || *SpecHead == NULL){
        printf("Nenhuma especializacao");
        return;

    }else{
        printf("Digite o novo nome da especializacao:\n");
        char ch = getchar();

        if(ch == '\n'){
            printf("Voce nao deixar uma especializacao sem nome!\n");
            return;
        }

        int size = 0;
        selectedSpec->name = (char *)realloc(selectedSpec->name, sizeof(char));
        selectedSpec->name[size] = ch;

        while(ch != '\n'){
            selectedSpec->name = (char *)realloc(selectedSpec->name, (size + 2) * sizeof(char));
            selectedSpec->name[size] = ch;
            size++;

            ch = getchar();
        }
        selectedSpec->name[size] = '\0';
        
    }
}

void deleteSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail){
    specNode *selectedSpec = NULL, *current = *SpecHead, *temp = NULL;

    selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);

    if(selectedSpec == NULL || *SpecHead == NULL){
        printf("Nenhuma especializacao");
        return;

    }else if( *SpecHead == selectedSpec){
        temp = *SpecHead;
        *SpecHead = (*SpecHead)->next;
        free(temp->name);
        free(temp);
        
    }else{
        while(current->next != selectedSpec){
            current = current->next;
        }

        temp = current->next;
        current->next = current->next->next;
        free(temp->name);
        free(temp);
        
    }

    if(*SpecHead == NULL){
        *SpecTail = NULL;

    }
}

void menuSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail, actvNode *ActvHead, actvNode *ActvTail,
 questForm *FormHead, questForm *FormTail){
    int command = -1;
    specNode *selectedSpec = NULL;

    while(command != 0){
        printf("[%s]\n", *SpecHead);
        printf("area: %s\n|----------------|\n", SelectedArea->name);
        
        if(*SpecHead == NULL){
            printf("Nao existe nenhuma especializacao\n-----------------\n");
        }else{
            specNode *current = *SpecHead;

            while(current != NULL){
                if(strcmp(current->area, SelectedArea->name) == 0){
                    printf("%s\n-----------------\n", current->name);
                    current = current->next;

                }else{
                    current = current->next;

                }
                
            }
        }


        printf("Selecione uma acao para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar especializacao\n");
        printf("(2) editar especializacao\n");
        printf("(3) selecionar especializacao\n");
        printf("(4) deletar especializacao\n");
        printf("(5) ver atividades de uma especializacao\n");
        scanf("%d", &command);

        switch(command){
        case 0:
            return;
            break;
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createSpec(SelectedArea, SpecHead, SpecTail);
            printf("\033[H\033[2J");
            break;

        case 2:
            printf("\033[H\033[2J");
            editSpec(SelectedArea, SpecHead);
            printf("\033[H\033[2J");
            break;

        case 3:
            printf("\033[H\033[2J");
            selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);
            printf("\033[H\033[2J");

            if(selectedSpec != NULL){
                printf("[%s]\n\n", selectedSpec->name);
            }
            break;

        case 4:
            printf("\033[H\033[2J");
            deleteSpec(SelectedArea, SpecHead, SpecTail);
            printf("\033[H\033[2J");
            break;

        case 5:
            printf("\033[H\033[2J");
            selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);
            printf("\033[H\033[2J");
            menuActv(selectedSpec, &ActvHead, &ActvTail, FormHead, FormTail);
            printf("\033[H\033[2J");
            break;

        }
    }

}

// AREA -------------------------------------------------------------------------

areaNode *selectArea(areaNode *AreaHead, areaNode *PrevSelected){

    if (AreaHead == NULL){
        printf("Nao existe nenhuma area\n-----------------\n");

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

        printf("Digite o numero da area: ");
        scanf("%d", &area);

        if (area == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;
        }
        if(area > count || area < 0){
            printf("Opcao invalida\n");
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

void createArea(areaNode **AreaHead, areaNode **AreaTail){
    printf("Digite o nome da area que deseja criar:\n");
    char ch = getchar();

    if(ch == '\n'){
        printf("Voce nao pode criar uma area sem nome!\n");
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
        (*AreaTail) = (*AreaHead);

    }else{
        (*AreaTail)->next = (areaNode *)malloc(sizeof(areaNode));
        (*AreaTail) = (*AreaTail)->next;

        int size = 0;
        (*AreaTail)->name = (char *)malloc(sizeof(char));
        (*AreaTail)->name[size] = ch;

        while(ch != '\n'){
            (*AreaTail)->name = (char *)realloc(((*AreaTail)->name), (size + 2) * sizeof(char));
            (*AreaTail)->name[size] = ch;
            size++;

            ch = getchar();
        }
        (*AreaTail)->name[size] = '\0';
        (*AreaTail)->next = NULL;
    }
}

void editArea(areaNode **AreaHead){
    
    areaNode *selectedArea = NULL;

    selectedArea = selectArea(*AreaHead, selectedArea);
    getchar();
    if(selectedArea == NULL || *AreaHead == NULL){
        printf("Nenhuma area");
        return;
    }else{
        printf("Digite o novo nome da area:\n");
        char ch = getchar();

        if(ch == '\n'){
            printf("Voce nao deixar uma area sem nome!\n");
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

void deleteArea(areaNode **AreaHead, areaNode **AreaTail){
    areaNode *selectedArea = NULL, *current = *AreaHead, *temp = NULL;

    selectedArea = selectArea(*AreaHead, selectedArea);

    if(selectedArea == NULL || *AreaHead == NULL){
        printf("Nenhuma area");
        return;

    }else if( *AreaHead == selectedArea){
        temp = *AreaHead;
        *AreaHead = (*AreaHead)->next;
        free(temp->name);
        free(temp);
        
    }else{
        while(current->next != selectedArea){
            current = current->next;
        }

        temp = current->next;
        current->next = current->next->next;
        free(temp->name);
        free(temp);
        
    }

    if(*AreaHead == NULL){
        *AreaTail = NULL;
    }
}

void menuArea(areaNode *AreaHead, areaNode *AreaTail, specNode *SpecHead, specNode *SpecTail,
 actvNode *ActvHead, actvNode *ActvTail, questForm *FormHead, questForm *FormTail){
    int command = -1;
    areaNode *selectedArea = NULL;
    //printf("\033[H\033[2J");

    while(command != 0){
        if(AreaHead == NULL){
            printf("Nao existe nenhuma area\n-----------------\n");
        }else{
            areaNode *current = AreaHead;

            while(current != NULL){
                printf("%s\n-----------------\n", current->name);
                current = current->next;
            }
        }

        printf("Selecione uma acao para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar area\n");
        printf("(2) editar area\n");
        printf("(3) selecionar area\n");
        printf("(4) deletar area\n");
        printf("(5) ver especializacoes de uma area\n");
        scanf("%d", &command);

        switch(command){
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createArea(&AreaHead, &AreaTail);
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
            deleteArea(&AreaHead, &AreaTail);
            printf("\033[H\033[2J");
            break;

        case 5:
            printf("\033[H\033[2J");
            selectedArea = selectArea(AreaHead, selectedArea);
            printf("\033[H\033[2J");
            menuSpec(selectedArea, &SpecHead, &SpecTail, ActvHead, ActvTail, FormHead, FormTail);
            printf("\033[H\033[2J");
            break;

        }
    }

}

// testes (sera apagado no fim)
int main()
{

    areaNode *currentArea = NULL, *AreaHead = NULL, *AreaTail = NULL, *selectedArea = NULL;
    specNode *currentSpec = NULL, *SpecHead = NULL, *SpecTail = NULL, *selectedSpec = NULL;
    actvNode *currentActiv = NULL, *ActvHead = NULL, *ActvTail = NULL, *selectedActiv = NULL;
    questForm *currentQuest = NULL, *ActvFormtHead = NULL, *ActvFormtTail = NULL, *selectedQuest = NULL;
    questForm *PrecAvtHead = NULL, *PrecAvTail = NULL;

    menuArea(AreaHead, AreaTail, SpecHead, SpecTail, ActvHead, ActvTail, ActvFormtHead, ActvFormtTail);

    specNode * c = SpecHead;
    areaNode * d = AreaHead;

    while(SpecHead != NULL){
        c = SpecHead;
        SpecHead = SpecHead->next;
        free(c);
    }

    while(AreaHead != NULL){
        d = AreaHead;
        AreaHead = AreaHead->next;
        free(d);
    }

    return 0;
}

//AREA DE FLAVIO:
/*dados do usuario*/

/*funcao para alocar memoria para criar espacos para cadastro*/
StructUser* criarCadastroLogin(StructUser* cadastro) {
    
    cadastro = malloc(sizeof(StructUser));
    cadastro->nome = malloc(sizeof(char) * 100);
    cadastro->email = malloc(sizeof(char) * 100);
    cadastro->endereco = malloc(sizeof(char) * 100);
    cadastro->area = malloc(sizeof(char) * 100);
    cadastro->especializacao = malloc(sizeof(char*) * 10); // Definido como maximo 10 especializacoes, ajuste conforme necessario
    // Inicialize o campo de especializacao para NULL
    for (int i = 0; i < 10; i++) {
        cadastro->especializacao[i] = NULL;
    }
    return cadastro;
}
/*liberar memoria criada para dados do cadastro*/
void liberarCadastroLogin(StructUser* cadastro) {

    free(cadastro->nome);
    free(cadastro->email);
    free(cadastro->endereco);
    free(cadastro->area);

    // Libere memoria para cada especializacao
    for (int i = 0; i < 10; i++) {
        if (cadastro->especializacao[i] != NULL) {
            free(cadastro->especializacao[i]);
        }
    }
    free(cadastro->especializacao);

    free(cadastro);
}
/*receber dados do usuario e salvar no txt*/
void salvarStructUser(const StructUser* user) {
    FILE* arquivo = fopen("dados.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "Permissao: %d\n", user->permissao);
    fprintf(arquivo, "Nome: %s\n", user->nome);
    fprintf(arquivo, "Email: %s\n", user->email);
    fprintf(arquivo, "CPF: %d\n", user->cpf);
    fprintf(arquivo, "Celular: %d\n", user->celular);
    fprintf(arquivo, "Endereco: %s\n", user->endereco);
    fprintf(arquivo, "Senha: %s\n", user->senha);
    fprintf(arquivo, "Area: %s\n", user->area);
    fprintf(arquivo, "Especializacoes:\n");
    char** especializacao = user->especializacao;
    do {
        fprintf(arquivo, "- %s\n", *especializacao);
        especializacao++;
    } while (*especializacao != NULL);

    fclose(arquivo);
    
}
/*fazer login*/
int fazerLogin(const char* email, const char* senha) {
    FILE* arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    char linha[256];
    int emailEncontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "Email: ", 7) == 0) {
            char* valorEmail = linha + 7;
            valorEmail[strlen(valorEmail) - 1] = '\0';
            if (strcmp(valorEmail, email) == 0) {
                emailEncontrado = 1;
            }else{
            fclose(arquivo);
            printf("Usuário incorreto");
            return 0;
            }
        }
        if (emailEncontrado==1 && strncmp(linha, "Senha: ", 7) == 0) {
            char* valorSenha = linha + 7;
            valorSenha[strlen(valorSenha) - 1] = '\0';
            if (strcmp(valorSenha, senha) == 0) {
                fclose(arquivo);
                return 1; // Login válido
            } else {
                fclose(arquivo);
                printf("Senha incorreta\n");
                return 0; // Senha incorreta
            }
        }
    }
    fclose(arquivo);
    return 0; // E-mail não encontrado
}
/*cadastrar funcionário*/
void cadastrarNovoUsuario() {
    char email[100];
    char senha[20];

    printf("Digite seu email: ");
    scanf("%s", email);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    int loginValido = fazerLogin(email, senha);
    if (loginValido) {
        StructUser* user = fazerLogin(email, senha);
        if (user != NULL && user->permissao == 0) {
            // Cadastrar novo usuário
            StructUser* novoUsuario = criarCadastroLogin(NULL);

            // Preencher os dados do novo usuário
            printf("Digite os dados do novo usuário:\n");
            printf("Nome: ");
            scanf(" %[^\n]s", novoUsuario->nome);  // Corrigido para aceitar espaços no nome
            printf("CPF: ");
            scanf("%d", &(novoUsuario->cpf));
            printf("Celular: ");
            scanf("%d", &(novoUsuario->celular));
            printf("Endereço: ");
            scanf(" %[^\n]s", novoUsuario->endereco);  // Corrigido para aceitar espaços no endereço
            printf("Senha: ");
            scanf(" %[^\n]s", novoUsuario->senha);  // Corrigido para aceitar espaços na senha
            printf("Área: ");
            scanf(" %[^\n]s", novoUsuario->area);  // Corrigido para aceitar espaços na área

            // Solicitar especializações
            int i = 0;
            while (1) {
                printf("Especialização %d (ou digite 'FIM' para finalizar): ", i + 1);
                char especializacao[100];
                scanf(" %[^\n]s", especializacao);  // Corrigido para aceitar espaços nas especializações
                if (strcmp(especializacao, "FIM") == 0) {
                    break;
                }
                novoUsuario->especializacao[i] = malloc(sizeof(char) * 100);
                strcpy(novoUsuario->especializacao[i], especializacao);
                i++;
            }

            // Salvar novo usuário no arquivo
            salvarStructUser(novoUsuario);

            // Liberar memória
            liberarCadastroLogin(novoUsuario);

            printf("Novo usuário cadastrado com sucesso!\n");
        } else {
            printf("Permissão insuficiente para cadastrar novo usuário.\n");
        }
        liberarCadastroLogin(user);
    } else {
        printf("Login inválido.\n");
    }
}




void give_feedback(){

}



//aREA DE VICTOR:

void answerQuestForm(actvNode *SelectedActiv, questForm *FormHead, questFormResp **FormRespHead, questFormResp **FormRespTail){
    char ch;
    int type, alts, altResp, size;

    if (FormHead==NULL){
        return;
    } else{
        questForm *current = FormHead;
        while(current != NULL){
            if(strcmp(current->activity, SelectedActiv->name)==0){
                printf("%s",current->quest);

                if(current->type==1){//fechado
                    for(int i=1; i< current->nAlts+1; i++){
                        printf("[%d/ %s]\n", i, current->alternatives[i-1]);
                    }
                    printf("-----------------\n"); 

                    if(*FormRespHead==NULL){
                        *FormRespHead=(questFormResp*)malloc(sizeof(questFormResp));
                        scanf("%d",&altResp);
                        (*FormRespHead)->alternative = altResp;
                        (*FormRespHead)->activity = (char*)malloc(sizeof(SelectedActiv->name));
                        strcpy((*FormRespHead)->activity,SelectedActiv->name);
                        (*FormRespHead)->quest = (char*)malloc(sizeof(current->quest));
                        strcpy((*FormRespHead)->quest,current->quest);
                        (*FormRespHead)->answer = NULL;
                        (*FormRespHead)->next = NULL;
                        *FormRespTail = *FormRespHead;


                    }else{
                        (*FormRespTail)->next=(questFormResp*)malloc(sizeof(questFormResp));
                        *FormRespTail=(*FormRespTail)->next;
                        scanf("%d",&altResp);
                        (*FormRespTail)->alternative = altResp;
                        (*FormRespTail)->activity = (char*)malloc(sizeof(SelectedActiv->name));
                        strcpy((*FormRespTail)->activity,SelectedActiv->name);
                        (*FormRespTail)->quest = (char*)malloc(sizeof(current->quest));
                        strcpy((*FormRespTail)->quest,current->quest);
                        (*FormRespTail)->answer = NULL;
                        (*FormRespTail)->next = NULL;

                    }

                }else{//se for aberto

                    if(*FormRespHead==NULL){
                        *FormRespHead=(questFormResp*)malloc(sizeof(questFormResp));

                        size = 0;

                        printf("Digite a resposta:\n");
                        ch = getchar();

                        (*FormRespHead)->answer = (char *)malloc(sizeof(char));
                        (*FormRespHead)->answer[size] = ch;

                        while(ch != '\n'){
                            (*FormRespHead)->answer = (char *)realloc(((*FormRespHead)->answer), (size + 2) * sizeof(char));
                            (*FormRespHead)->answer[size] = ch;
                            size++;

                            ch = getchar();
                        }
                        (*FormRespHead)->answer[size] = '\0';


                        (*FormRespHead)->alternative = -1;
                        (*FormRespHead)->activity = (char*)malloc(sizeof(SelectedActiv->name));
                        strcpy((*FormRespHead)->activity,SelectedActiv->name);
                        (*FormRespHead)->quest = (char*)malloc(sizeof(current->quest));
                        strcpy((*FormRespHead)->quest,current->quest);
                        (*FormRespHead)->next = NULL;
                        *FormRespTail = *FormRespHead;


                    }else{
                        (*FormRespTail)->next=(questFormResp*)malloc(sizeof(questFormResp));
                        *FormRespTail=(*FormRespTail)->next;

                        size = 0;

                        printf("Digite a resposta:\n");
                        ch = getchar();

                        (*FormRespTail)->answer = (char *)malloc(sizeof(char));
                        (*FormRespTail)->answer[size] = ch;

                        while(ch != '\n'){
                            (*FormRespTail)->answer = (char *)realloc(((*FormRespTail)->answer), (size + 2) * sizeof(char));
                            (*FormRespTail)->answer[size] = ch;
                            size++;

                            ch = getchar();
                        }
                        (*FormRespHead)->answer[size] = '\0';

                        (*FormRespTail)->alternative = -1;
                        (*FormRespTail)->activity = (char*)malloc(sizeof(SelectedActiv->name));
                        strcpy((*FormRespTail)->activity,SelectedActiv->name);
                        (*FormRespTail)->quest = (char*)malloc(sizeof(current->quest));
                        strcpy((*FormRespTail)->quest,current->quest);
                        (*FormRespTail)->next = NULL;

                    }

                }

                current = current->next;
            }else{
                current = current->next;
            }

        }
    }

}


//aREA DE JOaO:

//aREA DE HENRIQUE:

//aREA DE DIEGO:

typedef struct {
    char* nome;
    int especializacao;
    int avaliacao;
} Residente;

typedef struct {
    char* especializacao;
    Residente* residentes;
    int numResidentes;
} Especializacao;

Especializacao* criarEspecializacoes(int numEspecializacoes) {
    Especializacao* especializacoes = malloc(sizeof(Especializacao) * numEspecializacoes);
    for (int i = 0; i < numEspecializacoes; i++) {
        especializacoes[i].especializacao = malloc(sizeof(char) * 100);
        printf("Digite o nome da especialização %d: ", i + 1);
        scanf("%s", especializacoes[i].especializacao);
        especializacoes[i].residentes = NULL;
        especializacoes[i].numResidentes = 0;
    }
    return especializacoes;
}

void liberarEspecializacoes(Especializacao* especializacoes, int numEspecializacoes) {
    for (int i = 0; i < numEspecializacoes; i++) {
        free(especializacoes[i].especializacao);
        if (especializacoes[i].residentes != NULL) {
            free(especializacoes[i].residentes);
        }
    }
    free(especializacoes);
}

void selecionarEspecializacao(Especializacao* especializacoes, int numEspecializacoes) {
    printf("Especializações disponíveis:\n");
    for (int i = 0; i < numEspecializacoes; i++) {
        printf("%d. %s\n", i + 1, especializacoes[i].especializacao);
    }
    int opcao;
    printf("Selecione uma especialização: ");
    scanf("%d", &opcao);
    if (opcao >= 1 && opcao <= numEspecializacoes) {
        Especializacao selecionada = especializacoes[opcao - 1];
        printf("Especialização selecionada: %s\n", selecionada.especializacao);

        // Ler o documento com os alunos da especialização selecionada
        char nomeDocumento[100];
        printf("Digite o nome do documento com os alunos da especialização: ");
        scanf("%s", nomeDocumento);

        FILE* arquivo = fopen(nomeDocumento, "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Ler e exibir os alunos da especialização
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo)) {
            printf("Aluno: %s", linha);
        }

        fclose(arquivo);
    } else {
        printf("Opção inválida.\n");
    }
}