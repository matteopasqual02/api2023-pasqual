#include <stdio.h>
#include <stdlib.h>

//data structure
typedef struct node{
    int km; 

    int max_autonomia;
    int autonomia[512];

    struct node *tappa;
    int p;

    struct node *prox;
    struct node *prec;
}stazione;
typedef stazione *autostrada;


typedef struct n{
    int k;

    struct n *prossimo;
}percorso;
typedef percorso *p_percorso;

//pianifica_percorso  ##DONE
void pianifica_percorso(autostrada a_ip,int inizio_percorso,int fine_percorso){
    if(inizio_percorso == fine_percorso){
        printf("%d\n",inizio_percorso);
        return ;
    }

    autostrada index;
    autostrada step;
    int uscita;
    step=NULL;

    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    if(inizio_percorso < fine_percorso){
        while(a_ip->km != inizio_percorso){
            a_ip= a_ip->prox;
        }
        if(fine_percorso-inizio_percorso <= a_ip->max_autonomia){
            printf("%d %d\n",inizio_percorso,fine_percorso);
            return ;
        }

        index=a_ip;
        index->tappa=NULL;
        while(index->km != fine_percorso){
            index=index->prox;
            index->tappa=NULL;
        }

        index=a_ip;
        uscita=0;

        while(index->km != fine_percorso && uscita==0){
            step=index->prox;

            if(index->tappa!=NULL || index->km==inizio_percorso){
                while(step!=NULL && step->km<fine_percorso+1 && step->km-index->km <=index->max_autonomia && uscita==0){
                    if(step->tappa ==NULL ){
                        step->tappa= index;
                    }

                    if(step->km==fine_percorso){
                        uscita=1;
                    }
                    else{
                        step=step->prox;
                    }
                }
            }
            
            index=index->prox;
        }

        if(step!=NULL && step->tappa==NULL){
            printf("nessun percorso\n");
            return ;
        }

        p_percorso stampa;
        p_percorso new;

        stampa=(p_percorso)malloc(sizeof(percorso));
        stampa->k=step->km;
        stampa->prossimo=NULL;
        step=step->tappa;

        while(step->km != inizio_percorso){
            new=(p_percorso)malloc(sizeof(percorso));
            new->k=step->km;
            new->prossimo=stampa;
            stampa=new;

            step=step->tappa;
        }

        printf("%d ",inizio_percorso);
        while (stampa !=NULL){
            printf("%d ",stampa->k);
            stampa=stampa->prossimo;
        }
        printf("\n");

        return;
    }

    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    while(a_ip->km != inizio_percorso){
        if(a_ip->km >=fine_percorso){
            a_ip->tappa=NULL;
            a_ip->p=-1;
        }
        a_ip= a_ip->prox;
    }
    a_ip->tappa=NULL;
    a_ip->p=0;

    if(inizio_percorso-fine_percorso <= a_ip->max_autonomia){
        printf("%d %d\n",inizio_percorso,fine_percorso);
        return ;
    }

    index=a_ip;

    while (index->km !=fine_percorso ){
        step=index->prec;

        if(index->tappa!=NULL || index->km==inizio_percorso){
            while(step!=NULL && step->km>fine_percorso-1 && index->km-step->km<=index->max_autonomia ){
                if(step->p != index->p ){
                    step->tappa= index;
                    step->p=index->p +1;
                }

                step=step->prec;
                
            }
        }

        index=index->prec;
    }
   
    step=index;
    if(step!=NULL && step->tappa==NULL){
        printf("nessun percorso\n");
        return ;
    }

    p_percorso stampa;
    p_percorso new;

    stampa=(p_percorso)malloc(sizeof(percorso));
    stampa->k=step->km;
    stampa->prossimo=NULL;
    step=step->tappa;

    while(step->km != inizio_percorso){
        new=(p_percorso)malloc(sizeof(percorso));
        new->k=step->km;
        new->prossimo=stampa;
        stampa=new;

        step=step->tappa;
    }

    printf("%d ",inizio_percorso);
    while (stampa !=NULL){
        printf("%d ",stampa->k);
        stampa=stampa->prossimo;
    }
    printf("\n");

    return;
}

