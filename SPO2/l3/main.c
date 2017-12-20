//#include <process.h>
#include <stdio.h>
#include <iostream>
//#include <windows.h>
//#include <conio.h>
using namespace std;
int buf[5];//буффер
int SpeedWrite = 500;//скорость записи
int SpeedRead = 500;//скорость чтения
int red = 0;//счетчик для массива чтения
int writ = 0;//счетчик для массива записи
char ch;//считывание кнопок
BOOL flag1 = TRUE, flag2=TRUE;//exit  function
int flag = 0;
HANDLE hMutex;
void Write(void* pParams)
{
	int num=1;
	
	while (flag1)
	{
		
		WaitForSingleObject(
			hMutex,  // идентификатор объекта
			INFINITE// время ожидания в милисекундах
			);
		if (writ >= 5)
			writ = 0;
		if (flag < 5)
		{
			buf[writ++] = num++;
			flag++;
		}
		ReleaseMutex(hMutex);	
			Sleep(SpeedWrite);
	}
	
}
void Read(void* pParams)
{
	int i;
	while (flag2)
	{
		
		WaitForSingleObject(hMutex, INFINITE);
		if (red >= 5)
			red = 0;
		if (flag > 0)
		{
			buf[red++] = 0;
			flag--;
		}		
		ReleaseMutex(hMutex);
		Sleep(SpeedRead);
	}
	
}
void speed(void* pParams)
{
	while (flag2)
	{
		ch = _getch();
		switch (ch)
		{
		case '1':
		{SpeedWrite += 100;
		break; }
		case '2':
		{SpeedWrite -= 100;
		break; }
		case'3':
		{SpeedRead += 100;
		break; }
		case'4':
		{SpeedRead -= 100;
		break; }
		case'5':
		{flag1 = FALSE;
		flag2 = FALSE;
		break; }
		}
	}
}
int main(void)
{
	hMutex = CreateMutex(
		NULL,// атрибут безопастности
		FALSE,// флаг начального владельца
		NULL// имя объекта
		);
	_beginthread(
		Write,  // адрес функции задачи
		0,// начальный размер стека в байтах
		NULL// параметры для задачи
		);
	_beginthread(Read, 0, NULL);
	_beginthread(speed, 0, NULL);
	while (flag1)
	{
		if (SpeedRead <= 0)
			SpeedRead = 100;
		if (SpeedWrite <= 0)
			SpeedWrite = 100;
		WaitForSingleObject(hMutex, INFINITE);
		printf("%d  %d  %d  %d  %d        %d %d  SpeedRead 
SpeedWrite\n", buf[0], buf[1], buf[2], buf[3], buf[4], SpeedRead, 
SpeedWrite);
		ReleaseMutex(hMutex);
		Sleep(50);
	}
	
	return 0;
