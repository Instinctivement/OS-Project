#ifndef COPY_SERVER_H
#define COPY_SERVER_H

int copy_list(char* nomfichier, char*nomdossiersource, char* nomdossierdestination);
int copier_fichier_vers_dossier(char* nomfichier, char* nomdossiersource, char* nomdossierdestination);
int fichierExisteDeja(const char *nomFichier, const char *listFile);
void creerListProd(const char *productionRepertoire, const char *listFile);

#endif