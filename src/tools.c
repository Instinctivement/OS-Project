#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "tools.h"
#define MAX_LINE_LENGTH 512

char* fichier_log = "ModLog/log.txt";

int save_data_log(const char *fichier_log, const char *data)
{
    FILE *fichier = NULL;
    time_t temps_actuel;
    struct tm *heure_locale;
    // Obtenir le temps actuel
    temps_actuel = time(NULL);
    fichier = fopen(fichier_log, "a");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture de fichier\n.");
        enregistrer_erreur("Erreur lors de l'ouverture de fichier");
        return EXIT_FAILURE;
    }
    else
    {
        fprintf(fichier, "%s\t", data);
        // Récupérer la date de modification du fichier
        char dateTimeString[MAX_LINE_LENGTH];
        struct tm *modificationTime = localtime(&temps_actuel);
        strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %H:%M:%S", modificationTime);

        fprintf(fichier, "--- %s\n", dateTimeString);
    }

    fclose(fichier);

    return EXIT_SUCCESS;
}

int get_nombre_erreurs()
{
    return nombre_ligne_fichier("log/stat_erreur.txt");
}

int get_nombre_fichier_recu()
{
    return nombre_ligne_fichier("log/stat_fichier_recu.txt");
}

int nombre_ligne_fichier(char *nomfichier)
{

    FILE *fichier = fopen(nomfichier, "r");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int nombreLignes = 0;
    char caractere;

    while ((caractere = fgetc(fichier)) != EOF)
    {
        if (caractere == '\n')
        {
            nombreLignes++;
        }
    }

    fclose(fichier); // Ferme le fichier

    return nombreLignes;
}

int enregistrer_erreur(char *descriptif)
{
    return ecrire_ligne_fin_fichier_stat(descriptif, "log/stat_erreur.txt");
}

int enregistrer_fichier_recu(char *nomfichier)
{
    return ecrire_ligne_fin_fichier_stat(nomfichier, "log/stat_fichier_recu.txt");
}

int ecrire_ligne_fin_fichier_stat(char *ligne, char *nom_fichier)
{

    FILE *f = NULL;
    time_t now;
    struct tm *local_time;
    char date_str[100];

    now = time(NULL);
    local_time = localtime(&now);

    strftime(date_str, sizeof(date_str), "%d-%m-%Y, %H:%M:%S", local_time);

    f = fopen(nom_fichier, "a");

    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier, pour l'ecriture en fin de fichier");
        return 1;
    }

    fprintf(f, "%s > %s\n", date_str, ligne);

    fclose(f);

    return 0;
}
