#include <stdio.h>
#include "bin/headers/CustomHeader.h"
#include "bin/Currency.c"
#include "bin/AutoCheck.c"
#include "bin/MyHistory.c"

void cMenu();
void cHead();

int main()
{
    char ch, ch2;
    saveDefaultColor();
stMenu:
    cls();
    cHead();
    cMenu();
STINP:
    setColor(LIGHTGREEN);
    printf("\n     --> Input Option: ");
    resetColor();
    ch = getch();
    if (ch == '1')
    {
        cls();
        CalculateCurrency();
        goto stMenu;
    }
    else if (ch == '2')
    {
    autoCheck:
        cls();
        autoCheck();
        endOptAuto();
        hidecursor();
    autoCheckInp:
        ch2 = tolower(getch());
        if (ch2 == 'm')
        {
            showcursor();
            goto stMenu;
        }
        else if (ch2 == 'a')
        {
            showcursor();
            goto autoCheck;
        }
        else if (ch2 == 'x')
            exit(0);
        else
        {
            wrongInput();
            goto autoCheckInp;
        }
    }
    else if (ch == '3')
    {
        /* code */
    }
    else if (ch == '4')
    {
        cls();
        myHistory();
        goto stMenu;
    }
    else if (ch == 'x' || ch == 'X')
    {
        exit(0);
    }
    else
    {
        wrongInput();
        goto STINP;
    }
    return 0;
}

void cHead()
{
    setColor(LIGHTRED);
    printf("            ============================        \n");
    printf("            ||   Currency Converter   ||        \n");
    printf("            ============================        \n");
    resetColor();
}

void cMenu()
{
    setColor(LIGHTCYAN);
    printf("     ___________________________________________\n");
    printf("    |                                           |\n");
    setColor(LIGHTCYAN);
    printf("    |");
    resetColor();
    printf("       1. Convert Currency Live");
    setColor(LIGHTCYAN);
    printf("            |\n");
    printf("    |");
    resetColor();
    printf("       2. Automatic Rate Checking");
    setColor(LIGHTCYAN);
    printf("          |\n");
    printf("    |");
    resetColor();
    printf("       3. Currrency Rate History Live");
    setColor(LIGHTCYAN);
    printf("      |\n");
    printf("    |");
    resetColor();
    printf("       4. My History");
    setColor(LIGHTCYAN);
    printf("                       |\n");
    printf("    |");
    resetColor();
    printf("       x. Exit");
    setColor(LIGHTCYAN);
    printf("                             |\n");
    printf("    |___________________________________________|\n");
    resetColor();
}