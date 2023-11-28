#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "BattleMechanics.h"

Mob targetdefault = { "dummy",DEFAULT_HP,DEFAULT_ATK,DEFAULT_CRITC,DEFAULT_DEF,0,10 };
Usr userdefault = { "John Doe",20,20,5,60,30,1.4,2,0,200 };

//effect functions
//print 1by1 (mainly used in action field
void coolprint(char input[])
{
	int i = 0;
	while (input[i] != '\0') {
		printf("%c",input[i]);
		Sleep(15);
		i++;
	}
}

int main()
{
	generateItemsList();
	writeTargetData(targetdefault, S_DUMMY);
	readTargetData(S_DUMMY);
	listTargetData();
	writeUserData(userdefault, USRSAVE);
	readUserData(USRSAVE);
	
	Items cur_inv[10];
	readItemsList(&cur_inv);
	for (int i = 0; i < 10; i++) {
		invHold[i][0] += 2;
		if (invHold[i][0] > invHold[i][1]) invHold[i][0] = invHold[i][1];
	}
	srand((unsigned)time(NULL)); //roll the fucking D20
	Round = 1;
		//init battle	
		//setting up the field
		listUserData(); listActionField(); 
	
		//start loop
		while (1) {
			//select options 1.item 2.retreat 3.attack 4.skill
			//open corresponding menu
			rewind(stdin);
			char select = _getch();
			switch (select) {
			case '1':fastClear(); listInvMenu();selectItem();break;
			case '2':break;
			case '3':fastClear(); listAttackMove(); selectAttack(); break;
			case '4':break;
			}
			//round timer
			if (cur_user.hitpoints <= 0 || cur_target.hitpoints <= 0) return 0;
		}
		//battle resolved
		//saveInv(cur_inv);
		system("pause");
		return 0;
	}