//aggiungi_stazione ##DONE
autostrada aggiungi_stazione(autostrada a,int km){
    int numauto=0;
    int autonomialetta=0;
    int i=0,k=0;

    if(a==NULL){                                                                    //vuota
        a=(autostrada)malloc(sizeof(stazione));                                        
        a->km=km;
        a->max_autonomia=0;
        
        if(scanf("%d", &numauto)!=EOF){
            for(i=0;i<numauto;i++){
                if(scanf("%d", &autonomialetta)!=EOF){
                    a->autonomia[i]=autonomialetta;
                    if(autonomialetta > a->max_autonomia){
                        a->max_autonomia=autonomialetta;
                    }
                }
            }
            for(k=i;k<512;k++){
                a->autonomia[k]=-1;
            }
        }

        a->tappa=NULL;
        a->prec=NULL;
        a->prox=NULL;
        printf("aggiunta\n");
        
        return a;
    }

    if (a->km == km){                                                               //errore di primo
        printf("non aggiunta\n");
        return a;
    }

    if(a->km > km){                                                                 //inserimento in testa
        autostrada nuovo = (autostrada)malloc(sizeof(stazione)); 
        nuovo->km=km;
        nuovo->max_autonomia=0;

        if(scanf("%d", &numauto)!=EOF){
            for(i=0;i<numauto;i++){
                if(scanf("%d", &autonomialetta)!=EOF){
                    nuovo->autonomia[i]=autonomialetta;
                    if(autonomialetta > nuovo->max_autonomia){
                        nuovo->max_autonomia=autonomialetta;
                    }
                }
            }
            for(k=i;k<512;k++){
                nuovo->autonomia[k]=-1;
            }
        }
        
        nuovo->tappa=NULL;
        nuovo->prox=a;
        nuovo->prec=NULL;
        a->prec=nuovo;
        printf("aggiunta\n");

        return nuovo;
    }

    autostrada index;
    index=a;
    while(index->prox != NULL && index->prox->km < km){
        index=index->prox;

    }
    if (index->prox != NULL && index->prox->km == km){                             //gia esistente
        printf("non aggiunta\n");
        return a;
    }

    autostrada nuovo = (autostrada)malloc(sizeof(stazione));                        //inserimento classico
    nuovo->km=km;
    nuovo->max_autonomia=0;
    
    if(scanf("%d", &numauto)!=EOF){
        for(i=0;i<numauto;i++){
            if(scanf("%d", &autonomialetta)!=EOF){
                nuovo->autonomia[i]=autonomialetta;
                if(autonomialetta > nuovo->max_autonomia){
                    nuovo->max_autonomia=autonomialetta;
                }
            }
        }
        for(k=i;k<512;k++){
            nuovo->autonomia[k]=-1;
        }
    }

    nuovo->tappa=NULL;
    nuovo->prec=index;
    if( index->prox != NULL){
        nuovo->prox = index->prox;
        index->prox->prec= nuovo;
    }
    else{
        nuovo->prox=NULL;
    }
    index->prox=nuovo;
    printf("aggiunta\n");

    return a;
}

//aggiungi_auto ##DONE
autostrada aggiungi_auto(autostrada a,int km){
    autostrada index;
    int macchina=0;
    index=a;
    while(index->prox!=NULL && index->km <km){
        index=index->prox;
    }
    if(index->km!=km){
        printf("non aggiunta\n");
        return a;
    }

    if(scanf("%d", &macchina)!=EOF){
        int i=0;
        while(index->autonomia[i]!=-1 ){
            i++;
            if(i==512){
                printf("non aggiunta\n");
                return a;
            }
        }
        index->autonomia[i]=macchina;
        if(macchina>index->max_autonomia){
            index->max_autonomia=macchina;
        }
        
    }
    printf("aggiunta\n");
    return a;
}

