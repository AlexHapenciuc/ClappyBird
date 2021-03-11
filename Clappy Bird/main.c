#include "SDL.h"
#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "definitii.h"
#include "TDA.h"
#include "functii.h"


int main(int argc, char* argv[])
{
    int game_error = 0, ok=0;
    char nume[25], c;
    strcpy(nume, "default");
    JUCATOR player;
    do
    {
        system("cls");
        printf("1. Alege nume");
        printf("\n2. Incepe jocul");
        printf("\n3. Informatii joc");
        printf("\n4. Informatii autor");
        printf("\n5. Afiseaza scoruri");
        printf("\n0. Iesire joc");
        switch(c = getch())
        {
        case '1':
            system("cls");
            printf("Alege nume: ");
            scanf("%s", nume);
            break;
        case '2':
            system("cls");
            player = newJucator(nume, -1);
            ok=1;
            game_error = InitializareJoc(player);
            break;
        case '3':
            system("cls");
            printf("In jocul %c%s%c exista o simpla mecanica: ", '"',CLAPPY_GAME_NAME,'"');
            printf("jucatorul trebuie\nsa avanseze cu pasarea Clappy printre obstacole, "
                   "lucru care este\ningreunat de faptul ca aceasta pasare nu poate zbura corect.\nDeci "
                   "jucatorul trebuie prin apasarea space-ului sau butonului \nstang a mouse-ului"
                   "sa il tina pe Clappy in aer pentru cat mai mult timp. ");
            getch();
            break;
        case '4':
            system("cls");
            printf("Nume autor: Hapenciuc Alexandru-Vasile");
            printf("\nOcupatie: Student la FIESC, profilul Calculatoare din USV (GRUPA 3115A)");
            getch();
            break;
        case '5':
            system("cls");
            if(ok)
                AfiseazaScoruri(player, stdout);
            else printf("GOL");
            getch();
            break;
        default:
            if(c != '0')
            printf("\nNu exista optiunea selectata! ");
            getch();
        }

    }
    while(c != '0');

    return game_error;
}
