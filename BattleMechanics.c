#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#pragma once
#include "BattleMechanics.h"
#include "Mob_UsrStruct.c"
#include "itemActions.c"



//time counters
short Round = 1;
short ItemEffect[10];
//retreat option
int whiteFlag = 0;
//middle message field
typedef struct {
	char* message1[30];
	char* message2[30];
	char* message3[40];
}MsgField;
MsgField actionResult;


//action msg struct
struct Actions {
	char row1[30];
	char row2[30];
}playerTurn =
{ "1.ITEM          2.RETREAT",
  "3.ATTACK        4.SKILL" };

//Attack Actions
struct AttackAction {
	int moveID;
	char skillName[15];
	int buffHitC; //add to hitC
	int buffBaseD; //add to base damage
	float buffCritD; //add to crit damage
};
struct AttackAction AttackMove[3] = {
	{ 1,"Fast Attack",10,1,-0.3 } ,
	{ 2,"Heavy Slam",-20,5, 0.6 },
	{0 ,"Previous",0,0,0},
};

//effect functions
//print 1by1 (mainly used in action field
inline void coolprint(char input[])
{
	int i = 0;
	while (input[i] != '\0') {
		printf("%c", input[i]);
		Sleep(15);
		i++;
	}
}


//roll the fucking D20, remember to use variable to store results
inline int diceRoll()
{
	int roll = rand() % 100; //roll the dice
	printf("\nROLL THE DICE");
	printf(" \n%5d\n", roll);
	Sleep(1000); //see the result
	return roll;
}


//list target data
inline int listTargetData() {
	printf("%s\n", cur_target.MobName);
	printf("Hitpoints: ");
	for (int i = 0; i < cur_target.hitpoints; i += 2) {
		printf("|");
		Sleep(20);
	}
	printf("%3d\n", cur_target.hitpoints);
	printf("\n\n");
	return 0;
}

//central message field
inline int listMsgField(MsgField message)
{
	printf("Round %3d\n", Round);
	printf("%s\n", message.message1);
	printf("\r");
	for (int i = 0; i < 15; i++) {
		printf(" ");
		Sleep(10);
	};
	printf("%s\n", message.message2);
	printf("%s\n", message.message3);
	return 0;
}

//list user data
inline int listUserData()
{
	printf("%20s", cur_user.UsrName);
	printf("\nHitpoints ");
	for (int i = 0; i < cur_user.hitpoints; i += 2) {
		printf("|"); Sleep(20);
	}
	printf("\n%12d", cur_user.hitpoints);
	printf("%18s%3d \n", "ATK", cur_user.atk);
	printf("%30s%3d \n", "DEF", cur_user.def);
	printf("%30s%3d \n", "HIT%", cur_user.hitC);
	printf("%30s%3d \n", "CRIT%", cur_user.critC);
}

//actions field
inline int listActionField()
{
	//generate boundary
	for (int i = 0; i < BOUND__HIGH + 1; i++) {
		if (i == 0 || i == 5) {
			for (int x = 0; x < 35; x++) {
				printf("*"); if (x == 34) printf("\n");
			}
		}//top&bottom
		//printf("*"); 
		if (i == 1) { printf("%s", playerTurn.row1); printf("\n"); }
		if (i == 2) { printf("%s", playerTurn.row2); printf("\n"); }
	}
	return 0;
}

//just for switching menus,lists until player stats, remember to print current menu
inline int fastClear()
{
	system("cls");
	for (int i = 0; i < 36; i++) {
		putchar('-');
	}
	printf("\n");
	//listTargetData but no sleep
	printf("%s\n", cur_target.MobName);
	printf("Hitpoints: ");
	for (int i = 0; i < cur_target.hitpoints; i += 2) {
		printf("|");
	}
	printf("%3d\n", cur_target.hitpoints);
	printf("\n\n");//blank field

	//list user data but no sleep
	for (int i = 0; i < 36; i++) {
		putchar('-');
	}
	printf("\n");
	printf("%20s", cur_user.UsrName);
	printf("\nHitpoints ");
	for (int i = 0; i < cur_user.hitpoints; i += 2) {
		printf("|");
	}
	printf("\n%12d", cur_user.hitpoints);
	printf("%18s%3d \n", "ATK", cur_user.atk);
	printf("%30s%3d \n", "DEF", cur_user.def);
	printf("%30s%3d \n", "HIT%", cur_user.hitC);
	printf("%30s%3d \n", "CRIT%", cur_user.critC);
	return 0;
}

