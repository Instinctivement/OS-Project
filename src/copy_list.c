#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "includes.h"
#define MAX_FILENAME_LENGTH 512
#define MAX_LINE_LENGTH 512 

int copy_list(char* nameFile, char*sourceFolderName, char* destinationFolderName){

    FILE* f = NULL ;
    char ligne[50] ;
    char nom_fic[50] ;

    f = fopen(nameFile, "r");

    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier : %s\n", nameFile);
        save_error("Erreur lors de l'ouverture du fichier.");
        save_data_log(fichier_log, "Module Copy : Erreur lors de l'ouverture du fichier %s.");
        return 1;
    }

    while(fgets(ligne, 50, f)){

        ligne[strcspn(ligne, "\n")] = '\0';

        sscanf(ligne, "%s", nom_fic);

        printf("%s\n", nom_fic);
        save_data_log(fichier_log,  "Module Copy : copie d'un fichier. ");
        if(copy_file_to_folder(nom_fic, sourceFolderName, destinationFolderName) != 0){
            return 0 ;
        }
        save_received_file(nom_fic);
    }

    return 0 ;
}

int copy_file_to_folder(char* fileName, char* sourceFolderName, char* destinationFolderName){

    FILE* fsource = NULL ;
    FILE* fdestination = NULL ;
    char c ;

    char* nom_fichier_source = malloc(sizeof(char)*strlen(fileName) + sizeof(char)*strlen(sourceFolderName) + 1);
    char* nom_fichier_destination = malloc(sizeof(char)*strlen(fileName) + sizeof(char)*strlen(destinationFolderName) + 1);

    strcpy(nom_fichier_source, sourceFolderName);
    strcat(nom_fichier_source, "/");
    strcat(nom_fichier_source, fileName);

    strcpy(nom_fichier_destination, destinationFolderName);
    strcat(nom_fichier_destination, "/");
    strcat(nom_fichier_destination, fileName);

    printf("Nom du fichier => %s\n", fileName);

    fsource = fopen(nom_fichier_source, "r") ;

    if(fsource == NULL){
        printf("Erreur lors de l'ouverture du fichier source : %s\n", nom_fichier_source);
        save_error("Erreur lors de l'ouverture du fichier source.");
        save_data_log(fichier_log, "Module copy: Erreur lors de l'ouverture du fichier source.");
        return 1 ;
    }

    fdestination = fopen(nom_fichier_destination, "w") ;

    if(fdestination == NULL){
        printf("Erreur lors de l'ouverture du fichier destination : %s\n", nom_fichier_destination);
        save_error("Erreur lors de l'ouverture du fichier destination.");
        save_data_log(fichier_log, "Module copy: Erreur lors de l'ouverture de du fichier destination.");
        return 1 ;
    }

    while((c = fgetc(fsource)) != EOF){
        fputc(c, fdestination);
    }

    fclose(fsource);
    fclose(fdestination);

    return 0 ;
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

void createListProd(const char *production_directory, const char *listFile) {
    FILE *file = fopen(listFile, "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    DIR *dir = opendir(production_directory);
    if (dir == NULL) {
        printf("Erreur lors de l'ouverture du repertoire %s.\n", production_directory);
        return;
    }
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        char filePath[MAX_FILENAME_LENGTH];
        snprintf(filePath, sizeof(filePath), "%s/%s", production_directory, ent->d_name);

        struct stat fileStat;
        if (stat(filePath, &fileStat) == -1) {
            printf("Erreur lors de la récuperation des informations du fichier %s.\n", filePath);
            continue;
        }

        if (file_already_exist(ent->d_name, listFile)) {
            printf("Le fichier %s existe deja dans %s. Il ne sera pas ajoute.\n", ent->d_name, listFile);
            continue;
        }

        char dateTimeString[MAX_LINE_LENGTH];
        struct tm *modificationTime = localtime(&fileStat.st_mtime);
        strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %H:%M:%S", modificationTime);

        fprintf(file, "%s - %s\n", ent->d_name, dateTimeString);
    }


    closedir(dir);


    fclose(file);
    printf("Le fichier %s a ete mis a jour avec succes.\n", listFile);
}


