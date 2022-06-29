#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef void Object;

//structure d'une file
//typedef struct Cellule* PCellule;
typedef struct CelluleDbl* PCelluleDbl;

typedef struct CelluleDbl{
    Object* valeur;
    PCelluleDbl suivant;
    PCelluleDbl precedent;
} ListeDbl;

//Créer une liste doublée
void creerListeDbl(PCelluleDbl l, int n){
    PCelluleDbl tete;
    PCelluleDbl p;
    int donnee;
    //tete = malloc(sizeof(PCellule));
    printf("Entrez le premier élément : ");
    scanf("%d", &donnee);
    tete = l;
    tete->valeur = donnee;
    tete->suivant = NULL;
    tete->precedent = NULL;
    //l = tete;
    for(int i=2;i<=n;i++){
        p = malloc(sizeof(PCelluleDbl));
        printf("Entrez élément suivant : ");
        scanf("%d", &donnee);
        p->valeur = donnee;
        p->suivant = NULL;
        p->precedent = tete;
        tete->suivant = p;
        tete = p;
    }
}

//afficher une liste
void afficherListe(PCelluleDbl l){
    PCelluleDbl p;
    p = l;
    while(p!=NULL){
        printf("%d ",p->valeur);
        p = p->suivant;
    }
    printf("\n");
}

//afiicher listeDbl Inversé
void afficherListeDblInverse(PCelluleDbl l){
    PCelluleDbl p;
    p = l;
    while(p->suivant != NULL){
        p =p->suivant;
    }

    while(p!=NULL){
        printf("%d ", p->valeur);
        p = p->precedent;
    }
}

//ajouter tete
PCelluleDbl ajouterTeteDbl(PCelluleDbl l, Object* donnee){
    PCelluleDbl tete;
    tete = malloc(sizeof(PCelluleDbl));
    tete->valeur = donnee;
    tete->suivant = l;
    tete->precedent = NULL;
    l->precedent = tete;
    return tete;
}

//Ajouter que
void ajouterQueueDbl(PCelluleDbl l, Object *donnee) {
    PCelluleDbl que, p = l;
    que = malloc(sizeof(PCelluleDbl));
    que->valeur = donnee;
    que -> suivant = NULL;
    if(p!=NULL)
       while(p->suivant != NULL){
        p = p->suivant;
       }
    p->suivant = que;
    que->precedent = p;
}

//triBulles
void triBulleDbl(PCelluleDbl l){
    int permut;
    PCelluleDbl p,q;
    Object* temp;
    do{
        p = l;
        permut = 0;
        while(p != NULL){
            q = p->suivant;
            while(q != NULL){
                if(p->valeur > q->valeur){
                    permut = 1;
                    temp = p->valeur;
                    p->valeur = q->valeur;
                    q->valeur = temp;
                }
                q = q->suivant;
            }
            p = p->suivant;
        }
    }while(permut == 1);
}

PCelluleDbl supprimerListeDbl(PCelluleDbl l, Object* donnee){
    PCelluleDbl p=NULL, preced=NULL;
    if(l->valeur == donnee){
        p=l;
        l=l->suivant;
        if(l!=NULL){l->precedent = NULL;}
        free(p);
        return l;
    }else{
        if(rechercherListeDbl(l,donnee,&p)){
            preced = p->precedent;
            preced->suivant=p->suivant;
            if(p->suivant != NULL){
                p->suivant->precedent = preced;
            }
            free(p);
        }
        return l;
    }
}

PCelluleDbl supprimerDoublonDbl(PCelluleDbl l){
    PCelluleDbl p,q;
    if(l!=NULL){
        p=l;
        while(p->suivant != NULL){
            q = p->suivant;
            while(p->valeur == q->valeur){
                p->suivant = q->suivant;
                if(q->suivant != NULL) q->suivant->precedent = p;
                free(q);
                q = p->suivant;
                if(q == NULL) return l;
            }
            p = p->suivant;
        }
    }
    return l;
}


int rechercherListeDbl(PCelluleDbl l, int valeurRecherche, PCelluleDbl *addrRecherche ){

    PCelluleDbl p;
    int trouver = 0;
    p = l;
    //preced = NULL

    while(trouver == 0 && p != NULL){

        if(p->valeur==valeurRecherche){
            trouver=1;
            *addrRecherche = p;
        }
        p = p->suivant;
    }
    return trouver;
}

