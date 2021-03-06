//
// Created by hubert on 1/4/20.
//

#include "resolver.hpp"
#include <ncurses.h>

int main()
{
    initscr();
    refresh();
    resolver a;
    a.load("tmp1.cpp");
//    a.find("code");
//    a.nextConflict();
//    a.mergeCurrentToBoth();
//    a.previousConflict();
    for (;;) {
        a.printToTerminal();
        switch (getch())
        {
            case 'j':
                a.previousLine();
                break;
            case 'k':
                a.nextLine();
                break;
            case 'l':
                a.previousConflict();
                break;
            case ';':
                a.nextConflict();
                break;
            case 'f':
                a.find("code");
                break;
            case 'g':
                a.nextFound();
                break;
            case 'h':
                a.previousFound();
                break;
            default:
                break;
        }
    }
    endwin();
    return 0;
}

