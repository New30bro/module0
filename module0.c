#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int n=0;
int h=0;
typedef struct 
{
    char nom[50];
    float *note;
    float moy;
    int ind;
}Etudiant;
Etudiant *Tab;
int EstEntier(char *x) // Cette function vérifie si la chaîne de caractères x représente un entier valid
{
    if(strlen(x)==0){return 0;};
    for(int i=0;i<strlen(x);i++)
    {
        if(x[i]=='\n'){continue;};
        if(!isdigit(x[i])){return 0;};
    }
    return 1;
}
Etudiant Ajout() // Cette function permet d'ajouter un étudiant
{
    Etudiant V;
    char temp[20];
    int i;
    float sum=0;
    printf("Entrez le nom de l'etudiant: \n");
    // La function fflush est utilisée pour vider le tampon d'entrée standard (stdin) avant de lire le nom de l'étudiant. Cela permet d'éviter que des caractères résiduels dans le tampon n'affectent la lecture du nom.
    fflush(stdin);
    // La function fgets est utilisée pour lire une ligne de texte depuis l'entrée standard (stdin) et la stocker dans le champ nom de la structure Etudiant V.
    if(fgets(V.nom,sizeof(V.nom),stdin)!=NULL){ 
        V.nom[strcspn(V.nom,"\n")]='\0';
    };
    // La boucle do-while est utilisée pour demander à l'utilisateur d'entrer le matricule de l'étudiant jusqu'à ce qu'un entier valid soit saisi. La function EstEntier est appelée pour vérifier si la chaîne de caractères temp représente un entier valid. Si ce n'est pas le cas, un message d'avertissement est affiché et l'utilisateur est invité à saisir à nouveau le matricule.
    do{
        printf("Entrez le matricule de l'etudiant: \n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Ceci n'est pas un entier \n");
        };
    }while(!EstEntier(temp)); // La function atoi est utilisée pour convertir la chaîne de caractères temp en un entier, qui est ensuite assigné au champ ind de la structure Etudiant V.
    V.ind=atoi(temp);
    V.note=(float*)malloc(n*sizeof(float));
    for(i=0;i<n;i++)
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
    V.moy = sum / n;
    return V;
}
// La function afficher prend en paramètre une structure Etudiant V et affiche les informations de l'étudiant, y compris son nom, son matricule, ses notes et sa moyenne. La boucle for est utilisée pour parcourir les notes de l'étudiant et les afficher une par une.
void afficher(Etudiant V)
{
    int i;
    printf("Le nom de l'etudiant : %s\n",V.nom);
    printf("L'indentifiant de l'etudiant : %d\n",V.ind);
    printf("Les notes de l'etudiant sont : \n");
    for(i=0;i<n;i++)
    {
        printf("%.3f\n",V.note[i]);
    };
    printf("La moyenne de l'etudiant est : %.3f\n",V.moy);
}
// La function recherche prend en paramètre un tableau de structures Etudiant t et un entier x représentant le matricule de l'étudiant à rechercher. La fonction parcourt le tableau t à l'aide d'une boucle for et compare le matricule de chaque étudiant avec x. Si une correspondance est trouvée, l'indice de l'étudiant dans le tableau est retourné. Si aucune correspondance n'est trouvée après avoir parcouru tout le tableau, la fonction retourne -1 pour indiquer que l'étudiant n'a pas été trouvé.
int recherche(Etudiant *t, int x)
{
    int i;
    for(i=0;i<h;i++)
    {
        if(x==t[i].ind){
            return i;
        }else
        {
            return -1;
        };
    };
}
Etudiant Supprimer(Etudiant *t, int x) // La function Supprimer prend en paramètre un tableau de structures Etudiant t et un entier x représentant le matricule de l'étudiant à supprimer. La fonction utilise la function recherche pour trouver l'indice de l'étudiant dans le tableau. Si l'étudiant est trouvé, la mémoire allouée pour les notes de cet étudiant est libérée à l'aide de la function free, puis le tableau t est redimensionné à l'aide de la function realloc pour supprimer l'étudiant du tableau. Enfin, la variable h, qui représente le nombre d'étudiants dans le tableau, est décrémentée de 1.
{
    free(t[recherche(t,x)].note);
    t=(Etudiant*)realloc(t,(h-1)*sizeof(Etudiant));
    h--;
    return t;
}
Etudiant Modifier(Etudiant *t, int x) // La function Modifier prend en paramètre un tableau de structures Etudiant t et un entier x représentant le matricule de l'étudiant à modifier. La fonction utilise la function recherche pour trouver l'indice de l'étudiant dans le tableau. Si l'étudiant est trouvé, la function Ajout est appelée pour permettre à l'utilisateur de saisir les nouvelles informations de l'étudiant, qui sont ensuite assignées à la position correspondante dans le tableau t.
{
    t[recherche(t,x)]=Ajout();
    return t;
}
Etudiant nouveau(Etudiant *t, int x) // La function nouveau prend en paramètre un tableau de structures Etudiant t et un entier x représentant le matricule de l'étudiant à ajouter. La fonction utilise la function Ajout pour permettre à l'utilisateur de saisir les informations du nouvel étudiant, qui sont ensuite assignées à la position correspondante dans le tableau t.
{
    char temp[20];
    int c;
    do{
        printf("Combien d'etudiants voulez vous ajouter? : \n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Ceci n'est pas un entier \n");
        };
    }while(!EstEntier(temp));
    c=atoi(temp);
    t=(Etudiant*)realloc(t,(h+c)*sizeof(Etudiant));
    for(int i=h;i<h+c;i++)
    {
        t[i]=Ajout();
    };
    h+=c;
    return t;
}
int main()
{
    char temp[20];
    do{
        printf("Entrez le nombre d'etudiants: \n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Ceci n'est pas un entier \n");
        };
    }while(!EstEntier(temp));
    h=atoi(temp);
    do{
        printf("Entrez le nombre de matieres: \n");
        fgets(temp,sizeof(temp),stdin);
        if(!EstEntier(temp)){
            printf("Attention!!! Ceci n'est pas un entier \n");
        };
    }while(!EstEntier(temp));
    n=atoi(temp);
    Tab=(Etudiant*)malloc(h*sizeof(Etudiant));
    for(int i=0;i<h;i++)
    {
        Tab[i]=Ajout();
        afficher(Tab[i]);
    };
    return 0;
}
