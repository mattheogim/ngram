#include <stdio.h>
#include <ctype.h>
#include <string.h>

// index 0~25: a~z, 26: BOS, 27: EOS
#define BOS 26
#define EOS 27
#define SIZE 28

int main(void) {
    FILE *fin = fopen("data/dwyl-english-words/step01_result.csv", "r");
    FILE *fout = fopen("data/dwyl-english-words/step02_bigram_freq.csv", "w");
    if (!fin || !fout) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int bigram[SIZE][SIZE] = {{0}};
    char line[256];

    // 헤더 건너뛰기
    fgets(line, sizeof(line), fin);

    // 단어마다 bigram 세기
    while (fgets(line, sizeof(line), fin)) {
        // 줄바꿈 제거
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = '\0';

        if (len == 0)
            continue;

        // 소문자로 변환
        for (int i = 0; i < len; i++)
            line[i] = tolower(line[i]);

        // BOS → 첫 글자
        if (line[0] >= 'a' && line[0] <= 'z')
            bigram[BOS][line[0] - 'a']++;

        // 연속 글자 쌍 세기
        for (int i = 0; i < len - 1; i++) {
            int prev = line[i];
            int curr = line[i + 1];
            if (prev >= 'a' && prev <= 'z' && curr >= 'a' && curr <= 'z') {
                bigram[prev - 'a'][curr - 'a']++;
            }
        }

        // 마지막 글자 → EOS
        if (line[len - 1] >= 'a' && line[len - 1] <= 'z')
            bigram[line[len - 1] - 'a'][EOS]++;
    }
    fclose(fin);

    // CSV 출력 (빈도 > 0인 것만)
    fprintf(fout, "prev,next,frequency\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (bigram[i][j] > 0) {
                // prev 이름
                char prev_str[8];
                if (i == BOS)      snprintf(prev_str, sizeof(prev_str), "<BOS>");
                else if (i == EOS) snprintf(prev_str, sizeof(prev_str), "<EOS>");
                else               snprintf(prev_str, sizeof(prev_str), "%c", 'a' + i);

                // next 이름
                char next_str[8];
                if (j == BOS)      snprintf(next_str, sizeof(next_str), "<BOS>");
                else if (j == EOS) snprintf(next_str, sizeof(next_str), "<EOS>");
                else               snprintf(next_str, sizeof(next_str), "%c", 'a' + j);

                fprintf(fout, "%s,%s,%d\n", prev_str, next_str, bigram[i][j]);
            }
        }
    }
    fclose(fout);

    printf("완료: step02_bigram_freq.csv 저장됨 (BOS/EOS 포함)\n");
    return 0;
}
