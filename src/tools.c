#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#define MAX_LINE_LENGTH 512

char* fichier_log = "ModLog/log.txt";

int save_data_log(const char *file_log, const char *data)
{
    FILE *fichier = NULL;
    time_t temps_actuel;
    struct tm *heure_locale;
    temps_actuel = time(NULL);
    fichier = fopen(file_log, "a");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture de fichier\n.");
        save_error("Erreur lors de l'ouverture de fichier");
        return EXIT_FAILURE;
    } 
    else
    {
        fprintf(fichier, "%s\t", data);
        char dateTimeString[MAX_LINE_LENGTH];
        struct tm *modificationTime = localtime(&temps_actuel);
        strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %H:%M:%S", modificationTime);

        fprintf(fichier, "--- %s\n", dateTimeString);
    }

    fclose(fichier);

    return EXIT_SUCCESS;
}

int get_error_count()
{
    return file_line_count("log/stat_erreur.txt");
}

int get_received_file_count()
{
    return file_line_count("log/stat_fichier_recu.txt");
}

int file_line_count(char* namefile)
{

    FILE *fichier = fopen(namefile, "r");

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

    fclose(fichier);

    return nombreLignes;
}

int save_error(char* description)
{
    return write_end_of_file_stat_line(description, "log/stat_erreur.txt");
}

int save_received_file(char* namefile)
{
    return write_end_of_file_stat_line(namefile, "log/stat_fichier_recu.txt");
}

int write_end_of_file_stat_line(char* line, char* namefile)
{

    FILE *f = NULL;
    time_t now;
    struct tm *local_time;
    char date_str[100];

    now = time(NULL);
    local_time = localtime(&now);

    strftime(date_str, sizeof(date_str), "%d-%m-%Y, %H:%M:%S", local_time);

    f = fopen(namefile, "a");

    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier, pour l'ecriture en fin de fichier");
        return 1;
    }

    fprintf(f, "%s > %s\n", date_str, line);

    fclose(f);

    return 0;
}
