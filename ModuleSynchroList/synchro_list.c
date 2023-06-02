#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "synchro_list.h"
char* fichier_log_f = "ModLog/log.txt";

FILE* synchroList(const char* file1, const char* file2) {

    FILE* fp1 = fopen(file1, "r");

    FILE* fp2 = fopen(file2, "r");

    printf("%s\n",file1);
    printf("%s\n",file2);

    if (fp1 == NULL || fp2 == NULL ) {

        printf("Erreur lors de l'ouverture des fichiers.\n");
        enregistrer_erreur("Erreur lors de l'ouverture des fichiers.");
        save_data_log(fichier_log_f, "Module Synchro : Erreur lors de l'ouverture des deux fichiers.");
        return NULL;

    }

    char line1[256];

    char line2[256];

    int found;

    // Create the output file

    FILE* fpOutput = fopen("listeAcopier.txt", "w");

    if (fpOutput == NULL) {

        printf("Erreur lors de la création du fichier de sortie.\n");
        enregistrer_erreur("Erreur lors de la création du fichier de sortie.");
        save_data_log(fichier_log_f, "Module Synchro : Erreur lors de la création du fichier de sortie.");
        fclose(fp1);

        fclose(fp2);

        return NULL;
    }

    // Parcourir chaque ligne du premier fichier

    while (fgets(line1, sizeof(line1), fp1) != NULL) {

        found = 0;

        // Parcourir chaque ligne du deuxième fichier

        rewind(fp2); // Réinitialiser la position du curseur au début du fichier

        while (fgets(line2, sizeof(line2), fp2) != NULL) {

            // Comparer les lignes des deux fichiers (ignorer les sauts de ligne)

            if (strcmp(line1, line2) == 0) {

                found = 1;

                break;

            }

        }

        // Si la ligne n'a pas été trouvée dans le deuxième fichier, l'écrire dans le fichier de sortie

        if (!found) {

            fputs(line1, fpOutput);
        }
    }
    // Fermer les fichiers

    fclose(fp1);

    fclose(fp2);

    fclose(fpOutput);

    printf("Comparaison terminée. Le résultat a été écrit dans le fichier listeAcopier\n");
    save_data_log(fichier_log_f, "Module Synchro : Comparaison terminée. Le résultat a été écrit dans le fichier listeAcopier.");

    return fpOutput;

}
