#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "functions.h"

//ÁREA DE RODRIGO:

// estruturas (serão transferidas para o funcs.h)
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

// ATIVIDADE ---------------------------------------------------------------

actvNode *selectActv(specNode *SelectedSpec, actvNode *ActvHead, actvNode *PrevSelected){

    if(SelectedSpec == NULL){
        printf("Nenhuma especialização selecionada");
        return NULL;
    }

    if (ActvHead == NULL){
        printf("Não existe nenhuma atividade\n-----------------\n");
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
            printf("Opção inválida\n");
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

void createActv(specNode *SelectedSpec, actvNode **ActvHead){

    if(SelectedSpec == NULL){
        printf("Nenhuma especialização selecionada");
        return;
    }

    printf("Digite o nome da atividade que deseja criar:\n");
    char ch = getchar();

    if(ch == '\n'){
        printf("Você não pode criar uma atividade sem nome!\n");
        return;
    }

    if(*ActvHead == NULL){

        *ActvHead = (actvNode *)malloc(sizeof(actvNode));
        int size = 0;
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
        (*ActvHead)->next = NULL;

    }else{

        actvNode *current = *ActvHead;

        while(current->next != NULL){
            current = current->next;
        }

        current->next = (actvNode *)malloc(sizeof(actvNode));
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
        current->spec = (char *)malloc(sizeof(*(SelectedSpec->name)));
        strcpy(current->spec, SelectedSpec->name);
        current->next = NULL;
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
            printf("Você não deixar uma atividade sem nome!\n");
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

void deleteActv(specNode *SelectedSpec, actvNode **ActvHead){
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
}

void menuActv(specNode *SelectedSpec, actvNode **ActvHead){
    int command = -1;
    actvNode *selectedActv = NULL;

    while(command != 0){
        printf("[%s]\n", *ActvHead);
        printf("Especialização: %s\n|----------------|\n", SelectedSpec->name);
        
        if(*ActvHead == NULL){
            printf("Não existe nenhuma atividade\n-----------------\n");
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


        printf("Selecione uma ação para fazer:\n");
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
            createActv(SelectedSpec, ActvHead);
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
            deleteActv(SelectedSpec, ActvHead);
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
        printf("Não existe nenhuma especialização\n-----------------\n");
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

        printf("Digite o numero da especialização: ");
        scanf("%d", &spec);

        if (spec == 0){
            if(PrevSelected != NULL){
                return PrevSelected;
            }
            return NULL;

        }

        if(spec > count || spec < 0){
            printf("Opção inválida\n");
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
        (*SpecHead)->area = (char *)malloc(sizeof(SelectedArea->name));
        strcpy((*SpecHead)->area, SelectedArea->name);
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
        current->area = (char *)malloc(sizeof(*(SelectedArea->name)));
        strcpy(current->area, SelectedArea->name);
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

void deleteSpec(areaNode *SelectedArea, specNode **SpecHead){
    specNode *selectedSpec = NULL, *current = *SpecHead, *temp = NULL;

    selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);

    if(selectedSpec == NULL || *SpecHead == NULL){
        printf("Nenhuma especialização");
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
}

void menuSpec(areaNode *SelectedArea, specNode **SpecHead, actvNode *ActvHead){
    int command = -1;
    specNode *selectedSpec = NULL;

    while(command != 0){
        printf("[%s]\n", *SpecHead);
        printf("Área: %s\n|----------------|\n", SelectedArea->name);
        
        if(*SpecHead == NULL){
            printf("Não existe nenhuma especialização\n-----------------\n");
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


        printf("Selecione uma ação para fazer:\n");
        printf("(0) voltar\n");
        printf("(1) criar especialização\n");
        printf("(2) editar especialização\n");
        printf("(3) selecionar especialização\n");
        printf("(4) deletar especialização\n");
        printf("(5) ver atividades de uma especialização\n");
        scanf("%d", &command);

        switch(command){
        case 0:
            return;
            break;
        case 1:
            getchar();
            printf("\033[H\033[2J");
            createSpec(SelectedArea, SpecHead);
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
            deleteSpec(SelectedArea, SpecHead);
            printf("\033[H\033[2J");
            break;

        case 5:
            printf("\033[H\033[2J");
            selectedSpec = selectSpec(SelectedArea, *SpecHead, selectedSpec);
            printf("\033[H\033[2J");
            menuActv(selectedSpec, &ActvHead);
            printf("\033[H\033[2J");
            break;

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
}

void menuArea(areaNode *AreaHead, specNode *SpecHead, actvNode *ActvHead){
    int command = -1;
    areaNode *selectedArea = NULL;
    printf("\033[H\033[2J");

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
            break;

        case 5:
            printf("\033[H\033[2J");
            selectedArea = selectArea(AreaHead, selectedArea);
            printf("\033[H\033[2J");
            menuSpec(selectedArea, &SpecHead, ActvHead);
            printf("\033[H\033[2J");
            break;

        }
    }

}

// testes (será apagado no fim)
int main()
{

    areaNode *currentArea = NULL, *AreaHead = NULL, *selectedArea = NULL;
    specNode *currentSpec = NULL, *SpecHead = NULL, *selectedSpec = NULL;
    actvNode *currentActiv = NULL, *ActvHead = NULL, *selectedActiv = NULL;

    menuArea(AreaHead, SpecHead, ActvHead);

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

//ÁREA DE FLÁVIO:
typedef struct {
    int permissao;
    char* nome;
    char* email;
    int cpf;
    int celular;
    char* endereco;
    char senha[21];
    char* area;
    char** especializacao;
} StructUser;

/*função para alocar memória para criar espaços para cadastro*/
StructUser* criarCadastroLogin(StructUser* cadastro) {
    cadastro = malloc(sizeof(StructUser));
    cadastro->nome = malloc(sizeof(char) * 100);
    cadastro->email = malloc(sizeof(char) * 100);
    cadastro->endereco = malloc(sizeof(char) * 100);
    cadastro->area = malloc(sizeof(char) * 100);
    cadastro->especializacao = malloc(sizeof(char*) * 10); // Definido como máximo 10 especializações, ajuste conforme necessário
    // Inicialize o campo de especialização para NULL
    for (int i = 0; i < 10; i++) {
        cadastro->especializacao[i] = NULL;
    }
    return cadastro;
}
/*liberar memória criada para dados do cadastro*/
void liberarCadastroLogin(StructUser* cadastro) {
    free(cadastro->nome);
    free(cadastro->email);
    free(cadastro->endereco);
    free(cadastro->area);

    // Libere memória para cada especialização
    for (int i = 0; i < 10; i++) {
        if (cadastro->especializacao[i] != NULL) {
            free(cadastro->especializacao[i]);
        }
    }
    free(cadastro->especializacao);

    free(cadastro);
}
/*receber dados do usuário e salvar no txt*/
void salvarStructUser(const StructUser* user) {
    FILE* arquivo = fopen("dados.txt", "w");
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
    while (*especializacao != NULL) {
        fprintf(arquivo, "- %s\n", *especializacao);
        especializacao++;
    }

    fclose(arquivo);
    
}

StructUser* consultarUsuario(const char* email, const char* senha) {
    FILE* arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    StructUser* user;
    criarCadastroLogin(user);

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char* valorEmail;
        if (strncmp(linha, "Email: ", 7) == 0) {
            valorEmail = linha + 7;
            valorEmail[strlen(valorEmail) - 1] = '\0'; // Remover o caractere de nova linha
        }

        if  (strncmp(linha, "Senha: ", 7) == 0) {
            char* valorSenha = linha + 7;
            valorSenha[strlen(valorSenha) - 1] = '\0'; // Remover o caractere de nova linha
            if ((strcmp(valorSenha, senha) != 0)||(strcmp(valorEmail, email) != 0)) {
                // Senha não corresponde, avançar para a próxima linha
                printf("E-mail ou senha estão incorretos.\n");
                fclose(arquivo);
                return NULL;
            }
        }

        // Preencher os outros campos do usuário
        if (strncmp(linha, "Permissao: ", 11) == 0) {
            sscanf(linha, "Permissao: %d", &(user->permissao));
        } else if (strncmp(linha, "Nome: ", 6) == 0) {
            sscanf(linha, "Nome: %[^\n]", user->nome);
        } else if (strncmp(linha, "CPF: ", 5) == 0) {
            sscanf(linha, "CPF: %d", &(user->cpf));
        } else if (strncmp(linha, "Celular: ", 9) == 0) {
            sscanf(linha, "Celular: %d", &(user->celular));
        } else if (strncmp(linha, "Endereco: ", 10) == 0) {
            sscanf(linha, "Endereco: %[^\n]", user->endereco);
        } else if (strncmp(linha, "Senha: ", 7) == 0) {
            sscanf(linha, "Senha: %20[^\n]", user->senha);
        } else if (strncmp(linha, "Area: ", 6) == 0) {
            sscanf(linha, "Area: %[^\n]", user->area);
        }
    }
    fclose(arquivo);

    return user;
}



void give_feedback(){

}



//ÁREA DE VICTOR:

//ÁREA DE JOÃO:

//ÁREA DE HENRIQUE:

//ÁREA DE DIEGO:

