#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int n=0;
typedef struct Etudiant
{
    char nom[100];
    float *note;
    float moy;
    int ind;
}Etudiant;
typedef struct Noeud{
    Etudiant *data;
    struct Noeud *suivant;
}Noeud;
typedef struct BaseEtudiants{
    Noeud *tete;
    int taille;
}BaseEtudiants;
BaseEtudiants *initBase(BaseEtudiants *ptr)
{
    ptr=(BaseEtudiants*)malloc(sizeof(BaseEtudiants));
    if(ptr==NULL){
        printf("Erreur d'allocation de la base de donnees d'etudiants\n");
        exit(1);
    }
    ptr->tete=NULL;
    ptr->taille=0;
    return ptr;
}
Noeud *creerNoeud(BaseEtudiants *ptr)
{
    if(ptr==NULL){
        printf("Base de donnees introuvable\n");
        return NULL;
    }
    Noeud *unit=(Noeud*)malloc(sizeof(Noeud));
    if(unit==NULL){
        printf("Erreur d'allocation memoire au noeud\n");
        return NULL;
    }
    unit->data=NULL;
    unit->suivant=NULL;
    return unit;
}
int EstEntier(char *x)
{
    if(strlen(x)==0){return 0;};
    for(int i=0;i<strlen(x);i++)
    {
        if(x[i]=='\n'){continue;};
        if(!isdigit(x[i])){return 0;};
    }
    return 1;
}
Etudiant *creerEtudiant(BaseEtudiants *ptr)
{
    if(ptr==NULL){
        printf("Base de donnees vide \n");
        printf("Impossible de creer l'etudiant\n");
        return NULL;
    }else
    {
        if(ptr->tete==NULL){
            printf("Abscence de noeud de stockage\n");
            printf("Impossible de creer un etudiant\n");
            return NULL;
        }
    }
    Etudiant *V=(Etudiant*)malloc(sizeof(Etudiant));
    char temp[100];
    int i;
    float sum=0;
    if(V==NULL){
        printf("Erreur d'allocation memoire a l'etudiant\n");
        free(V);
        return NULL;
    }
    V->note=(float*)malloc(n*sizeof(float));
    if(V->note==NULL){
        printf("Erreur d'allocation memoire pour les notes de l'etudiant\n");
        free(V);
        return NULL;
    }
    printf("Entrez le nom de l'etudiant: \n");
    fflush(stdin);
    if(fgets(V->nom,sizeof(V->nom),stdin)!=NULL){
        V->nom[strcspn(V->nom,"\n")]='\0';
    }
    do{
        printf("Entrez le matricule de l'etudiant: \n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Entrez uniquement un nombre ici: \n");
        }
    }while(!EstEntier(temp));
    V->ind=atoi(temp);
    if(n==0){
        printf("Le nombre de note n'a pas ete initialise\n");
        return V;
    }else
    {
        for(i=0;i<n;i++)
        {
            printf("Entrez la %d e note de l'etudiant: \n",i+1);
            if(scanf("%f",&V->note[i])!=1){
                while(getchar()!='\n');
                i--;
                continue;
            }
            if(V->note[i]<0 || V->note[i]>20){i--;};
            sum+=V->note[i];
        }
        V->moy = sum / n;
    }
    return V;
}
void afficherEtudiant(Etudiant *e)
{
    if(e==NULL){
        printf("Etudiant invalide\n");
        return;
    }
    printf("Nom: %s\n",e->nom);
    printf("ID: %d\n",e->ind);
    if(n==0){
        printf("Les notes n'ont pas ete initialise\n");
        printf("Moyenne non disponible\n");
        return;
    }
    printf("Les notes de l'etudiant sont: \n");
    for(int i=0;i<n;i++)
    {
        printf("Note %d: %.3f\n",i+1,e->note[i]);
    }
    printf("Moyenne: %.3f\n",e->moy);
}
void afficher(BaseEtudiants *ptr)
{
    if(ptr==NULL){
        printf("La base de donnee est vide\n");
        return;
    }else
    {
        if(ptr->tete==NULL){
            printf("La liste d'etudiants est vide\n");
            return;
        }
    }
    int i;
    Noeud *nav=ptr->tete;
    while(nav!=NULL){
        afficherEtudiant(nav->data);
        nav=nav->suivant;
    }
    printf("\n");
}
int recherche(BaseEtudiants *ptr, int valeur)
{
    if(ptr==NULL){
        printf("Base de donnees introuvable\n");
        return -1;
    }else
    {
        if(ptr->tete==NULL){
            printf("Base de donnees vide\n");
            return -1;
        }
    }
    Noeud *nav=ptr->tete;
    while(nav!=NULL)
    {
        if(nav->data->ind==valeur){
            return 1;
        }
        nav=nav->suivant;
    }
    return -1;
}
void InsererEnTete(BaseEtudiants **ptr)
{
    if(*ptr==NULL){
        printf("Base de donnees introuvable\n");
        return;
    }
    Noeud *nouveau=creerNoeud(*ptr);
    nouveau->data=creerEtudiant(*ptr);
    if(nouveau->data==NULL){
        free(nouveau);
        return;
    }
    nouveau->suivant=(*ptr)->tete;
    (*ptr)->tete=nouveau;
    (*ptr)->taille++;
}
void InsererEnQueue(BaseEtudiants **ptr)
{
    if(*ptr==NULL){
        printf("Base de donnees introuvable\n");
        return;
    }
    Noeud *nouveau=creerNoeud(*ptr);
    nouveau->data=creerEtudiant(*ptr);
    if(nouveau->data==NULL){
        free(nouveau);
        return;
    }
    if((*ptr)->tete==NULL){
        (*ptr)->tete=nouveau;
    }else
    {
        Noeud *temp= (*ptr)->tete;
        while(temp->suivant!=NULL){
            temp=temp->suivant;
        }
        temp->suivant=nouveau;
    }
    (*ptr)->taille++;
}
int supprimer(BaseEtudiants **ptr,int valeur)
{
    if(*ptr==NULL){
        printf("Base de donnees introuvable\n");
        return 0;
    }else
    {
        if((*ptr)->tete==NULL){
            printf("La base de donnees est vide\n");
            return 0;
        }
    }
    Noeud *courant= (*ptr)->tete;
    Noeud *precedent= NULL;
    while(courant!=NULL){
        if(courant->data->ind==valeur){
            if(precedent==NULL){
                (*ptr)->tete=courant->suivant;
            } else {
                precedent->suivant=courant->suivant;
            }
            free(courant->data->note);
            free(courant->data);
            free(courant);
            (*ptr)->taille--;
            return 1;
        }
        precedent=courant;
        courant=courant->suivant;
    }
    return 0;
}
void LibererBase(BaseEtudiants **ptr)
{
    Noeud *temp= (*ptr)->tete;
    while(temp!=NULL){
        Noeud *unit=temp->suivant;
        free(temp->data->note);
        free(temp->data);
        free(temp);
        temp=unit;
    }
    free(*ptr);
}
void Interface(BaseEtudiants **ptr)
{
    int choix;
    char temp[100];
    printf("1. Ajouter un etudiant en tete\n");
    printf("2. Ajouter un etudiant en fin\n");
    printf("3. Rechercher un etudiant\n");
    printf("4. Afficher tous les etudiants\n");
    printf("5. Afficher les etudiants ayant une moyenne superieur ou egale a 10\n");
    printf("6. Afficher les etudiants ayant une moyenne inferieur a 10\n");
    printf("7. Supprimer un etudiant\n");
    printf("8. Quitter\n");
    do{
        printf("Entrez votre choix: ");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Entrez uniquement un nombre ici: \n");
        }
    }while(!EstEntier(temp));
    choix=atoi(temp);
    switch(choix)
    {
    case 1:
        do{
            printf("Combien d'etudiants voulez-vous ajouter en tete? ");
            fgets(temp,sizeof(temp),stdin);
            if(!EstEntier(temp)){
                printf("Attention!!! Entrez uniquement un nombre ici: \n");
            }
        }while(!EstEntier(temp));
        int x=atoi(temp);
        for(int i=0;i<x;i++)
        {
            InsererEnTete(ptr);
        }
        break;
    case 2:
        do{
            printf("Combien d'etudiants voulez-vous ajouter en fin? ");
            fgets(temp,sizeof(temp),stdin);
            if(!EstEntier(temp)){
                printf("Attention!!! Entrez uniquement un nombre ici: \n");
            }
        }while(!EstEntier(temp));
        int y=atoi(temp);
        for(int i=0;i<y;i++)
        {
            InsererEnQueue(ptr);
        }
        break;
    case 3:
        do{
            printf("Entrez le matricule de l'etudiant a rechercher: ");
            fgets(temp,sizeof(temp),stdin);
            if(!EstEntier(temp)){
                printf("Attention!!! Entrez uniquement un nombre ici: \n");
            }
        }while(!EstEntier(temp));
        recherche((*ptr), atoi(temp));
        break;
    case 4:
        afficher(*ptr);
        break;
    case 5:
        printf("Les etudiants ayant une moyenne superieur ou egale a 10 sont: \n");
        Noeud *nav= (*ptr)->tete;
        while(nav!=NULL){
            if(nav->data->moy>=10){
                afficherEtudiant(nav->data);
            }
            nav=nav->suivant;
        }
        break;
    case 6:
        printf("Les etudiants ayant une moyenne inferieur a 10 sont: \n");
        Noeud *nav2= (*ptr)->tete;
        while (nav2!=NULL)
        {
            if(nav2->data->moy<10){
                afficherEtudiant(nav2->data);
            }
            nav2=nav2->suivant;
        }
        break;
    case 7:
        do{
            printf("Combien d'etudiants voulez-vous supprimer? ");
            fgets(temp,sizeof(temp),stdin);
            if(!EstEntier(temp)){
                printf("Attention!!! Entrez uniquement un nombre ici: \n");
            }
        }while(!EstEntier(temp));
        x=atoi(temp);
        for(int i=0;i<x;i++)
        {
            char temp3[100];
            do{
                printf("Entrez le matricule de l'etudiant a supprimer: ");
                fgets(temp3,sizeof(temp3),stdin);
                if(!EstEntier(temp3)){
                    printf("Attention!!! Entrez uniquement un nombre ici: \n");
                }
            }while(!EstEntier(temp3));
            if(supprimer(ptr, atoi(temp3))){
                printf("Etudiant supprime avec succes\n");
            }else{
                printf("Etudiant non trouve\n");
                i--;
            }
        }
        break;
    case 8:
        LibererBase(ptr);
        printf("Au revoir!\n");
        break;
    default:
        printf("Choix invalide\n");
        break;
    }while(choix!=8);
}
int main()
{
    char temp[100];
    BaseEtudiants *base = initBase(base);
    if(base==NULL){
        printf("Erreur d'allocation de la base de donnees d'etudiants\n");
        return 1;
    }
    do{
        printf("Entrez le nombre de notes par etudiants:\n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("ATTENTION CECI N'EST PAS UN ENTIER!!!\n");
        }
    }while(!EstEntier(temp));
    n=atoi(temp);
    if(n<=0){
        printf("Le nombre de notes doit etre supperieur a 0\n");
        return 1;
    }
    Interface(&base);
    return 0;
}
