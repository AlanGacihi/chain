#ifndef CHAIN_H
#define CHAIN_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

void readline(int fd, char *buffer);
void split(int fd,int length, char *str);

#endif /* CHAIN_H */
