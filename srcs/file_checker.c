#include "../includes/minishell.h"

int is_directory(char *path)
{
    struct stat *buf;

    buf = malloc(sizeof(struct stat));

    int k = stat(path, buf);

    free(buf);
    if (k == -1)
        return 0;
    if (buf->st_mode & S_IFDIR)
        return 1;
    return 0;
}

int is_executable(char *path)
{
    struct stat *buf;

    buf = malloc(sizeof(struct stat));

    int k = stat(path, buf);

    free(buf);
    if (k == -1)
        return 0;
    if (buf->st_mode & S_IXUSR)
        return 1;
    return 0;
}

int is_file(char *path)
{
    struct stat *buf;

    buf = malloc(sizeof(struct stat));

    int k = stat(path, buf);

    free(buf);
    if (k == -1)
        return 0;
    if (buf->st_mode & S_IFREG)
        return 1;
    return 0;
}

int is_link(char *path)
{
    struct stat *buf;

    buf = malloc(sizeof(struct stat));

    int k = stat(path, buf);

    free(buf);
    if (k == -1)
        return 0;
    if (buf->st_mode & S_IFLNK)
        return 1;
    return 0;
}

int is_socket(char *path)
{
    struct stat *buf;

    buf = malloc(sizeof(struct stat));

    int k = stat(path, buf);

    free(buf);
    if (k == -1)
        return 0;
    if (buf->st_mode & S_IFSOCK)
        return 1;
    return 0;
}

// int is_block_device(char *path)
// {
//     struct stat *buf;

//     buf = malloc(sizeof(struct stat));

//     int k = stat(path, buf);