inline int listAttackMove()
{	//boundary
	for (int i = 0; i < MENU_HEIGHT + 1; i++)
	{
		if (i == 0) {
			for (int x = 0; x < 35; x++) {
				printf("*"); if (x == 34) printf("\n");
			}
		}
	}
	printf("    SKILL        HIT%%BUFF  SKILL DAMAGE\n");
	for (int x = 0; x < 3; x++) {
		printf("%d%14s%10d%13d\n", AttackMove[x].moveID, AttackMove[x].skillName, AttackMove[x].buffHitC, AttackMove[x].buffBaseD + cur_user.atk);
	}
}
inline int selectAttack()
{
	//attackmove menu
	char selectSub3 = _getch();
	if (selectSub3 == '1')
	{
		int roll = diceRoll();
		//light attack move rotation
		if (roll <= cur_user.critC) //within crit successful range
			usrAttack_HitCritical(&AttackMove[0], &cur_target);
		else if (roll <= cur_user.hitC)
			usrAttack_Hit(&AttackMove[0], &cur_target);
		else {
			//moster action;
			strcpy(actionResult.message1, "Nothing Happened.");
			updateRound(actionResult);
		}
	}
	else if (selectSub3 == '2') {
		int roll = diceRoll();
		//light attack move rotation
		if (roll <= cur_user.critC) //within crit successful range
			usrAttack_HitCritical(&AttackMove[1], &cur_target);
		else if (roll <= cur_user.hitC)
			usrAttack_Hit(&AttackMove[1], &cur_target);
		else {
			//moster action;
			strcpy(actionResult.message1, "Nothing Happened.");
			updateRound(actionResult);
		}
	}
	else if (selectSub3 == '0') {
		fastClear();
		listActionField();
	}
}

inline int listInvMenu()
{//boundary
	for (int x = 0; x < 35; x++) printf("*"); printf("\n");
	printf("             ITEM        INVENTORY\n");
	for (int i = 0; i < 10; i++) {
		if (invHold[i][0] <= 0) continue;
		printf("%d%16s", util[i].item_ID, util[i].item_Name); //1,2
		//printf("%d", util[i].itemBuff_HP); //4
		//printf("%d", util[i].itemBuff_atk); //5
		//printf("%d", util[i].itemBuff_hitC); //6
		//printf("%d", util[i].itemBuff_critC); //7
		//printf("%d", util[i].itemBuff_critD); //8
		//printf("%d", util[i].itemBuff_def); //9

		printf("%14d / %3d", invHold[i][0], invHold[i][1]);
		printf("\n");
	}
	return 0;
}
inline int selectItem()
{
	int opt = _getch();
	opt -= '0'; //nasty trick to convert
	if (opt == 0) {
		fastClear(); listActionField(); return NULL; //back to root menu, rerun loop
	}
	else {
		if (invHold[opt][0] == 0) { //none left
			printf("\nBut What Are You Looking For?");
			Sleep(1500);
			fastClear(); listInvMenu(); selectItem();
		}
		printf("\n%s", util[opt].itemDescription);
		printf("\n            USE (y/n)");
	}
	char sel;
	while (sel = _getch()) {
		if (sel == 'y') {
			cur_user.hitpoints += util[opt].itemBuff_HP;
			cur_user.atk += util[opt].itemBuff_atk;
			cur_user.hitC += util[opt].itemBuff_hitC;
			cur_user.critC += util[opt].itemBuff_critC;
			cur_user.critD += util[opt].itemBuff_critD;
			cur_user.def += util[opt].itemBuff_def;
			invHold[opt][0]--;
			ItemEffect[opt] += 2; //lasts for 2 rounds
			strcpy(actionResult.message1, "You used an Item");
			strcpy(actionResult.message2, util[opt].item_Name);
			//no overheals
			if (cur_user.hitpoints > cur_user.hitpoints_max) {
				cur_user.hitpoints = cur_user.hitpoints_max;
				strcpy(actionResult.message1, "You Healed");
				strcpy(actionResult.message2, "...But You Cannot Overheal");
			}
			updateRound(actionResult); return 0;
		}
		else if (sel == 'n') { fastClear(); listInvMenu(); selectItem(); return 0; }
	}
	return 0;
}

inline int checkRetreat(Mob* target)
{
	printf("\nYou Check Your Surroundings,\nThere May Be a Way Out.");
	printf("\n            Attempt (y/n)");
	char opt;
	while (opt = _getch()) {
		if (opt == 'y') {
			if (target->allowRetreat == 1) {
				whiteFlag = 1;
				strcpy(actionResult.message2, "You Escaped From The Battle");
				updateRound(actionResult); return 0;
			}
			else {
				strcpy(actionResult.message1, "The Entrance is Blocked,");
				strcpy(actionResult.message2, "There is No Escape.");
				updateRound(actionResult); return 0;
			}
		}
		else if (opt == 'n') {
			fastClear(); listActionField(); return 0;
		}
		else rewind(stdin);
	}
}
//crit action
inline int usrAttack_HitCritical(struct AttackAction* attackMove, Mob* target)
{
	int damage = ((cur_user.atk + attackMove->buffBaseD) * (cur_user.critD + AttackMove->buffCritD)) - target->def; //(base atk+skill atk) x (player critD+move critD) 
	//printf("\nCritical Hit");
	//Sleep(1000);
	if (damage <= 0) { damage = 0; strcpy(actionResult.message1, "Ineffective Hit! \n"); }
	else {
		target->hitpoints -= damage;

		strcpy(actionResult.message1, "Critical Hit!! \n");
		//strcpy(actionResult.message2, damage);
	}
	updateRound(actionResult);
	return 0;
}

