#include <stdio.h>
#include "bin/headers/CustomHeader.h"
#include "bin/Currency.c"
#include "bin/AutoCheck.c"
#include "bin/MyHistory.c"
#include "bin/CheckRateHistoryLive.c"

void cMenu();
void cHead();
// This function will read api from file, if failed it will return -1
int scanAPI();
// This function is to change api which also ask api if scanAPI() fails
void inputAPI();

//
// Main function of this project
int main()
{
    char ch, ch2;
    saveDefaultColor();
    // Checking api
apiCheck:
    system("TITLE Currency Converter v1.0.0");
    if (scanAPI() == -1)
    {
        inputAPI();
        goto apiCheck;
    }
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
        cls();
        checkRateHistoryLive();
        goto stMenu;
    }
    else if (ch == '4')
    {
        cls();
        myHistory();
        goto stMenu;
    }
    else if (ch == '5')
    {
        cls();
        inputAPI();
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

//
// Decoration Functions
//
// Main Header
void cHead()
{
    setColor(LIGHTRED);
    printf("            ============================        \n");
    printf("            ||   Currency Converter   ||        \n");
    printf("            ============================        \n");
    resetColor();
}

// Main Menu
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
    printf("       3. Currency Rate History Live");
    setColor(LIGHTCYAN);
    printf("       |\n");
    printf("    |");
    resetColor();
    printf("       4. My History");
    setColor(LIGHTCYAN);
    printf("                       |\n");
    printf("    |");
    resetColor();
    printf("       5. Change API Key");
    setColor(LIGHTCYAN);
    printf("                   |\n");
    printf("    |");
    resetColor();
    printf("       X. Exit");
    setColor(LIGHTCYAN);
    printf("                             |\n");
    printf("    |___________________________________________|\n");
    resetColor();
}

//
// Operational Functions
//
int scanAPI()
{
    FILE *apiFile;
    char apiLocation[128] = "bin/api.txt";
    ifFolderNotExist("bin");
    apiFile = fopen(apiLocation, "r");
    if (apiFile == NULL)
    {
        apiFile = fopen(apiLocation, "a+");
        fclose(apiFile);
        return -1;
    }
    fscanf(apiFile, "%s", &api);
    fclose(apiFile);
    if (strlen(api) == 0)
        return -1;
}

void inputAPI()
{
    cls();
    cHead();
    FILE *apiFile;
    char tmp[128] = "";
    char apiLocation[128] = "bin/api.txt";
    ifFolderNotExist("bin");
    printf("\n");
    if (strlen(api) == 0)
    {
        setColor(LIGHTRED);
        printf("                 API IS MISSING!!!\n");
        resetColor();
        printf(" You can get your own api from ");
        setColor(LIGHTBLUE);
        printf("https://free.currencyconverterapi.com\n\n");
        resetColor();
        printf(" Please Input Your API Key: ");
    }
    else
    {
        resetColor();
        printf(" Your Current API Key is ");
        setColor(LIGHTBLUE);
        printf("%s \n\n", api);
        resetColor();
        setColor(LIGHTCYAN);
        printf(" (Type 'cancel' to Cancel) \n");
        resetColor();
        printf(" Please Input New API Key: ");
    }
InputAPI:
    scanf("%s", &tmp);
    if (strlen(tmp) < 6 && strlen(tmp) > 127)
    {
        wrongInput();
        goto InputAPI;
    }
    else if (strcmp(strlwr(tmp), "cancel") == 0)
    {
        // Noting need to do.....
    }
    else
    {
        sprintf(api, "%s", tmp);
        apiFile = fopen(apiLocation, "w");
        fprintf(apiFile, "%s", api);
        fclose(apiFile);
    }
}