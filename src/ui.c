#include <ui.h>
#include <signal.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <panel.h>

void init_ncurses();
void destroy_ncurses();
void init_draw_main(WINDOW* win_main);
void init_draw_register(WINDOW* window, EmString name, EmString desc);
void handle_input(WINDOW *win_main, WINDOW* win_filename);
void draw_register(WINDOW* window, EmData value, EmString name);
void draw_code(WINDOW* window, EmSize* size);
void init_draw_code(WINDOW* window, EmSize* size, EmData* code);
void init_draw_footer(WINDOW* window);
void init_draw_control(WINDOW* window);
void draw_control(WINDOW* window);
void restart();
void dump_memory();
void init_draw_memory(WINDOW* window);
void draw_memory(WINDOW* window);
void init_draw_alu(WINDOW* window);
void draw_alu(WINDOW* window);
void draw_mux2x1(WINDOW* window, EmData* data);
void draw_mux4x1(WINDOW* window, EmData* data); 

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
EmData cu_elem[BUFFER_SIZE_CU_CELEM];
EmData mem_elem[BUFFER_SIZE_MEM_CELEM];
EmData alu_elem[4];
EmData mux2x1_elem[4];
EmData mux4x1_elem[6];


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

    int comp_x = width - (comp_width*2 + 2*gap_x), comp_y = gap_y + 2;

    int code_win_height = height - 18, code_win_width = 50;
    int code_win_x = gap_x, code_win_y = 12 + gap_y;

    WINDOW* win_ra = newwin(comp_height, comp_width, comp_y, comp_x);
    WINDOW* win_rb = newwin(comp_height, comp_width, comp_y, comp_x + comp_width + gap_x);
    WINDOW* win_pc = newwin(comp_height, comp_width, comp_y + comp_height + gap_y, comp_x);
    WINDOW* win_sp = newwin(comp_height, comp_width, comp_y + comp_height + gap_y, comp_x + comp_width + gap_x);
    WINDOW* code_window = newwin(code_win_height, code_win_width, code_win_y, code_win_x);
    WINDOW* win_filename = newwin(5, 40, height - 10, 6);
    WINDOW* footer = newwin(2, 80, height - 2, width-80);
    WINDOW* control = newwin(comp_height*2 + 2, comp_width*2 + gap_x, comp_y + 2*comp_height + 2*gap_y, comp_x);
    WINDOW* alu = newwin(comp_height, comp_width, comp_y + comp_height + gap_y, comp_x - 40);
    WINDOW* memory = newwin(comp_height, comp_width, comp_y, comp_x - 40);
    WINDOW* mux2x1 = newwin(comp_height, comp_width, comp_y + 2*comp_height + 2*gap_y, comp_x - 40);
    WINDOW* mux4x1 = newwin(comp_height, comp_width, comp_y + 3*comp_height + 3*gap_y, comp_x - 40);


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
    init_draw_control(control);
    init_draw_memory(memory);
    init_draw_alu(alu);
    draw_mux2x1(mux2x1, mux2x1_elem);
    draw_mux4x1(mux4x1, mux4x1_elem);


    timeout(100);

    while (1) {
        draw_register(win_ra, val_regA, "Register A");
        draw_register(win_rb, val_regB, "Register B");
        draw_register(win_pc, val_pc, "Program Counter");
        draw_register(win_sp, val_sp, "Stack Pointer");
        draw_code(code_window, &data);
        init_draw_control(control);
        draw_memory(memory);
        draw_alu(alu);
        draw_mux2x1(mux2x1, mux2x1_elem);
        draw_mux4x1(mux4x1, mux4x1_elem);

        handle_input(win_main, win_filename);
    }

    destroy_ncurses();
    return EXIT_SUCCESS;
}

/**
* Initialise the ncurses library
******************************************* */
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
        init_pair(UI_COLOR_PAIR_4, COLOR_CYAN, COLOR_BLACK);
        init_pair(UI_COLOR_PAIR_5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(UI_COLOR_PAIR_6, COLOR_BLACK, COLOR_WHITE);
        init_pair(UI_COLOR_PAIR_7, COLOR_WHITE, COLOR_BLUE);
        init_pair(UI_COLOR_PAIR_8, COLOR_WHITE, COLOR_RED);
        init_pair(UI_COLOR_PAIR_9, COLOR_WHITE, COLOR_GREEN);
        init_pair(UI_COLOR_PAIR_10, COLOR_WHITE, COLOR_CYAN);
        init_pair(UI_COLOR_PAIR_11, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(UI_COLOR_PAIR_12, COLOR_WHITE, COLOR_YELLOW);
    }
}

