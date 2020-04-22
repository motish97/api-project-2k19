#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TABLE_SIZE 37

typedef struct Entity {
    char nome[50];
    struct Entity *next;
}Entity;

typedef struct {
    Entity **lista;
}tabEntita;

typedef struct MIAO{
                    char nome[50];
                    char id_dest[50];
                    int num_frecce_entranti;
                    tabEntita *ElencoFrecceEntranti;
                    struct MIAO *next;
                    } Relation;

tabEntita *Entities;
Relation *relHead;

void init()
{
    Entities=malloc(sizeof(tabEntita));
    Entities->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
    relHead=malloc(sizeof(Relation));
    relHead->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
    relHead->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
    relHead->num_frecce_entranti=-1;
    for(int i=0;i<TABLE_SIZE;i++)
    {
        Entities->lista[i]=NULL;
        relHead->ElencoFrecceEntranti->lista[i]=NULL;
    }
}

int hash(char *key)
{
    int value=0;
    int key_len=strlen(key);
    
    for(int i=0; i<key_len;i++){
        value=value+key[i];
    }
    
    value=value%TABLE_SIZE;
    return value;
}



void printAllEntities()
{
    for(int i=0;i<TABLE_SIZE;i++){
        if(Entities->lista[i]==NULL)
        {
            printf("%d) EMPTY\n",i);
        }
        else
        {
            Entity *nav=Entities->lista[i];
            printf("%d) ",i);
            while(nav!=NULL)
            {
                printf("[%s] ", nav->nome);
                nav=nav->next;
            }
            printf("\n");
        }
        
    }
}

int entityExists(Entity *head, char *daControllare)
{
    if(head==NULL)
        return 0;
    else
    {
        Entity *nav=head;
        while(nav!=NULL)
        {
            if(strcmp(nav->nome, daControllare)==0)
            {
                return 1;
            }
            else
            {
                nav=nav->next;
            }   
        }
    }
    return 0;
}

