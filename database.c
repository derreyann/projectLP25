//
// Created by flassabe on 16/11/2021.
//

#include "database.h"

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "utils.h"

void create_db_directory(char *name) {
    if (!directory_exists(name)) {
        mkdir(name, S_IRWXU);
    }
}

void recursive_rmdir(char *dirname) {
    if(directory_exists(dirname)){
        char command[PATH_MAX + sizeof("rm -r ")];
        sprintf(command, "rm -r %s", dirname);
        system(command);
    }  
}