void destroy_ncurses() {
    endwin();
}

/**
 * Drawing Functions for Components
 ****************************************/

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
    snprintf(buf, sizeof(buf), "LSD Emulator");
    mvwprintw(win_main, 10, 4, buf);

    wattron(win_main, COLOR_PAIR(UI_COLOR_PAIR_7));
    int x = 4, y = 0;
    mvwprintw(win_main, y+8,  x+65, " ");
    mvwprintw(win_main, y+9,  x+65, " ");
    mvwprintw(win_main, y+10, x+65, " ");
    mvwprintw(win_main, y+11, x+65, " ");
    mvwprintw(win_main, y+12, x+65, " ");
    mvwprintw(win_main, y+13, x+65, " ");
    mvwprintw(win_main, y+14, x+65, " ");
    mvwprintw(win_main, y+15, x+65, " ");
    mvwprintw(win_main, y+16, x+65, " ");
    mvwprintw(win_main, y+16, x+65, " ");
    mvwprintw(win_main, y+17, x+65, " ");
    mvwprintw(win_main, y+18, x+65, " ");
    mvwprintw(win_main, y+18, x+66, " ");
    mvwprintw(win_main, y+18, x+67, " ");
    mvwprintw(win_main, y+18, x+68, " ");
    mvwprintw(win_main, y+18, x+69, " ");
    mvwprintw(win_main, y+18, x+70, " ");
    mvwprintw(win_main, y+18, x+71, " ");
    mvwprintw(win_main, y+18, x+72, " ");
    mvwprintw(win_main, y+18, x+73, " ");
    mvwprintw(win_main, y+18, x+74, " ");
    mvwprintw(win_main, y+18, x+75, " ");
    mvwprintw(win_main, y+18, x+76, " ");
    mvwprintw(win_main, y+18, x+77, " ");
    mvwprintw(win_main, y+18, x+78, " ");
    wattroff(win_main, COLOR_PAIR(UI_COLOR_PAIR_7));
    wattron(win_main, COLOR_PAIR(UI_COLOR_PAIR_11));
    x = -2;
    mvwprintw(win_main, y+14, x+65, " ");
    mvwprintw(win_main, y+14, x+66, " ");
    mvwprintw(win_main, y+14, x+67, " ");
    mvwprintw(win_main, y+14, x+68, " ");
    mvwprintw(win_main, y+14, x+69, " ");
    mvwprintw(win_main, y+14, x+70, " ");
    mvwprintw(win_main, y+14, x+71, " ");
    mvwprintw(win_main, y+14, x+72, " ");
    mvwprintw(win_main, y+14, x+73, " ");
    mvwprintw(win_main, y+14, x+74, " ");
    mvwprintw(win_main, y+14, x+75, " ");
    mvwprintw(win_main, y+14, x+76, " ");
    mvwprintw(win_main, y+14, x+77, " ");
    mvwprintw(win_main, y+14, x+78, " ");
    mvwprintw(win_main, y+15, x+65, " ");
    EmInt i;
    for (i = 0; i < 6; i++) {
        mvwprintw(win_main, y+15+i, x+65, " ");
    }
    for (i = 0; i < 14; i++) {
        mvwprintw(win_main, y+20, x+65+i, " ");
    }
    for (i = 0; i < 6; i++) {
        mvwprintw(win_main, y+20+i, x+65+13, " ");
    }
    for (i = 0; i < 14; i++) {
        mvwprintw(win_main, y+25, x+65+i, " ");
    }
    x = 4;
    wattroff(win_main, COLOR_PAIR(UI_COLOR_PAIR_11));
    wattron(win_main, COLOR_PAIR(UI_COLOR_PAIR_12));
    for (i = 0; i < 10; i++) {
        mvwprintw(win_main, y+23+i, x+65, " ");
    }
    for (i = 0; i < 13; i++) {
        mvwprintw(win_main, y+32, x+65+i, " ");
    }
    for (i = 0; i < 8; i++) {
        mvwprintw(win_main, y+24+i, x+78, " ");
    }
    for (i = 0; i < 13; i++) {
        mvwprintw(win_main, y+23, x+65+i, " ");
    }
    wattroff(win_main, COLOR_PAIR(UI_COLOR_PAIR_12));

    char* text = "\"From a rock fallen to the depth\"";
    char* line2 = "\"echoes the call of revelation\"";
    char* line3 = "\"arcane are named those breath\"";
    char* line4 = "\"plenty of weeds and fishes in the ocean\"";
    int col1 = 80 - strlen(text) / 2;
    int col2 = 80 - strlen(line2) / 2;
    int col3 = 80 - strlen(line3) / 2;
    int col4 = 80 - strlen(line4) / 2;
    wattron(win_main, A_BOLD);
    wattron(win_main, COLOR_PAIR(UI_COLOR_PAIR_5));
    mvwprintw(win_main, 38, col1, text);
    mvwprintw(win_main, 39, col2, line2);
    mvwprintw(win_main, 40, col3, line3);
    mvwprintw(win_main, 41, col4, line4);
    wattroff(win_main, COLOR_PAIR(UI_COLOR_PAIR_5));
    wattron(win_main, COLOR_PAIR(UI_COLOR_PAIR_4));
    mvwprintw(win_main, 43, 80, "- Developer");
    wattroff(win_main, COLOR_PAIR(UI_COLOR_PAIR_4));
    wattroff(win_main, A_BOLD);

    wrefresh(win_main);
}

