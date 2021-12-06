#define CHECK_DISK_LENGTH

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

typedef struct SuperBlock_Struct {
    uint32_t magic_number;
    uint32_t block_size;
    uint32_t fs_size;
    uint32_t fat_length;
    uint32_t root_dir;
} SuperBlock_t;

char *devnull;

int main(int argc, char **argv) {
    unsigned long starts[20], ends[20];

#ifdef CHECK_DISK_LENGTH
    struct statvfs fs;
    statvfs(argv[1], &fs);
    unsigned long num_blocks = fs.f_blocks;
    printf("Num blocks: %lu\n", num_blocks);
#endif

    FILE *descriptor_file = fopen(argv[2], O_RDONLY);
    char *line;
    size_t len;
    int num_sections = 0;
    while (getline(&line, &len, descriptor_file) != -1) {
        char *section;
        sscanf(line, "%s %lu", section, &starts[num_sections]);

        char *volume;
        strcpy(volume, argv[1]);  // /dev/sda
        strcat(volume, section);  // 1
        // volume = /dev/sda1

        SuperBlock_t superblock;
        int volume_fd = open(volume, O_RDONLY);
        read(volume_fd, devnull, 1024);
        read(volume_fd, &superblock, sizeof(SuperBlock_t));
        close(volume_fd);

        ends[num_sections] = starts[num_sections] + superblock.fs_size - 1;

        num_sections++;
    }

    for (int i = 0; i < num_sections; i++) {
        for (int j = 0; j < num_sections; j++) {
            if (i == j) continue;
#ifdef CHECK_DISK_LENGTH
            if (ends[i] > num_blocks) {
                printf("disk length error");
                return -1;
            }
#endif
            if (starts[j] < starts[i] && starts[i] < ends[j]) {
                printf("overlap");
                return -1;
            }
        }
    }

    printf("ok");
    return 0;
}
