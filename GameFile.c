#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "BattleMechanics.h"

Mob targetdefault = { "dummy",DEFAULT_HP,DEFAULT_ATK,DEFAULT_CRITC,1,DEFAULT_DEF,0,10,1 };
Usr userdefault = { "John Doe",20,20,5,60,30,1.4,2,0,200 };


int main()
{
	//for testing, will remove upon completion
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

	//beta starts here
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
			case '2':checkRetreat(&cur_target); break;
			case '3':fastClear(); listAttackMove(); selectAttack(); break;
			case '4':break;
			}
			//round timer
			if (cur_user.hitpoints <= 0 || cur_target.hitpoints <= 0 || whiteFlag==1) return 0;
		}
		//battle resolved
		//saveInv(cur_inv);
		system("pause");
		return 0;
	}