void init_draw_register(WINDOW* window, EmString name, EmString desc) {
    wclear(window);

    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_2));
    wattron(window, A_BOLD);
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_8));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_8));
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
    wattron(window, A_BOLD);
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_10));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_10));
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_5));
    mvwprintw(window, 2, 2, "CODE SECTION");
    wattroff(window, A_BOLD);
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_5));

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
            mvwprintw(window, 5 + iter, 12, "0x%08x", iter + index);
            wattron(window, COLOR_PAIR(UI_COLOR_PAIR_4));
            mvwprintw(window, 5 + iter, 26, "0x%08x", buffer[iter + index]);
            wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_4));
        }

        wattron(window, WA_ITALIC);
        wattron(window, WA_BOLD);
        mvwprintw(window, 2, 20, filename);
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

void init_draw_control(WINDOW* window) {

    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_9));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_9));
    wattron(window, A_BOLD);
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_6));    
    mvwprintw(window, 2, 2, "\t%-*s %-*s", 38, "Control Unit", 26, "Status");
    wattroff(window, A_BOLD);
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_6));

    mvwprintw(window, 3, 2, "\t%-*s %-*d", 38, "ALU SEL", 26, cu_elem[INDEX_PORT_CU_ALU_SEL]);
    mvwprintw(window, 4, 2, "\t%-*s %-*d", 38, "IMM VAL", 26, cu_elem[INDEX_PORT_CU_IMM]);
    mvwprintw(window, 5, 2, "\t%-*s %-*d", 38, "MUX A IN", 26, cu_elem[INDEX_PORT_CU_MUX_A_IN]);
    mvwprintw(window, 6, 2, "\t%-*s %-*d", 38, "MUX MEM IN", 26, cu_elem[INDEX_PORT_CU_MUX_MEM_IN]);
    mvwprintw(window, 7, 2, "\t%-*s %-*d", 38, "MUX ALU A", 26, cu_elem[INDEX_PORT_CU_MUX_ALU_A]);
    mvwprintw(window, 8, 2, "\t%-*s %-*d", 38, "MUX ALU B", 26, cu_elem[INDEX_PORT_CU_MUX_ALU_B]);
    mvwprintw(window, 9, 2, "\t%-*s %-*d", 38, "W EN MEM", 26, cu_elem[INDEX_PORT_CU_W_EN_MEM]);
    mvwprintw(window, 10, 2, "\t%-*s %-*d", 38, "W EN PC", 26, cu_elem[INDEX_PORT_CU_W_EN_PC]);
    mvwprintw(window, 11, 2, "\t%-*s %-*d", 38, "W EN A", 26, cu_elem[INDEX_PORT_CU_W_EN_A]);
    mvwprintw(window, 12, 2, "\t%-*s %-*d", 38, "MUX PC IN", 26, cu_elem[INDEX_PORT_CU_MUX_PC_IN]);
    mvwprintw(window, 13, 2, "\t%-*s %-*d", 38, "MUX BR", 26, cu_elem[INDEX_PORT_CU_MUX_BR]);
    mvwprintw(window, 14, 2, "\t%-*s %-*d", 38, "MUX BR FINE", 26, cu_elem[INDEX_PORT_CU_MUX_BR_FINE]);
    mvwprintw(window, 15, 2, "\t%-*s %-*d", 38, "W EN SP", 26, cu_elem[INDEX_PORT_CU_W_EN_SP]);
    mvwprintw(window, 16, 2, "\t%-*s %-*d", 38, "W EN B", 26, cu_elem[INDEX_PORT_CU_W_EN_B]);
    mvwprintw(window, 17, 2, "\t%-*s %-*d", 38, "W EN A", 26, cu_elem[INDEX_PORT_CU_W_EN_A]);
    mvwprintw(window, 18, 2, "\t%-*s %-*d", 38, "W EN PC", 26, cu_elem[INDEX_PORT_CU_W_EN_PC]);
    mvwprintw(window, 19, 2, "\t%-*s %-*d", 38, "W EN MEM", 26, cu_elem[INDEX_PORT_CU_W_EN_MEM]);

    wrefresh(window);
}


