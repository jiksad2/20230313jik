#include "screen.hpp"
#include <stdio.h>
#include <cstring>

void gotoxy(int x, int y) {
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int clearBuffer(char* screenBuf, int width, int height)
{
	int i = 0;	
	int j = 0; 
	while (j < height)
	{
		while (i < width + 1)
		{
			if (i == width)
				screenBuf[i + (j * (width + 1))] = '\n';
			else
			{
				if (i == 0 || i == 1 || i == (width - 1) || i == (width - 2) || j == 0 || j == (height - 1))
					screenBuf[i + (j * (width + 1))] = '#';
				else
					screenBuf[i + (j * (width + 1))] = ' ';
			}
			i = i + 1;
		}
		i = 0;
		j = j + 1;
	}
	screenBuf[height * (width + 1) - 1] = '\0';
	return 0;
}

int writeString(const char* string, int x, int y)
{
	gotoxy(x, y);
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == '\n') {
			gotoxy(x, y + 1);
			y++;
		}
		else printf("%c", string[i]);
	}

	gotoxy(6, y);


	return 0;
}

int setTitle(char* screenBuf, int width, int height)
{
	width = 40; height = 18;
	clearBuffer(screenBuf, width, height); return 0;
}

int setGameOver(char* screenBuf, int width, int height)
{
	width = 40; height = 18;
	clearBuffer(screenBuf, width, height); return 0;
}

int setDescription(char* screenBuf, int width, int height) {
	width = 40; height = 18;
	clearBuffer(screenBuf, width, height); return 0;
}

int setRanking(char* screenBuf, int width, int height) {
	width = 40; height = 18;
	clearBuffer(screenBuf, width, height); return 0;
}