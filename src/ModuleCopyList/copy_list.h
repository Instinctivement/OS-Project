#ifndef COPY_SERVER_H
#define COPY_SERVER_H

int copy_list(char* nameFile, char*sourceFolderName, char* destinationFolderName);
int copy_file_to_folder(char* fileName, char* sourceFolderName, char* destinationFolderName);
int file_already_exist(const char *fileName, const char *listFile);
void createListProd(const char *production_directory, const char *listFile);

#endif