inline int usrAttack_Hit(struct AttackAction* attackMove, Mob* target)
{
	int damage = ((cur_user.atk + attackMove->buffBaseD) - target->def); //base atk+skill atk
	if (damage <= 0) { damage = 0; strcpy(actionResult.message1, "Ineffective Hit! \n"); }
	else {
		target->hitpoints -= damage;
		char* dmgnum = ("%d damage", damage);
		strcpy(actionResult.message1, "Solid Hit! \n");
		strcpy(actionResult.message2, &dmgnum);
	}
	updateRound(actionResult);
	return 0;
}

//game system functions
inline int updateRound(MsgField lastaction)
{
	Round++;
	//check for item duration
	for (int i = 0; i < 10; i++) {
		if (ItemEffect[i] > 0) {
			ItemEffect[i]--;
			if (ItemEffect[i] == 0) {//end effect
				//cur_user.hitpoints -= util[i].itemBuff_HP;
				cur_user.atk -= util[i].itemBuff_atk;
				cur_user.hitC -= util[i].itemBuff_hitC;
				cur_user.critC -= util[i].itemBuff_critC;
				cur_user.critD -= util[i].itemBuff_critD;
				cur_user.def -= util[i].itemBuff_def;
				strcpy(lastaction.message3, "Some Item Effects Have Worn Off");
			}
		}
	}
	system("cls");
	for (int i = 0; i < 36; i++) {
		putchar('-');
	}
	printf("\n"); listTargetData();
	Sleep(1000);
	listMsgField(lastaction);
	Sleep(1000);
	for (int i = 0; i < 36; i++) {
		putchar('-');
	}
	printf("\n"); listUserData(); listActionField();
	strcpy(actionResult.message1, BLANKLINE);
	strcpy(actionResult.message2, BLANKLINE);
	strcpy(actionResult.message3, BLANKLINE); //reset msgfield
	rewind(stdin);
	return 0;
}


//save a Usr structure to a file (can predefine)
inline int writeUserData(Usr toSave, const char* filename)
{
	//create pointer for file
	FILE* file = fopen(filename, "wb"); //open input file code, write binary
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't create/open file\n");
		exit(1);
	}

	//write out saved
	int flag = 0;
	flag = fwrite(&toSave, sizeof(Usr), 1, file);
	//check
	if (flag)
	{
		printf("\nsave successful");
		//clean up the save message
		Sleep(500); printf("\r");
		for (int i = 0; i < 36; i++) {
			putchar('-');
			Sleep(20);
		}
		printf("\n");
	}

	else printf("save error\n");
	Sleep(500);
	fclose(file);
	return 0;
}

//load a Usr stat sheet save
inline int readUserData(const char* filename)
{
	//create pointer for file
	FILE* file = fopen(filename, "rb");
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't open file\n");
		exit(1);
	}
	//file opened, determine the start pos of data
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);
	//save into global struct: current target
	fread(&cur_user, sizeof(Mob), 1, file);
	return 0;
}

//save a Mob struct into a file, input filecode, func will read the code contents
inline int writeTargetData(Mob input, const char* filename)
{
	//create pointer for file
	FILE* file = fopen(filename, "wb"); //open input file code, write binary
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't create/open file\n");
		exit(1);
	}

	//write out saved
	int flag = 0;
	flag = fwrite(&input, sizeof(Mob), 1, file);
	//check
	if (flag)
	{
		printf("\nsave successful");
		//clean up the save message
		Sleep(500); printf("\r");
		for (int i = 0; i < 36; i++) {
			putchar('-');
			Sleep(20);
		}
		printf("\n");
	}

	else printf("save error\n");
	Sleep(500);

	fclose(file);
	return 0;
}

//read Mob struct into struct of current target
inline int readTargetData(const char* filename)
{
	//create pointer for file
	FILE* file = fopen(filename, "rb");
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't open file\n");
		exit(1);
	}
	//file opened, determine the start pos of data
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);
	//save into global struct: current target
	fread(&cur_target, sizeof(Mob), 1, file);
	return 0;
}
