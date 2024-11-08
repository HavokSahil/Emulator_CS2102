#include <ui.h>
#include <signal.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init_ncurses();
void destroy_ncurses();
void init_draw_main(WINDOW* win_main);
void init_draw_register(WINDOW* window, EmString name, EmString desc);
void handle_input(WINDOW *win_main, WINDOW* win_filename);
void draw_register(WINDOW* window, EmData value, EmString name);
void draw_code(WINDOW* window, EmSize* size);
void init_draw_code(WINDOW* window, EmSize* size, EmData* code);
void init_draw_footer(WINDOW* window);

#define STATUS_HALT 0
#define STATUS_RUNNING 1

API* api;
EmData* code;
EmSize index = 0;
char* filename;
EmSize filesize;

EmData val_regA;
EmData val_regB;
EmData val_pc;
EmData val_sp;
EmState state = STATUS_RUNNING;


int main(int argc, char *argv[]) {
    
    code = (EmData*)malloc(sizeof(EmData) * SIZE_MEM);
    filename = (char*)malloc(sizeof(char) * 512);

    if (code == NULL || filename == NULL)
        return EXIT_FAILURE;

    memset(code, 0, SIZE_MEM);

    init_ncurses();
    
    WINDOW *win_main = newwin(20, 80, 0, 0);

    int height, width;
    getmaxyx(stdscr, height, width);

    int comp_height = 10, comp_width = 35;
    int gap_x = 5;
    int gap_y = 2;

    int comp_x = width - (comp_width*2 + 2*gap_x), comp_y = gap_y;

    int code_win_height = height - 18, code_win_width = 50;
    int code_win_x = gap_x, code_win_y = 12 + gap_y;

    WINDOW* win_ra = newwin(comp_height, comp_width, comp_y, comp_x);
    WINDOW* win_rb = newwin(comp_height, comp_width, comp_y, comp_x + comp_width + gap_x);
    WINDOW* win_pc = newwin(comp_height, comp_width, comp_y + comp_height + gap_y, comp_x);
    WINDOW* win_sp = newwin(comp_height, comp_width, comp_y + comp_height + gap_y, comp_x + comp_width + gap_x);
    WINDOW* code_window = newwin(code_win_height, code_win_width, code_win_y, code_win_x);
    WINDOW* win_filename = newwin(5, 40, height - 10, 6);
    WINDOW* footer = newwin(2, 80, height - 2, width-80);

    EmErr err = get_api(&api);
    if (err != SUCCESS) {
        fprintf(stderr, "Error: Failed to initialize emulator API\n");
        return EXIT_FAILURE;
    }

    EmData data = 0;

    getch();

    init_draw_main(win_main);
    init_draw_register(win_ra, "Register A", "Accumulator Register named A");
    init_draw_register(win_rb, "Register B", "Not an accumulator register");
    init_draw_register(win_pc, "Program Counter", "Connected to the memory port A");
    init_draw_register(win_sp, "Stack Pointer", "Connected to the memory input");
    init_draw_code(code_window, &data, &data);
    init_draw_footer(footer);

    timeout(100);

    while (1) {
        draw_register(win_ra, val_regA, "Register A");
        draw_register(win_rb, val_regB, "Register B");
        draw_register(win_pc, val_pc, "Program Counter");
        draw_register(win_sp, val_sp, "Stack Pointer");
        draw_code(code_window, &data);
        handle_input(win_main, win_filename);
    }

    destroy_ncurses();
    return EXIT_SUCCESS;
}

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    timeout(100);
    keypad(stdscr, TRUE);
    if (has_colors()) {
        start_color();
        init_pair(UI_COLOR_PAIR_1, COLOR_RED, COLOR_BLACK);
        init_pair(UI_COLOR_PAIR_2, COLOR_GREEN, COLOR_BLACK);
        init_pair(UI_COLOR_PAIR_3, COLOR_WHITE, COLOR_BLUE);
        init_pair(UI_COLOR_PAIR_4, COLOR_CYAN, COLOR_BLACK);
        init_pair(UI_COLOR_PAIR_5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(UI_COLOR_PAIR_6, COLOR_BLACK, COLOR_WHITE);
    }
}

void destroy_ncurses() {
    endwin();
}

