#include <stdio.h>
#include <stdlib.h>

//albero ##DONE
typedef struct n{
    struct n *padre;
    struct n *left;
    struct n *right;

    int km;
    int max_autonomia;
    int autonomia[512];

}node;
typedef node *p_node;
typedef struct s{
    int km;
    int max_autonomia;
    int p;

    struct s *prox;
    struct s *tappa;
}percorso;
typedef percorso *p_percorso;
typedef struct p{
    int k;

    struct p *prossimo;
}stampa;
typedef stampa *p_stampa;

//tree min and max 
p_node tree_minimum(p_node a){
    while(a->left != NULL){
        a=a->left;
    }
    return a;
}
p_node tree_maximum(p_node a){
    while(a->right != NULL){
        a=a->right;
    }
    return a;
}
p_node tree_succ(p_node a){
    if(a->right != NULL){
        return tree_minimum(a->right);
    }

    p_node id;
    id=a->padre;
    while(id != NULL && a == id->right){
        a=id;
        id=id->padre;
    }
    return id;
}
p_node tree_pred(p_node a){
    if(a->left != NULL){
        return tree_maximum(a->left);
    }

    p_node id;
    id=a->padre;
    while(id != NULL && a == id->left){
        a=id;
        id=id->padre;
    }
    return id;
}

//aggiungi_stazione ##DONE
p_node aggiungi_stazione(p_node a, int km){
    p_node index, point;
    p_node new;
    
    point=NULL;
    index=a;
    while(index != NULL){
        point=index;
        if(km == index->km){
            printf("non aggiunta\n");
            return a;
        }
        if(km < index->km){
            index=index->left;
        }
        else{
            index=index->right;
        }
    }
    
    new=(p_node)malloc(sizeof(node));
    new->padre=point;
    new->km=km;
    new->right=NULL;
    new->left=NULL;
    new->max_autonomia=0;

    int i,k,numauto,autonomialetta;
    if(scanf("%d", &numauto)!=EOF){
        for(i=0;i<numauto;i++){
            if(scanf("%d", &autonomialetta)!=EOF){
                new->autonomia[i]=autonomialetta;
                if(autonomialetta > new->max_autonomia){
                    new->max_autonomia=autonomialetta;
                }
            }
        }
        for(k=i;k<512;k++){
            new->autonomia[k]=-1;
        }
    }
    printf("aggiunta\n");

    if(point==NULL){
        return new;
    }
    if (km <point->km){
        point->left=new;
    }
    else{
        point->right=new;
    }
    return a;
}

//demolisci_stazione  
p_node demolisci_stazione(p_node a, int km){
    p_node x, y, z;
    p_node root;

    root=a;
    z=NULL;
    while(a!=NULL){
        if(a->km == km){
            z=a;
        }
        if(km < a->km){
            a=a->left;
        }
        else{
            a=a->right;
        }
    }
    if(z==NULL){
        printf("non demolita\n");
        return root;
    }
    
    
    if(z->left==NULL || z->right==NULL){
        y=z;
    }
    else{
        y = tree_succ(z);
    }

    if(y->left!=NULL){
        x=y->left;
    }
    else{
        x=y->right;
    }

    if(x!=NULL){
        x->padre=y->padre;
    }

    if(y->padre==NULL){
        root=x;
    }
    else if(y==y->padre->left){
        y->padre->left=x;
    }
    else{
        y->padre->right=x;
    }

    if(y!=z){
        z->km=y->km;
        z->max_autonomia=y->max_autonomia;
        int i;
        for(i=0;i<512;i++){
            z->autonomia[i]=y->autonomia[i];
        }
    }

    free(y);
    printf("demolita\n");
    return root;
}

//aggiungi_auto ##DONE
void aggiungi_auto(p_node a, int km){
    while(a!=NULL){
        if(a->km == km){
            int macchina,i;
            if(scanf("%d", &macchina)!=EOF){
                i=0;
                while(a->autonomia[i] !=-1){
                    i++;
                    if(i==512){
                        printf("non aggiunta\n");
                        return;
                    }
                }
                a->autonomia[i]=macchina;
                if(macchina > a->max_autonomia){
                    a->max_autonomia=macchina;
                }
            }
            printf("aggiunta\n");
            return;
        }

        if(km < a->km){
            a=a->left;
        }
        else{
            a=a->right;
        }
    }

    printf("non aggiunta\n");
    return; 
}

