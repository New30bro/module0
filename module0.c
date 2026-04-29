#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int n = 0;

typedef struct {
    char nom[50];
    float *note;
    float moy;
    int ind;
} Etudiant;

typedef struct {
    Etudiant *data;
    int taille;
    int capacite;
} BaseEtudiants;

void creerBase(BaseEtudiants **ptr, int capaciteInitiale)
{
    *ptr = malloc(sizeof(BaseEtudiants));
    if (*ptr == NULL) {
        printf("Erreur d'allocation sur la base de donnees\n");
        exit(1);
    }
    (*ptr)->data = malloc(capaciteInitiale * sizeof(Etudiant));
    if ((*ptr)->data == NULL) {
        printf("Erreur d'allocation sur la liste d'etudiants\n");
        free(*ptr);
        exit(1);
    }
    (*ptr)->taille = 0;
    (*ptr)->capacite = capaciteInitiale;
}

int EstEntier(const char *x)
{
    if (x == NULL) {
        return 0;
    }
    size_t len = strlen(x);
    if (len == 0) {
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        if (x[i] == '\n' || x[i] == '\r') {
            continue;
        }
        if (!isdigit((unsigned char)x[i])) {
            return 0;
        }
    }
    return 1;
}

void AjouterEtudiant(BaseEtudiants *ptr)
{
    if (ptr == NULL || ptr->data == NULL) {
        printf("La base de donnees n'est pas initialisee.\n");
        return;
    }
    if (n <= 0) {
        printf("Le nombre de notes n'a pas ete defini.\n");
        return;
    }

    if (ptr->capacite == ptr->taille) {
        int nouvelleCap = ptr->capacite * 2;
        if (nouvelleCap == 0) {
            nouvelleCap = 2;
        }
        Etudiant *temp = realloc(ptr->data, nouvelleCap * sizeof(Etudiant));
        if (temp == NULL) {
            printf("Le realloc de la liste d'etudiants a echoue\n");
            exit(1);
        }
        ptr->data = temp;
        ptr->capacite = nouvelleCap;
    }

    int index = ptr->taille;
    float *notes = malloc(n * sizeof(float));
    if (notes == NULL) {
        printf("Erreur d'allocation pour les notes\n");
        exit(1);
    }

    char temp[20];
    printf("Entrez le nom de l'etudiant: \n");
    while (getchar() != '\n');
    if (fgets(ptr->data[index].nom, sizeof(ptr->data[index].nom), stdin) != NULL) {
        ptr->data[index].nom[strcspn(ptr->data[index].nom, "\r\n")] = '\0';
    }

    do {
        printf("Entrez le matricule de l'etudiant: \n");
        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            continue;
        }
        if (!EstEntier(temp)) {
            printf("Attention!!! Ceci n'est pas un entier \n");
        }
    } while (!EstEntier(temp));
    ptr->data[index].ind = atoi(temp);

    for (int i = 0; i < n; i++) {
        do {
            printf("Entrez la %d e note de l'etudiant: \n", i + 1);
            if (scanf("%f", &notes[i]) != 1) {
                printf("Valeur non valide. Recommencez.\n");
                while (getchar() != '\n');
                continue;
            }
            if (notes[i] < 0.0f || notes[i] > 20.0f) {
                printf("La note doit etre entre 0 et 20.\n");
                continue;
            }
            break;
        } while (1);
    }
    while (getchar() != '\n');

    ptr->data[index].note = notes;
    ptr->data[index].moy = 0.0f;
    for (int i = 0; i < n; i++) {
        ptr->data[index].moy += notes[i];
    }
    ptr->data[index].moy /= n;
    ptr->taille++;
}

void afficher(const Etudiant *data)
{
    if (data == NULL) {
        return;
    }
    printf("Le nom de l'etudiant : %s\n", data->nom);
    printf("L'identifiant de l'etudiant : %d\n", data->ind);
    printf("Les notes de l'etudiant sont : \n");
    for (int i = 0; i < n; i++) {
        printf("%.2f\n", data->note[i]);
    }
    printf("La moyenne de l'etudiant est : %.2f\n", data->moy);
}

