#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exec.h"

void exec_execl(const char *path, char *const args[])
{
    if (execv(path, args) == -1)
    {
        perror("execl");
        exit(EXIT_FAILURE);
    }
}

void exec_execlp(const char *file, char *const args[])
{
    if (execvp(file, args) == -1)
    {
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

void exec_execle(const char *path, char *const args[], char *const envp[])
{
    if (execve(path, args, envp) == -1)
    {
        perror("execle");
        exit(EXIT_FAILURE);
    }
}

void exec_execv(const char *path, char *const argv[])
{
    if (execv(path, argv) == -1)
    {
        perror("execv");
        exit(EXIT_FAILURE);
    }
}

void exec_execvp(const char *file, char *const argv[])
{
    if (execvp(file, argv) == -1)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}
