#include <iostream>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <conio.h>
using namespace std;
//----------------Variable Declaration-----------------//
int score = 0;
bool gameOver = true;
//---------Coordinates of Position of Pac-Man----------//
int pacmanX = 9;
int pacmanY = 31;
//---------Coordinates of Position of Ghost------------//
int ghostX = 19;
int ghostY = 25;

int gx1 = 11;                //   The ghost which is moving Verically
int gy1 = 58;

int gx2 = 16;                //   The ghost which is moving Horizontally
int gy2 = 53;

int gx3 = 2;                 // The intelligent ghost moving towards PacMan 
int gy3 = 28;

// we have done this so that ghost might eat food dots, so we have to store them in a variable before
char previousItem = ' ';
string gD1 = "up";
string gD2 = "right";
//-----------------Array of Maze------------------//
char maze[24][71] = {{"#####################################################################"},
                     {"||.. .....................................................  ......  ||"},
                     {"||.. %%%%%%%%%%%%%%%%       G...     %%%%%%%%%%%%%%  |%|..   %%%%   ||"},
                     {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
                     {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
                     {"||..        %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%     ..   %%%%.  ||"},
                     {"||..        |%|       . . |%|...    ............... |%| ..       .  ||"},
                     {"||..        %%%%%%%%%%. . |%|...    %%%%%%%%%%%%    |%| ..   %%%%.  ||"},
                     {"||..               |%|.             |%|......       |%| ..    |%|.  ||"},
                     {"||..     ......... |%|.        P    |%|......|%|        ..    |%|.  ||"},
                     {"||..|%|  |%|%%%|%|.|%|. |%|            ......|%|        ..|%| |%|.  ||"},
                     {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|        G.|%|.      ||"},
                     {"||..|%|  |%|   |%|..           ...|%|     %%%%%%        . |%|.      ||"},
                     {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
                     {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
                     {"||...............................................   |%| ..........  ||"},
                     {"||   ............................................ G        .......  ||"},
                     {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|    |%| ..|%|.      ||"},
                     {"||..|%|  |%|   |%|..           ...|%|     %%%%%%    |%| ..|%|.      ||"},
                     {"||..|%|            .     G     ...|%|               |%| ..|%|.      ||"},
                     {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
                     {"||...............................................   |%| ..........  ||"},
                     {"||  .............................................          .......  ||"},
                     {"##################################################################### "}};
//-----------------Function Prototypes-------------------//
void printMaze();
void storeMaze();
void loadMaze();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void calculateScore();
void printScore();
int ghostDirection();
bool ghostMovement();
bool moveGhost1();
bool moveGhost2();
bool moveGhostToPacman();
void gotoxy(int x, int y);
//------------------Main Body-------------------------//
main()
{
    storeMaze();
    system("cls");
    loadMaze();
    bool gameRunning = true;
    printMaze();
    while (gameRunning)
    {
        gameRunning = moveGhost1();
        gameRunning = moveGhost2();
        gameRunning = moveGhostToPacman();
        gameRunning = ghostMovement();
        printScore();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft(); // Function call to move Pacman towards left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight(); // Function call to move Pacman towards right
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp(); // Function call to move Pacman towards up
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown(); // Function call to move Pacman towards down
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; // Stop the game
        }
    }
}
void printMaze()
{
    cout << endl;
    cout << endl;
    cout << endl;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 71; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}
void storeMaze()
{
    fstream file;
    file.open("Maze.txt", ios::out);
    for (int i = 0; i < 24; i++)
    {
        file << maze[i];
        file << endl;
    }
    file.close();
}
void loadMaze()
{
    string line;
    fstream file;
    file.open("Maze.txt", ios::in);
    for (int i = 0; i < 24; i++)
    {
        getline(file, line);
        for (int j = 0; j < 71; j++)
        {
            maze[i][j] = line[j];
        }
    }
    file.close();
}
void movePacmanLeft()            
{                           
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] == '.')
    {

        gotoxy(pacmanY, pacmanX);
        cout << ' ';
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        gotoxy(pacmanY, pacmanX);
        cout << ' ';
    }
}
void movePacmanRight()
{
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.')
    {
       // maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << ' ';
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        gotoxy(pacmanY, pacmanX);
        cout << 'P';
    }
}
void movePacmanUp()
{
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.')
    {
        gotoxy(pacmanY, pacmanX);
        cout << ' ';
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        gotoxy(pacmanY, pacmanX);
        cout << 'P';
    }
}
void movePacmanDown()
{
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.')
    {
        gotoxy(pacmanY, pacmanX);
        cout << ' ';
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        //maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << 'P';
    }
}
void calculateScore()
{
    score = score + 1;
}
void printScore()
{
   // cout << endl << "Score: " << score << endl;
}
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}
bool ghostMovement()
{
    int value = ghostDirection();
    if (value == 1)
    {
        if (maze[ghostX][ghostY - 1] == ' ' || maze[ghostX][ghostY - 1] == '.' || maze[ghostX][ghostY - 1] == 'P')
        {
            gotoxy(ghostY,ghostX);
            cout << previousItem;
            ghostY = ghostY - 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(ghostY,ghostX);
            cout << 'G';
        }
    }
    if (value == 2)
    {
        if (maze[ghostX][ghostY + 1] == ' ' || maze[ghostX][ghostY + 1] == '.' || maze[ghostX][ghostY + 1] == 'P')
        {
            gotoxy(ghostY,ghostX);
            cout << previousItem;
            ghostY = ghostY + 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    if (value == 3)
    {
        if (maze[ghostX - 1][ghostY] == ' ' || maze[ghostX - 1][ghostY] == '.' || maze[ghostX - 1][ghostY] == 'P')
        {
            gotoxy(ghostY,ghostX);
            cout << previousItem;
            ghostX = ghostX - 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    if (value == 4)
    {
        if (maze[ghostX + 1][ghostY] == ' ' || maze[ghostX + 1][ghostY] == '.' || maze[ghostX + 1][ghostY] == '.')
        {
            gotoxy(ghostY,ghostX);
            cout << previousItem;
            ghostX = ghostX + 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(ghostY, ghostX);
            cout << 'G';
        }
    }
    return 1;
}
bool moveGhost1()
{
    if (gx1 == 1 || gx1 == 23)
    {
        gD1 == "down";
        return 1;
    }
    else if(gD1 == "up")
    {
        if (maze[gx1 - 1][gy1] == ' ' || maze[gx1 - 1][gy1] == '.' || maze[gx1 - 1][gy1] == '.')
        {
            gotoxy(gy1, gx1);
            cout << previousItem;
            gx1 = gx1 - 1;
            previousItem = maze[gx1][gy1];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(gy1, gx1);
            cout << 'G';
        }
        return 1;
    }
    else if (gD1 == "down")
    {
        if (maze[gx1 + 1][gy1] == ' ' || maze[gx1 + 1][gy1] == '.' || maze[gx1 + 1][gy1] == '.')
        {
            gotoxy(gy1, gx1);
            cout << previousItem;
            gx1 = gx1 + 1;
            previousItem = maze[gx1][gy1];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(gy1, gx1);
            cout << 'G';
        }
        return 1;
    }
}
bool moveGhost2()
{
    if (gy2 == 1 || gy2 == 70)
    {
        gD2 == "left";
        return 1;
    }
    else if (gD2 == "right")
    {
        if (maze[gx2][gy2 + 1] == ' ' || maze[gx2][gy2 + 1] == '.' || maze[gx2][gy2 + 1] == '.')
        {
            gotoxy(gy2, gx2);
            cout << previousItem;
            gy2 = gy2 + 1;
            previousItem = maze[gx2][gy2];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(gy2, gx2);
            cout << 'G';
        }
        return 1;
    }
    else if (gD2 == "left")
    {
        if (maze[gx2][gy2 - 1] == ' ' || maze[gx2][gy2 - 1] == '.' || maze[gx2][gy2 - 1] == '.')
        {
            gotoxy(gy1, gx1);
            cout << previousItem;
            gy2 = gy2 - 1;
            previousItem = maze[gx2][gy2];
            if (previousItem == 'P')
            {
                return 0;
            }
            gotoxy(gy2, gx2);
            cout << 'G';
        }
        return 1;
    }
}
bool moveGhostToPacman()
{
    int a , b;
    a = gx1 - pacmanX;
    b = gy1 - pacmanY;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}