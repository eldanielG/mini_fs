// This file serves as a public interface for the file system, allowing other modules to access the defined structures and functions.

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <time.h>

// Define constants for permissions
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

// Function prototypes
void mkdir(const char *path);
void cd(const char *path);
void touch(const char *filename);
void echo(const char *filename, const char *content);
void cat(const char *filename);
void cp(const char *source, const char *destination);
void mv(const char *source, const char *destination);
void rm(const char *filename);
void chmod(const char *filename, int permissions);

#endif // FILESYSTEM_H