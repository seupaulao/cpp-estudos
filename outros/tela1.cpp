#include <iostream>
#include <ncurses.h>

using namespace std;

int main() {

	initscr();
	move(48,50); printw("ola mundo, posicao final 48");
	move(24,50); printw("linha 24, coluna 50");
	move(15,50); printw("linha 15, coluna 50");
	refresh();
	getch();
	endwin();
	return 0;
}
