#include <ncurses.h>

int main() {
    initscr();
    start_color();

    init_pair(1, COLOR_CYAN , COLOR_BLACK);
    printw("Uma baita string que acabei colocando aqui para testar qualquer coisa que ainda não sei o q é...");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);

    refresh();
    getch();
    endwin();
    return 0;
}