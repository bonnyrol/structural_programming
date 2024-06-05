#include <ncurses.h>
#include <string.h>
#include <locale.h>
//#include <features.h>

WINDOW *create_win(int y, int x, int starty, int startx);

int main() {
    int rows = 0, columns = 0;
    int x = 100, y = 50;
    int ch;
    WINDOW *my_win;

    //setlocale(LC_ALL, "C-TRADITIONAL");
    initscr();
    //printw("Colors? : %d\n", has_colors());
    curs_set(0);
    
    // do {
    //     getmaxyx(stdscr, rows, columns);
    //     mvprintw(rows / 2, columns / 2, "rows: %d, columns: %d", rows, columns); 
    //     refresh();
    // } while (rows < y && columns < x);
    while ((ch = getch()) != 'q') {
        clear();
        getmaxyx(stdscr, rows, columns);

        while (rows < y || columns < x) {
            mvprintw(rows / 2, columns / 2, "rows: %d, columns: %d", rows, columns);
            refresh();
            getmaxyx(stdscr, rows, columns);
        }
        clear();


        my_win = create_win(y, x, (rows - y) / 2, (columns - x) / 2);
        // //wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
        // box(my_win, 0, 0);
        for (int i = 1; i < y - 1; i++) {
            for (int j = 1; j < x - 1; j++) {

                    if ((i == (y / 2)) && (j == (x / 2))) {
                        mvwaddch(my_win, i, j, ACS_PLUS);
                    } else if (j == (x / 2)) {
                        mvwaddch(my_win, i, j, ACS_VLINE);
                    } else if (i == (y / 2)) {
                        mvwaddch(my_win, i, j, ACS_HLINE);
                    }
                    
            // mvwaddch(my_win, i, j, ACS_CKBOARD);
            }
        }
        refresh();
        wrefresh(my_win);
        
        //getch();
        
        // wrefresh(my_win);
        // printw("hello world");
        // mvprintw(0, strlen("hello world") + 1, "%s", "second str");
        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < columns; j++) {
        //         mvaddch(i, j, ACS_DIAMOND | A_BOLD);
            
        //     }
        // }

        //wborder(stdscr, '|', '|', '|', '|', '|', '|', '|', '|');

        // for (int i = 0; i < 5; i++) {
        //     printw("%s.%s\n", folder2[i].name, folder2[i].extension);
        // }

        
        //mvprintw(rows / 2, columns / 2,  "%s", "hello world");
        //addstr("hello world");
    }
    
    delwin(my_win);
    endwin();
    return 0;
}

WINDOW *create_win(int y, int x, int starty, int startx) {
    WINDOW *locale_win = newwin(y, x, starty, startx);
    //box(locale_win, 0, 0);
    //wborder(locale_win, WACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    
    wrefresh(locale_win);
    return locale_win;
}
