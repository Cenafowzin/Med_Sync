#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "functions.h"

//aREA DE RODRIGO:

// estruturas (serao transferidas para o funcs.h)
typedef struct areaNode{
    char *name;
    struct areaNode *next;
} areaNode;
/*especializacao*/
typedef struct specNode{
    char *name;
    char *area;
    struct specNode *next;
} specNode;
/*atividade*/
typedef struct actvNode{
    char *name;
    int mod;
    char *spec;
    struct actvNode *next;
} actvNode;
/*questão do formulário*/
typedef struct questForm{
    int type;
    char *activity;//FAZ A LIGAÇÃO ENTRE PERGUNTA E ATIVIDADE
    char *quest;
    int nAlts;
    char **alternatives;
    struct questForm *next;
} questForm;
/*resposta da questão do formulário*/
typedef struct questFormResp{
    char *activity;
    char *quest;
    char *answer;
    int alternative;
    struct questFormResp *next;
} questFormResp;

// ATIVIDADE ---------------------------------------------------------------

void saveActvs(actvNode *ActvHead){
    FILE * fp = fopen("db/gerencia/actvs.txt", "w+");
    actvNode * current = ActvHead;

    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    while(current != NULL){
        fprintf(fp, "%s\n", current->spec);
        fprintf(fp, "%s\n", current->name);
        fprintf(fp, "%d\n", current->mod);
        current = current->next;
    }
    
    fclose(fp);
}

