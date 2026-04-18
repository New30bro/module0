#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define H 100
#define N 12
typedef struct
{
    char nom[50];
    float note[N];
    float moy;
    int ind;
}Etudiant;
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
Etudiant Ajout()
{
    Etudiant V;
    char temp[20];
    int i;
    float sum=0;
    printf("Entrez le nom de l'etudiant: \n");
    fflush(stdin);
    if(fgets(V.nom,sizeof(V.nom),stdin)!=NULL){
        V.nom[strcspn(V.nom,"\n")]='\0';
    };
    do{
        printf("Entrez le matricule de l'etudiant: \n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Entrez uniquement un nombre ici: \n");
        };
    }while(!EstEntier(temp));
    V.ind=atoi(temp);
    for(i=0;i<N;i++)
    {
        printf("Entrez la %d e note de l'etudiant: \n",i+1);
        if(scanf("%f",&V.note[i])!=1){
            while(getchar()!='\n');
            i--;
            continue;
        };
        if(V.note[i]<0 || V.note[i]>20){i--;};
        sum+=V.note[i];
    };
    V.moy = sum / N;
    return V;
}
void afficher(Etudiant V)
{
    int i;
    printf("Le nom de l'etudiant : %s\n",V.nom);
    printf("L'indentifiant de l'etudiant : %d\n",V.ind);
    printf("Les notes de l'etudiant sont : \n");
    for(i=0;i<N;i++)
    {
        printf("%.3f\n",V.note[i]);
    };
    printf("La moyenne de l'etudiant est : %.3f\n",V.moy);
}
int recherche(Etudiant T[H], int x)
{
    int i;
    for(i=0;i<H;i++)
    {
        if(x==T[i].ind){
            return i;
        }else
        {
            return -1;
        };
    };
}
int main()
{
    Etudiant E1,tab[H];
    int i;
    for(i=0;i<H;i++)
    {
        tab[i]=Ajout();
        afficher(tab[i]);
    };
    return 0;
}
