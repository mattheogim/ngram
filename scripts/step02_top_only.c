#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *fin = fopen("data/dwyl-english-words/step01_letter_freq.csv", "r");
    if (!fin) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[256];
    fgets(line, sizeof(line), fin); // 헤더 건너뛰기

    // 가장 빈도 높은 글자 찾기
    int rank;
    char letter;
    int count;
    char top_letter = 'a';
    int top_count = 0;

    while (fscanf(fin, "%d,%c,%d", &rank, &letter, &count) == 3) {
        if (count > top_count) {
            top_count = count;
            top_letter = letter;
        }
    }
    fclose(fin);

    printf("가장 빈도 높은 글자: %c (%d번)\n\n", top_letter, top_count);

    FILE *fout = fopen("data/dwyl-english-words/step02_top_only.txt", "w");
    if (!fout) {
        printf("출력 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 10줄 출력, 각 줄 5단어, 각 단어 5글자
    for (int line_i = 0; line_i < 10; line_i++) {
        for (int word = 0; word < 5; word++) {
            for (int j = 0; j < 5; j++) {
                fputc(top_letter, fout);
            }
            if (word < 4)
                fputc(' ', fout);
        }
        fputc('\n', fout);
    }
    fclose(fout);

    // 결과 출력
    fout = fopen("data/dwyl-english-words/step02_top_only.txt", "r");
    while (fgets(line, sizeof(line), fout)) {
        printf("%s", line);
    }
    fclose(fout);

    return 0;
}