void addRel(Relation **relHead, char *id_orig, char *id_dest, char *id_rel)
{
    Relation *nav=*relHead, *tmp=NULL;
    //printf("[%d] [%d]\n",strcmp((*relHead)->nome, id_rel), strcmp((*relHead)->id_dest, id_dest));
    if((*relHead)->num_frecce_entranti==-1)
    {
        (*relHead)->num_frecce_entranti=1;
        strcpy((*relHead)->id_dest, id_dest);
        strcpy((*relHead)->nome, id_rel);
        addEntity(&(*relHead)->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
        (*relHead)->next=NULL;
        return;
    }

    if(strcmp(id_dest, id_orig)==0)
    {
        while(nav->next!=NULL)
        {
            if(strcmp((*relHead)->nome, id_rel)==0 && strcmp((*relHead)->id_dest, id_dest)>0)
            {   
                nav=*relHead;
                *relHead=malloc(sizeof(Relation));
                (*relHead)->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
                (*relHead)->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
                strcpy((*relHead)->nome, id_rel);
                strcpy((*relHead)->id_dest, id_dest);
                (*relHead)->num_frecce_entranti=1;
                addEntity(&(*relHead)->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                (*relHead)->next=nav;
                return;
            }
            if(strcmp(nav->nome, id_rel)==0 && strcmp(nav->id_dest, id_dest)==0)
            {
                if(entityExists((nav)->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig)==1)
                {
                    //printf("Relazione già esistente\n");
                    return;
                }
                else
                {
                    (nav)->num_frecce_entranti++;
                    addEntity(&(nav)->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig);
                    return;
                }
            }
            else if(strcmp(nav->nome, nav->next->nome)!=0 && strcmp(id_rel, nav->next->nome)==0 && strcmp(id_dest, nav->next->id_dest)<0)
            {
                tmp=malloc(sizeof(Relation));
                tmp->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
                tmp->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
                strcpy(tmp->nome, id_rel);
                strcpy(tmp->id_dest, id_dest);
                tmp->num_frecce_entranti=1;
                addEntity(&tmp->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                tmp->next=nav->next;
                nav->next=tmp;
            }
            else if(strcmp(nav->nome, id_rel)<0 && strcmp(nav->next->nome,id_rel)>0)
            {
                tmp=malloc(sizeof(Relation));
                tmp->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
                tmp->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
                strcpy(tmp->nome, id_rel);
                strcpy(tmp->id_dest, id_dest);
                tmp->num_frecce_entranti=1;
                addEntity(&tmp->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                tmp->next=nav->next;
                nav->next=tmp;
            }  
            else if(strcmp(nav->nome, nav->next->nome)==0 && strcmp(id_dest, nav->next->id_dest)<0 && strcmp(nav->nome, id_rel)==0)
            {   
                tmp=malloc(sizeof(Relation));
                tmp->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
                tmp->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
                strcpy(tmp->nome, id_rel);
                strcpy(tmp->id_dest, id_dest);
                tmp->num_frecce_entranti=1;
                addEntity(&tmp->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                tmp->next=nav->next;
                nav->next=tmp;
            }
            
            else
                nav=nav->next;
            
        }
        if(strcmp(nav->nome, id_rel)==0 && strcmp(nav->id_dest, id_dest)==0)
            {
                if(entityExists((nav)->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig)==1)
                {
                    //printf("Relazione già esistente\n");
                    return;
                }
                else
                {
                    (nav)->num_frecce_entranti++;
                    addEntity(&(nav)->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig);
                    return;
                }
            }
    }

    if(strcmp((*relHead)->nome, id_rel)==0 && strcmp((*relHead)->id_dest, id_dest)==0)
    {
        if(entityExists((*relHead)->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig)==1)
        {
            //printf("Relazione già esistente\n");
            return;
        }
        else
        {
            (*relHead)->num_frecce_entranti++;
            addEntity(&(*relHead)->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig);
            return;
        }
        
    }
    if(strcmp((*relHead)->nome, id_rel)==0 && strcmp((*relHead)->id_dest, id_dest)>0)
    {   
        nav=*relHead;
        *relHead=malloc(sizeof(Relation));
        (*relHead)->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
        (*relHead)->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
        strcpy((*relHead)->nome, id_rel);
        strcpy((*relHead)->id_dest, id_dest);
        (*relHead)->num_frecce_entranti=1;
        addEntity(&(*relHead)->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
        (*relHead)->next=nav;
        return;
    }
    if(strcmp((*relHead)->nome, id_rel)==0 && strcmp((*relHead)->id_dest, id_dest)<0 && (*relHead)->next==NULL)
    {   
        
                
                tmp=malloc(sizeof(Relation));
                tmp->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
                tmp->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
                strcpy(tmp->nome, id_rel);
                strcpy(tmp->id_dest, id_dest);
                tmp->num_frecce_entranti=1;
                addEntity(&tmp->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                tmp->next=(*relHead)->next;
                (*relHead)->next=tmp;
                return;

            
        
        
    }
    
    if(strcmp((*relHead)->nome, id_rel)==0 && strcmp((*relHead)->nome, (*relHead)->next->nome)!=0)
    {   
        nav=malloc(sizeof(Relation));
        nav->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
        nav->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
        strcpy(nav->nome, id_rel);
        strcpy(nav->id_dest, id_dest);
        nav->num_frecce_entranti=1;
        addEntity(&nav->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
        nav->next=(*relHead)->next;
        (*relHead)->next=nav;
        return;
    }

    if(strcmp((*relHead)->nome, id_rel)>0)
    {
        nav=*relHead;
        *relHead=malloc(sizeof(Relation));
        (*relHead)->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
        (*relHead)->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
        strcpy((*relHead)->nome, id_rel);
        strcpy((*relHead)->id_dest, id_dest);
        (*relHead)->num_frecce_entranti=1;
        addEntity(&(*relHead)->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
        (*relHead)->next=nav;
        return;

    }
    
    while(nav->next!=NULL)
    {
          
        if(strcmp(nav->next->nome, id_rel)==0 && strcmp(nav->next->id_dest,id_dest)==0)
        {
            if(entityExists(nav->next->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig)==1)
            {
                //printf("Relazione già esistente!\n");
                return;
            }
            else
            { 
                nav->next->num_frecce_entranti++;
                addEntity(&nav->next->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                return;
            }
            
        }
        
        if(strcmp(nav->next->nome, id_rel)==0 && strcmp(nav->next->id_dest, id_dest)>0)
        {   
            tmp=nav->next;            
            nav->next=malloc(sizeof(Relation));
            nav->next->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
            nav->next->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
            strcpy(nav->next->nome, id_rel);
            strcpy(nav->next->id_dest, id_dest);
            nav->next->num_frecce_entranti=1;
            addEntity(&nav->next->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig);
            nav->next->next=tmp;
            return;
        }
        
        if(strcmp(nav->next->nome, id_rel)>0)
        {   
            tmp=nav->next;
            nav->next=malloc(sizeof(Relation));
            nav->next->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
            nav->next->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
            strcpy(nav->next->nome, id_rel);
            strcpy(nav->next->id_dest, id_dest);
            nav->next->num_frecce_entranti=1;
            addEntity(&nav->next->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig);
            nav->next->next=tmp;
            return;
        }
        nav=nav->next;        
    }
    
    nav->next=malloc(sizeof(Relation));
    nav->next->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
    nav->next->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
    strcpy(nav->next->nome, id_rel);
    strcpy(nav->next->id_dest, id_dest);
    nav->next->num_frecce_entranti=1;
    addEntity(&nav->next->ElencoFrecceEntranti->lista[hash(id_orig)], id_orig);
    nav->next->next=NULL;
    //printRelations(relHead);
    return;

    
}



void printEntities(Relation *rel)
{
    for(int i=0;i<TABLE_SIZE;i++){
        if(rel->ElencoFrecceEntranti->lista[i]!=NULL)
        {
            Entity *nav=rel->ElencoFrecceEntranti->lista[i];
            printf("%d) ",i);
            while(nav!=NULL)
            {
                printf("[%s] ", nav->nome);
                nav=nav->next;
            }
            printf("\n");
        }
        
    }
}

void printRelations(Relation *head)
{
    Relation *nav=head;
    while (nav!=NULL)
    {
        printf("id_relazione: [%s] \n", nav->nome);
        printf("Destinatario: [%s] \n", nav->id_dest);
        printf("Numero frecce entranti: %d \n",nav->num_frecce_entranti);
        printf("Mittenti:\n");
        printEntities(nav);
        printf("------\n");
        nav=nav->next;
        
        

    }
}

void addEntity(Entity **head,char *daAggiungere)
{
    if(*head==NULL)
    {
        *head=malloc(sizeof(Entity));
        strcpy((*head)->nome, daAggiungere);
        (*head)->next=NULL;
        return;
    }
    else
    {
        Entity *new=malloc(sizeof(Entity));
        strcpy(new->nome, daAggiungere);
        new->next=*head;
        *head=new;
    }
    
}

void cancellaEntitaEBasta(Entity **head, char *daCancellare)
{
    Entity *xd, *lol;

    if(*head==NULL)
    {
        return;
    }
    else
    {
       xd=*head;
       while (xd->next!=NULL)
       {
           if(strcmp(xd->next->nome, daCancellare)==0)
           {
               lol=xd->next;
               xd->next=xd->next->next;
               free(lol);
               return;
           }
           else
           {
               xd=xd->next;
           }
       }
       if(strcmp((*head)->nome,daCancellare)==0)
       {
           
           lol=*head;
           *head=(*head)->next;
           free(lol);
       }
    }
    
}
void delRel(Relation **RelHead, char *id_orig, char *id_dest, char *id_rel)
{
    Relation *lmao, *f;
    if((*RelHead)->num_frecce_entranti==-1)
    {
        //printf("LISTA VUOTA\n");
        return; //lista vuota
    }
    else
    {
        lmao=*RelHead;
        while(lmao->next!=NULL)
        {
            
            if(strcmp(lmao->next->nome, id_rel)==0 && strcmp(lmao->next->id_dest, id_dest)==0 && entityExists(lmao->next->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig))
            {
                
                if(lmao->next->num_frecce_entranti==1)
                {
                    //printf("Una sola freccia entrante, più Relazioni\n"); 
                    f=lmao->next;
                    lmao->next=lmao->next->next;
                    free(f);
                    return;               
                }
                else
                {   
                    //printf("piu frecce entranti, più relazioni\n"); 
                    lmao->next->num_frecce_entranti--;
                    cancellaEntitaEBasta(&lmao->next->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                    return;
                }
                
            }
            else
            {
                lmao=lmao->next;
            }
            
            
        }

        
        
        if(strcmp((*RelHead)->nome, id_rel)==0 && strcmp((*RelHead)->id_dest, id_dest)==0 && 1==entityExists((*RelHead)->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig))
        {
            f=*RelHead;
            //printf("QUA CI ENTRO\n");
            if((*RelHead)->num_frecce_entranti==1)
            {
                //printf("Primo elemento da cancellare, una sola freccia entrante\n");
                *RelHead=(*RelHead)->next;
                free(f);
            }    
            else
            {
                (*RelHead)->num_frecce_entranti--;
                cancellaEntitaEBasta(&(*RelHead)->ElencoFrecceEntranti->lista[hash(id_orig)],id_orig);
                
            }        
        }

        if(*RelHead==NULL)
        {
            *RelHead=malloc(sizeof(Relation));
            (*RelHead)->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
            (*RelHead)->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
            (*RelHead)->num_frecce_entranti=-1;
            for(int i=0;i<TABLE_SIZE;i++)
            {
                (*RelHead)->ElencoFrecceEntranti->lista[i]=NULL;
            }
        }
        
    }
    
}

void delEntity(Relation **relHead, Entity **head, char *daCancellare)
{
    cancellaEntitaEBasta(&Entities->lista[hash(daCancellare)], daCancellare);
    Relation *nav,*tmp;
    nav=*relHead;
    if((*relHead)->num_frecce_entranti==-1)
        return;
    while (nav->next!=NULL)
    {
        if(strcmp(nav->next->id_dest, daCancellare)==0)
        {
            tmp=nav->next;
            nav->next=nav->next->next;
            free(tmp);
        }
        else if (entityExists(nav->next->ElencoFrecceEntranti->lista[hash(daCancellare)],daCancellare))
        {
            if(nav->next->num_frecce_entranti>1)
            {
                nav->next->num_frecce_entranti--;
                cancellaEntitaEBasta(&nav->next->ElencoFrecceEntranti->lista[hash(daCancellare)],daCancellare);
            }
            else
            {
                tmp=nav->next;
                nav->next=nav->next->next;
                free(tmp);
            }
            
        }
        else
        {
            nav=nav->next;
        }
        
    }

    //printf("[%d]\n",strcmp((*relHead)->id_dest, daCancellare));
    if(strcmp((*relHead)->id_dest, daCancellare)==0)
    {
        tmp=*relHead;
        *relHead=(*relHead)->next;
        free(tmp);
    }
    else
    {
        if(entityExists((*relHead)->ElencoFrecceEntranti->lista[hash(daCancellare)],daCancellare))
        {
            if((*relHead)->num_frecce_entranti>1)
            {
                (*relHead)->num_frecce_entranti--;
                cancellaEntitaEBasta(&(*relHead)->ElencoFrecceEntranti->lista[hash(daCancellare)],daCancellare);
            }
            else
            {
                tmp=*relHead;
                *relHead=(*relHead)->next;
                free(tmp);
                //(*relHead)->num_frecce_entranti=-1;
            }
            
        }
    }
    if((*relHead)==NULL)
    {
        *relHead=malloc(sizeof(Relation));
        (*relHead)->ElencoFrecceEntranti=malloc(sizeof(tabEntita));
        (*relHead)->ElencoFrecceEntranti->lista=malloc(sizeof(tabEntita)*TABLE_SIZE);
        (*relHead)->num_frecce_entranti=-1;
        for(int i=0;i<TABLE_SIZE;i++)
        {
            (*relHead)->ElencoFrecceEntranti->lista[i]=NULL;
        }
    }
    if((*relHead)->num_frecce_entranti==-1)
        return;
    
}

void report(Relation **relHead)
{
    if((*relHead)->num_frecce_entranti==-1)
    {
        printf("none\n");
    }
    else
    {
        Relation *nav, *riferimento;
        riferimento=*relHead;
        nav=riferimento->next;

        char output[20000];

        sprintf(output,"%s %s", riferimento->nome, riferimento->id_dest);
        //fputs(output, stdout);
        while(nav!=NULL)
        {
            if(strcmp(nav->nome, riferimento->nome)==0 && nav->num_frecce_entranti==riferimento->num_frecce_entranti)
            {
                sprintf(output,"%s %s",output, nav->id_dest);
                nav=nav->next;
            }
            else if(strcmp(nav->nome, riferimento->nome)==0 && nav->num_frecce_entranti>riferimento->num_frecce_entranti)
            {
                riferimento=nav;
                strcpy(output,"");
                sprintf(output,"%s %s", riferimento->nome, riferimento->id_dest);
                nav=nav->next;
            }
            else if(strcmp(nav->nome, riferimento->nome)!=0)
            {
                sprintf(output,"%s %d; ", output, riferimento->num_frecce_entranti);
                fputs(output, stdout);
                riferimento=nav;
                nav=nav->next;
                sprintf(output,"%s %s", riferimento->nome, riferimento->id_dest);
            }
            else
            {
                nav=nav->next;
            }
            
        }
        sprintf(output,"%s %d;\n", output, riferimento->num_frecce_entranti);
        fputs(output, stdout);
    }
    
}


    //NB QUANDO FAI ADDREL, DELREL, ADDENT E DELENT PRIMA DI INVOCARLE CONTROLLA LE ENTITA!!
int main(char argc, char* argv)
{
    init();
    
    char comando[50], param1[50], param2[50], param3[50];
    FILE *input;
    input=stdin;
    //input=fopen("Suite1/batch1.1.in","r");
    while(!feof(input))
    {
        fscanf(input, "%s", &comando);
        if (strcmp(comando,"addent")==0)
        {
            fscanf(input, "%s", &param1);
            if(!entityExists(Entities->lista[hash(param1)],param1))
            {
                addEntity(&Entities->lista[hash(param1)],param1);
            }
        }
        else if (strcmp(comando,"delent")==0)
        {
            fscanf(input, "%s", &param1);
            if(entityExists(Entities->lista[hash(param1)],param1))
            {
                delEntity(&relHead, &Entities->lista[hash(param1)],param1);
            }
            
        }
        else if (strcmp(comando,"report")==0)
        {
        //printf("[%d]",strcmp("Jonathan_Archer","Jonathan_Archer"));
            report(&relHead);
        }
        else if (strcmp(comando,"addrel")==0)
        {
            fscanf(input, "%s", &param1);
            fscanf(input, "%s", &param2);
            fscanf(input, "%s", &param3);
            if(entityExists(Entities->lista[hash(param1)],param1) && entityExists(Entities->lista[hash(param2)],param2))
            {
                addRel(&relHead, param1, param2, param3);
            }
            
        } 
        else if (strcmp(comando,"delrel")==0)
        {
            fscanf(input, "%s", &param1);
            fscanf(input, "%s", &param2);
            fscanf(input, "%s", &param3);
            if(entityExists(Entities->lista[hash(param1)],param1) && entityExists(Entities->lista[hash(param2)],param2))
            {
                delRel(&relHead, param1, param2, param3);
            }
            
        }
        else if (strcmp(comando,"end")==0)
        {
            /*printf("\n\n-------------\n\n");
            printRelations(relHead);
            printf("\n\n-------------\n\n");
            printAllEntities();
            //printf("%s",relHead->nome);*/
            return 0;
        }
        else
        {
            printf("Comando non valido \n");
        }
          
    }
    
    return 0;
}