int recherche(const BaseEtudiants *ptr, int x)
{
    if (ptr == NULL || ptr->data == NULL) {
        return -1;
    }
    for (int i = 0; i < ptr->taille; i++) {
        if (ptr->data[i].ind == x) {
            return i;
        }
    }
    return -1;
}

void Supprimer(BaseEtudiants *ptr, int x)
{
    if (ptr == NULL || ptr->data == NULL) {
        printf("Aucun etudiant n'existe\n");
        return;
    }
    int y = recherche(ptr, x);
    if (y == -1) {
        printf("Cet etudiant n'existe pas \n");
        return;
    }
    free(ptr->data[y].note);
    for (int i = y; i < ptr->taille - 1; i++) {
        ptr->data[i] = ptr->data[i + 1];
    }
    ptr->taille--;
}

void Modifier(BaseEtudiants *ptr, int x)
{
    if (ptr == NULL || ptr->data == NULL) {
        printf("Aucun etudiant n'existe \n");
        return;
    }
    int y = recherche(ptr, x);
    if (y == -1) {
        printf("Cet etudiant n'existe pas \n");
        return;
    }

    char temp[20];
    int choix;

    do {
        printf("Que voulez-vous modifier ?\n");
        printf("1- Nom\n");
        printf("2- Matricule\n");
        printf("3- Notes\n");
        printf("4- Tout\n");
        printf("Entrez votre choix : \n");
        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            continue;
        }
        if (!EstEntier(temp)) {
            printf("Choix invalide. Entrez 1, 2, 3 ou 4.\n");
            continue;
        }
        choix = atoi(temp);
    } while (choix < 1 || choix > 4);

    if (choix == 1 || choix == 4) {
        printf("Entrez le nouveau nom de l'etudiant: \n");
        if (fgets(ptr->data[y].nom, sizeof(ptr->data[y].nom), stdin) != NULL) {
            ptr->data[y].nom[strcspn(ptr->data[y].nom, "\r\n")] = '\0';
        }
    }

    if (choix == 2 || choix == 4) {
        do {
            printf("Entrez le nouveau matricule de l\'etudiant: \n");
            if (fgets(temp, sizeof(temp), stdin) == NULL) {
                continue;
            }
            if (!EstEntier(temp)) {
                printf("Attention!!! Ceci n\'est pas un entier \n");
            }
        } while (!EstEntier(temp));
        ptr->data[y].ind = atoi(temp);
    }

    if (choix == 3 || choix == 4) {
        float *notes = malloc(n * sizeof(float));
        if (notes == NULL) {
            printf("Erreur d\'allocation pour les notes\n");
            exit(1);
        }

        for (int i = 0; i < n; i++) {
            do {
                printf("Entrez la %d e note de l'etudiant: \n", i + 1);
                if (scanf("%f", &notes[i]) != 1) {
                    printf("Valeur non valide. Recommencez.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (notes[i] < 0.0f || notes[i] > 20.0f) {
                    printf("La note doit etre entre 0 et 20.\n");
                    continue;
                }
                break;
            } while (1);
        }
        while (getchar() != '\n');

        free(ptr->data[y].note);
        ptr->data[y].note = notes;
        ptr->data[y].moy = 0.0f;
        for (int i = 0; i < n; i++) {
            ptr->data[y].moy += notes[i];
        }
        ptr->data[y].moy /= n;
    }
}

