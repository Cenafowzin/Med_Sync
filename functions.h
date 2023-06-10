#ifndef __FUNCTIONS__
#define __FUNCTIONS__

//ÁREA DE RODRIGO:
// ESTRUTURAS ---------------------------------------------------------------
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
specNode *selectSpec(areaNode *SelectedArea, specNode *SpecHead, specNode *PrevSelected);
void createSpec(areaNode *SelectedArea, specNode **SpecHead);
void editSpec(areaNode *SelectedArea, specNode **SpecHead);
void deleteSpec(areaNode *SelectedArea, specNode **SpecHead);
void menuSpec(areaNode *SelectedArea, specNode **SpecHead);

// AREA -----------------------------------------------------------------------
areaNode *selectArea(areaNode *AreaHead, areaNode *PrevSelected);
void createArea(areaNode **AreaHead);
void editArea(areaNode **AreaHead);
void deleteArea(areaNode **AreaHead);
void menuArea(areaNode *AreaHead, specNode *SpecHead);

//ÁREA DE FLÁVIO:
/*dados do usuário. 0.Ger, 1.Pre, 2.Res*/
typedef struct {
    int permissao;//0=gerencia, 1=preceptor, 2=residente
    char* nome;
    char* email;
    int cpf;
    int celular;
    char* endereco;
    char senha[21];
    char* area;
    char** especializacao;
} StructUser;
StructUser* criarCadastroLogin(StructUser* cadastro);
void liberarCadastroLogin(StructUser* cadastro);
void salvarStructUser(const StructUser* user);
int fazerLogin(const char* email, const char* senha);
StructUser* cadastrarLogin(const char* email, const char* senha);
//ÁREA DE JOÃO:

//ÁREA DE HENRIQUE:

//ÁREA DE VICTOR:

//ÁREA DE DIEGO:

#endif