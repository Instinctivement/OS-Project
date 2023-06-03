#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <signal.h>

typedef struct dirent DirEntry;

void generer_liste_fichiers(const char* repertoirePath, int fichierListe);
void exit_callback();
void sigint_handler(int signal);

int main(void)
{
    int etatServeur = 1;

    // Ouverture du fichier d'état du serveur de production
    FILE* fichierEtatServeur = fopen("EtatServeurProd.txt", "r+");

    // Vérification de l'ouverture du fichier d'état du serveur de production
    if (fichierEtatServeur == NULL)
    {
        perror("fichierEtatServeur : Erreur d'ouverture du fichier d'état de serveur");
        exit(EXIT_FAILURE);
    }

    // Lecture de l'état initial du serveur
    fscanf(fichierEtatServeur, "%d", &etatServeur);
    rewind(fichierEtatServeur);

    // Écriture de la valeur 1 dans le fichier si l'état initial est différent de 1
    if (etatServeur != 1)
    {
        fprintf(fichierEtatServeur, "1\n");
        rewind(fichierEtatServeur);
    }

    fscanf(fichierEtatServeur, "%d", &etatServeur);
    rewind(fichierEtatServeur);

    // Enregistrement de la fonction de rappel pour la sortie normale du programme
    atexit(exit_callback);

    // Enregistrement du gestionnaire de signal pour SIGINT (Ctrl+C)
    signal(SIGINT, sigint_handler);

    // Tant que le serveur est allumé, on génère des listes toutes les 10 secondes
    while (etatServeur)
    {
        // Ouverture de la liste des fichiers du serveur de production
        int fichier_liste_production = open("ListeFichiers.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fichier_liste_production == -1)
        {
            perror("filesProd : Erreur d'ouverture de la liste des fichiers du serveur de production");
            exit(EXIT_FAILURE);
        }

        printf("[Serveur de production] Génération d'une nouvelle liste de fichiers...\n");
        generer_liste_fichiers("./home/", fichier_liste_production);
        printf("[Serveur de production] Liste générée\n");

        // Fermeture de la liste des fichiers du serveur de production
        close(fichier_liste_production);

        sleep(4); // Attendre 10 secondes

        // Mise à jour de l'état du serveur
        fscanf(fichierEtatServeur, "%d", &etatServeur);
        rewind(fichierEtatServeur);
    }

    // Fermeture du fichier d'état du serveur de production
    fclose(fichierEtatServeur);

    printf("\n\n ALERTE : LE SERVER DE PRODUCTION S'EST ARRETE SUITE A UNE PANNE, LE SERVEUR BACKUP PREND LE RELAIS\n");

    return EXIT_SUCCESS;
}

// Fonction de rappel exécutée à la sortie normale du programme
void exit_callback()
{
    // Ouverture du fichier pour écriture
    FILE* fichierEtatServeur = fopen("EtatServeurProd.txt", "w");

    // Vérification de l'ouverture du fichier
    if (fichierEtatServeur == NULL)
    {
        perror("fichierEtatServeur : Erreur d'ouverture du fichier d'état de serveur");
        exit(EXIT_FAILURE);
    }

    // Écriture de la valeur 0 dans le fichier
    fprintf(fichierEtatServeur, "0\n");

    // Fermeture du fichier
    fclose(fichierEtatServeur);
}

// Fonction de traitement du signal SIGINT (Ctrl+C)
void sigint_handler(int signal)
{
    // Appel de la fonction de rappel pour écrire la valeur 0 dans le fichier
    exit_callback();

    // Terminaison du programme
    exit(EXIT_SUCCESS);
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


