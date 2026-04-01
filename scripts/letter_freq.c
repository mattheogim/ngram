#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *fin = fopen("data/dwyl-english-words/step01_result.csv", "r");
    FILE *fout = fopen("data/dwyl-english-words/step01_letter_freq.csv", "w");
    if (!fin || !fout) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int freq[26] = {0};
    char line[256];

    // 헤더 건너뛰기
    fgets(line, sizeof(line), fin);

    // 글자 빈도 세기
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (ch == '\n' || ch == '\r')
            continue;
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }

    // 순위 정렬 (내림차순)
    int order[26];
    for (int i = 0; i < 26; i++)
        order[i] = i;

    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[order[j]] > freq[order[i]]) {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    // CSV 출력
    fprintf(fout, "rank,letter,frequency\n");
    for (int i = 0; i < 26; i++) {
        fprintf(fout, "%d,%c,%d\n", i + 1, 'a' + order[i], freq[order[i]]);
    }

    fclose(fin);
    fclose(fout);
    printf("완료: step01_letter_freq.csv 저장됨\n");
    return 0;
}
