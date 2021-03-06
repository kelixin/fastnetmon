#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Init ncurses screen
    initscr();

    // disable any character output
    noecho();

    // hide cursor
    curs_set(0);

    // Do not wait for getch
    timeout(0);

    while (true) {
        sleep(1);

        // clean up screen
        clear();

        int c = getch();

        if (c == 'q') {
            endwin();
            exit(0);
        }

        std::ifstream reading_file;
        reading_file.open("/tmp/fastnetmon.dat", std::ifstream::in);

        if (!reading_file.is_open()) {
            std::cout << "Can't open fastnetmon stats file";
        }

        std::string line = "";
        std::stringstream screen_buffer;
        while (getline(reading_file, line)) {
            screen_buffer << line << "\n";
        }

        reading_file.close();

        printw(screen_buffer.str().c_str());
        // update screen
        refresh();
    }

    /* End ncurses mode */
    endwin();
}
