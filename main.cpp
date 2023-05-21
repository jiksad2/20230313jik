#define TitleState 10
#define GameStartState 1
#define DescriptionState 2
#define RankingState 3
#define GameOverState 99

#define TitleString "지렁이 게임\nSnake Bike\n1. 게임 시작\n2. 게임 설명\n3. 게임 랭킹 보기\n4. 게임 종료(q)\n"
#define DescriptionString "<게임 설명>\n방향키로 움직이세요.\n[돌아가기 : 'Z']\n"
#define RankingString "<지렁이 게임 랭킹>\n1st\n2nd\n3rd\n4th\n5th\n\n[돌아가기 : 'Z']\n"
#define GameOverString "게임 오버[돌아가기 : 'Z']\n"

#include <stdio.h>
#include <conio.h>
#include "screen.hpp"
#include "MuSoeun.hpp"


int main()
{
    char screenBuf[800];
    int width = 40;
    int height = 18;
    int isGamePlay = 10;
    int KeyEvent = 1;

    char string[200];


    while (isGamePlay)
    {
        MuSoeun::MGameLoop GamePlay;
        clearBuffer(screenBuf, width, height);

        setTitle(screenBuf, width, height);

        while (isGamePlay)
        {
            KeyEvent = 1;

            switch (isGamePlay)
            {
            case TitleState:
                setTitle(screenBuf, width, height);
                strcpy(string, TitleString); 
                    break;
            case GameStartState:
                GamePlay.Run();
                system("cls");
                setGameOver(screenBuf, width, height);
                strcpy(string, GameOverString);
                isGamePlay = GameOverState;
                    break;
            case DescriptionState:
                setDescription(screenBuf, width, height);
                strcpy(string, DescriptionString); 
                    break;
            case RankingState:
                setRanking(screenBuf, width, height);
                strcpy(string, RankingString); 
                    break;
            default:
                break;
            }

            printf("%s\ninput>", screenBuf);

            writeString(string, 5, 2);

            while (KeyEvent)
            {
                if (_kbhit())
                {
                    switch (isGamePlay)
                    {
                    case TitleState:
                        switch (_getch())
                        {
                        case '1': isGamePlay = GameStartState; break;
                        case '2': isGamePlay = DescriptionState; break;
                        case '3': isGamePlay = RankingState; break;
                        case '4': case 'q': isGamePlay = 0; system("cls"); break;
                        default:
                            break;
                        } break;
                    case GameStartState:
                    case DescriptionState:
                    case RankingState:
                    case GameOverState:
                        if (_getch() == 'z') isGamePlay = TitleState; break;
                    default:
                        break;
                    }
                    KeyEvent = 0;
                    system("cls");
                }
            }
        }
    }

    cout << "게임을 종료하였습니다." << endl;

    return 0;
}