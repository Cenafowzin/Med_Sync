#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
    areaNode *currentArea = NULL, *AreaHead = NULL, *AreaTail = NULL, *selectedArea = NULL;
    specNode *currentSpec = NULL, *SpecHead = NULL, *SpecTail = NULL, *selectedSpec = NULL;
    actvNode *currentActiv = NULL, *ActvHead = NULL, *ActvTail = NULL, *selectedActiv = NULL;
    questForm *currentQuest = NULL, *ActvFormHead = NULL, *ActvFormTail = NULL, *selectedQuest = NULL;
    questForm *PrecAvtHead = NULL, *PrecAvTail = NULL;
    questFormResp *QuestRespHead = NULL, *QuestRespTail = NULL;

    loadAreas(&AreaHead, &AreaTail);
    loadSpecs(&SpecHead, &SpecTail);
    loadActvs(&ActvHead, &ActvTail);
    loadQuests(&ActvFormHead, &ActvFormTail);
    entradaRegistro(AreaHead, AreaTail, SpecHead, SpecTail, ActvHead, ActvTail, ActvFormHead, ActvFormTail, QuestRespHead, QuestRespTail);

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