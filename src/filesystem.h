#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <time.h>

// Funções para manipulação do sistema de arquivos
int mkdir(const char *path);
int cd(const char *path);
int touch(const char *filename);
int echo(const char *filename, const char *content);
int cat(const char *filename);
int cp(const char *source, const char *destination);
int mv(const char *source, const char *destination);
int rm(const char *filename);
int chmod(const char *filename, int permissions);
void init_file_system();
void free_file_system();

#endif // FILESYSTEM_H