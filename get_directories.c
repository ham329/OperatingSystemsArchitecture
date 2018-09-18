

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


void getDirectories(const char *path);
static char **files = NULL;
int main (int argc, char **argv)
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s path\n", argv[0]);
        return 1;
    }
    getDirectories(argv[1]);
}
 
void getDirectories(const char *path)
{
    DIR *dir = opendir(path);
    struct dirent *dp;
    char *p;
    char *newpath;
    size_t fileCount = 0;
    char *symbol = "/";
    if (dir == NULL){
        printf("DIR IS NULL\n");
        return;
    }
    while ((dp = readdir (dir)) != NULL){
        p=dp->d_name;
        if((*p!='.')&&(dp->d_type==DT_DIR))
            printf("%s\n",dp->d_name);
    }
 
    rewinddir (dir);
    while ((dp = readdir(dir)) != NULL){
        p=dp->d_name;
        if((*p!='.')&&(dp->d_type==DT_DIR))
        {
                newpath =(char *)malloc(strlen(dp->d_name)+strlen(path)+2);
                        strcat(newpath, path);       // add the path to new path
                        strcat(newpath,symbol);     // add a / to the new path
                        strcat(newpath,dp->d_name);     // add file name to the new path        
                getDirectories(newpath);
            free(newpath);
            newpath = NULL;
        }
    }
 
    closedir(dir);
    return;
}
