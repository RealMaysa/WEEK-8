#include <vector>
#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;

#define screen_x 80
#define screen_y 25

HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x-1,screen_y-1 };

struct positionship
{
    int x;
    int y;
}posship;

int score=0;
vector <int> starx,stary;

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console,&lpCursor);
}

int setConsole(int x, int y)
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    setcursor(0);
    return 0;
}
int setMode()
{
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
    ENABLE_MOUSE_INPUT;
    SetConsoleMode(rHnd, fdwMode);
    return 0;
}

void setcolor(int fg,int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg*16+fg);
}

void gotoxy(int x, int y)
{
    COORD c = {x,y};
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
void draw_ship(int x,int y,int color)
{
    gotoxy(x,y);
    setcolor(color,0);
    cout << "<->";
    setcursor(0);
}

void erase_ship(int x,int y)
{

    setcolor(0,0);
    COORD c={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cout << "     ";
    setcursor(0);
}

void board()
{
    gotoxy(65,0);
    setcolor(7,0);
    cout << "Your score : " << score;
    setcursor(0);
}

void draw_star(int x,int y)
{
    gotoxy(x,y);
    setcolor(7,0);
    cout << "*";
    setcursor(0);
}

char cursor(int x, int y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2];
    COORD c = {x,y};
    DWORD num_read;

    if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )   return '\0';
    else return buf[0];

}
void clear_star(int x,int y)
{
gotoxy(x,y); printf(" ");
}
int main()
 
{   setcursor(0);
    board();
    bool play = true;
    DWORD numEvents = 0;
    DWORD numEventsRead = 0;
    setConsole(screen_x, screen_y);
    setMode();
    int color=7;
    int posx=0;
    int posy=0;
    int star_x,star_y;
    srand(time(NULL));
for(int c=0;c<40;c++)
    {   
        star_x=rand()%80;
        star_y=rand()%25;
        if(star_y<1) star_y=1;
        if(star_x==79&&star_y==24) star_y=23;
        draw_star(star_x,star_y);
        starx.push_back(star_x);
        stary.push_back(star_y);
    }
    
    while (play)
    {
        GetNumberOfConsoleInputEvents(rHnd, &numEvents);
        if (numEvents != 0)
        {
            INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
            for (DWORD i = 0; i < numEventsRead; ++i)
            {
                if (eventBuffer[i].EventType == KEY_EVENT&&eventBuffer[i].Event.KeyEvent.bKeyDown == true )
                {
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)  play=false;
                    if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar=='c')
                    {   erase_ship(posship.x,posship.y);
                        color=rand() % 8;
                        if(color==0) color=7;
                        setcolor(color,0);
                        draw_ship(posx,posy,color);
                    }
                    
                }
                else if (eventBuffer[i].EventType == MOUSE_EVENT)
                {
                        posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
                        posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
                    if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                    {   erase_ship(posship.x,posship.y); 
                        color=rand() % 8;
                        if(color==0) color=7;
                        draw_ship(posx,posy,color);
                        
                    }
                    else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
                    {
                        erase_ship(posship.x,posship.y); 
                        if(posx>76)posx=76;
                        if(posy==24) posy=23;
                        if(posy<1) posy=1;
                        draw_ship(posx,posy,color);
                        posship.x=posx;
                        posship.y=posy;
                    }
                }
            }
            delete[] eventBuffer;
        }
        
                for(int c=0;c<40;c++)
                        { if(posship.x==starx[c]&&posship.y==stary[c]
                        ||posship.x+1==starx[c]&&posship.y==stary[c]
                        ||posship.x+2==starx[c]&&posship.y==stary[c]
                        ||posship.x+3==starx[c]&&posship.y==stary[c])
                            {   starx[c]=rand()%80;
                                starx[c]=rand()%25;
                                if(stary[c]<1) stary[c]=1;
                                if(starx[c]==79&&stary[c]==24) stary[c]=23;
                                draw_star(starx[c],stary[c]);
                                score++;
                                board(); }
                            
                            }
        if(score==10)
        {
            break;
        }
        Sleep(100);
        
        
    }
    
    return 0;
}