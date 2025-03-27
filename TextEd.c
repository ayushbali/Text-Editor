#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// We are storing the terminal's original attributes into global variable
struct termios orig_termios;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    // then assigning this orig_termios struct to raw struct to make a copy of it before making changes
    struct termios raw = orig_termios;

    // turning off CTRL-S and CTRL-Q
    // CTRL-S => XOFF (pause transmission)
    // CTRL-Q => XON (resume transmission)
    // ICRNL => I - input flag, CR - Carriage return, NL - New Line
    raw.c_iflag &= ~(IXON | ICRNL);
    // ISIG turns off CTRL-C and CTRL-Z
    // IEXTEN turns off CTRL-V and CTRL-O
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 


    // raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(){
    
    enableRawMode();

    char c;
    // read() will read 1 byte from standard input store it into the variable c until there are no more bytes to read.
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        // if the key is a control key means CTRL-C or CTRL-V etc.. print the ascii value
        if(iscntrl(c)){
            printf("%d\n", c); 
        } else {
        // else print the ascii val and character
            printf("%d (Key: '%c')\n", c, c); 
        }
    } 
    


    return 0;

}