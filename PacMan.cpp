//--------------Header Files---------//
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <time.h>
using namespace std;
//-----------------Function Prototypes-------------------//
int menu();
void printMaze();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void playGame();
void gotoxy(int x, int y);
void scoreboard();
void winner();
bool gameover();
void readMaze();
void moveGhost1();
void moveGhost2();
void moveGhost3();
int ghostDirection();
int moveGhost4();
void gameOverMessage();
//----------------Variable Declaration-----------------//
bool playingGame = true;
//---------Coordinates of Position of Pac-Man----------//
int PacmanX = 9;
int PacmanY = 31;
//---------Coordinates of Position of Ghost------------//

int g1x = 16; //   The ghost which is moving Verically
int g1y = 31;
int flag1 = 0;

int g2x = 1; //   The ghost which is moving Verically
int g2y = 29;
int flag2 = 0;

int g3x = 1; //   The ghost which is moving Verically
int g3y = 60;

int g4x = 5; //   The intelligent ghost moving towards PacMan
int g4y = 5;

int score = 0; //    for maintaining score record
int lives = 3; //    for maintaining lives count

// we have done this so that ghost might eat food dots, so we have to store them in a variable before
char previousItem = ' ';
string gD1 = "up";
string gD2 = "right";
// fixed number of Rows and Columns in Maze
const int rows = 24, cols = 71;
//-----------------Array of Maze------------------//
char maze[rows][cols] = {{"#####################################################################"},
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

//------------------Color Change----------//
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//------------------Main Body----------------------//
main()
{
    system("cls");
    int option;
    readMaze();
    option = menu();
    while (option < 3)
    {
        if (option == 1)
        {
            // SetConsoleTextAttribute(hConsole, 15);
            // SetConsoleTextAttribute(hConsole, 13);
            SetConsoleTextAttribute(hConsole, 14);
            while (playingGame)
            {
                lives = 3;
                score = 0;
                playGame();
            }
        }
        else if (option == 2)
        {
            system("cls");
            cout << endl;
            cout << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 13);
            cout << "\t\t\t\t\t       ----------------------------" << endl;
            cout << "\t\t\t\t\t       |     Game Description     |" << endl;
            cout << "\t\t\t\t\t       ----------------------------" << endl;
            cout << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\t How to Play :  ";
            SetConsoleTextAttribute(hConsole, 11);
            cout << "Pac Man is a human-computer game, so only 1 player can play at a time " << endl;
            cout << "\t\t\t        The player controls Pac-Man, who must eat all the dots inside an" << endl;
            cout << "\t\t\t        enclosed maze while avoiding four colored ghosts. Eating dots called  " << endl;
            cout << "\t\t\t        (Food Pellets) causes Pac-Man to earn bonus points. Pac-Man can only" << endl;
            cout << "\t\t\t        move inside the maze, cannot go outside the walls of maze. Pac-Man has" << endl;
            cout << "\t\t\t        to avoid ghosts. Colliding with the ghosts result in -1 from lives." << endl;
            cout << "\t\t\t        There are total three lives of Pac-Man. If Pac-Man collides with the" << endl;
            cout << "\t\t\t        ghosts more than three times, then the game will be over. If score " << endl;
            cout << "\t\t\t        becomes above 500, game stops and player wins" << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\tPlayers Required : ";
            SetConsoleTextAttribute(hConsole, 11);
            cout << " 1 " << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\t\tSkills Required :";
            SetConsoleTextAttribute(hConsole, 11);
            cout << "  Strategy, Tactics, Observation." << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 12);
            cout << endl;
        }
        // resetting if user select option 1, to play again
        playingGame = true;
        score = 0;
        lives = 3;
        //PacmanX = 10;
        //PacmanY = 32;
        //readMaze();
        cout << endl;
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\tPress any key to continue_";
        getch();
        system("cls");
        option = menu();
        SetConsoleTextAttribute(hConsole, 15); // set back to black background and white text  coz 15 = white
    }
}
//-----------------Function of Main Menu------------------//
int menu()
{
    cout << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t\t\t\t\t\t*********************" << endl;
    cout << "\t\t\t\t\t\t*      Pac-Man      *" << endl;
    cout << "\t\t\t\t\t\t*********************" << endl;
    cout << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 3);
    cout << " -------------------------------" << endl;
    cout << " | Select one option from menu |" << endl;
    cout << " -------------------------------" << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t1. Play" << endl;
    cout << "\t2. Game Description" << endl;
    cout << "\t3. Exit" << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 14);
    cout << " Your option_";
    int option;
    cin >> option;
    return option;
}
//-----------------Function for playing Game------------------//
void playGame()
{
    system("cls");
    printMaze();              //   printing maze on screen
    gotoxy(PacmanY, PacmanX); //   printing PacMan on a specific location on screen
    cout << 'P';
    while (playingGame)
    {
        Sleep(100); //  delay in game is mandatory, otherwise screen will flicker and it will not run smoothly

        // Functions to move our 4 ghosts

        moveGhost1();
        moveGhost2();
        moveGhost3();
        moveGhost4();

        scoreboard(); //      function to display sScoreBoard

        if (gameover())
        {
            playingGame = false;
        }

        if (GetAsyncKeyState(VK_LEFT)) //    to move PaCman left
        {
            movePacmanLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT)) //    to move PaCman right
        {
            movePacmanRight();
        }
        if (GetAsyncKeyState(VK_UP)) //    to move PaCman up
        {
            movePacmanUp();
        }
        if (GetAsyncKeyState(VK_DOWN)) //    to move PaCman down
        {
            movePacmanDown();
        }
        if (GetAsyncKeyState(VK_ESCAPE)) //    to exit from game before game over
        {
            playingGame = false;
        }
        if (score == 100) // We also have set a score goal to win the game
        {
            winner();
            playingGame = false;
        }
    }
}
//-----------------Function to print maze on screen------------------//
void printMaze()
{
    for (int row = 0; row < rows; row++)
    {

        for (int col = 0; col < cols; col++)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}
//-----------------Function to Pac-Man Left------------------//
void movePacmanLeft()
{
    if (maze[PacmanX][PacmanY - 1] == ' ' || maze[PacmanX][PacmanY - 1] == '.')
    {
        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanY--;

        SetConsoleTextAttribute(hConsole, 11);
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
        SetConsoleTextAttribute(hConsole, 15);

        if (maze[PacmanX][PacmanY - 1] == '.')
        {
            score++;
        }
    }
}
//-----------------Function to Pac-Man Right------------------//
void movePacmanRight()
{
    if (maze[PacmanX][PacmanY + 1] == ' ' || maze[PacmanX][PacmanY + 1] == '.')
    {
        if (maze[PacmanX][PacmanY + 1] == '.')
        {
            score++;
        }

        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanY++;
        SetConsoleTextAttribute(hConsole, 11);
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
        SetConsoleTextAttribute(hConsole, 15);
    }
}

//-----------------Function to Pac-Man Up------------------//
void movePacmanUp()
{
    if (maze[PacmanX - 1][PacmanY] == ' ' || maze[PacmanX - 1][PacmanY] == '.')
    {
        if (maze[PacmanX - 1][PacmanY] == '.')
        {
            score++;
        }

        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanX--;
        SetConsoleTextAttribute(hConsole, 11);
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
        SetConsoleTextAttribute(hConsole, 15);
    }
}

//-----------------Function to Pac-Man Down------------------//
void movePacmanDown()
{
    if (maze[PacmanX + 1][PacmanY] == ' ' || maze[PacmanX + 1][PacmanY] == '.')
    {
        if (maze[PacmanX + 1][PacmanY] == '.')
        {
            score++;
        }

        maze[PacmanX][PacmanY] = ' ';
        gotoxy(PacmanY, PacmanX);
        cout << ' ';
        PacmanX++;
        SetConsoleTextAttribute(hConsole, 11);
        gotoxy(PacmanY, PacmanX);
        cout << 'P';
        SetConsoleTextAttribute(hConsole, 15);
    }
}
//-----------------Function to display on a specific location------------------//
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
//-----------------Function to display ScoreBoard------------------//
void scoreboard()
{
    gotoxy(90, 10);
    cout << "Score : " << score << endl;
    gotoxy(90, 11);
    cout << "Lives : " << lives << endl;
}
//-----------------Function to display Winner------------------//
void winner()
{
    {
        system("cls");
        cout << endl;
        cout << endl;
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t\t\t\t\t*********************" << endl;
        cout << "\t\t\t\t\t\t*      Pac-Man      *" << endl;
        cout << "\t\t\t\t\t\t*********************" << endl;
        cout << endl;
        cout << endl;
        SetConsoleTextAttribute(hConsole, 13);
        cout << "\t\t\t\t\t------------------------------------" << endl;
        cout << "\t\t\t\t\t------------------------------------" << endl;
        cout << "\t\t\t\t\t|              WINNER              |" << endl;
        cout << "\t\t\t\t\t------------------------------------" << endl;
        cout << "\t\t\t\t\t------------------------------------" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        //cout << "\n\n Press any key to continue_";
        //getch();
        cout << "\n\n Enter any key to continue_";
        string option;
        cin >> option;
    }
}
//-----------------Function to read Maze from txt file------------------//
void readMaze()
{
    fstream file;
    string line;
    file.open("Maze.txt", ios::in);
    for (int x = 0; x < 24; x++)
    {
        getline(file, line);
        for (int y = 0; y < 71; y++)
        {
            maze[x][y] = line[y];
        }
    }
    file.close();
}
//-----------------Function if GameOver------------------//
bool gameover()
{
    if (PacmanX == g1x && PacmanY == g1y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    else if (PacmanX == g2x && PacmanY == g2y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    else if (PacmanX == g3x && PacmanY == g3y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    else if (PacmanX == g4x && PacmanY == g4y)
    {
        lives--;
        PacmanX = 9;
        PacmanY = 31;
    }
    SetConsoleTextAttribute(hConsole, 11);
    gotoxy(PacmanY, PacmanX);
    cout << 'P';
    SetConsoleTextAttribute(hConsole, 15);
    if (lives == 0)
    {
        gameOverMessage();
        return true;
    }
    return false;
}
//-----------------Function to move Ghost1 (Horizontal Moving Ghost)------------------//
void moveGhost1()
{
    char pre;
    //  Move Ghost Left
    if ((maze[g1x][g1y - 1] == ' ' || maze[g1x][g1y - 1] == '.') && flag1 == 1)
    {
        pre = maze[g1x][g1y];
        maze[g1x][g1y] = pre;
        gotoxy(g1y, g1x);
        cout << pre;
        g1y--;
        SetConsoleTextAttribute(hConsole, 13);
        gotoxy(g1y, g1x);
        cout << 'G';
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        flag1 = 0;
    }

    //  Move Ghost Right
    if ((maze[g1x][g1y + 1] == ' ' || maze[g1x][g1y + 1] == '.') && flag1 == 0)
    {
        pre = maze[g1x][g1y];

        maze[g1x][g1y] = pre;
        gotoxy(g1y, g1x);
        cout << pre;
        g1y++;
        SetConsoleTextAttribute(hConsole, 13);
        gotoxy(g1y, g1x);
        cout << 'G';
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        flag1 = 1;
    }
}
//-----------------Function to move Ghost2 (Vertical Moving Ghost)------------------//
void moveGhost2()
{
    char pre;

    //  Move Ghost Up
    if ((maze[g2x - 1][g2y] == ' ' || maze[g2x - 1][g2y] == '.') && flag2 == 1)
    {
        pre = maze[g2x][g2y];

        maze[g2x][g2y] = pre;
        gotoxy(g2y, g2x);
        cout << pre;
        g2x--;
        SetConsoleTextAttribute(hConsole, 13);
        gotoxy(g2y, g2x);
        cout << 'G';
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        flag2 = 0;
    }
    //  Move Ghost Down
    if ((maze[g2x + 1][g2y] == ' ' || maze[g2x + 1][g2y] == '.') && flag2 == 0)
    {
        pre = maze[g2x][g2y];

        maze[g2x][g2y] = pre;
        gotoxy(g2y, g2x);
        cout << pre;
        g2x++;
        SetConsoleTextAttribute(hConsole, 13);
        gotoxy(g2y, g2x);
        cout << 'G';
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        flag2 = 1;
    }
}
//-----------------Function to randomly decide ghost location-----------------//
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}
//-----------------Function to move Ghost3  (Randomly Moving Ghost)------------------//
void moveGhost3()
{
    int n = ghostDirection();

    char pre;

    if (n == 1) //  Move Ghost Right
    {
        if (maze[g3x][g3y + 1] == ' ' || maze[g3x][g3y + 1] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3y++;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g3y, g3x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    else if (n == 2) //  Move Ghost Left
    {
        if (maze[g3x][g3y - 1] == ' ' || maze[g3x][g3y - 1] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3y--;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g3y, g3x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    else if (n == 3) //  Move Ghost Up
    {
        if (maze[g3x - 1][g3y] == ' ' || maze[g3x - 1][g3y] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3x--;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g3y, g3x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    else if (n == 4) //  Move Ghost Down
    {
        if (maze[g3x + 1][g3y] == ' ' || maze[g3x + 1][g3y] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3x++;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g3y, g3x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
}
//-----------------Function to move Ghost4 (behind the PacMan)------------------//
int moveGhost4()
{
    char pre;
    Sleep(50);
    // if PacmanX greater than ghostX, then move ghost right
    if (PacmanX > g4x)
    {
        if (maze[g4x + 1][g4y] == ' ' || maze[g4x + 1][g4y] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4x++;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g4y, g4x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
            return 1;
        }
    }
    // if PacmanX less than ghostX, then move ghost left
    if (PacmanX < g4x)
    {
        if (maze[g4x - 1][g4y] == ' ' || maze[g4x - 1][g4y] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4x--;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g4y, g4x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
            return 1;
        }
    }
    // if PacmanY greater than ghostY, then move ghost Down
    if (PacmanY > g4y)
    {
        if (maze[g4x][g4y + 1] == ' ' || maze[g4x][g4y + 1] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4y++;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g4y, g4x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
            return 1;
        }
    }
    // if PacmanY less than ghostY, then move ghost up
    if (PacmanY < g4y)
    {
        if (maze[g4x][g4y - 1] == ' ' || maze[g4x][g4y - 1] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4y--;
            SetConsoleTextAttribute(hConsole, 13);
            gotoxy(g4y, g4x);
            cout << 'G';
            SetConsoleTextAttribute(hConsole, 15);
            return 1;
        }
    }
}
//-----------------Function to print GameOver------------------//
void gameOverMessage()
{
    system("cls");
    cout << endl;
    cout << endl;
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\t\t\t\t\t\t*********************" << endl;
    cout << "\t\t\t\t\t\t*      Pac-Man      *" << endl;
    cout << "\t\t\t\t\t\t*********************" << endl;
    cout << endl;
    cout << endl;
    cout << "\n\n\n";
    SetConsoleTextAttribute(hConsole, 13);
    cout << "\t\t\t\t\t-----------------------------------" << endl;
    cout << "\t\t\t\t\t-----------------------------------" << endl;
    cout << "\t\t\t\t\t|            Game Over            |" << endl;
    cout << "\t\t\t\t\t-----------------------------------" << endl;
    cout << "\t\t\t\t\t-----------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 15);
    //cout << "\n\n Press any key to continue_";
    //getch();
    cout << "\n\n Enter any key to continue_";
    string option;
    cin >> option;
}