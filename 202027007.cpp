#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

void SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 25;

const int MAX_LENGTH = 100;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Position
{
    int x;
    int y;
};

struct Snake
{
    Position body[MAX_LENGTH];
    int length;
    Direction direction;
};

struct Fruit
{
    Position position;
};

struct Game
{
    Snake snake;
    Fruit fruit;
    bool gameOver;
    int score;
    int speed;
};

void Setup(Game& game)
{
    game.snake.length = 1;
    game.snake.body[0] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    game.snake.direction = RIGHT;

    game.fruit.position = { rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };

    game.gameOver = false;
    game.score = 0;
}

void DrawGameScreen(const Game& game)
{
    system("cls");

    SetConsoleColor(11);
  
    for (int i = 0; i < SCREEN_WIDTH + 2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            if (x == 0)
            {
                SetConsoleColor(11);
                std::cout << "#";
            }

            if (x == game.snake.body[0].x && y == game.snake.body[0].y)
            {
                SetConsoleColor(14);
                std::cout << "O";
            }
            else if (x == game.fruit.position.x && y == game.fruit.position.y)
            {
                SetConsoleColor(13);
                std::cout << "A";
            }
            else
            {
                bool isBodyPart = false;
                for (int i = 1; i < game.snake.length; i++)
                {
                    if (x == game.snake.body[i].x && y == game.snake.body[i].y)
                    {
                        SetConsoleColor(14);
                        std::cout << "o";
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart)
                {
                    std::cout << " ";
                }
            }

            if (x == SCREEN_WIDTH - 1)
            {
                SetConsoleColor(11);
                std::cout << "#";
            }
        }
        std::cout <<""<< std::endl;
    }

    
    for (int i = 0; i < SCREEN_WIDTH + 2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    SetConsoleColor(7);
    std::cout << " 점수 : " << game.score << std::endl;
}

void Update(Game& game)
{
    if (_kbhit())
    {
        char key = _getch();

        switch (key)
        {
        case 'w':
        case 'W':
            if (game.snake.direction != DOWN)
            {
                game.snake.direction = UP;
            }
            break;
        case 's':
        case 'S':
            if (game.snake.direction != UP)
            {
                game.snake.direction = DOWN;
            }
            break;
        case 'a':
        case 'A':
            if (game.snake.direction != RIGHT)
            {
                game.snake.direction = LEFT;
            }
            break;
        case 'd':
        case 'D':
            if (game.snake.direction != LEFT)
            {
                game.snake.direction = RIGHT;
            }
            break;
        case 27:
            game.gameOver = true;
            break;
        }
    }

    for (int i = game.snake.length - 1; i > 0; i--)
    {
        game.snake.body[i] = game.snake.body[i - 1];
    }

    switch (game.snake.direction)
    {
    case UP:
        game.snake.body[0].y--;
        break;
    case DOWN:
        game.snake.body[0].y++;
        break;
    case LEFT:
        game.snake.body[0].x--;
        break;
    case RIGHT:
        game.snake.body[0].x++;
        break;
    }

    if (game.snake.body[0].x < 0 || game.snake.body[0].x >= SCREEN_WIDTH ||
        game.snake.body[0].y < 0 || game.snake.body[0].y >= SCREEN_HEIGHT)
    {
        game.gameOver = true;
    }

    for (int i = 1; i < game.snake.length; i++)
    {
        if (game.snake.body[0].x == game.snake.body[i].x && game.snake.body[0].y == game.snake.body[i].y)
        {
            game.gameOver = true;
            break;
        }
    }

    if (game.snake.body[0].x == game.fruit.position.x && game.snake.body[0].y == game.fruit.position.y)
    {
        game.snake.length++;

        int speedIncrement = 50; 
        game.speed -= speedIncrement;

        if (game.speed < 1000)
        {
            game.speed = 250;
        }
        
        game.fruit.position = { rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
        game.score++;
    }
}

void ExitGame()
{
    std::cout << " 게임을 종료합니다. " << std::endl;
}


void PlaySnakeGame()
{
    Game game;
    Setup(game);

    while (!game.gameOver)
    {
        DrawGameScreen(game);
        Update(game);
        Sleep(100);
    }

    system("cls");

    SetConsoleColor(14);
    std::cout << "\n  게임 오버 " << std::endl;
    std::cout << "  당신의 최종 점수 : " << game.score << "점입니다!"<<std::endl;
    SetConsoleColor(7);

    std::cout << "\n\n 게임을 다시 시작하겠습니까?";
    std::cout << "\n 다시 시작하려면 y, 아니면 아무 키나 누르세요. ";
    char input;
    std::cin >> input;

    if (input == 'y' || input == 'Y')
    {
        PlaySnakeGame();
    }
    else
    {
        ExitGame();
    }
}

void GameDescription()
{
    std::cout << " === 게임 설명 ===" << std::endl;
    std::cout << " wasd로 조작하시면 됩니다." << std::endl;

    std::cout << "그럼 게임을 시작하시겠습니까? (y): ";

    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        PlaySnakeGame();
    }
    else
    {
        std::cout << "그럼 게임을 시작하겠습니다 ";
        PlaySnakeGame();
    }
}

int main()
{
    std::cout << "\n\n  === 게임 시작 화면 ===" << std::endl;
    std::cout << "\n     1. 게임 시작" << std::endl;
    std::cout << "     2. 게임 설명" << std::endl;
    std::cout << "     3. 게임 종료" << std::endl;

    char choice;
    std::cin >> choice;

    srand(time(NULL));

    switch (choice)
    {
    case '1':
        PlaySnakeGame();
        break;
    case '2':
        GameDescription();
        break;
    case '3':
        ExitGame();
        break;
    default:
        std::cout << "게임을 종료하겠습니다." << std::endl;
        break;
    }

    return 0;
}