void loadActvs(actvNode **ActvHead, actvNode **ActvTail){
    FILE * fp = fopen("db/gerencia/actvs.txt", "r");
    char ch;
    int size = 0, mod;

    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    ch = fgetc(fp);

    while(ch != EOF){
        if(*ActvHead == NULL){

            size = 0;

            *ActvHead = (actvNode *)malloc(sizeof(actvNode));
            (*ActvHead)->spec = (char *)malloc(sizeof(char));
            (*ActvHead)->spec[size] = ch;

            while(ch != '\n'){
                (*ActvHead)->spec = (char *)realloc(((*ActvHead)->spec), (size + 2) * sizeof(char));
                (*ActvHead)->spec[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*ActvHead)->spec[size] = '\0';

            ch = fgetc(fp);

            size = 0;

            (*ActvHead)->name = (char *)malloc(sizeof(char));
            (*ActvHead)->name[size] = ch;

            while(ch != '\n'){
                (*ActvHead)->name = (char *)realloc(((*ActvHead)->name), (size + 2) * sizeof(char));
                (*ActvHead)->name[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*ActvHead)->name[size] = '\0';

            ch = fgetc(fp);

            (*ActvHead)->mod = ch - '0';

            (*ActvHead)->next = NULL;
            *ActvTail = *ActvHead;

            ch = fgetc(fp); 

        }else{
            (*ActvTail)->next = (actvNode *)malloc(sizeof(actvNode));
            (*ActvTail) = (*ActvTail)->next;

            size = 0;
            (*ActvTail)->spec = (char *)malloc(sizeof(char));
            (*ActvTail)->spec[size] = ch;

            while(ch != '\n'){
                (*ActvTail)->spec = (char *)realloc(((*ActvTail)->spec), (size + 2) * sizeof(char));
                (*ActvTail)->spec[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*ActvTail)->spec[size] = '\0';

            ch = fgetc(fp);

            size = 0;

            (*ActvTail)->name = (char *)malloc(sizeof(char));
            (*ActvTail)->name[size] = ch;

            while(ch != '\n'){
                (*ActvTail)->name = (char *)realloc(((*ActvTail)->name), (size + 2) * sizeof(char));
                (*ActvTail)->name[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*ActvTail)->name[size] = '\0';

            ch = fgetc(fp);

            (*ActvTail)->mod = ch - '0';
            (*ActvTail)->next = NULL;

            ch = fgetc(fp);

        }

        ch = fgetc(fp);   
    }
}
/*seleciona atividade*/
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
        getchar();

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
/*cria atividade*/
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
    getchar();

    if(mod < 0 || mod > 1){
        printf("Opcao invalida");
        return;
    }
    
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

    saveActvs(*ActvHead);
}
/*edita atividade*/
void editActv(specNode *SelectedSpec, actvNode **ActvHead){
    
    actvNode *selectedActiv = NULL;

    selectedActiv = selectActv(SelectedSpec, *ActvHead, selectedActiv);

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

    saveActvs(*ActvHead);
}
/*apaga atividade*/
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

        if(current->next == *ActvTail){
            *ActvTail = current;
        }

        current->next = current->next->next;
        free(temp->name);
        free(temp->spec);
        free(temp);
        
    }

    if(*ActvHead == NULL){
        *ActvTail = NULL;
    }

    saveActvs(*ActvHead);
}

//FORMULARIO ---------------------------------------------------------------

void saveQuests(questForm *QuestFormHead){
    printf("ENTREI NA FUNCAO");
    FILE * fp = fopen("db/gerencia/quests.txt", "w+");
    questForm * current = QuestFormHead;
    printf("abriu arquivo");
    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    while(current != NULL){
        fprintf(fp, "%s\n", current->activity);
        fprintf(fp, "%s\n", current->quest);
        fprintf(fp, "%d\n", current->type);
      
        if(current->type == 1){
            fprintf(fp, "%d\n", current->nAlts);

            for(int i=0; i<current->nAlts; i++){
                fprintf(fp, "%s\n", current->alternatives[i]);
            }
        }
        current = current->next;
    }
    
    fclose(fp);
}
/*seleciona questão do form*/
questForm *selectQuest(actvNode *SelectedActivity, questForm *QuestFormHead, questForm *PrevSelected){
    if(SelectedActivity == NULL){
        printf("Nenhuma atividade selecionada");
        return NULL;
    }

    if (QuestFormHead == NULL){
        printf("Nao existe nenhuma questao\n-----------------\n");
        return NULL;

    }else{
        int quest, count = 0;
        questForm *current = QuestFormHead;

        printf("(%d) voltar\n-----------------\n", count);
        count++;

        while(current != NULL){
            if(strcmp(current->activity, SelectedActivity->name) == 0){
                printf("(%d) %s\n-----------------\n", count, current->quest);
                current = current->next;
                count++;
            }else{
                current = current->next;

            }
        }

        printf("Digite o numero da atividade: ");
        scanf("%d", &quest);
        getchar();

        if (quest == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;

        }

        if(quest > count || quest < 0){
            printf("Opcao invalida\n");
            return NULL;
        }

        current = QuestFormHead;
        count = 1;

        while(count <= quest){
            if(count == quest && strcmp(current->activity, SelectedActivity->name) == 0){
                return current;

            }else if(strcmp(current->activity, SelectedActivity->name) == 0){
                current = current->next;
                count++;
            }else{
                current = current->next;
            }
        }

        return current;
    }
}
/*cria questão no formulário*/
void createQuestForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail){
    char ch;
    int type, alts, size=0;

    if(SelectedActiv == NULL){
        printf("Nenhuma atividade selecionada");
        return;
    }
    
    printf("(0) Aberta\n");
    printf("(1) Fechada\n");
    printf("Selecione o tipo de pergunta:\n");
    scanf("%d", &type);
    getchar();

    if(type < 0 || type > 1){
        printf("Opcao invalida");
        return;
    }

    printf("Digite o que quer escrever na pergunta:\n");
    ch = getchar();

    if(ch == '\n'){
        printf("Voce nao pode criar uma pergunta sem nome!\n");
        return;
    }

    if(*FormHead == NULL){
        size = 0;

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
        
        }else{
            printf("Digite o numero de alternativas:\n");
            scanf("%d", &alts);
            getchar();

            (*FormHead)->alternatives = (char**)calloc(alts, sizeof(char*));


            for(int i=0; i<alts; i++){
                size = 0;

                printf("Digite a alternativa %d:\n", (i+1));
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

            }
            (*FormHead)->nAlts = alts;
        }

    }else{
        (*FormTail)->next = (questForm*)malloc(sizeof(questForm));
        (*FormTail) = (*FormTail)->next;

        size = 0;
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
        
        }else{
            printf("Digite o numero de alternativas:\n");
            scanf("%d", &alts);
            getchar();

            (*FormTail)->alternatives = (char**)calloc(alts, sizeof(char*));


            for(int i=0; i<alts; i++){
                size = 0;

                printf("Digite a alternativa %d:\n", (i+1));
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

            }

            (*FormTail)->nAlts = alts;
        }

      
    }
  saveQuests(*FormHead);
}
/*edita questão no formulário*/
void editQuestForm(actvNode *SelectedActiv, questForm **FormHead){
    questForm *selectedQuest = NULL;
    int type, alts;

    selectedQuest = selectQuest(SelectedActiv, *FormHead, selectedQuest);

    if(selectedQuest == NULL || *FormHead == NULL){
        printf("Nenhuma questao");
        return;

    }else{

        printf("(0) Aberta\n");
        printf("(1) Fechada\n");
        printf("Selecione o novo tipo da pergunta:\n");
        scanf("%d", &type);
        getchar();

        if(type < 0 || type > 1){
            printf("Opcao invalida");
            return;
        }

        selectedQuest->type = type;

        printf("Digite a nova pergunta:\n");
        char ch = getchar();

        if(ch == '\n'){
            printf("Voce nao pode deixar pergunta vazia!\n");
            return;
        }

        int size = 0;
        selectedQuest->quest = (char *)realloc(selectedQuest->quest, sizeof(char));
        selectedQuest->quest[size] = ch;

        while(ch != '\n'){
            selectedQuest->quest = (char *)realloc(selectedQuest->quest, (size + 2) * sizeof(char));
            selectedQuest->quest[size] = ch;
            size++;

            ch = getchar();
        }
        selectedQuest->quest[size] = '\0';

        if(type == 0){
            if(selectedQuest->alternatives != NULL){
                for(int i=0; i<selectedQuest->nAlts; i++){
                    free(selectedQuest->alternatives[i]);
                }
                free(selectedQuest->alternatives);
            }

            selectedQuest->nAlts = 0;
            selectedQuest->alternatives = NULL;

        }else{
            if(selectedQuest->alternatives != NULL){
                for(int i=0; i<selectedQuest->nAlts; i++){
                    free(selectedQuest->alternatives[i]);
                }
                free(selectedQuest->alternatives);
            }

            printf("Digite o numero de alternativas:\n");
            scanf("%d", &alts);
            getchar();

            selectedQuest->alternatives = (char**)calloc(alts, sizeof(char*));


            for(int i=0; i<alts; i++){
                size = 0;

                printf("Digite a alternativa %d:\n", i+1);
                ch = getchar();

                selectedQuest->alternatives[i] = (char *)malloc(sizeof(char));
                selectedQuest->alternatives[i][size] = ch;

                while(ch != '\n'){
                    selectedQuest->alternatives[i] = (char *)realloc((selectedQuest->alternatives[i]), (size + 2) * sizeof(char));
                    selectedQuest->alternatives[i][size] = ch;
                    size++;

                    ch = getchar();
                }
                selectedQuest->alternatives[i][size] = '\0';

                selectedQuest->nAlts = alts;
            }
        }
        
    }

    saveQuests(*FormHead);
}

void deleteQuestForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail){
    questForm *selectedQuest = NULL, *current = *FormHead, *temp = NULL;

    selectedQuest = selectQuest(SelectedActiv, *FormHead, selectedQuest);

    if(selectedQuest == NULL || *FormHead == NULL){
        printf("Nenhuma questao");
        return;

    }else if( *FormHead == selectedQuest){
        temp = *FormHead;
        *FormHead = (*FormHead)->next;

        free(temp->quest);
        free(temp->activity);
        if(temp->alternatives != NULL){
            for(int i=0; i<temp->nAlts; i++){
                free(temp->alternatives[i]);
            }
            free(temp->alternatives);
        }
        free(temp);
        
    }else{
        while(current->next != selectedQuest){
            current = current->next;
        }

        temp = current->next;

        if(current->next == *FormTail){
            *FormTail = current;
        }

        current->next = current->next->next;
        free(temp->quest);
        free(temp->activity);
        if(temp->alternatives != NULL){
            for(int i=0; i<temp->nAlts; i++){
                free(temp->alternatives[i]);
            }
            free(temp->alternatives);
        }
        free(temp);
        
    }

    if(*FormHead == NULL){
        *FormTail = NULL;
    }

    saveQuests(*FormHead);
}

/*menu do formulário*/
void menuForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail){
    int command = -1;
    questForm *selectedQuest = NULL;

    while(command != 0){
        printf("[%p]\n", *FormHead);
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
        printf("(2) editar pergunta\n");
        printf("(3) selecionar pergunta\n");
        printf("(4) deletar pergunta\n");
        scanf("%d", &command);
        getchar();

        switch(command){
        case 0:
            return;
            break;
        case 1:
            //clear
            createQuestForm(SelectedActiv, FormHead, FormTail);
            printf("\033[H\033[2J");
            break;
        case 2:
            printf("\033[H\033[2J");
            editQuestForm(SelectedActiv, FormHead);
            printf("\033[H\033[2J");
            break;

        case 3:
            printf("\033[H\033[2J");
            selectedQuest = selectQuest(SelectedActiv, *FormHead, selectedQuest);
            printf("\033[H\033[2J");

            if(selectedQuest != NULL){
                printf("[%s]\n\n", selectedQuest->quest);
            }
            break;

        case 4:
            printf("\033[H\033[2J");
            deleteQuestForm(SelectedActiv, FormHead, FormTail);
            printf("\033[H\033[2J");
            break;
        }
    }

}

