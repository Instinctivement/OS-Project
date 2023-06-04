#include "includes.h"

const char *myProdFile = "../Production/ListeFichiers.txt";
const char *myBackFile = "../Backup/ListeFichiers.txt";
const char *myIntFile = "src/IntergrationServer/ListeFichiers.txt";
char *copyFile = "src/listToCopy.txt";

void copy_list_main();
void synchro_list_main();

int main() {

    printf("\n##############################################\n");
    printf("\n\tPHARMOS - COSMOS -VETERINOS\n");
    printf("\n##############################################\n");
    
    while (1)
    {
        printf("\n\n------------------ Test Des Serveurs ----------------------\n\n");
        testServerP();
        testServerB();

        printf("\n\n------------------ Synchronisations Des Serveurs ----------------------\n\n");
        synchro_list_main();

        copy_list_main();

        printf("\n\tSTATISTIQUES\n");
        printf("\t----------------------------------------\n");
        printf("\tErreurs : %d\n", get_error_count());
        printf("\tFichiers copier : %d\n\n\n\n", get_received_file_count());

        sleep(6); // Attendre 10 secondes
    }
    
    
    return EXIT_SUCCESS;
}


void synchro_list_main() {
    synchroList(myProdFile, myIntFile);
    synchroList(myProdFile, myBackFile);
}

void copy_list_main() {

    // Ouverture de la liste des fichiers du serveur de backup
    int fichier_liste_backup = open(myBackFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fichier_liste_backup == -1) {
        perror("filesProd : Erreur d'ouverture de la liste des fichiers du serveur de backup");
        exit(EXIT_FAILURE);
    }

    printf("\n\n------------------ Copie Vers Le Serveurs De Backup ----------------------\n\n");
    copy_list(copyFile, "../Production/home", "../Backup/home");
    generer_liste_fichiers("../Backup/home/", fichier_liste_backup);
    save_data_log(fichier_log, "Module copy: Copy de list réussi vers Backup");

    // Ouverture de la liste des fichiers du serveur de integration
    int fichier_liste_int = open(myIntFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fichier_liste_int == -1) {
        perror("filesProd : Erreur d'ouverture de la liste des fichiers du serveur de integration");
        exit(EXIT_FAILURE);
    }

    printf("\n\n------------------ Copie Vers Le Serveurs D'Intégration ----------------------\n\n");
    copy_list(copyFile, "../Production/home", "src/IntergrationServer/home");
    generer_liste_fichiers("src/IntergrationServer/home/", fichier_liste_int);
    save_data_log(fichier_log, "Module copy: Copy de list réussi vers Integration");
}