void draw_control(WINDOW* window) {
    wattron(window, WA_BOLD);
    mvwprintw(window, 2, 2, "Control Unit");
    wattroff(window, WA_BOLD);
    wrefresh(window);
}

void init_draw_alu(WINDOW* window) {
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    wattron(window, A_UNDERLINE);
    wattron(window, WA_BOLD);
    mvwprintw(window, 2, 2, "ALU");
    wattroff(window, WA_BOLD);
    wattroff(window, A_UNDERLINE);
    wrefresh(window);
}

void draw_alu(WINDOW* window) {
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    EmInt i;
    EmInt j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 32; j++) {
            mvwprintw(window, 4 + i, 2+j, " ");
        }
    }
    mvwprintw(window, 4, 2, "ALU A: %d", alu_elem[0]);
    mvwprintw(window, 5, 2, "ALU B: %d", alu_elem[1]);
    mvwprintw(window, 6, 2, "ALU OUT: %d", alu_elem[3]);
    mvwprintw(window, 7, 2, "ALU SEL: %d", alu_elem[2]);
    wrefresh(window);
}

void init_draw_memory(WINDOW* window) {
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    wattroff(window, A_UNDERLINE);
    wattron(window, A_BOLD);
    wattron(window, A_UNDERLINE);
    mvwprintw(window, 2, 2, "MEMORY");
    wattron(window, A_UNDERLINE);
    wattroff(window, A_BOLD);
    wrefresh(window);
}

void draw_memory(WINDOW* window) {
    wattroff(window, A_UNDERLINE);
    wattroff(window, A_BOLD);
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_11));
    /* Delete all the present values*/
    EmInt i;
    EmInt j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 32; j++) {
            mvwprintw(window, 4 + i, 2+j, " ");
        }
    }
    mvwprintw(window, 4, 2, "OUT A : %d", mem_elem[INDEX_PORT_MEM_DOUT_A]);
    mvwprintw(window, 4, 18, "RADDR A : %d", mem_elem[INDEX_PORT_MEM_RADDR_A]);
    mvwprintw(window, 5, 2, "OUT B : %d", mem_elem[INDEX_PORT_MEM_DOUT_B]);
    mvwprintw(window, 5, 18, "RADDR B : %d", mem_elem[INDEX_PORT_MEM_RADDR_B]);
    mvwprintw(window, 6, 2, "IN : %d", mem_elem[INDEX_PORT_MEM_DIN]);
    mvwprintw(window, 6, 18, "WEN : %d", mem_elem[INDEX_PORT_MEM_WEN]);
    mvwprintw(window, 7, 2, "WADDR : %d", mem_elem[INDEX_PORT_MEM_WADDR]);

    wrefresh(window);
}

void draw_mux2x1(WINDOW* window, EmData* data) {
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_12));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_12));
    wattron(window, A_UNDERLINE);
    wattron(window, WA_BOLD);
    mvwprintw(window, 2, 2, "MUX 2X1 M in");
    wattroff(window, WA_BOLD);
    wattroff(window, A_UNDERLINE);
    EmInt i;
    EmInt j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 32; j++) {
            mvwprintw(window, 4 + i, 2+j, " ");
        }
    }
    mvwprintw(window, 4, 2, "IN 0 : %d", data[INDEX_PORT_MUX_2X1_IN_0]);
    mvwprintw(window, 4, 18, "IN 1 : %d", data[INDEX_PORT_MUX_2X1_IN_1]);
    mvwprintw(window, 5, 2, "OUT : %d", data[INDEX_PORT_MUX_2X1_OUT]);
    mvwprintw(window, 5, 18, "SEL : %d", data[INDEX_PORT_MUX_2X1_SEL]);
    wrefresh(window);
}

