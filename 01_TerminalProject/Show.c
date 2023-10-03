#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC_CODE 27
#define SPACE_CODE 32

void showFile(WINDOW* win, char* fileContent, int scrollCnt) {
    werase(win);
    wmove(win, 1, 0);
    char *currentLine = fileContent;
    int currentLineCnt = 0;

    while (currentLine && currentLineCnt - scrollCnt < LINES - 1) {
        char *curLineLastSymbol = strchr(currentLine, '\n');
        if (curLineLastSymbol)
            *curLineLastSymbol = '\0';
        if (currentLineCnt >= scrollCnt)
            wprintw(win, " %.*s\n", COLS - 3,currentLine);
        if (curLineLastSymbol)
            *curLineLastSymbol = '\n';
        currentLine = curLineLastSymbol ? (curLineLastSymbol + 1) : NULL;
        currentLineCnt++;
    }
    box(win, 0, 0);
    wrefresh(win);
}

int countLines(char* fileContent) {
    int numOfLines = 0;
    char *currentLine = fileContent;
    while (currentLine ) {
        char *nextLine = strchr(currentLine, '\n');
        if (nextLine) 
            *nextLine = '\n';
        currentLine = nextLine ? (nextLine + 1) : NULL;
        numOfLines++;
    }
    return numOfLines;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Show: missing file operand\n");
        return 1;
    }
    FILE* fp = fopen(argv[1], "r");
    if (NULL == fp) {
        fprintf(stderr, "Couldn't open file `%s`\n", argv[1]);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* fileContent = malloc(size);
    fread(fileContent, 1, size, fp);
    fclose(fp);
    int numOfLines = countLines(fileContent);

    initscr();
    printw("File: %s, lines: %d\n", argv[1], numOfLines);

    WINDOW *win = newwin(LINES-1, COLS, 1, 0);
    refresh();

    keypad(win, TRUE);
    scrollok (win, TRUE);
    int scrollCnt = 0;

    showFile(win, fileContent, scrollCnt);
    int userCommand = 0;
    while((userCommand = wgetch(win)) != ESC_CODE) {
        if (userCommand == SPACE_CODE && scrollCnt + LINES - 1 < numOfLines) {
            scrollCnt++;
        }
        showFile(win, fileContent, scrollCnt);
    }

    free(fileContent);
    delwin(win);
    endwin();
}
