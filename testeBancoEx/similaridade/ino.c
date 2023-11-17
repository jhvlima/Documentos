#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PATH_MAX 1024

int main()
{
    const char *path = "."; // Change this to your directory path

    // Open the directory
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    struct stat fileStat;

    // Read the directory entries
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { // Check if it's a regular file
            char file_path[PATH_MAX];
            snprintf(file_path, PATH_MAX, "%s/%s", path, entry->d_name);

            // Get the inode number using stat
            if (stat(file_path, &fileStat) == 0)
            {
                printf("File: %s, Inode: %lu\n", entry->d_name, (unsigned long)fileStat.st_ino);
            }
            else
            {
                perror("stat");
            }
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
