#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main(void) {
    // step01_letter_freq.csv 읽기
    FILE *fin = fopen("data/dwyl-english-words/step01_letter_freq.csv", "r");
    if (!fin) {
        printf("step01_letter_freq.csv를 열 수 없습니다.\n");
        return 1;
    }

    int freq[26] = {0};
    char line[256];
    fgets(line, sizeof(line), fin); // 헤더 건너뛰기

    int rank;
    char letter;
    int count;
    while (fscanf(fin, "%d,%c,%d", &rank, &letter, &count) == 3) {
        freq[letter - 'a'] = count;
    }
    fclose(fin);

    // 누적분포 만들기 (룰렛 칸 이어 붙이기)
    int cumulative[26];
    int total = 0;
    for (int i = 0; i < 26; i++) {
        total += freq[i];
        cumulative[i] = total;
    }

    // 난수 초기화
    srand(time(NULL));

    // 글 생성: 5개 단어, 각 단어 3~8글자
    FILE *fout = fopen("data/dwyl-english-words/step02_generated.txt", "w");
    if (!fout) {
        printf("출력 파일을 열 수 없습니다.\n");
        return 1;
    }

    for (int line = 0; line < 10; line++) {
        for (int word = 0; word < 5; word++) {
            int word_len = 3 + rand() % 6; // 3~8글자

            for (int j = 0; j < word_len; j++) {
                // 룰렛에 공 던지기
                int r = rand() % total;

                // 공이 어느 칸에 떨어졌는지 찾기
                for (int k = 0; k < 26; k++) {
                    if (r < cumulative[k]) {
                        fputc('a' + k, fout);
                        break;
                    }
                }
            }

            if (word < 4)
                fputc(' ', fout);
        }
        fputc('\n', fout);
    }
    fclose(fout);

    // 결과 출력
    fout = fopen("data/dwyl-english-words/step02_generated.txt", "r");
    while (fgets(line, sizeof(line), fout)) {
        printf("%s", line);
    }
    fclose(fout);

    return 0;
}
