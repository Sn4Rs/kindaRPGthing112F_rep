#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define TARGET_ATTR 5
#define DEFAULT_HP 100
#define DEFAULT_ATK 5
#define DEFAULT_CRITC 60
#define DEFAULT_DEF 2

struct Mob {
	char MobID[10];
	int HP;
	int Atk;
	int Crit;
	int Def;
} Monster1 = {"Bob",0,0,0,0};

char slowprint(char[]);
char slowprint(n)
{
	
	while (n !='¡C') {
		printf("%d", n);
		Sleep(30);
	}
	printf("\n");
}


void teststruct()
{
	slowprint("kadkfj;alkdjf;askf");
}