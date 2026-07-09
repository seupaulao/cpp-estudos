#include <ncurses.h>

using namespace std;

int main() {

   int ch;
   initscr();
   raw();
   keypad(stdscr, TRUE);
   noecho();

   printw("Pressione alguma tecla, e a mesma aparecerá em negrito.\n");
   ch = getch();

   if (ch == KEY_F(2)) {
       printw("a tecla F2 foi pressionada");
   } else {
       printw("A tecla que vc pressionou foi: ");
       attron(A_BOLD); 
       printw("%c", ch);
       attroff(A_BOLD);
   } 

  refresh();
  getch();
  endwin();

  return 0;
}
