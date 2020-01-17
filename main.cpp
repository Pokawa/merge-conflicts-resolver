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
    a.load("tmp.cpp");
    a.mergeCurrentToBoth();
    a.printToTerminal();
    getch();
    a.revertCurrent();
    a.printToTerminal();
    getch();
    a.mergeCurrentToBothR();
    a.printToTerminal();
    getch();
    a.mergeCurrentToNew();
    a.printToTerminal();
    getch();
    endwin();
    return 0;
}

