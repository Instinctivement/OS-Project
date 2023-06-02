#ifndef TOOLS_H
#define TOOLS_H

int save_data_log(const char *fichier_log, const char *data);
int get_nombre_erreurs();
int get_nombre_fichier_recu();
int nombre_ligne_fichier(char* nomfichier);
int enregistrer_erreur(char* descriptif);
int enregistrer_fichier_recu(char* nomfichier);
int ecrire_ligne_fin_fichier_stat(char* ligne, char* nom_fichier);

#endif 