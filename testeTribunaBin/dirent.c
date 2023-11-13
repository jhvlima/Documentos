#include <dirent.h>
#include <stdio.h>

int main()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // Open the current directory
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        printf("File: %s, Inode: %lu\n", entry->d_name, (unsigned long)entry->d_ino);
    }

    closedir(dir);

    return 0;
}
