#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int isdigit_str(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
}

int devnull;

int main (int argc, char** argv)
{
    DIR *dp;
    struct dirent *dir_iter;

    char self_tty[100];
    strcpy(self_tty, ttyname(STDIN_FILENO));

    dp = opendir("/proc/");

    printf("PID\t\tTTY\t\tCMD\n");

    int all = 0;
    if (argc == 2) {
        if (strcmp(argv[1], "-e") == 0) {
            all = 1;
        }
    }

    while ((dir_iter = readdir(dp)) != NULL) {
        if (! isdigit_str(dir_iter->d_name)) continue;

        char path[1000];
        sprintf(path, "/proc/%s/fd/0", dir_iter->d_name);

        int fd = open(path, O_RDONLY);
        char *tty = ttyname(fd);
        close(fd);

        if (tty == NULL) {
            if (all) tty = "?\t";
            else continue;
        }

        if (!all) {
            if (strcmp(tty, self_tty) != 0)
                continue;
        }

        char cmd[1000];
        sprintf(path, "/proc/%s/stat", dir_iter->d_name);
        FILE* stat_file = fopen(path, "r");
        fscanf(stat_file,"%d%s", &devnull, cmd);
        fclose(stat_file);

        printf("%s\t%s\t%s\n", dir_iter->d_name, tty, cmd);
    }
    closedir(dp);

    return 0;
}
