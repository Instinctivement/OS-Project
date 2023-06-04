#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#define MAX_LINE_LENGTH 512

char *fichier_log = "src/ModLog/log.txt";
char *fichier_stat_erreur = "src/ModStat/stat_erreur.txt";
char *fichier_stat_fichier_recu = "src/ModStat/stat_fichier_recu.txt";

int save_data_log(const char *file_log, const char *data)
{
    FILE *fichier = NULL;
    time_t temps_actuel;
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
    return file_line_count(fichier_stat_erreur);
}

int compare_files(const char *file1, const char *file2)
{
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return 0;
    }

    int c1, c2;
    int different = 0;

    while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF)
    {
        if (c1 != c2)
        {
            different = 1;
            break;
        }
    }

    if (c1 != c2)
    {
        different = 1;
    }

    fclose(f1);
    fclose(f2);

    return !different;
}

int get_received_file_count()
{
    return file_line_count(fichier_stat_fichier_recu);
}

int file_line_count(char *namefile)
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

int save_error(char *description)
{
    return write_end_of_file_stat_line(description, fichier_stat_erreur);
}

int save_received_file(char *namefile)
{
    return write_end_of_file_stat_line(namefile, fichier_stat_fichier_recu);
}

int write_end_of_file_stat_line(char *line, char *namefile)
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
        printf("Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    fprintf(f, "%s > %s\n", date_str, line);

    fclose(f);

    return 0;
}
