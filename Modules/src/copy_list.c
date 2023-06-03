#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include "includes.h"
#define MAX_FILENAME_LENGTH 512
#define MAX_LINE_LENGTH 512 

typedef struct dirent DirEntry;

int copy_list(char* nameFile, char* sourceFolderName, char* destinationFolderName) {
    FILE* f = fopen(nameFile, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier : %s\n", nameFile);
        save_error("Erreur lors de l'ouverture du fichier.");
        save_data_log(fichier_log, "Module Copy : Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    char ligne[50];
    char nom_fic[50];

    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = '\0';
        sscanf(ligne, "%s", nom_fic);

        printf("%s\n", nom_fic);
        save_data_log(fichier_log, "Module Copy : copie d'un fichier.");
        if (copy_file_to_folder(nom_fic, sourceFolderName, destinationFolderName) != 0) {
            fclose(f);
            return 1;
        }
        save_received_file(nom_fic);
    }

    fclose(f);
    return 0;
}

int copy_file_to_folder(char* fileName, char* sourceFolderName, char* destinationFolderName) {
    char* nom_fichier_source = malloc(strlen(fileName) + strlen(sourceFolderName) + 2);
    char* nom_fichier_destination = malloc(strlen(fileName) + strlen(destinationFolderName) + 2);

    strcpy(nom_fichier_source, sourceFolderName);
    strcat(nom_fichier_source, "/");
    strcat(nom_fichier_source, fileName);

    strcpy(nom_fichier_destination, destinationFolderName);
    strcat(nom_fichier_destination, "/");
    strcat(nom_fichier_destination, fileName);

    printf("Copie du fichier %s en cours...\n", fileName);

    FILE* fsource = fopen(nom_fichier_source, "r");
    if (fsource == NULL) {
        printf("Erreur lors de l'ouverture du fichier source : %s\n", nom_fichier_source);
        save_error("Erreur lors de l'ouverture du fichier source.");
        save_data_log(fichier_log, "Module copy: Erreur lors de l'ouverture du fichier source.");
        free(nom_fichier_source);
        free(nom_fichier_destination);
        return 1;
    }

    FILE* fdestination = fopen(nom_fichier_destination, "w");
    if (fdestination == NULL) {
        printf("Erreur lors de l'ouverture du fichier destination : %s\n", nom_fichier_destination);
        save_error("Erreur lors de l'ouverture du fichier destination.");
        save_data_log(fichier_log, "Module copy: Erreur lors de l'ouverture du fichier destination.");
        fclose(fsource);
        free(nom_fichier_source);
        free(nom_fichier_destination);
        return 1;
    }

    int c;
    while ((c = fgetc(fsource)) != EOF) {
        fputc(c, fdestination);
    }

    fclose(fsource);
    fclose(fdestination);
    free(nom_fichier_source);
    free(nom_fichier_destination);

    return 0;
}


int file_already_exist(const char *fileName, const char *listFile) {
    FILE *file = fopen(listFile, "r");
    if (file == NULL) {
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strstr(line, fileName) != NULL) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
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