void Interface(BaseEtudiants *ptr)
{
    int y;
    char conf, temp[20];
    int rep, choix;

    do {
        printf("Que voulez vous faire? \n");
        printf("-------------------------------------------------- \n");
        printf("1- Ajouter un ou plusieurs etudiants \n");
        printf("2- Verifier qu'un etudiant existe \n");
        printf("3- Modifier un etudiant \n");
        printf("4- Supprimer un etudiant \n");
        printf("5- Afficher un etudiant en particulier \n");
        printf("6- Afficher les etudiants \n");
        printf("7- Afficher les etudiants avec une moyenne superieure a 10 \n");
        printf("8- Afficher les etudiants avec une moyenne inferieure a 10 \n");
        printf("9- Quitter \n");
        printf("-------------------------------------------------- \n");
        printf("Entrez votre choix: \n");
        if (scanf("%d", &choix) != 1) {
            printf("Choix invalide.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                do {
                    printf("Entrez le nombre d'etudiants a ajouter: \n");
                    fgets(temp, sizeof(temp), stdin);
                    if (!EstEntier(temp)) {
                        printf("Attention!!! Ceci n'est pas un entier\n");
                    }
                } while (!EstEntier(temp));
                rep = atoi(temp);
                for (int i = 0; i < rep; i++) {
                    AjouterEtudiant(ptr);
                }
                break;

            case 2:
                do {
                    printf("Entrez le matricule de l'etudiant a verifier: \n");
                    fgets(temp, sizeof(temp), stdin);
                    if (!EstEntier(temp)) {
                        printf("Attention!!! Ceci n'est pas un entier\n");
                    }
                } while (!EstEntier(temp));
                rep = atoi(temp);
                y = recherche(ptr, rep);
                if (y == -1) {
                    printf("Cet etudiant n'existe pas \n");
                } else {
                    printf("Cet etudiant existe \n");
                }
                break;

            case 3:
                do {
                    printf("Entrez le matricule de l'etudiant a modifier: \n");
                    fgets(temp, sizeof(temp), stdin);
                    if (!EstEntier(temp)) {
                        printf("Attention!!! Ceci n'est pas un entier\n");
                    }
                } while (!EstEntier(temp));
                rep = atoi(temp);
                Modifier(ptr, rep);
                break;

            case 4:
                do {
                    printf("Entrez le matricule de l'etudiant a supprimer: \n");
                    fgets(temp, sizeof(temp), stdin);
                    if (!EstEntier(temp)) {
                        printf("Attention!!! Ceci n'est pas un entier\n");
                    }
                } while (!EstEntier(temp));
                rep = atoi(temp);
                Supprimer(ptr, rep);
                break;

            case 5:
                do {
                    printf("Entrez le matricule de l'etudiant a afficher: \n");
                    fgets(temp, sizeof(temp), stdin);
                    if (!EstEntier(temp)) {
                        printf("Attention!!! Ceci n'est pas un entier\n");
                    }
                } while (!EstEntier(temp));
                rep = atoi(temp);
                y = recherche(ptr, rep);
                if (y == -1) {
                    printf("Cet etudiant n'existe pas \n");
                } else {
                    afficher(&ptr->data[y]);
                }
                break;

            case 6:
                if (ptr == NULL || ptr->data == NULL || ptr->taille == 0) {
                    printf("Aucun etudiant a afficher.\n");
                    break;
                }
                for (int j = 0; j < ptr->taille; j++) {
                    afficher(&ptr->data[j]);
                }
                break;

            case 7:
                if (ptr == NULL || ptr->data == NULL || ptr->taille == 0) {
                    printf("Aucun etudiant a afficher.\n");
                    break;
                }
                for (int j = 0; j < ptr->taille; j++) {
                    if (ptr->data[j].moy >= 10.0f) {
                        afficher(&ptr->data[j]);
                    }
                }
                break;

            case 8:
                if (ptr == NULL || ptr->data == NULL || ptr->taille == 0) {
                    printf("Aucun etudiant a afficher.\n");
                    break;
                }
                printf("Les etudiants avec une moyenne inferieure a 10 sont : \n");
                for (int j = 0; j < ptr->taille; j++) {
                    if (ptr->data[j].moy < 10.0f) {
                        afficher(&ptr->data[j]);
                    }
                }
                break;

            case 9:
                printf("Voulez vous vraiment quitter? (O/N) \n");
                scanf(" %c", &conf);
                while (getchar() != '\n');
                if (conf == 'O' || conf == 'o') {
                    return;
                }
                break;

            default:
                printf("Choix invalide \n");
                break;
        }
    } while (1);
}

int main()
{
    BaseEtudiants *ptr = NULL;
    printf("Entrez le nombre de notes par etudiant: \n");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Nombre de notes invalide.\n");
        return 1;
    }
    while (getchar() != '\n');

    creerBase(&ptr, 2);
    Interface(ptr);

    for (int i = 0; i < ptr->taille; i++) {
        free(ptr->data[i].note);
    }
    free(ptr->data);
    free(ptr);
    return 0;
}
