#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
const int limit = 100000;
int px = 0;
int py = 0;
const int playerheigth = 4;
const int playerwidth = 6;
int ex1 = 6;
int ey1 = 3;
int ex2 = 120;
int ey2 = 4;
int ex3 = 24;
int ey3 = 7;
int playerY = 0, playerX = 0;
int score = 0;
char fire = 239;
int bx = 0;
int by = 0;
int health = 50;
int bulletCount = 0;
int fireLimit = 0;

int e1bulletx[limit];
int e1bullety[limit];
bool activeEbullet[limit];
int e1index = 0;
int e1count = 0;

char arr[50][150] = {{"#####################################################################################################################################################"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#p                                                                                                                                                  #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},
                     {"#                                                                                                                                                   #"},

                     {"#####################################################################################################################################################"}};

char arr1[20][20] = {
    {"___________________"},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {" Press Rigth key "},
    {"to move player left"},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
    {"                  "},
};

char player[playerheigth][playerwidth] = {
    "  u",
    ".:::.",
    ":::::",
    ":::::",
};
void printBoard();
void printPlayer();
void gotoxy(int x, int y);
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void erasePlayer();
void movePlayerLeft();
void moveplayerRigth();
void movePlayerUp();
void movePlayerDown();
char getCharAtxy(short int x, short int y);
void clear();
void hideCursor();
void printe1();
void erasee1();
void checkDirection2(string &direction);
void printe2();
void erasee2();
void movee2(string direction);
void printe3();
void erasee3();
void movee3(string direction);
void checkDirection(string &direction);
void checkDirection3(string &direction);
void moveEnemey1(string direction);
void moveBullet();
void createBullet();
void interface1();
void moveBullet1();
void enemy1Bullet();
void moveE1bullet();
void healthDecrease();
void logo();
void youLose();
void youWin(); 
string menu();
void instructions();
main()
{
  hideCursor();
  SetConsoleTextAttribute(h, 11);
  system("cls");
  interface1();
  logo();
  getch();
  system("cls");
  printBoard();
  printPlayer();
  string direction1 = "rigth";
  string direction2 = "rigth";
  string direction3 = "rigth";

  while (true)
  {
    string result = menu();
    if (result == "1")
    {
      instructions();
      getch();
    }
    else if (result == "2")
    {
      while (true)
      {
        if (GetAsyncKeyState(VK_LEFT))
        {
          clear();
          movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
          clear();
          moveplayerRigth();
        }
        if (GetAsyncKeyState(VK_UP))
        {
          clear();
          movePlayerUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
          clear();
          movePlayerDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
          clear();
          createBullet();
        }

        checkDirection(direction1);
        moveEnemey1(direction1);
        checkDirection2(direction2);
        movee2(direction2);
        checkDirection3(direction3);
        movee3(direction3);
        moveBullet();

        moveE1bullet();
        healthDecrease();
        gotoxy(150, 10);
        cout << "Score(30 to win): " << score;
        gotoxy(150, 11);
        cout << "Health: " << health << "     ";
        Sleep(30);
        if (health == 0)
        {
          youLose();
          getch();
          break;
        }
        else if (score == 30)
        {
          youWin();
          getch();
          break;
        }
      }
    }
    else if (result == "3")
    {
      break;
    }

    else
    {
      cout << "Invalid option.";
    }
  }
}
void healthDecrease()
{

  int i = py + 2;
  int j = px;
  if (getCharAtxy(i, j) == 'u')
  {
    if (getCharAtxy(i - 2, j) == '*' || getCharAtxy(i - 2, j + 1) == '*' || getCharAtxy(i - 2, j + 2) == '*' || getCharAtxy(i - 2, j + 3) == '*' || getCharAtxy(i - 1, j) == '*' || getCharAtxy(i + 1, j) == '*' || getCharAtxy(i + 2, j) == '*' || getCharAtxy(i + 3, j) == '*' || getCharAtxy(i + 3, j + 1) == '*' || getCharAtxy(i + 3, j + 2) == '*' || getCharAtxy(i + 3, j + 3) == '*')
      health--;
  }
}
void printBoard()
{
  for (int i = 0; i < 40; i++)
  {
    for (int j = 0; j < 150; j++)
    {
      if (arr[i][j] == 'p')
      {
        px = i;
        py = j;
        printPlayer();
      }
      else
      {
        gotoxy(j, i);
        cout << arr[i][j];
      }
    }
  }
}

void printPlayer()
{
  for (int i = 0; i < playerheigth; i++)
  {
    for (int j = 0; j < playerwidth; j++)
    {
      gotoxy(py + j, px + i);
      cout << player[i][j];
      if (player[i][j] == '*')
      {
        score = score + 1;
      }
    }
  }
}
void erasePlayer()
{
  for (int i = 0; i < playerheigth; i++)
  {
    for (int j = 0; j < playerwidth; j++)
    {
      gotoxy(py, px + i);
      cout << "      ";
    }
  }
}

void createBullet()
{
  for (int i = 0; i < 40; i++)
  {
    for (int j = 0; j < 150; j++)
    {
      if (arr[i][j] == 'p' && arr[i - 1][j] == ' ')
      {
        gotoxy(j + 2, i - 1);
        cout << ".";

        bx = j + 2;
        by = i - 1;
      }
    }
  }
}

void moveBullet()
{

  if (bx != 0 && by != 0)
  {
    if (getCharAtxy(bx, by - 1) != '#')
    {
      gotoxy(bx, by);
      cout << " ";
      if (getCharAtxy(bx, by) != '#')
      {
        gotoxy(bx, by - 1);
        cout << " ";
        gotoxy(bx, by - 1);
        by = by - 1;
        cout << ".";

        if (getCharAtxy(bx, by - 1) == '_' || getCharAtxy(bx, by - 1) == '|' || getCharAtxy(bx, by - 1) == ',' || getCharAtxy(bx, by - 1) == '(' || getCharAtxy(bx, by - 1) == ')' || getCharAtxy(bx, by - 1) == '+' || getCharAtxy(bx, by - 1) == '\\' || getCharAtxy(bx, by - 1) == '/')
        {
          gotoxy(bx, by);
          cout << " ";
          score = score + 1;
        }
      }
    }
    else
    {
      gotoxy(bx, by);
      cout << " ";
    }
  }
}
void moveBullet1()
{
  for (int i = 0; i < 35; i++)
  {
    for (int j = 0; j < 130; j++)
    {
      if (getCharAtxy(j, i) == '*')
      {
        gotoxy(j, i);
        cout << " ";
        gotoxy(j, i + 1);
        cout << "*";
        break;
      }
    }
  }
}

void movePlayerLeft()
{
  if (arr[px][py - 1] != '#')
  {
    erasePlayer();
    arr[px][py] = ' ';
    py = py - 1;
    arr[px][py] = 'p';
    printPlayer();
    if (arr[px][py - 1] == '*')
    {
      score = score + 1;
    }
  }
}
void scoreIncrement()
{
  for (int i = 0; i < playerheigth; i++)
  {
    for (int j = 0; j < playerwidth; j++)
    {
      if (player[i][j] == '*')
      {
        score = score + 1;
      }
    }
  }
}

void moveplayerRigth()
{
  if (arr[px][py + 7] != '#')
  {
    erasePlayer();
    arr[px][py] = ' ';
    py = py + 1;
    arr[px][py] = 'p';
    printPlayer();
    if (arr[px][py + 1] == '*')
    {
      score = score + 1;
    }
  }
}

void movePlayerUp()
{
  if (arr[px - 1][py] != '#')
  {
    erasePlayer();
    arr[px][py] = ' ';
    px = px - 1;
    arr[px][py] = 'p';
    printPlayer();
    if (arr[px - 1][py] == '*')
    {
      score = score + 1;
    }
  }
}

void movePlayerDown()
{
  if (arr[px + 4][py] != '#')
  {
    erasePlayer();
    arr[px][py] = ' ';
    px = px + 1;
    arr[px][py] = 'p';
    printPlayer();
    if (arr[px + 1][py] == '*')
    {
      score = score + 1;
    }
  }
}
void gotoxy(int x, int y)
{
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
  CHAR_INFO ci;
  COORD xy = {0, 0};
  SMALL_RECT rect = {x, y, x, y};
  COORD coordBufSize;
  coordBufSize.X = 1;
  coordBufSize.Y = 1;
  return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar
                                                                                          : ' ';
}

void clear()
{
  COORD cursorPos;
  cursorPos.X = 0;
  cursorPos.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}
void printe1()
{
  gotoxy(ex1, ey1);
  cout << "'__' " << endl;
  gotoxy(ex1, ey1 + 1);
  cout << "(++) " << endl;
  gotoxy(ex1, ey1 + 2);
  cout << "/||\\" << endl;
  gotoxy(ex1, ey1 + 3);
  cout << "_||_ " << endl;
}

void erasee1()
{
  gotoxy(ex1, ey1);
  cout << "     " << endl;
  gotoxy(ex1, ey1 + 1);
  cout << "     " << endl;
  gotoxy(ex1, ey1 + 2);
  cout << "     " << endl;
  gotoxy(ex1, ey1 + 3);
  cout << "     " << endl;
}
void checkDirection(string &direction)
{
  if (direction == "rigth" && ex1 >= 142)
  {
    direction = "Left";
  }
  if (direction == "Left" && ex1 <= 2)
  {
    direction = "rigth";
  }
}

void enemy1Bullet()
{
  int exb1 = ex1 + 1; 
  int eyb1 = ey1 + 2; 
  gotoxy(exb1, eyb1);
  SetConsoleTextAttribute(h, 6);
  cout << "*";

  e1bulletx[e1index] = exb1;
  e1bullety[e1index] = eyb1;
  activeEbullet[e1index] = true;
  e1index++;
  e1count++;
}
void moveE1bullet()
{
  for (int i = 0; i < e1count; i++) 
  {
    if (activeEbullet[i] == true)
    {
      if (getCharAtxy(e1bulletx[i], e1bullety[i] + 1) == ' ')
      {
        gotoxy(e1bulletx[i], e1bullety[i]);
        cout << " ";
        e1bullety[i] = e1bullety[i] + 1;
        gotoxy(e1bulletx[i], e1bullety[i]);
        SetConsoleTextAttribute(h, 6);
        cout << "*";
      }
      else if (getCharAtxy(e1bulletx[i], e1bullety[i + 1]) != ' ')
      {
        gotoxy(e1bulletx[i], e1bullety[i]);
        cout << " ";
      }
      else if (getCharAtxy(0, 0) == 'u')
      {
        health--;
      }
    }
  }
  if (fireLimit > 10)
  {
    enemy1Bullet();
    fireLimit = 0;
  }
  else
  {
    fireLimit++;
  }
}


void moveEnemey1(string direction) 
{
  if (direction == "rigth")
  {
    erasee1();

    ex1 = ex1 + 1;

    printe1();
  }
  else if (direction == "Left")
  {
    erasee1();
    ex1 = ex1 - 1;

    printe1();
  }
}

void printe2()
{
  gotoxy(ex2, ey2);
  cout << "'__' " << endl;
  gotoxy(ex2, ey2 + 1);
  cout << "(++) " << endl;
  gotoxy(ex2, ey2 + 2);
  cout << "/||\\" << endl;
  gotoxy(ex2, ey2 + 3);
  cout << "_||_ " << endl;
}

void checkDirection2(string &direction)

{
  if (direction == "rigth" && ey2 >= 35)
  {
    direction = "left";
  }
  if (direction == "left" && ey2 <= 2)
  {
    direction = "rigth";
  }
}
// oid health1()
//
//  if(getCharAtxy(px-1,py)=='*'||getCharAtxy(px-1,py)=='*'||getCharAtxy(px,py+1)=='*'||getCharAtxy(px,py-1)=='*')
//  {
//      health = health - 1;
//      cout<<px<<py;
//  }
//

void erasee2()
{
  gotoxy(ex2, ey2);
  cout << "     " << endl;
  gotoxy(ex2, ey2 + 1);
  cout << "     " << endl;
  gotoxy(ex2, ey2 + 2);
  cout << "     " << endl;
  gotoxy(ex2, ey2 + 3);
  cout << "     " << endl;
}

void movee2(string direction)
{
  if (direction == "rigth")
  {
    erasee2();

    ey2 = ey2 + 1;

    printe2();
  }
  if (direction == "left")

  {
    erasee2();
    ey2 = ey2 - 1;
    printe2();
  }
}
void checkDirection3(string &direction)
{
  if (direction == "rigth" && ex3 >= 50 && ey3 >= 30)
  {
    direction = "left";
  }
  if (direction == "left" && ex3 <= 20 && ey3 <= 20)
  {
    direction = "rigth";
  }
}

void printe3()
{
  gotoxy(ex3, ey3);
  cout << "'__' " << endl;
  gotoxy(ex3, ey3 + 1);
  cout << "(++) " << endl;
  gotoxy(ex3, ey3 + 2);
  cout << "/||\\" << endl;
  gotoxy(ex3, ey3 + 3);
  cout << "_||_ " << endl;
}

void erasee3()
{
  gotoxy(ex3, ey3);
  cout << "     " << endl;
  gotoxy(ex3, ey3 + 1);
  cout << "     " << endl;
  gotoxy(ex3, ey3 + 2);
  cout << "     " << endl;
  gotoxy(ex3, ey3 + 3);
  cout << "     " << endl;
}

void movee3(string direction)
{
  if (direction == "rigth")
  {
    erasee3();

    ex3 = ex3 + 1;
    ey3 = ey3 + 1;

    printe3();
  }
  if (direction == "left")
  {
    erasee3();
    ex3 = ex3 - 1;
    ey3 = ey3 - 1;
    printe3();
  }
}
void hideCursor()
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void interface1()
{
  gotoxy(40, 20);
  cout << " _   _                     _ _   _       _   _                         " << endl;
  gotoxy(40, 21);
  cout << "| | | | ___ _ __ _ __ ___ (_) |_( )___  | | | | __ ___   _____   ___   " << endl;
  gotoxy(40, 22);
  cout << "| |_| |/ _ \\ '__| '_ ` _ \\| | __|// __| | |_| |/ _` \\ \\ / / _ \\ / __|  " << endl;
  gotoxy(40, 23);
  cout << "|  _  |  __/ |  | | | | | | | |_  \\__ \\ |  _  | (_| |\\ V / (_) | (__   " << endl;
  gotoxy(40, 24);
  cout << "|_| |_|\\___|_|  |_| |_| |_|_|\\__| |___/ |_| |_|\\__,_| \\_/ \\___/ \\___|  " << endl;
}
void logo()
{

  cout << "                                                                         mdv                   " << endl;
  cout << "                                                                         vii                   " << endl;
  cout << "                                                                          vdr                  " << endl;
  cout << "                                                                           rdv                 " << endl;
  cout << "                                                                            ii                 " << endl;
  cout << "                                                                            v0m                " << endl;
  cout << "                                                                             r0v               " << endl;
  cout << "                                                                              di               " << endl;
  cout << "                                                      vv                       0m              " << endl;
  cout << "                                                   vmi  mdv                    rdv             " << endl;
  cout << "                                                 dm        vdm                 v0m0            " << endl;
  cout << "                                             m00iiiiiidiiiiidd060v           rirmm0            " << endl;
  cout << "                                             vmiiidm   r0m0miimv         rim1 rivrim           " << endl;
  cout << "                                                   d   r0rd     vvvvridiimr v6v   div          " << endl;
  cout << "                                                   rr r0r r6W6dr r0v   vmiv  vi    0m          " << endl;
  cout << "                       v0immmmimmmr                 dr0mmirviid  v0r  m0r     vi   rdv         " << endl;
  cout << "                       vd0di0dmr1v    mi66mrrriii00mv  vii0m  6rvi  v0d      rmi    ii         " << endl;
  cout << "                         dmm6i rmi       rdm      div   v6R6v    irm6  m00iv        v0r        " << endl;
  cout << "                               ird         0m      idr     dr    rimmv               m0        " << endl;
  cout << "                               0rd   dir    idm     viv   r01dr   d                  vmd       " << endl;
  cout << "                               0dr    rd0v   virm           6  rd d                   mmr      " << endl;
  cout << "                                vvd0dd0dm  v           6v 0rrv                    id          " << endl;
  cout << "                                          riv0i      vr0rmdvd                     vdr         " << endl;
  cout << "                                            vii60v     rddmvi                                 " << endl;
  cout << "                                               d m6W6ddd1driv                                 " << endl;
  cout << "                                             drr6drv     vr0                                  " << endl;
  cout << "                                          riv mvviimiddmv      rmmm                           " << endl;
  cout << "                                       riv    d  riiv iv        r6v  iir                      " << endl;
  cout << "                                     0v      vi  irr   d      vdd       d                     " << endl;
  cout << "                                  m0idmrimrdmv   riv   iv     dd        i                     " << endl;
  cout << "                               ir  drrvi          0r   d    vivr       mr                     " << endl;
  cout << "                             mm v  viiv iv        0    0r   iviv      rr                      " << endl;
  cout << "                           dr irmdv0mrrr dv      dd    6rmvi iv      rm                       " << endl;
  cout << "                        vir   d   ridrimi rr    rri    0m   rr      vm                        " << endl;
  cout << "                      r00v mm vm      v0ddrvi    i     iv066dmrv    rv                        " << endl;
  cout << "                   vir  vi    v    vvidv  d6i0v  vvvridiivivrr  vddmir                        " << endl;
  cout << "                 dr   i0drdv   vdmv          vvvv     vidr   vdv                              " << endl;
  cout << "              viv  i0dv     mmr                       r00000iimmmiv                           " << endl;
  cout << "             vd    im                                                                         " << endl;
  cout << "r000000000000000600r" << endl;
}
void youLose()
{
  cout << "__   __               _                   " << endl;
  cout << "\\ \\ / /__  _   _     | |    ___  ___  ___ " << endl;
  cout << " \\ V / _ \\| | | |    | |   / _ \\/ __|/ _ \\  " << endl;
  cout << "  | | (_) | |_| |    | |__| (_) \\__ \\  __/" << endl;
  cout << "  |_|\\___/ \\__,_|    |_____\\___/|___/\\___|" << endl;
}

void youWin()
{
  cout << "__   __              __        __           " << endl;
  cout << "\\ \\ / /__  _   _     \\ \\      / /__  _ __   " << endl;
  cout << " \\ V / _ \\| | | |     \\ \\ /\\ / / _ \\| '_ \\  " << endl;
  cout << "  | | (_) | |_| |      \\ V  V / (_) | | | | " << endl;
  cout << "  |_|\\___/ \\__,_|       \\_/\\_/ \\___/|_| |_| " << endl;
}
string menu()
{
  string op;
  gotoxy(30, 40);
  cout << "1. See the instructions: " << endl;
  gotoxy(30, 41);
  cout << "2. Play the Game: " << endl;
  gotoxy(30, 42);
  cout << "3. Exit: " << endl;
  getline(cin, op);
  return op;
}
void instructions()
{
  gotoxy(30, 20);
  cout << "Enter space to create bullet." << endl;
  gotoxy(30, 21);
  cout << "Enter left arrow key to move left." << endl;
  gotoxy(30, 22);
  cout << "Enter rigth arrow key to move rigth." << endl;
  gotoxy(30, 23);
  cout << "Enter up arrow key to move up." << endl;
  gotoxy(30, 24);
  cout << "Enter down arrow key to move down." << endl;
  gotoxy(30, 25);
  cout << "You have to score 30 points to win the game." << endl;
}