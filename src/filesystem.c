#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

// Estruturas internas para o sistema em memória

typedef struct File {
    char name[256];
    size_t size;
    char type[10];
    char created_at[20];
    char modified_at[20];
    int id;
    int permissions;
    struct File *next;
} File;

typedef struct Directory {
    char name[256];
    struct Directory *parent;
    struct Directory *subdirs;
    File *files;
    struct Directory *next;
} Directory;

Directory *root = NULL;
Directory *current_dir = NULL;

// ===========================
// Inicialização do sistema
// ===========================
void init_file_system() {
    root = malloc(sizeof(Directory));
    strcpy(root->name, "/");
    root->parent = NULL;
    root->subdirs = NULL;
    root->files = NULL;
    root->next = NULL;

    current_dir = root;
}

// ===========================
// Criação de diretório
// ===========================
int mkdir(const char *name) {
    if (!current_dir || !name || name[0] == '\0') return -1;
    if (strchr(name, '/')) return -1;

    Directory *iter = current_dir->subdirs;
    while (iter) {
        if (strcmp(iter->name, name) == 0) return -1;
        iter = iter->next;
    }

    Directory *d = malloc(sizeof(Directory));
    strncpy(d->name, name, sizeof(d->name));
    d->parent = current_dir;
    d->subdirs = NULL;
    d->files = NULL;
    d->next = NULL;

    if (!current_dir->subdirs) {
        current_dir->subdirs = d;
    } else {
        iter = current_dir->subdirs;
        while (iter->next) iter = iter->next;
        iter->next = d;
    }

    return 0;
}

// ===========================
// cd (mudar diretório atual)
// ===========================
int cd(const char *path) {
    if (!current_dir) return -1;

    if (strcmp(path, "/") == 0) {
        current_dir = root;
        return 0;
    }
    if (strcmp(path, "..") == 0) {
        if (current_dir->parent)
            current_dir = current_dir->parent;
        return 0;
    }

    Directory *iter = current_dir->subdirs;
    while (iter) {
        if (strcmp(iter->name, path) == 0) {
            current_dir = iter;
            return 0;
        }
        iter = iter->next;
    }

    return -1;
}

// ===========================
// Criar arquivo
// ===========================
int touch(const char *name) {
    if (!current_dir || !name || name[0] == '\0') return -1;

    File *iter = current_dir->files;
    while (iter) {
        if (strcmp(iter->name, name) == 0) return -1;
        iter = iter->next;
    }

    File *f = malloc(sizeof(File));
    strncpy(f->name, name, sizeof(f->name));
    f->size = 0;

    const char *dot = strrchr(name, '.');
    if (dot)
        strncpy(f->type, dot + 1, sizeof(f->type));
    else
        strcpy(f->type, "txt");

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(f->created_at, sizeof(f->created_at), "%Y-%m-%d %H:%M:%S", tm_info);
    strftime(f->modified_at, sizeof(f->modified_at), "%Y-%m-%d %H:%M:%S", tm_info);

    static int next_id = 1;
    f->id = next_id++;
    f->permissions = 0644;
    f->next = NULL;

    if (!current_dir->files)
        current_dir->files = f;
    else {
        iter = current_dir->files;
        while (iter->next) iter = iter->next;
        iter->next = f;
    }

    return 0;
}

// ===========================
// echo - escrever em arquivo
// ===========================
int echo(const char *name, const char *content) {
    File *f = current_dir->files;
    while (f && strcmp(f->name, name) != 0) f = f->next;

    if (!f) {
        if (touch(name) != 0) return -1;
        f = current_dir->files;
        while (f && strcmp(f->name, name) != 0) f = f->next;
        if (!f) return -1;
    }

    char path[512];
    snprintf(path, sizeof(path), ".mini_fs_data_%d.bin", f->id);

    FILE *fp = fopen(path, "wb");
    if (!fp) return -1;

    size_t len = strlen(content);
    fwrite(content, 1, len, fp);
    fclose(fp);
    f->size = len;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(f->modified_at, sizeof(f->modified_at), "%Y-%m-%d %H:%M:%S", tm_info);

    return 0;
}