void init_draw_main(WINDOW* win_main) {
    wclear(win_main);

    int height, width;
    getmaxyx(stdscr, height, width);

    int padding_x = 2;
    int padding_y = 1;

    wresize(win_main, height - 2, width - 4);
    mvwin(win_main, 1, 2);
    
    wborder(win_main, '|', '|', '*', '_', '*', '*', '^', '^');

    char buf[512];
    wattron(win_main, COLOR_PAIR(UI_COLOR_PAIR_4));
    wattron(win_main, A_BOLD);
    snprintf(buf, sizeof(buf), "   _      ____    ____    ");
    mvwprintw(win_main, 1, 2, buf);
    snprintf(buf, sizeof(buf), "  |\"|    / __\"| u|  _\"\\   ");
    mvwprintw(win_main, 2, 2, buf);
    snprintf(buf, sizeof(buf), "U | | u <\\___ \//| | | |  ");
    mvwprintw(win_main, 3, 2, buf);
    snprintf(buf, sizeof(buf), " \\| |/__ u___) |U| |_| |\\ ");
    mvwprintw(win_main, 4, 2, buf);
    snprintf(buf, sizeof(buf), "  |_____||____/>>|____/ u ");
    mvwprintw(win_main, 5, 2, buf);
    snprintf(buf, sizeof(buf), "  //  \\\\  )(  (__)|||_    ");
    mvwprintw(win_main, 6, 2, buf);
    snprintf(buf, sizeof(buf), " (__) (__)(__)    (__)_)   ");
    mvwprintw(win_main, 7, 2, buf);
    snprintf(buf, sizeof(buf), " (_\")(\")(_)(__)    (__)_)  ");
    mvwprintw(win_main, 8, 2, buf);
    wattroff(win_main, COLOR_PAIR(UI_COLOR_PAIR_4));
    snprintf(buf, sizeof(buf), "LDS Emulator");
    mvwprintw(win_main, 10, 4, buf);
    wattroff(win_main, A_BOLD);

    wrefresh(win_main);
}

void init_draw_register(WINDOW* window, EmString name, EmString desc) {
    wclear(window);

    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_2));
    wattron(window, A_BOLD);
    wborder(window, '|', '|', '_', '$', '*', '*', '*', '*');
    wattron(window, A_UNDERLINE);
    mvwprintw(window, 2, 2, name);
    wattroff(window, A_UNDERLINE);
    wattron(window, A_ITALIC);
    mvwprintw(window, 5, 2, desc);
    wattroff(window, A_ITALIC);
    wattroff(window, A_BOLD);
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_2));

    wrefresh(window);
}

void init_draw_code(WINDOW* window, EmSize* size, EmData* code) {
    wclear(window);
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_2));
    wattron(window, A_BOLD);
    wborder(window, '|', '|', '_', '$', '.', '.', '.', '.');
    wattron(window, A_UNDERLINE);
    mvwprintw(window, 2, 2, "Code");
    wattroff(window, A_UNDERLINE);
    wattroff(window, A_BOLD);
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_2));

    wrefresh(window);
}

#define CODE_BUF_SIZE 100

void draw_code(WINDOW* window, EmSize* size) {

    static int cur = 0;
    static EmData* buffer = NULL;

    if (buffer == NULL) {
        buffer = (EmData*)malloc(sizeof(EmData) * CODE_BUF_SIZE);
    }

    if (cur != index) {
        /* Updated data */

        memset(buffer, 0, sizeof(EmData) * CODE_BUF_SIZE);

        memcpy(buffer, code+cur, (CODE_BUF_SIZE < SIZE_MEM - cur)? CODE_BUF_SIZE : SIZE_MEM - cur); 
        cur = index;

        wattron(window, WA_BOLD);
        EmSize iter;
        wattron(window, A_UNDERLINE);
        mvwprintw(window, 4, 12, "Address");
        mvwprintw(window, 4, 28, "Code");

        wattroff(window, A_UNDERLINE);
        for (iter = 0; iter < CODE_BUF_SIZE/4; iter++) {
            wattron(window, COLOR_PAIR(UI_COLOR_PAIR_1));
            mvwprintw(window, 5 + iter, 12, "0x%08x", iter + index);
            wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_1));
            wattron(window, COLOR_PAIR(UI_COLOR_PAIR_4));
            mvwprintw(window, 5 + iter, 26, "0x%08x", buffer[iter + index]);
            wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_4));

        }

        wattron(window, WA_ITALIC);
        wattron(window, WA_BOLD);
        mvwprintw(window, 2, 12, filename);
        wattroff(window, WA_BOLD);
        wattroff(window, WA_ITALIC);
        wrefresh(window);
    }

    wrefresh(window);
}

void draw_register(WINDOW* window, EmData value, EmString name) {
    wattron(window, WA_BOLD);
    mvwprintw(window, 3, 20, "0x%08x", value);
    wattroff(window, WA_BOLD);

    wrefresh(window);
}


char* take_filename_input(WINDOW* win_filename, char* buffer) {

    int height, width;
    wattron(win_filename, A_BOLD);
    wattron(win_filename, A_UNDERLINE);
    wattron(win_filename, COLOR_PAIR(UI_COLOR_PAIR_6));
    mvwprintw(win_filename, 2, 2, "Enter filename: ");
    wattroff(win_filename, A_UNDERLINE);
    wattroff(win_filename, A_BOLD);
    echo();
    wgetstr(win_filename, buffer);
    noecho();
    werase(win_filename);
    wrefresh(win_filename);
}

