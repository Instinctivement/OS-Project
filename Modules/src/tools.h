#ifndef TOOLS_H
#define TOOLS_H

int save_data_log(const char *file_log, const char *data);
int get_error_count();
int compare_files(const char* file1, const char* file2);
int get_received_file_count();
int file_line_count(char* namefile);
int save_error(char* description);
int save_received_file(char* namefile);
int write_end_of_file_stat_line(char* line, char* namefile);

#endif 