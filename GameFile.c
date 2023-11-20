﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//data file locations
#define MOBSTATS "..\\MobStats.bin"
#define USRSAVE  "..\\UserSave.bin"
//entity info
#define TARGET_ATTR 5
#define DEFAULT_HP 20
#define DEFAULT_ATK 5
#define DEFAULT_CRITC 60
#define DEFAULT_DEF 2

#define DUMMYTEXT "dummy text super effective!!!"
#define BLANKLINE "\n"
#define BOUND__HIGH 5 

//declare structs
// USER structure
struct Usr {
	char UsrName[50];
	int hitpoints;
	int atk;
	int critC;
	float critD;
	int def;
}userdefault = { "John Doe",20,5,60,1.4,2 };
//target structure
struct Mob {
	char MobName[50];
	int hitpoints;
	int atk;
	int critC;
	float critD;
	int def;
}targetdefault = {"dummy",DEFAULT_HP,DEFAULT_ATK,DEFAULT_CRITC,DEFAULT_DEF};

struct Mob cur_target;//data of the current target
struct Usr cur_user;//this is you

//action msg struct
struct Actions {
	char row1[30];
	char row2[30];
}playerTurn=
{"1.ITEM          2.OPTIONS",
  "3.ATTACK         4.SKILL"};

struct MsgField {
	char *message1[30];
	char *message2[30];
}genericmsg = { DUMMYTEXT,DUMMYTEXT }; 
struct MsgField blankmsg = { BLANKLINE,BLANKLINE };
struct MsgField actionResult = { "",""};

//effect functions
void clrscr();
void coolprint(char s[]);
void coolprint(const char *s)
{
	int i = 0;
	while (s != '\0') {
		putchar(s[i]);
		Sleep(15);
		i++;
	}
}

//game system functions
int updateRound(struct MsgField lastaction)
{
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
	printf("\n"); listUserData();
	return 0;
}


//save a Usr structure to a file (can predefine)
void writeUserData(struct Usr toSave, const char* filename)
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
	flag = fwrite(&toSave, sizeof(struct Mob), 1, file);
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
void readUserData(const char* filename)
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
	fread(&cur_user, sizeof(struct Mob), 1, file);
	return 0;
}

//save a Mob struct into a file, input filecode, func will read the code contents
void writeTargetData(struct Mob input , const char *filename)
{
	//create pointer for file
	FILE*file = fopen(filename, "wb"); //open input file code, write binary
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't create/open file\n");
		exit(1);
	}

	//write out saved
	int flag = 0;
	flag= fwrite(&input, sizeof(struct Mob), 1, file);
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
void readTargetData(const char *filename)
{
	//create pointer for file
	FILE*file= fopen(filename, "rb");
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
	fread(&cur_target, sizeof(struct Mob), 1, file);
	return 0;
}

//list target data
int listTargetData() {
	printf("%s\n", cur_target.MobName);
	printf("Hitpoints: "); 
	for (int i = 0; i < cur_target.hitpoints; i++) {
		printf("|");
		Sleep(20);
	}
	printf("%3d\n", cur_target.hitpoints);
	printf("\n\n");
	return 0;
}

//central message field
int listMsgField(struct MsgField message)
{
	printf("%s\n",message.message1);
	printf("%s\n", message.message2);
	return 0;
}

//list user data
int listUserData()
{
	printf("%20s", cur_user.UsrName);
	printf("\nHitpoints "); 
	for (int i = 0; i < cur_user.hitpoints; i += 2) {
		printf("|"); Sleep(20);
	}
	printf("\n%12d", cur_user.hitpoints);
	printf("%18s%3d \n", "ATK", cur_user.atk);
	printf("%30s%3d \n", "DEF", cur_user.def);
	printf("%30s%3d \n", "CRIT%", cur_user.critC);
	listActionField();
}

//actions field
int listActionField()
{
	//generate boundary
	for (int i = 0; i < BOUND__HIGH; i++) {
		if (i == 0 || i == 5) {
			for (int x = 0; x < 35; x++) {
				printf("*"); if(x==34) printf("\n");
			}
		}//top&bottom
		//printf("*"); 
		if (i == 1) { printf("%s", playerTurn.row1); printf("\n"); }
		if (i == 2) { printf("%s", playerTurn.row2); printf("\n"); }
	}
	return 0;
}
//messages in field
int listActions()
{
		printf(" %s\n %s",playerTurn.row1,playerTurn.row2 );
		return 0;
}
//crit action
int usrAction_HitCritical(struct Usr *user ,struct Mob *target)
{
	int damage = user->atk * user->critD;
	//printf("\nCritical Hit");
	//Sleep(1000);
	target->hitpoints -= damage;
	strcpy(actionResult.message1, "Critical Hit!! %d DMG \n",damage);
	//strcpy(actionResult.message2, "%d DMG",damage);
	updateRound(actionResult);
	return 0;
}


int main()
{
	//testing
	writeTargetData(targetdefault, MOBSTATS);
	readTargetData(MOBSTATS);
	listTargetData();
	writeUserData(userdefault, USRSAVE);
	readUserData(USRSAVE);
	listUserData();
	usrAction_HitCritical(&cur_user,&cur_target);
	
	system("pause");
	return 0;
}