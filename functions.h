#ifndef __FUNCTIONS__
#define __FUNCTIONS__

//ÁREA DE RODRIGO:
// ESTRUTURAS ---------------------------------------------------------------
typedef struct {
    char login[50];
    char password[50];
    char nome[50];
    char cargo[50];
    char area[50];
    char especializacao[50];
} Account;

typedef struct {
    Account* accounts;
    int count;
} AccountList;

typedef struct {
    char account_name[50];
    char feedback[1000];
} Feedback;

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

void saveActvs(actvNode *ActvHead);
void loadActvs(actvNode **ActvHead, actvNode **ActvTail);
actvNode *selectActv(char *SelectedSpec, actvNode *ActvHead, actvNode *PrevSelected);
void createActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail);
void editActv(specNode *SelectedSpec, actvNode **ActvHead);
void deleteActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail);
void saveQuests(questForm *QuestFormHead);
void loadQuests(questForm **FormHead, questForm **FormTail);
questForm *selectQuest(actvNode *SelectedActivity, questForm *QuestFormHead, questForm *PrevSelected);
void createQuestForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail);
void editQuestForm(actvNode *SelectedActiv, questForm **FormHead);
void deleteQuestForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail);
void menuForm(actvNode *SelectedActiv, questForm **FormHead, questForm **FormTail);
void menuActv(specNode *SelectedSpec, actvNode **ActvHead, actvNode **ActvTail, questForm *FormHead, questForm *FormTail,
 questFormResp *QuestRespHead, questFormResp *QuestRespTail);
void saveSpecs(specNode *SpecHead);
void loadSpecs(specNode **SpecHead, specNode **SpecTail);
specNode *selectSpec(areaNode *SelectedArea, specNode *SpecHead, specNode *PrevSelected);
void createSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail);
void editSpec(areaNode *SelectedArea, specNode **SpecHead);
void deleteSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail);
void menuSpec(areaNode *SelectedArea, specNode **SpecHead, specNode **SpecTail, actvNode *ActvHead, actvNode *ActvTail,
 questForm *FormHead, questForm *FormTail, questFormResp *QuestRespHead, questFormResp *QuestRespTail);
void saveAreas(areaNode *AreaHead);
void loadAreas(areaNode **AreaHead, areaNode **AreaTail);
areaNode *selectArea(areaNode *AreaHead, areaNode *PrevSelected);
void createArea(areaNode **AreaHead, areaNode **AreaTail);
void editArea(areaNode **AreaHead);
void deleteArea(areaNode **AreaHead, areaNode **AreaTail);
void menuManager(areaNode *AreaHead, areaNode *AreaTail, specNode *SpecHead, specNode *SpecTail,
 actvNode *ActvHead, actvNode *ActvTail, questForm *FormHead, questForm *FormTail, questFormResp *QuestRespHead, questFormResp *QuestRespTail);
void entradaRegistro(areaNode *AreaHead, areaNode *AreaTail, specNode *SpecHead, specNode *SpecTail,
 actvNode *ActvHead, actvNode *ActvTail, questForm *FormHead, questForm *FormTail, questFormResp *QuestRespHead, 
 questFormResp *QuestRespTail);

// ESPECIALIZACAO ---------------------------------------------------------------


// AREA -----------------------------------------------------------------------


//ÁREA DE FLÁVIO:
/*dados do usuário. 0.Ger, 1.Pre, 2.Res*/

//ÁREA DE JOÃO:


void save_account(Account account);
int valid_role(char *cargo);
void create_account();
Account * login_account(char* login, char* password);
AccountList show_specialization(char* specialization, char* cargo);
Account choose_account_by_number(AccountList accountList, int number);
void menuPreceptor();
void menuResident(Account * User, actvNode * ActvHead, questForm *FormHead, questFormResp **FormRespHead, questFormResp **FormRespTail);
void save_feedback(Feedback feedback);
void give_feedback(Account chosenAccount);
void print_feedback(const char* account_name);
//ÁREA DE DIEGO:


//ÁREA DE VICTOR:
void answerQuestForm(actvNode *SelectedActiv, questForm *FormHead, questFormResp **FormRespHead, questFormResp **FormRespTail);

#endif