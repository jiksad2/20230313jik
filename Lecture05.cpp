// Lecture05.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>

#define MAP_WIDTH 40
#define MAP_HEIGHT 20

char game_map[MAP_HEIGHT][MAP_WIDTH] = { 0 };

int print_title_screen()
{
    std::cout << "****************************************\n";
    std::cout << "*              지렁이 게임             *\n";
    std::cout << "*             (Snake Bite)             *\n";
    std::cout << "*                                      *\n";
    std::cout << "*     1. 게임 시작                     *\n";
    std::cout << "*     2. 게임 설명                     *\n";
    std::cout << "*     3. 게임 랭킹 보기                *\n";
    std::cout << "*     4. 게임 종료(esc)                *\n";
    std::cout << "****************************************\n";
    return 0;
}

int introduction_screen()
{
    std::cout << "****************************************\n";
    std::cout << "*        게임 설명 화면입니다.         *\n";
    std::cout << "****************************************\n";
    std::cout << "타이틀 화면으로 돌아갈까요?(Y/N)\n";
    return 0;
}

void draw_game_map()
{
    system("cls");
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            std::cout << game_map[i][j];
        }
        std::cout << std::endl;
    }
}

void init_game_map()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (i == 0 || i == MAP_HEIGHT - 1) {
                game_map[i][j] = '*';
            }
            else if (j == 0 || j == MAP_WIDTH - 1)
            {
                game_map[i][j] = '*';
            }
            else {
                game_map[i][j] = ' ';
            }
        }
    }
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
    int game_state = 0;
    int is_game_running = 1;
    int screen = 1;
    int stage = 1;

    while (is_game_running)
    {
        char key_input = 0;
        switch (game_state)
        {
        case 0:
            if (screen == 1)
            {
                print_title_screen();
                screen = 0;
            }
            key_input = 0;
            key_input = _getch();
            if (key_input == '1')
            {
                game_state = 1;
                screen = 0;
                init_game_map();
                draw_game_map();
                key_input = 0;
                key_input = _getch();
                if (key_input == 'y')
                {
                    game_state = 0;
                    screen = 1;
                }
                break;
            }
            else if (key_input == '2')
            {
                game_state = 2;
                screen = 2;
            }
            else if (key_input == '3')
            {
                game_state = 3;
                screen = 3;
            }
            else if (key_input == '4' || key_input == 27)
                is_game_running = 0;
            break;
        case 2:
            if (screen == 2)
            {
                introduction_screen();
                screen = 0;
            }
            key_input = 0;
            key_input = _getch();
            if (key_input == 'y')
            {
                game_state = 0;
                screen = 1;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
