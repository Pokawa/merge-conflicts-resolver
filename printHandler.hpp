//
// Created by hubert on 1/17/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_PRINTHANDLER_HPP
#define MERGE_CONFLICTS_RESOLVER_PRINTHANDLER_HPP

#include "coloredString.hpp"
#include <ncurses.h>

class printHandler
{
private:
    WINDOW * window;

    static void initializeColorPairs()
    {
        start_color();
        init_pair(textColor::WhiteText, COLOR_WHITE, COLOR_BLACK);
        init_pair(textColor::BlueText, COLOR_BLUE, COLOR_BLACK);
        init_pair(textColor::YellowText, COLOR_YELLOW, COLOR_BLACK);
        init_pair(textColor::RedText, COLOR_MAGENTA, COLOR_BLACK);
    }

    void initializeWindow()
    {
       window = newwin(LINES-2, COLS, 1, 0);
    }

public:
    printHandler()
    {
        curs_set(0);
        initializeColorPairs();
        initializeWindow();
    }

    void printOnScreen(const coloredStringVector & lines, unsigned int index)
    {
        wclear(window);

        for (unsigned int i = index, printed = 0; i < lines.size() and printed < LINES - 2; i++)
        {
            printed += lines[i].line.size() / COLS;
            wattron(window, COLOR_PAIR(lines[i].color));
            waddstr(window, lines[i].line.c_str());
            waddch(window, '\n');
            wattroff(window, COLOR_PAIR(lines[i].color));
        }

        wrefresh(window);
    }
};

#endif //MERGE_CONFLICTS_RESOLVER_PRINTHANDLER_HPP
