#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>


void show_baud(int speed) {
    switch (speed) {
        case B110:    printf("110");    break;
        case B300:    printf("300");    break;
        case B600:    printf("600");    break;
        case B1200:   printf("1200");   break;
        case B1800:   printf("1800");   break;
        case B2400:   printf("2400");   break;
        case B4800:   printf("4800");   break;
        case B9600:   printf("9600");   break;
        case B19200:  printf("19200");  break;
        case B38400:  printf("38400");  break;
        case B57600:  printf("57600");  break;
        case B115200: printf("115200"); break;
        default:      printf("fast");   break;                // Can't be bothered past this point
    }
}

void show_flag(tcflag_t term_flag, int def_flag, char *str_flag) {
    char minus = ' ';
    if ((term_flag & def_flag) == 0) minus = '-';
    printf("%c%s ", minus, str_flag);
}



int main (int argc, char** argv)
{
    struct termios term;
    if (argc == 1) {
        printf("speed ");
        show_baud(cfgetospeed(&term));
        printf(" baud; line = %d\n",term.c_line);
    } else if (argc == 2) {
        if (strcmp(argv[1], "-a") == 0) {
            printf("speed ");
            show_baud(cfgetospeed(&term));
            printf(" baud; line = %d\n",term.c_line);
            show_flag(term.c_iflag, IGNBRK, "ignbrk");
            show_flag(term.c_iflag, BRKINT, "brkint");
            show_flag(term.c_iflag, IGNPAR, "ignpar");
            show_flag(term.c_iflag, PARMRK, "parmrk");
            show_flag(term.c_iflag, INPCK, "inpck");
            show_flag(term.c_iflag, ISTRIP, "istrip");
            show_flag(term.c_iflag, INLCR, "inlcr");
            show_flag(term.c_iflag, IGNCR, "igncr");
            show_flag(term.c_iflag, ICRNL, "icrnl");
            show_flag(term.c_iflag, IUCLC, "iuclc");
            show_flag(term.c_iflag, IXON, "ixon");
            show_flag(term.c_iflag, IXANY, "ixany");
            show_flag(term.c_iflag, IXOFF, "ixoff");
            show_flag(term.c_iflag, IMAXBEL, "imaxbel");
            show_flag(term.c_iflag, IUTF8, "iutf8");
            printf("\n");
            show_flag(term.c_lflag, ISIG, "isig");
            show_flag(term.c_lflag, ICANON, "icanon");
            show_flag(term.c_lflag, XCASE, "xcase");
            show_flag(term.c_lflag, ECHO, "echo");
            show_flag(term.c_lflag, ECHOE, "echoe");
            show_flag(term.c_lflag, ECHOK, "echok");
            show_flag(term.c_lflag, ECHONL, "echonl");
            show_flag(term.c_lflag, NOFLSH, "noflsh");
            show_flag(term.c_lflag, TOSTOP, "tostop");
            show_flag(term.c_lflag, ECHOCTL, "echoctl");
            show_flag(term.c_lflag, ECHOPRT, "echoprt");
            show_flag(term.c_lflag, ECHOKE, "echoke");
            show_flag(term.c_lflag, FLUSHO, "flusho");
            show_flag(term.c_lflag, PENDIN, "pendin");
            show_flag(term.c_lflag, IEXTEN, "iexten");
            show_flag(term.c_lflag, EXTPROC, "extproc");
        } else if (strcmp(argv[1], "-g") == 0) {
            printf("%x:", term.c_cflag);
            printf("%x:", term.c_lflag);
            printf("%x:", term.c_iflag);
            printf("%x:", term.c_oflag);
        } else {
            char flag[100];
            int minus = (argv[1][0] == '-');
            if (minus) memcpy(flag, &argv[1][1], strlen(argv[1]) - 1);
            else memcpy(flag, &argv[1][0], strlen(argv[1]));

            if (strcmp(flag, "isig") == 0) {
                if (minus) term.c_lflag &= ~ISIG;
                else term.c_lflag |= ISIG;
            }
            if (strcmp(flag, "icanon") == 0) {
                if (minus) term.c_lflag &= ~ICANON;
                else term.c_lflag |= ICANON;
            }
            if (strcmp(flag, "xcase") == 0) {
                if (minus) term.c_lflag &= ~XCASE;
                else term.c_lflag |= XCASE;
            }
            if (strcmp(flag, "echo") == 0) {
                if (minus) term.c_lflag &= ~ECHO;
                else term.c_lflag |= ECHO;
            }
            if (strcmp(flag, "echoe") == 0) {
                if (minus) term.c_lflag &= ~ECHOE;
                else term.c_lflag |= ECHOE;
            }
            if (strcmp(flag, "echok") == 0) {
                if (minus) term.c_lflag &= ~ECHOK;
                else term.c_lflag |= ECHOK;
            }
            if (strcmp(flag, "echonl") == 0) {
                if (minus) term.c_lflag &= ~ECHONL;
                else term.c_lflag |= ECHONL;
            }
            if (strcmp(flag, "noflsh") == 0) {
                if (minus) term.c_lflag &= ~NOFLSH;
                else term.c_lflag |= NOFLSH;
            }
            if (strcmp(flag, "tostop") == 0) {
                if (minus) term.c_lflag &= ~TOSTOP;
                else term.c_lflag |= TOSTOP;
            }
            if (strcmp(flag, "echoctl") == 0) {
                if (minus) term.c_lflag &= ~ECHOCTL;
                else term.c_lflag |= ECHOCTL;
            }
            if (strcmp(flag, "echoprt") == 0) {
                if (minus) term.c_lflag &= ~ECHOPRT;
                else term.c_lflag |= ECHOPRT;
            }
            if (strcmp(flag, "echoke") == 0) {
                if (minus) term.c_lflag &= ~ECHOKE;
                else term.c_lflag |= ECHOKE;
            }
            if (strcmp(flag, "flusho") == 0) {
                if (minus) term.c_lflag &= ~FLUSHO;
                else term.c_lflag |= FLUSHO;
            }
            if (strcmp(flag, "pendin") == 0) {
                if (minus) term.c_lflag &= ~PENDIN;
                else term.c_lflag |= PENDIN;
            }
            if (strcmp(flag, "iexten") == 0) {
                if (minus) term.c_lflag &= ~IEXTEN;
                else term.c_lflag |= IEXTEN;
            }
            if (strcmp(flag, "extproc") == 0) {
                if (minus) term.c_lflag &= ~EXTPROC;
                else term.c_lflag |= EXTPROC;
            }
            if (strcmp(flag, "ignbrk") == 0) {
                if (minus) term.c_iflag &= ~IGNBRK;
                else term.c_iflag |= IGNBRK;
            }
            if (strcmp(flag, "brkint") == 0) {
                if (minus) term.c_iflag &= ~BRKINT;
                else term.c_iflag |= BRKINT;
            }
            if (strcmp(flag, "ignpar") == 0) {
                if (minus) term.c_iflag &= ~IGNPAR;
                else term.c_iflag |= IGNPAR;
            }
            if (strcmp(flag, "parmrk") == 0) {
                if (minus) term.c_iflag &= ~PARMRK;
                else term.c_iflag |= PARMRK;
            }
            if (strcmp(flag, "inpck") == 0) {
                if (minus) term.c_iflag &= ~INPCK;
                else term.c_iflag |= INPCK;
            }
            if (strcmp(flag, "istrip") == 0) {
                if (minus) term.c_iflag &= ~ISTRIP;
                else term.c_iflag |= ISTRIP;
            }
            if (strcmp(flag, "inlcr") == 0) {
                if (minus) term.c_iflag &= ~INLCR;
                else term.c_iflag |= INLCR;
            }
            if (strcmp(flag, "igncr") == 0) {
                if (minus) term.c_iflag &= ~IGNCR;
                else term.c_iflag |= IGNCR;
            }
            if (strcmp(flag, "icrnl") == 0) {
                if (minus) term.c_iflag &= ~ICRNL;
                else term.c_iflag |= ICRNL;
            }
            if (strcmp(flag, "iuclc") == 0) {
                if (minus) term.c_iflag &= ~IUCLC;
                else term.c_iflag |= IUCLC;
            }
            if (strcmp(flag, "ixon") == 0) {
                if (minus) term.c_iflag &= ~IXON;
                else term.c_iflag |= IXON;
            }
            if (strcmp(flag, "ixany") == 0) {
                if (minus) term.c_iflag &= ~IXANY;
                else term.c_iflag |= IXANY;
            }
            if (strcmp(flag, "ixoff") == 0) {
                if (minus) term.c_iflag &= ~IXOFF;
                else term.c_iflag |= IXOFF;
            }
            if (strcmp(flag, "imaxbel") == 0) {
                if (minus) term.c_iflag &= ~IMAXBEL;
                else term.c_iflag |= IMAXBEL;
            }
            if (strcmp(flag, "iutf8") == 0) {
                if (minus) term.c_iflag &= ~IUTF8;
                else term.c_iflag |= IUTF8;
            }
            if (strcmp(flag, "csize") == 0) {
                if (minus) term.c_cflag &= ~CSIZE;
                else term.c_cflag |= CSIZE;
            }
            if (strcmp(flag, "cs5") == 0) {
                if (minus) term.c_cflag &= ~CS5;
                else term.c_cflag |= CS5;
            }
            if (strcmp(flag, "cs6") == 0) {
                if (minus) term.c_cflag &= ~CS6;
                else term.c_cflag |= CS6;
            }
            if (strcmp(flag, "cs7") == 0) {
                if (minus) term.c_cflag &= ~CS7;
                else term.c_cflag |= CS7;
            }
            if (strcmp(flag, "cs8") == 0) {
                if (minus) term.c_cflag &= ~CS8;
                else term.c_cflag |= CS8;
            }
            if (strcmp(flag, "cstopb") == 0) {
                if (minus) term.c_cflag &= ~CSTOPB;
                else term.c_cflag |= CSTOPB;
            }
            if (strcmp(flag, "cread") == 0) {
                if (minus) term.c_cflag &= ~CREAD;
                else term.c_cflag |= CREAD;
            }
            if (strcmp(flag, "parenb") == 0) {
                if (minus) term.c_cflag &= ~PARENB;
                else term.c_cflag |= PARENB;
            }
            if (strcmp(flag, "parodd") == 0) {
                if (minus) term.c_cflag &= ~PARODD;
                else term.c_cflag |= PARODD;
            }
            if (strcmp(flag, "hupcl") == 0) {
                if (minus) term.c_cflag &= ~HUPCL;
                else term.c_cflag |= HUPCL;
            }
            if (strcmp(flag, "clocal") == 0) {
                if (minus) term.c_cflag &= ~CLOCAL;
                else term.c_cflag |= CLOCAL;
            }

            tcsetattr(STDIN_FILENO, TCSANOW, &term);
        }
    }

    return 0;
}