//demolisci_stazione  ##DONE
autostrada demolisci_stazione(autostrada a,int km){
    if(a==NULL){                            //autostrada vuota
        printf("non demolita\n");
        return a;
    }

    if(a->km == km){                        //demolizione inizio
        if(a->prox==NULL){
            free(a);
            return NULL;
        }

        autostrada n;
        n=a->prox;
        n->prec=NULL;
        free(a);
        return n;
    }

    autostrada index;
    index=a;

    while(index->prox!=NULL && index->km <km){
        index=index->prox;
    }
    if(index->km!=km){
        printf("non demolita\n");
        return a;
    }

    if(index->prox != NULL){
        index->prec->prox=index->prox;
        index->prox->prec=index->prec; 
    }
    else{
        index->prec->prox=NULL;
    }
    
    free(index);

    printf("demolita\n");

    return a;
}

//demolisci_auto  ##DONE
autostrada demolisci_auto(autostrada a,int km){
    autostrada index;
    index=a;
    int i=0;
    int macchina,trovato=0;

    while(index->prox!=NULL && index->km <km){
        index=index->prox;
    }
    if(index->km!=km){
        printf("non rottamata\n");
        return a;
    }
    
    if(scanf("%d", &macchina)!=EOF){
        while(i<512 && trovato==0){
            if(macchina == index->autonomia[i]){
                trovato=1;
                index->autonomia[i]=-1;
                if(macchina == index->max_autonomia){
                    index->max_autonomia=0;
                    for (int k=0;k<512;k++){
                        if(index->max_autonomia < index->autonomia[k]){
                            index->max_autonomia=index->autonomia[k];
                        }
                    }
                    
                }
            }
            i++;
        }
    }

    if(trovato==0){
        printf("non rottamata\n");
    }
    else{
        printf("rottamata\n");
    }

    return a;
}

//di aiuto debug  ##DONE
void stampa_autostrada(autostrada a){
    printf("\nkm %d maxa %d :",a->km,a->max_autonomia);
    for(int i=0;i<10;i++){
        printf("%d :",a->autonomia[i]);
    }
    if(a->prox!=NULL){
        stampa_autostrada(a->prox);
    }
    
}

//main ##DONE
int main(){
    char lettura[20];
    autostrada inizio_autostrada;
    int km, inizio, fine;
    inizio_autostrada= NULL;

    while(scanf("%s",lettura) != EOF){                                           //lettura_da_stdin

        if(lettura[0]=='p'){                                                     //pianifica_percorso
            if(scanf("%d", &inizio)!=EOF && scanf("%d", &fine)!=EOF){
                pianifica_percorso(inizio_autostrada,inizio,fine);
            }  
        } 

        else if(lettura[0]=='a' && lettura[9]=='s'){                             //aggiungi_stazione
            if(scanf("%d", &km)!=EOF){
                inizio_autostrada = aggiungi_stazione(inizio_autostrada,km); 
            }  
        }

        else if(lettura[0]=='a' && lettura[9]=='a'){                             //aggiungi_auto
            if(scanf("%d", &km)!=EOF){
                inizio_autostrada=aggiungi_auto(inizio_autostrada,km);
            } 
        }

        else if(lettura[0]=='d' && lettura[10]=='s'){                           //demolisci_stazione
            if(scanf("%d", &km)!=EOF){
                inizio_autostrada=demolisci_stazione(inizio_autostrada,km);
            } 
        }

        else if(lettura[0]=='r'){                                               //demolisci_auto
            if(scanf("%d", &km)!=EOF){
                inizio_autostrada=demolisci_auto(inizio_autostrada,km);
            } 
        }
    }
    
    return 0;
}
