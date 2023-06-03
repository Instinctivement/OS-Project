#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

typedef struct dirent DirEntry;

void generer_liste_fichiers(const char* repertoirePath, int fichierListe);

int main(void)
{
    int etatServeur = 1;

    // Ouverture du fichier d'état du serveur de production
    FILE* fichierEtatServeurProd = fopen("../Production/EtatServeurProd.txt", "r");

    // Vérification de l'ouverture du fichier d'état du serveur de production
    if (fichierEtatServeurProd == NULL)
    {
        perror("fichierEtatServeurProd : Erreur d'ouverture du fichier d'état de serveur");
        exit(EXIT_FAILURE);
    }

    // Lecture de l'état initial du serveur
    fscanf(fichierEtatServeurProd, "%d", &etatServeur);
    fclose(fichierEtatServeurProd);

    while (1)
    {
        if (etatServeur == 0)
        {
            // Ouverture de la liste des fichiers du serveur de production
            FILE* fichier_liste_production = fopen("ListeFichiers.txt", "w");
            if (fichier_liste_production == NULL)
            {
                perror("filesProd : Erreur d'ouverture de la liste des fichiers du serveur de production");
                exit(EXIT_FAILURE);
            }

            printf("[Serveur de backup] Génération d'une nouvelle liste de fichiers...\n");

            // Modifier cet appel en utilisant fileno pour obtenir le descripteur de fichier
            generer_liste_fichiers("./home/", fileno(fichier_liste_production));

            printf("[Serveur de backup] Liste générée\n");

            // Fermeture de la liste des fichiers du serveur de production
            fclose(fichier_liste_production);

            sleep(4); // Attendre 10 secondes

            // Mise à jour de l'état du serveur
            fichierEtatServeurProd = fopen("../Production/EtatServeurProd.txt", "r");
            fscanf(fichierEtatServeurProd, "%d", &etatServeur);
            fclose(fichierEtatServeurProd);
        }
        else
        {
            printf("[Serveur de backup] En attente . . .\n");

            fichierEtatServeurProd = fopen("../Production/EtatServeurProd.txt", "r");
            fscanf(fichierEtatServeurProd, "%d", &etatServeur);
            fclose(fichierEtatServeurProd);
        }
        sleep(4); // Attendre 10 secondes
    }

    return EXIT_SUCCESS;
}

void generer_liste_fichiers(const char* repertoirePath, int fichierListe)
{
    DIR* repertoire = opendir(repertoirePath);
    if (repertoire == NULL)
    {
        printf("Erreur : impossible d'ouvrir le répertoire suivant >> %s\n", repertoirePath);
        return;
    }

    DirEntry* fichierCourant;

    while ((fichierCourant = readdir(repertoire)) != NULL)
    {
        if (strcmp(".", fichierCourant->d_name) == 0 || strcmp("..", fichierCourant->d_name) == 0)
            continue;

        if (fichierCourant->d_type == DT_DIR)
        {
            generer_liste_fichiers(fichierCourant->d_name, fichierListe);
        }
        else
        {
            dprintf(fichierListe, "%s\n", fichierCourant->d_name);
        }
    }

    closedir(repertoire);
}

