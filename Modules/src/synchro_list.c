#include <string.h>
#include "includes.h"

char* fichier_log_s = "src/ModLog/log.txt";

FILE* synchroList(const char* file1, const char* file2) {
    FILE* fp1 = fopen(file1, "r");
    FILE* fp2 = fopen(file2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        save_error("Erreur lors de l'ouverture des fichiers.");
        save_data_log(fichier_log_s, "Module Synchro : Erreur lors de l'ouverture des deux fichiers.");
        return NULL;
    }

    printf("%s\n", file1);
    printf("%s\n", file2);

    char line1[256];
    char line2[256];
    int found;

    FILE* fpOutput = fopen("src/listToCopy.txt", "w");

    if (fpOutput == NULL) {
        printf("Erreur lors de la création du fichier de sortie.\n");
        save_error("Erreur lors de la création du fichier de sortie.");
        save_data_log(fichier_log_s, "Module Synchro : Erreur lors de la création du fichier de sortie.");
        fclose(fp1);
        fclose(fp2);
        return NULL;
    }

    while (fgets(line1, sizeof(line1), fp1) != NULL) {
        found = 0;
        rewind(fp2);

        while (fgets(line2, sizeof(line2), fp2) != NULL) {
            if (strcmp(line1, line2) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            fputs(line1, fpOutput);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fpOutput);

    printf("Comparaison terminée. Le résultat a été écrit dans le fichier listeAcopier\n\n");
    save_data_log(fichier_log_s, "Module Synchro : Comparaison terminée. Le résultat a été écrit dans le fichier listeAcopier.");

    return fpOutput;
}
