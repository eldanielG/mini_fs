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
int init_file_system();
int free_file_system();

#define PERM_READ  0b100
#define PERM_WRITE 0b010
#define PERM_EXEC  0b001

// Structure to hold file metadata
typedef struct {
    char name[256];          // File name
    size_t size;            // File size in bytes
    char type[10];          // File type (e.g., "text", "binary")
    time_t creation_time;   // Creation timestamp
    time_t modification_time;// Last modification timestamp
    int inode_id;           // Unique ID simulating inode
    int permissions;        // Permissions (RWX for owner, group, public)
} FileMetadata;

// Structure to represent a directory
typedef struct Directory {
    char name[256];                  // Directory name
    struct Directory *parent;        // Pointer to parent directory
    struct Directory *subdirectories; // Pointer to subdirectories
    struct Directory *next;          // Pointer to next sibling directory
    FileMetadata *files;             // Pointer to files in the directory
} Directory;

#endif // FILESYSTEM_H