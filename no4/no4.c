  #include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

void list_directory(const char *path, int level) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    // 디렉토리 열기
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // 디렉토리 내의 항목을 하나씩 읽어서 출력
    while ((entry = readdir(dir)) != NULL) {
        // "."과 ".."은 출력하지 않음
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // 들여쓰기와 레벨 출력
            for (int i = 0; i < level; i++) {
                printf("    ");  // 들여쓰기
            }

            printf("%s", entry->d_name);

            // 경로 결합
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);

            // 파일 또는 디렉토리 유형을 확인
            if (stat(new_path, &statbuf) == 0) {
                if (S_ISDIR(statbuf.st_mode)) {
                    printf(" (Directory)\n");
                    list_directory(new_path, level + 1);  // 디렉토리라면 재귀 호출
                } else {
                    printf(" (File)\n");
                }
            } else {
                perror("stat");
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    // 주어진 디렉토리 목록을 나열
    list_directory(argv[1], 0);

    return 0;
}