//demolisci_auto  ##DONE
void rottama_auto(p_node a,int km){
    while(a!=NULL){
        if(a->km == km){
            int macchina,trovato=0,i=0;

            if(scanf("%d", &macchina)!=EOF){
                while(i<512 && trovato==0){
                    if(macchina == a->autonomia[i]){
                    trovato=1;
                    a->autonomia[i]=-1;
                    if(macchina == a->max_autonomia){
                        a->max_autonomia=0;
                        for (int k=0;k<512;k++){
                            if(a->max_autonomia < a->autonomia[k]){
                                a->max_autonomia=a->autonomia[k];
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
            return;
        }

        if(km < a->km){
            a=a->left;
        }
        else{
            a=a->right;
        }
    }

    printf("non rottamata\n");
    return; 
}

//pianifica_percorso ##DONE
void pianifica_percorso(p_node a,int inizio_percorso,int fine_percorso){
    if(inizio_percorso == fine_percorso){
        printf("%d\n",inizio_percorso);
        return ;
    }

    while(a->km!=inizio_percorso){
        if(inizio_percorso < a->km){
            a=a->left;
        }
        else{
            a=a->right;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    if(inizio_percorso<fine_percorso){

    p_percorso inizio;
    p_percorso index,new;

    inizio=(p_percorso)malloc(sizeof(percorso));
    inizio->km=a->km;
    inizio->max_autonomia=a->max_autonomia;
    inizio->prox=NULL;
    inizio->tappa=NULL;
    index=inizio;

    while(a->km!=fine_percorso){
        a=tree_succ(a);
        new=(p_percorso)malloc(sizeof(percorso));
        new->km=a->km;
        new->max_autonomia=a->max_autonomia;
        new->prox=NULL;
        new->tappa=NULL;
        index->prox=new;
        index=index->prox;
    }

    int uscita=0;
    while(inizio->km !=fine_percorso && uscita==0){
        index=inizio->prox;

        if(inizio->tappa!=NULL || inizio->km==inizio_percorso){
            while(index!=NULL && index->km<fine_percorso+1 && index->km-inizio->km <=inizio->max_autonomia && uscita==0){
                if(index->tappa==NULL){
                    index->tappa=inizio;
                }

                if(index->km==fine_percorso){
                    uscita=1;
                }
                else{
                    index=index->prox;
                }
            }
        }
        inizio=inizio->prox;
    }

    if(index!=NULL && index->tappa==NULL){
        printf("nessun percorso\n");
        return ;
    }

    p_stampa st;
    p_stampa j;

    st=(p_stampa)malloc(sizeof(stampa));
    st->k=index->km;
    st->prossimo=NULL;
    index=index->tappa;

    while(index->km != inizio_percorso){
        j=(p_stampa)malloc(sizeof(stampa));
        j->k=index->km;
        j->prossimo=st;
        st=j;

        index=index->tappa;
    }

    printf("%d ",inizio_percorso);
    while (st !=NULL){
        printf("%d ",st->k);
        st=st->prossimo;
    }
    printf("\n");

    return;
    }

    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    p_percorso inizio;
    p_percorso index,new;

    inizio=(p_percorso)malloc(sizeof(percorso));
    inizio->km=a->km;
    inizio->max_autonomia=a->max_autonomia;
    inizio->p=0;
    inizio->prox=NULL;
    inizio->tappa=NULL;
    index=inizio;

    while(a->km!=fine_percorso){
        a=tree_pred(a);
        new=(p_percorso)malloc(sizeof(percorso));
        new->km=a->km;
        new->max_autonomia=a->max_autonomia;
        new->p=-1;
        new->prox=NULL;
        new->tappa=NULL;
        index->prox=new;
        index=index->prox;
    }

    
    while(inizio->km !=fine_percorso ){
        index=inizio->prox;

        /*if(inizio->tappa!=NULL || inizio->km==inizio_percorso){*/
            while(index!=NULL && index->km>fine_percorso-1 && inizio->km-index->km <=inizio->max_autonomia ){
                if(index->p!=inizio->p){
                    index->tappa=inizio;
                    index->p=inizio->p+1;
                }

                index=index->prox;
            }
        //}
        inizio=inizio->prox;
    }

    index=inizio;
    if(index!=NULL && index->tappa==NULL){
        printf("nessun percorso\n");
        return ;
    }

    p_stampa st;
    p_stampa j;

    st=(p_stampa)malloc(sizeof(stampa));
    st->k=index->km;
    st->prossimo=NULL;
    index=index->tappa;

    while(index->km != inizio_percorso){
        j=(p_stampa)malloc(sizeof(stampa));
        j->k=index->km;
        j->prossimo=st;
        st=j;

        index=index->tappa;
    }

    printf("%d ",inizio_percorso);
    while (st !=NULL){
        printf("%d ",st->k);
        st=st->prossimo;
    }
    printf("\n");

    return;
}

//di aiuto debug  ##DONE
void stampa_autostrada(p_node a){
    if(a!=NULL){
        stampa_autostrada(a->left);
        printf("\nkm: %d ma: %d  ",a->km,a->max_autonomia);
        stampa_autostrada(a->right);
    }
}

//main ##DONE
int main(){
    char lettura[20];
    p_node Troot;
    int km,inizio,fine;

    Troot=NULL;

    while(scanf("%s",lettura) != EOF){
        if(lettura[0]=='p'){                                                    //pianifica_percorso
            if(scanf("%d", &inizio)!=EOF && scanf("%d", &fine)!=EOF){
                pianifica_percorso(Troot,inizio,fine);
            }                                                      
        } 

        else if(lettura[0]=='a' && lettura[9]=='s'){                             //aggiungi_stazione
            if(scanf("%d", &km)!=EOF){
                Troot=aggiungi_stazione(Troot,km);
            }  
        }

        else if(lettura[0]=='a' && lettura[9]=='a'){                             //aggiungi_auto
            if(scanf("%d", &km)!=EOF){
                aggiungi_auto(Troot,km);
            }
        }

        else if(lettura[0]=='d'){                                                //demolisci_stazione
            if(scanf("%d", &km)!=EOF){
                Troot=demolisci_stazione(Troot,km);
            }
        }

        else if(lettura[0]=='r'){                                                //demolisci_auto
            if(scanf("%d", &km)!=EOF){
                rottama_auto(Troot,km);
            }
        }
    }
    
    return 0;
}
