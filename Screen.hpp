#pragma once
#include <windows.h>

void gotoxy(int x, int y);

int clearBuffer(char* screenBuf, int width, int height);

int writeString(const char* string, int x, int y);

int setTitle(char* screenBuf, int width, int height);

int setGameOver(char* screenBuf, int width, int height);

int setDescription(char* screenBuf, int width, int height);

int setRanking(char* screenBuf, int width, int height);