#include <ncurses.h>
#include <cstring>

int main() {

	 char mesg[] = "Alguma string";
	 int linha, coluna;

	 initscr();
	 getmaxyx(stdscr, linha, coluna);
	 mvprintw(linha/2, (coluna - strlen(mesg))/2, "%s", mesg);

	 mvprintw(linha-2, 0, "Essa tela tem %d linhas e %d colunas", linha, coluna);
	 printw("\ntente redimensionar essa janela e execute o programa novamente...");
	 refresh();
	 getch();
	 endwin();

	 return 0;
}