void answerQuestForm(actvNode *SelectedActiv, questForm *FormHead, questFormResp **FormRespHead, questFormResp **FormRespTail);

/*menu da atividade*/
void menuActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail, questForm *FormHead, questForm *FormTail,
 questFormResp *QuestRespHead, questFormResp *QuestRespTail){
    int command = -1;
    actvNode *selectedActv = NULL;

    while(command != 0){
        printf("[%p]\n", *ActvHead);
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
        getchar();

        switch(command){
        case 0:
            return;
            break;
        case 1:
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

        case 6:
            selectedActv = selectActv(SelectedSpec, *ActvHead, selectedActv);
            printf("\033[H\033[2J");
            answerQuestForm(selectedActv, FormHead, &QuestRespHead, &QuestRespTail);
            printf("\033[H\033[2J");
            break;

        }
    }

}



// ESPECIALIZACAO ---------------------------------------------------------------

void saveSpecs(specNode *SpecHead){
    FILE * fp = fopen("db/gerencia/specs.txt", "w+");
    specNode * current = SpecHead;

    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    while(current != NULL){
        fprintf(fp, "%s\n", current->area);
        fprintf(fp, "%s\n", current->name);
        current = current->next;
    }
    
    fclose(fp);
}

void loadSpecs(specNode **SpecHead, specNode **SpecTail){
    FILE * fp = fopen("db/gerencia/specs.txt", "r");
    char ch;
    int size = 0;

    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    ch = fgetc(fp);

    while(ch != EOF){
        if(*SpecHead == NULL){
            *SpecHead = (specNode *)malloc(sizeof(specNode));
            
            size = 0;
            (*SpecHead)->area = (char *)malloc(sizeof(char));
            (*SpecHead)->area[size] = ch;

            while(ch != '\n'){
                (*SpecHead)->area = (char *)realloc(((*SpecHead)->area), (size + 2) * sizeof(char));
                (*SpecHead)->area[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*SpecHead)->area[size] = '\0';

            ch = fgetc(fp);
            
            size = 0;
            (*SpecHead)->name = (char *)malloc(sizeof(char));
            (*SpecHead)->name[size] = ch;

            while(ch != '\n'){
                (*SpecHead)->name = (char *)realloc(((*SpecHead)->name), (size + 2) * sizeof(char));
                (*SpecHead)->name[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*SpecHead)->name[size] = '\0';

            (*SpecHead)->next = NULL;
            (*SpecTail) = (*SpecHead);

        }else{
            (*SpecTail)->next = (specNode *)malloc(sizeof(specNode));
            (*SpecTail) = (*SpecTail)->next;

            size = 0;
            (*SpecTail)->area = (char *)malloc(sizeof(char));
            (*SpecTail)->area[size] = ch;

            while(ch != '\n'){
                (*SpecTail)->area = (char *)realloc(((*SpecTail)->area), (size + 2) * sizeof(char));
                (*SpecTail)->area[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*SpecTail)->area[size] = '\0';

            ch = fgetc(fp);

            size = 0;
            (*SpecTail)->name = (char *)malloc(sizeof(char));
            (*SpecTail)->name[size] = ch;

            while(ch != '\n'){
                (*SpecTail)->name = (char *)realloc(((*SpecTail)->name), (size + 2) * sizeof(char));
                (*SpecTail)->name[size] = ch;
                size++;

                ch = fgetc(fp);
            }
            (*SpecTail)->name[size] = '\0';

            (*SpecTail)->next = NULL;
        }

        ch = fgetc(fp);
    }
}

/*seleciona especialidade*/
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
/*cria especialidade*/
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

    saveSpecs(*SpecHead);
}
/*edita especialidade*/
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

    saveSpecs(*SpecHead);
}
/*apaga especialidade*/
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

        if(current->next == *SpecTail){
            *SpecTail = current;
        }

        current->next = current->next->next;
        free(temp->name);
        free(temp);
        
    }

    if(*SpecHead == NULL){
        *SpecTail = NULL;

    }

    saveSpecs(*SpecHead);
}
/*menu de especialização*/
void menuSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail, actvNode *ActvHead, actvNode *ActvTail,
 questForm *FormHead, questForm *FormTail, questFormResp *QuestRespHead, questFormResp *QuestRespTail){
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
            menuActv(selectedSpec, &ActvHead, &ActvTail, FormHead, FormTail, QuestRespHead, QuestRespTail);
            printf("\033[H\033[2J");
            break;

        }
    }

}