int nombreElmDbl(PCelluleDbl l, PCelluleDbl *d){
    int nbr = 1;
    while(l->suivant != NULL){
        nbr++;
        l = l->suivant;
    }
    *d = l;
    return nbr;
}

//Vérifier palyndrome
int palyndromeDbl(PCelluleDbl l){
    PCelluleDbl p, premier = l, dernier;
    int i, valeurParcours = nombreElmDbl(l, &dernier) / 2;
    for(i=1; i <= valeurParcours; i++){
        if(premier->valeur != dernier->valeur) return 0;
        premier = premier->suivant;
        dernier = dernier->precedent;
    }
    return 1;
}

//fusion
PCelluleDbl fusionListeDbl(PCelluleDbl p1, PCelluleDbl p2){
    PCelluleDbl p = p1;
    if(p!=NULL)
       while(p->suivant != NULL){
        p = p->suivant;
       }
    p->suivant = p2;
    p2->precedent = p;
}




int main()
{
    int choix;
    PCelluleDbl maListeDbl, maListeDbl2;
    PCelluleDbl p = malloc(sizeof(PCelluleDbl));
    Object* element;
    maListeDbl = malloc(sizeof(PCelluleDbl));
    maListeDbl2 = malloc(sizeof(PCelluleDbl));

    do{
        printf("\n --------------------------------------------------------");
        printf("\n MENU des operations");
        printf("\n--------------------------------------------------------");
        printf("\n OPERATIONS : ");
        printf("\n 1-Créer une liste chainee d'entier");
        printf("\n 2-Ajouter un element en tete de liste");
        printf("\n 3-Ajouter un element en queue de liste");
        printf("\n 4-Trier une liste");
        printf("\n 5-Supprimer un element donne de la liste");
        printf("\n 6-Supprimer les doublons de la liste");
        printf("\n 7-Rechercher un element dans la liste");
        printf("\n 8-Fusionner deux listes");
        printf("\n 9-Inverser une liste");
        printf("\n 10-Verifier si une liste est un palyndrome");
        printf("\n 11-Quitter");
        printf("\n Quelle opération voulez vous effectuer :");
        scanf("%d",&choix);
        printf("............. %d", &maListeDbl->valeur);

        switch(choix){
        case 1:
            printf("Entrez le nombre d'element de votre liste : ");
            int nbr;
            scanf("%d", &nbr);
            creerListeDbl(maListeDbl,nbr);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 2:
            printf("Entrez l'element a ajouter en tete de la liste: ");
            scanf("%d", &element);
            ajouterTeteDbl(maListeDbl,element);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 3:
            printf("Entrez l'element a ajouter a la queue de la liste: ");
            scanf("%d", &element);
            ajouterQueueDbl(maListeDbl,element);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 4:
            triBulleDbl(maListeDbl);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 5:
            printf("Entrez l'element a supprimer de la liste: ");
            scanf("%d", &element);
            supprimerListeDbl(maListeDbl, element);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 6:
            supprimerDoublonDbl(maListeDbl);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 7:
            printf("Entrez l'element que vous voulez rechercher dans la liste : ");
            scanf("%d", &element);
            if(rechercherListeDbl(maListeDbl, element, &p)==1){
                printf("Cet element est bien dans la liste");
            }else{
                printf("Cet element n'existe pas dans la liste");
            }
            break;
        case 8:
            printf("Entrez le nombre d'element de votre liste : ");
            int nbr2;
            scanf("%d", &nbr2);
            creerListeDbl(maListeDbl2,nbr2);
            fusionListeDbl(maListeDbl, maListeDbl2);
            afficherListe(maListeDbl);
            afficherListeDblInverse(maListeDbl);
            break;
        case 9:
            afficherListeDblInverse(maListeDbl);
            break;
        case 10:
            if(palyndromeDbl(maListeDbl)==1){
                printf("Cette liste est un palyndrome");
            }else{
                printf("Cette liste n'est pas un palyndrome");
            }
            break;
        default:
            printf("Veuillez entrer un numéro de choix valide \n");
        }
    }while(choix!=11);

    return 0;
}