void draw_mux4x1(WINDOW* window, EmData* data) {
    wattron(window, COLOR_PAIR(UI_COLOR_PAIR_12));
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(window, COLOR_PAIR(UI_COLOR_PAIR_12));
    wattron(window, A_UNDERLINE);
    wattron(window, WA_BOLD);
    mvwprintw(window, 2, 2, "MUX 4X1 (A in)");
    wattroff(window, WA_BOLD);
    wattroff(window, A_UNDERLINE);
     EmInt i;
    EmInt j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 32; j++) {
            mvwprintw(window, 4 + i, 2+j, " ");
        }
    }
    mvwprintw(window, 4, 2, "IN 0 : %d", data[INDEX_PORT_MUX_4X1_IN_0]);
    mvwprintw(window, 4, 18, "IN 1 : %d", data[INDEX_PORT_MUX_4X1_IN_1]);
    mvwprintw(window, 5, 2, "IN 2 : %d", data[INDEX_PORT_MUX_4X1_IN_2]);
    mvwprintw(window, 5, 18, "IN 3 : %d", data[INDEX_PORT_MUX_4X1_IN_3]);
    mvwprintw(window, 6, 2, "OUT : %d", data[INDEX_PORT_MUX_4X1_OUT]);
    mvwprintw(window, 6, 18, "SEL : %d", data[INDEX_PORT_MUX_4X1_SEL]);
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

void update_alu() {
    EmErr err = api->get(api, TYPE_CELEM_ALU, alu_elem);
    if (err != SUCCESS) {
        show_error_window("Failed to get ALU elements");
    }
}

void update_memory() {
    EmErr err = api->get(api, TYPE_CELEM_MEM, mem_elem);
    if (err != SUCCESS) {
        show_error_window("Failed to get memory elements");
    }
}

void update_control_unit() {
    EmErr err = api->get(api, TYPE_CELEM_CU, cu_elem);
    if (err != SUCCESS) {
        char buf[512];
        snprintf(buf, sizeof(buf), "Failed to get CU elements %d", err);
        show_error_window(buf);
    }
}

void update_mux2x1() {
    EmErr err = api->get(api, TYPE_CELEM_MUX_2X1, mux2x1_elem);
    if (err != SUCCESS) {
        show_error_window("Failed to get MUX 2X1 elements");
    }
}

void update_mux4x1() {
    EmErr err = api->get(api, TYPE_CELEM_MUX_4X1, mux4x1_elem);
    if (err != SUCCESS) {
        show_error_window("Failed to get MUX 4X1 elements");
    }
}

void right_handler() {
    if (state == STATUS_HALT) {
        show_message_window("Program Halted");
        return;
    }
    if (api != NULL) {
        EmData data;
        EmErr err = api->clock(api, 1);
        update_control_unit();
        update_alu();
        update_memory();
        update_mux2x1();
        update_mux4x1();
        if (err != SUCCESS) {
            if (err == STATUS_PROG_HALT) {
                show_message_window("Program Halted");
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

void burst_mode() {
    int ch = 0;
    timeout(2000);
    show_message_window("Enter the number of clock cycles to burst");
    timeout(10000);
    ch = getch();

    if (isalnum(ch)) {
        int count = ch - '0';
        int iter;
        for (iter = 0; iter < count; iter++) {
            right_handler();
            if (state == STATUS_HALT) {
                break;
            }
        }
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
            restart();
            break;
        case 'b':
            burst_mode();
            break;
        case 'd':
            dump_memory();
            break;
        default:
            break;
    }
}


void restart() {
    if (api == NULL) {
        show_error_window("Failed to initialize emulator API");
        return;
    }
    
    EmErr err = api->restart(api);

    if (err != SUCCESS) {
        show_error_window("Failed to reset the emulator");
        return;
    }
    read_all_elements();
    state = STATUS_RUNNING;
    update_control_unit();
    update_memory();
    update_alu();
    update_mux2x1();
    update_mux4x1();
    show_message_window("Emulator reset");
}

void dump_memory() {
    FILE* file = fopen("memory.dump", "w");
    if (file == NULL) {
        show_error_window("Failed to open file");
        return;
    }
    EmErr err = api->dump_mem(api, file);
    if (err != SUCCESS) {
        show_error_window("Failed to dump memory");
        return;
    }
    show_message_window("Memory dumped to file");
    fclose(file);
}

void init_draw_footer(WINDOW* footer) {
    int height, width;
    getmaxyx(stdscr, height, width);

    footer = newwin(2, 140, height - 3, (width - 140)/2);
    wattron(footer, A_BOLD);
    wattron(footer, COLOR_PAIR(UI_COLOR_PAIR_6));
    mvwprintw(footer, 0, 0, "  q: Quit | i: Load program | p: Run | r: Reset | b <int>: Burst | up: Code up | down: Code down | right: pulse | d: Dump memory  ");
    wattroff(footer, COLOR_PAIR(UI_COLOR_PAIR_6));
    wattroff(footer, A_BOLD);
    wrefresh(footer);
}