// AREA -------------------------------------------------------------------------

void saveAreas(areaNode *AreaHead){
    FILE * fp = fopen("db/gerencia/areas.txt", "w+");
    areaNode * current = AreaHead;

    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    while(current != NULL){
        fprintf(fp, "%s\n", current->name);
        current = current->next;
    }
    
    fclose(fp);
}

void loadAreas(areaNode **AreaHead, areaNode **AreaTail){
    FILE * fp = fopen("db/gerencia/areas.txt", "r");
    char ch;

    if(fp == NULL){
        printf("nao foi possivel abrir arquivo!");
        return;
    }

    ch = fgetc(fp);

    while(ch != EOF){

        if(*AreaHead == NULL){

            *AreaHead = (areaNode *)malloc(sizeof(areaNode));
            int size = 0;
            (*AreaHead)->name = (char *)malloc(sizeof(char));
            (*AreaHead)->name[size] = ch;

            while(ch != '\n'){
                (*AreaHead)->name = (char *)realloc(((*AreaHead)->name), (size + 2) * sizeof(char));
                (*AreaHead)->name[size] = ch;
                size++;

                ch = fgetc(fp);
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

                ch = fgetc(fp);
            }
            (*AreaTail)->name[size] = '\0';
            (*AreaTail)->next = NULL;
        }

        ch = fgetc(fp);
    }

    fclose(fp);  
}