// ===========================
// cat - ler arquivo
// ===========================
int cat(const char *name) {
    File *f = current_dir->files;
    while (f && strcmp(f->name, name) != 0) f = f->next;
    if (!f) return -1;

    char path[512];
    snprintf(path, sizeof(path), ".mini_fs_data_%d.bin", f->id);

    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;

    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
        fwrite(buf, 1, n, stdout);

    fclose(fp);
    return 0;
}

// ===========================
// rm - remover arquivo
// ===========================
int rm(const char *name) {
    File *f = current_dir->files, *prev = NULL;
    while (f && strcmp(f->name, name) != 0) {
        prev = f;
        f = f->next;
    }
    if (!f) return -1;

    char path[512];
    snprintf(path, sizeof(path), ".mini_fs_data_%d.bin", f->id);
    remove(path);

    if (prev)
        prev->next = f->next;
    else
        current_dir->files = f->next;

    free(f);
    return 0;
}

// ===========================
// chmod
// ===========================
int chmod(const char *name, int permissions) {
    if (permissions < 0 || permissions > 0777) return -1;

    File *f = current_dir->files;
    while (f && strcmp(f->name, name) != 0) f = f->next;
    if (!f) return -1;

    f->permissions = permissions;
    return 0;
}

// ===========================
// Liberar memória
// ===========================
void free_dir(Directory *dir) {
    File *f = dir->files;
    while (f) {
        File *nextf = f->next;
        char path[512];
        snprintf(path, sizeof(path), ".mini_fs_data_%d.bin", f->id);
        remove(path);
        free(f);
        f = nextf;
    }

    Directory *d = dir->subdirs;
    while (d) {
        Directory *nextd = d->next;
        free_dir(d);
        d = nextd;
    }
    free(dir);
}

void free_file_system() {
    if (!root) return;
    free_dir(root);
    root = NULL;
}

int cp(const char *source, const char *destination) {
    File *fsrc = current_dir->files;
    while (fsrc && strcmp(fsrc->name, source) != 0) fsrc = fsrc->next;
    if (!fsrc) return -1;

    File *f = current_dir->files;
    while (f) {
        if (strcmp(f->name, destination) == 0) return -1;
        f = f->next;
    }

    File *fdst = malloc(sizeof(File));
    memcpy(fdst, fsrc, sizeof(File));
    strncpy(fdst->name, destination, sizeof(fdst->name));
    fdst->next = NULL;

    static int next_id = 10000;
    fdst->id = next_id++;

    char src_path[512];
    snprintf(src_path, sizeof(src_path), ".mini_fs_data_%d.bin", fsrc->id);

    char dst_path[512];
    snprintf(dst_path, sizeof(dst_path), ".mini_fs_data_%d.bin", fdst->id);

    FILE *fp_src = fopen(src_path, "rb");
    FILE *fp_dst = fopen(dst_path, "wb");

    if (fp_src && fp_dst) {
        char buf[1024];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), fp_src)) > 0)
            fwrite(buf, 1, n, fp_dst);
    }

    if (fp_src) fclose(fp_src);
    if (fp_dst) fclose(fp_dst);

    if (!current_dir->files)
        current_dir->files = fdst;
    else {
        File *iter = current_dir->files;
        while (iter->next) iter = iter->next;
        iter->next = fdst;
    }

    return 0;
}

int mv(const char *source, const char *destination) {
    File *f = current_dir->files;
    while (f && strcmp(f->name, source) != 0) f = f->next;
    if (!f) return -1;

    File *check = current_dir->files;
    while (check) {
        if (strcmp(check->name, destination) == 0) return -1;
        check = check->next;
    }

    strncpy(f->name, destination, sizeof(f->name));
    return 0;
}