#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// index 0~25: a~z, 26: BOS, 27: EOS
#define BOS 26
#define EOS 27
#define SIZE 28
#define MAX_WORD_LEN 20

int main(void) {
    // step02_bigram_freq.csv 읽기
    FILE *fin = fopen("data/dwyl-english-words/step02_bigram_freq.csv", "r");
    if (!fin) {
        printf("step02_bigram_freq.csv를 열 수 없습니다.\n");
        return 1;
    }

    int bigram[SIZE][SIZE] = {{0}};
    char line[256];
    fgets(line, sizeof(line), fin); // 헤더 건너뛰기

    // CSV 파싱: prev,next,frequency
    char prev_str[8], next_str[8];
    int count;
    while (fgets(line, sizeof(line), fin)) {
        // 줄바꿈 제거
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = '\0';

        // comma로 분리
        char *tok1 = strtok(line, ",");
        char *tok2 = strtok(NULL, ",");
        char *tok3 = strtok(NULL, ",");
        if (!tok1 || !tok2 || !tok3) continue;

        // prev index
        int pi, ni;
        if (strcmp(tok1, "<BOS>") == 0)      pi = BOS;
        else if (strcmp(tok1, "<EOS>") == 0)  pi = EOS;
        else                                  pi = tok1[0] - 'a';

        // next index
        if (strcmp(tok2, "<BOS>") == 0)      ni = BOS;
        else if (strcmp(tok2, "<EOS>") == 0)  ni = EOS;
        else                                  ni = tok2[0] - 'a';

        bigram[pi][ni] = atoi(tok3);
    }
    fclose(fin);

    // 각 행마다 cumulative distribution 계산
    int cumulative[SIZE][SIZE] = {{0}};
    int row_total[SIZE] = {0};

    for (int i = 0; i < SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < SIZE; j++) {
            sum += bigram[i][j];
            cumulative[i][j] = sum;
        }
        row_total[i] = sum;
    }

    // 난수 초기화
    srand(time(NULL));

    // 글 생성: 10줄, 각 줄 5단어
    FILE *fout = fopen("data/dwyl-english-words/step02_bigram_generated.txt", "w");
    if (!fout) {
        printf("출력 파일을 열 수 없습니다.\n");
        return 1;
    }

    for (int line_i = 0; line_i < 10; line_i++) {
        for (int word = 0; word < 5; word++) {
            // BOS 행에서 첫 글자 뽑기
            int r = rand() % row_total[BOS];
            int current = 0;
            for (int k = 0; k < SIZE; k++) {
                if (r < cumulative[BOS][k]) {
                    current = k;
                    break;
                }
            }
            fputc('a' + current, fout);

            // 다음 글자를 계속 뽑기, EOS가 나오면 종료
            for (int j = 1; j < MAX_WORD_LEN; j++) {
                if (row_total[current] == 0)
                    break;

                r = rand() % row_total[current];
                int next = 0;
                for (int k = 0; k < SIZE; k++) {
                    if (r < cumulative[current][k]) {
                        next = k;
                        break;
                    }
                }

                if (next == EOS)
                    break;

                fputc('a' + next, fout);
                current = next;
            }

            if (word < 4)
                fputc(' ', fout);
        }
        fputc('\n', fout);
    }
    fclose(fout);

    // 결과 출력
    fout = fopen("data/dwyl-english-words/step02_bigram_generated.txt", "r");
    while (fgets(line, sizeof(line), fout)) {
        printf("%s", line);
    }
    fclose(fout);

    return 0;
}