void show_error_window(const char *error_message) {
    int height = 5;
    int width = 40;
    int start_y = (LINES - height)/2;
    int start_x = (COLS - width)/2;
    
    WINDOW *error_win = newwin(height, width, start_y, start_x);
    box(error_win, 0, 0);
    
    wattron(error_win, A_BOLD);
    wattron(error_win, COLOR_PAIR(UI_COLOR_PAIR_1));
    mvwprintw(error_win, 2, 2, "Error: %s", error_message);

    wrefresh(error_win);
    wattroff(error_win, A_BOLD);
    wattroff(error_win, COLOR_PAIR(UI_COLOR_PAIR_1));

    timeout(10000);
    getch();
    timeout(10);

    werase(error_win);
    wrefresh(error_win);
    delwin(error_win);
}


void show_message_window(const char *message) {
    int height = 5;
    int width = 40;
    int start_y = (LINES - height)/2;
    int start_x = (COLS - width)/2;
    
    WINDOW *error_win = newwin(height, width, start_y, start_x);
    box(error_win, 0, 0);
    
    wattron(error_win, A_BOLD);
    wattron(error_win, COLOR_PAIR(UI_COLOR_PAIR_2));
    mvwprintw(error_win, 2, 2, "%s", message);

    wrefresh(error_win);
    wattroff(error_win, A_BOLD);
    wattroff(error_win, COLOR_PAIR(UI_COLOR_PAIR_2));

    timeout(800);
    getch();
    timeout(100);

    werase(error_win);
    wrefresh(error_win);
    delwin(error_win);
}

void open_file(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        show_error_window("Failed to open file");
        return;
    }
    memset(code, 0, SIZE_MEM);

    EmErr err = api->load(api, file);
    if (err != SUCCESS) {
        show_error_window("Failed to load program");
        return;
    }

    fseek(file, 0, SEEK_SET);

    fread(code, sizeof(EmData), SIZE_MEM, file);
    show_message_window("Program loaded successfully");

    /* update the code buffer with the contents of the file */
    fclose(file);
}

void read_all_elements() {
    EmErr err;
    err = api->get(api, TYPE_CELEM_RA, &val_regA);
    err = api->get(api, TYPE_CELEM_RB, &val_regB);
    err = api->get(api, TYPE_CELEM_PC, &val_pc);
    err = api->get(api, TYPE_CELEM_SP, &val_sp);        
}

void right_handler() {
    if (state == STATUS_HALT) {
        show_message_window("Program Halted");
        return;
    }
    if (api != NULL) {
        EmData data;
        EmErr err = api->clock(api, 1);
        if (err != SUCCESS) {
            if (err == STATUS_PROG_HALT) {
                show_message_window("Program halted");
                read_all_elements();
                state = STATUS_HALT;
               return;
            }
            else {
                show_error_window("Failed to clock the emulator");
                return;
            }
        }
        read_all_elements();
        show_message_window("Clock ticked");
        return;
    } else {
        show_error_window("Failed to initialize emulator API");
    }

}

void handle_input(WINDOW *win_main, WINDOW* win_filename) {

    int ch = getch();

    switch (ch) {
        case 'q':
            endwin();
            exit(0);
            break;
        case 'i':
            take_filename_input(win_filename, filename);
            if (api != NULL) {
                open_file(filename);
            } else {
                show_error_window("Failed to initialize emulator API");
            }
            break;
        case KEY_UP:
            index = ((int)index - 1 < 0)? 0 : index - 1;
            break;
        case KEY_DOWN:
            index = (index + 1 >= SIZE_MEM)? SIZE_MEM - 1 : index + 1;
            break;
        case 'p':
            break;
        case KEY_RIGHT:
            right_handler();
            break;
        case 'r':
            break;
        case 's':
            break;
        case 'l':
            break;
        default:
            break;
    }
}

void init_draw_footer(WINDOW* footer) {
    int height, width;
    getmaxyx(stdscr, height, width);

    footer = newwin(2, 150, height - 4, width-150);
    wattron(footer, A_BOLD);
    wattron(footer, COLOR_PAIR(UI_COLOR_PAIR_6));
    mvwprintw(footer, 0, 0, "    q: Quit | i: Load program | p: Run | r: Reset | s: Step | b <int>: Burst | up: Code up | down: Code down | right: Next");
    wattroff(footer, COLOR_PAIR(UI_COLOR_PAIR_6));
    wattroff(footer, A_BOLD);
    wrefresh(footer);
}