/*selecionar área*/
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
/*criar área*/
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

    saveAreas(*AreaHead);
}
/*editar área*/
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

    saveAreas(*AreaHead);
}
/*apagar área*/
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

        if(current->next == *AreaTail){
            *AreaTail = current;
        }

        current->next = current->next->next;
        free(temp->name);
        free(temp);
        
    }

    if(*AreaHead == NULL){
        *AreaTail = NULL;
    }

    saveAreas(*AreaHead);
}
/*menu de área*/
void menuArea(areaNode *AreaHead, areaNode *AreaTail, specNode *SpecHead, specNode *SpecTail,
 actvNode *ActvHead, actvNode *ActvTail, questForm *FormHead, questForm *FormTail, questFormResp *QuestRespHead, questFormResp *QuestRespTail){
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
            menuSpec(selectedArea, &SpecHead, &SpecTail, ActvHead, ActvTail, FormHead, FormTail, QuestRespHead, QuestRespTail);
            printf("\033[H\033[2J");
            break;

        }
    }

}
void entradaRegistro();
// testes (sera apagado no fim)
int main()
{

    areaNode *currentArea = NULL, *AreaHead = NULL, *AreaTail = NULL, *selectedArea = NULL;
    specNode *currentSpec = NULL, *SpecHead = NULL, *SpecTail = NULL, *selectedSpec = NULL;
    actvNode *currentActiv = NULL, *ActvHead = NULL, *ActvTail = NULL, *selectedActiv = NULL;
    questForm *currentQuest = NULL, *ActvFormtHead = NULL, *ActvFormtTail = NULL, *selectedQuest = NULL;
    questForm *PrecAvtHead = NULL, *PrecAvTail = NULL;
    questFormResp *QuestRespHead = NULL, *QuestRespTail = NULL;

    loadAreas(&AreaHead, &AreaTail);
    loadSpecs(&SpecHead, &SpecTail);
    loadActvs(&ActvHead, &ActvTail);
    entradaRegistro();
    menuArea(AreaHead, AreaTail, SpecHead, SpecTail, ActvHead, ActvTail, ActvFormtHead, ActvFormtTail, QuestRespHead, QuestRespTail);

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
                printf("%s\n",current->quest);

                if(current->type==1){//fechado
                    for(int i=1; i< current->nAlts+1; i++){
                        printf("[%d/ %s]\n", i, current->alternatives[i-1]);
                    }
                    printf("-----------------\n"); 

                    if(*FormRespHead==NULL){
                        *FormRespHead=(questFormResp*)malloc(sizeof(questFormResp));
                        scanf("%d",&altResp);
                        getchar();
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
                        getchar();
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


//aREA DE JOaO e Henrique:
typedef struct {
    char login[50];
    char password[50];
    char nome[50];
    char cargo[50];
    char area[50];
    char especializacao[50];
} Account;

void save_account(Account account) {
    FILE *file = fopen("db/gerencia/accounts.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fprintf(file, "%s;%s;%s;%s;%s;%s\n", account.login, account.password, account.nome, account.cargo, account.area, account.especializacao);
    fclose(file);
}

int valid_role(char *cargo) {
    if (strcmp(cargo, "Preceptor") == 0) return 1;
    if (strcmp(cargo, "Gerente") == 0) return 1;
    if (strcmp(cargo, "Residente") == 0) return 1;
    return 0;
}

void create_account() {
    Account account;
    char confirm_password[50];
    printf("Cadastrando uma Conta:\n\n");
    printf("Digite o login: ");
    scanf("%s", account.login);

    printf("Digite a senha: ");
    scanf("%s", account.password);

    printf("Confirme a senha: ");
    scanf("%s", confirm_password);

    if (strcmp(account.password, confirm_password) != 0) {
        printf("As senhas não coincidem. Tente novamente.\n");
        return;
    }

    printf("Digite o nome: ");
    getchar();  // Limpa o buffer do teclado
    fgets(account.nome, sizeof(account.nome), stdin);
    account.nome[strcspn(account.nome, "\n")] = '\0';  // Remove a quebra de linha no final

    do {
        printf("Digite o cargo (Preceptor, Gerente, Residente): ");
        scanf("%s", account.cargo);
        if (!valid_role(account.cargo)) {
            printf("Cargo inválido. Tente novamente.\n");
        }
    } while (!valid_role(account.cargo));

    printf("Digite a área: ");
    scanf("%s", account.area);

    printf("Digite a especialização: ");
    scanf("%s", account.especializacao);

    save_account(account);
    printf("Conta criada com sucesso.\n");
}

int login_account(char* login, char* password) {
    FILE *file = fopen("db/gerencia/accounts.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    Account account;
    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", account.login, account.password, account.nome, account.cargo, account.area, account.especializacao) != EOF) {
        if (strcmp(login, account.login) == 0 && strcmp(password, account.password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


//Area de Diego:

typedef struct {
    Account* accounts;
    int count;
} AccountList;

AccountList show_specialization(char* specialization) {
    static Account accounts[100];
    int count = 0;

    FILE *file = fopen("db/gerencia/accounts.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    Account account;
    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", account.login, account.password, account.nome, account.cargo, account.area, account.especializacao) != EOF) {
        if (strcmp(specialization, account.especializacao) == 0) {
            accounts[count++] = account;
        }
    }
    fclose(file);

    // Exibir os nomes com um numero vinculado
    for (int i = 0; i < count; i++) {
        printf("%d - %s\n", i+1, accounts[i].nome);
    }

    AccountList accountList = {accounts, count};
    return accountList;
}


Account choose_account_by_number(AccountList accountList, int number) {
    if (number > 0 && number <= accountList.count) {
        return accountList.accounts[number-1];
    }

    // Se o numero fornecido não for válido, retornar uma conta vazia
    Account empty_account = {"", "", "", "", "", ""};
    return empty_account;
}

//PARTE 2 DE DIEGO
typedef struct {
    char account_name[50];
    char feedback[1000];
} Feedback;

void save_feedback(Feedback feedback) {
    FILE *file = fopen("db/gerencia/feedbacks.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fprintf(file, "%s: %s\n", feedback.account_name, feedback.feedback);
    fclose(file);
}

void give_feedback(Account chosenAccount) {
    Feedback feedback;

    // Copia o nome da conta escolhida para a estrutura de feedback
    strcpy(feedback.account_name, chosenAccount.nome);

    printf("Dê seu feedback para %s: ", chosenAccount.nome);
    getchar();  // Limpa o buffer do teclado
    fgets(feedback.feedback, sizeof(feedback.feedback), stdin);
    feedback.feedback[strcspn(feedback.feedback, "\n")] = '\0';  // Remove a quebra de linha no final

    save_feedback(feedback);
    printf("Feedback salvo com sucesso.\n");
}

void entradaRegistro(){
  int escolha = 0;
  while(escolha != 9){
  printf("BEM VINDO AO MEDSYNC\n\n");
  printf("Escolha uma opcao:\n");
  printf("1 - Login:\n");
  printf("2 - Registre-se:\n");
  printf("9 - Encerrar:\n");
  scanf("%d", &escolha);
  getchar();
    if(escolha == 1){
      char login[50], password[50];
      printf("Log in:\n\n");
      printf("Digite o login: ");
      scanf("%s", login);
      getchar();
  
      printf("Digite a senha: ");
      scanf("%s", password);
      getchar();
  
      if (login_account(login, password)) {
        printf("Logado com sucesso.\n");
      } else {
        printf("Falha ao logar. Tente novamente.\n");
        printf("\033[H\033[2J");
        entradaRegistro();
      }  
      
    }else if (escolha == 2){
      create_account();
      printf("\033[H\033[2J");
      entradaRegistro();
      
    }else{
      printf("\nOpcao invalida\n");
      sleep(2);
      printf("\033[H\033[2J");
      //entradaRegistro();
    }
  }
}