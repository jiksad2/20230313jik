#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
using namespace std;

namespace MuSoeun
{
    class Scene {
    private:
        char screenBuf[51 * 20 + 1];

    public:
        int width = 50;
        int height = 20;
        char input[10];

        std::vector<Object> objList;
        std::vector<Snake> snakeLine;

        void gotoxy(int x, int y) {
            COORD pos = { x, y };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        }

        void SetCursorState(bool visible) {
            CONSOLE_CURSOR_INFO consoleCursorInfo;
            consoleCursorInfo.bVisible = visible;
            consoleCursorInfo.dwSize = 1;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
        }

        void Draw() {
            for (int i = 0; i < snakeLine.size(); i++)
               
                snakeLine[i].Render(screenBuf, snakeLine[i].CoordX, snakeLine[i].CoordY, width);
            gotoxy(0, 0);
            cout << screenBuf << endl;
        }

        void ReleaseScreenBuf() { 
            int i = 0;	
            int j = 0;
            while (j < height)
            {
                while (i < width + 1)
                {
                    if (i == width) screenBuf[i + (j * (width + 1))] = '\n';
                    else
                    {
                        if (i == 0 || i == 1 || i == (width - 1) || i == (width - 2) || j == 0 || j == (height - 1))
                            screenBuf[i + (j * (width + 1))] = '#';
                        else
                            screenBuf[i + (j * (width + 1))] = ' ';
                    }
                    i = i + 1;
                }
                i = 0; j = j + 1;
            }
            screenBuf[height * (width + 1) - 1] = '\0';
        }

        void ClearScreenBuf() {
            ReleaseScreenBuf();  
            system("cls");  
            cout << screenBuf << endl;
        }

        void ObjectCreate() {
            Snake snake;

            for (int i = 0; i < 5; i++)
            {
                snake.CoordX++;
                snakeLine.push_back(snake);
            }

            for (int i = 0; i < snakeLine.size(); i++)
                objList.push_back(snakeLine[i]);
        }
    };

    class Object : public Componant {
    public:
        vector<Componant*> ComList;
        int CoordX = 10;
        int CoordY = 5;

        Object() {}
        ~Object() {}

        void virtual Render() 
        {

        }
    };

    class Snake : public Object {
    public:
        void Render(char* screenBuf, int x, int y, int width) {
            screenBuf[(width + 1) * y + x] = '#';
        }
    };

    class Componant {
    public:

        Componant() {}
        ~Componant() {}

        void Start() {}

        void Update() {}
    };

    class MGameLoop : public Scene {
    public:
        void Run() {
            ClearScreenBuf();
            ObjectCreate(); 

            while (1) { 
                Draw(); 
                cout << "게임을 나가려면 'z'를 누르시오" << endl;
                if (_kbhit()) {
                    if (_getch() == 'z') break;
                } 
            }
        }
    };
}