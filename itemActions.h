#pragma once

#define ITEMFILE "..\\ItemsList.bin"

typedef struct {
	char item_ID; //1
	char item_Name[20]; //2
	char itemDescription[80]; //3
	int itemBuff_HP; //4
	int itemBuff_atk; //5
	int itemBuff_hitC; //6
	int itemBuff_critC; //7
	float itemBuff_critD; //8
	int itemBuff_def; //9
	int carryMax; //10 not listed
	
}Items;
Items util[10] = {
{0,"Previous","",0,0,0,0,0,0,0},
{1,"Heal(S)","Heals for 8",8,0,0,0,0,0,5},
{2,"Heal(M)","Heals for 15",15,0,0,0,0,0,3},
{3,"Heal(L)","Heals for 28",28,0,0,0,0,0,2},
{4,"Crit Juice","Bonus Hit / Crit Performance\n\
Hit%+10 Crit%+20 CritDmg+0.4x",0,0,10,20,0.4,0,5},
{5,"Slam Juice","Slapp dem Cheeks Harder \n\
Base Attack+8  Hit%+15 ",0,8,15,0,0,0,5},
{6,"Armor Plate","Blocks Some Damage\n  ",0,0,0,0,0,15,4},
{7,"Emergency Armor","Blocks a Lot of Damage, Very Heavy",0,0,0,0,0,40,1},
{8,"J U I C C","Why Are Those All Prime Numbers???",7,13,17,19,2.3,29,1},
{9,"DewRitos","The Ultimate Gamer Food\n Crazy Heals & Crit Boost", 357,36,0,42,0,0,1},
};

int invHold[10][2] = //0.current hold 1. max carry 
{
	{9999,9999},//0 is empty, gold will be in character sheet
	{0,5},//1
	{0,3},//2
	{0,2},//3
	{0,5},//4
	{0,5},//5
	{0,4},//6
	{0,1},//7
	{0,1},//8
	{0,1},//9
};

//export item list
int generateItemsList() //init generation
{
	//create pointer for file
	FILE* file = fopen(ITEMFILE, "wb"); //open input file code, write binary
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't create/open file\n");
		exit(1);
	}
	//write out saved
	int flag = 0;
	flag = fwrite(&util, sizeof(Items), 10, file);
	//check
	if (flag)
	{
		printf("\nITEMS generate successful");
		//clean up the save message
		Sleep(500); printf("\r");
		for (int i = 0; i < 36; i++) {
			putchar('-');
			Sleep(20);
		}
		//printf("\n");
		printf("\r");
		return 0;
	}

	else printf("save error\n");
	Sleep(500);
	fclose(file);
}

int saveInv(currentInv) //save player inventory
{
	//create pointer for file
	FILE* file = fopen(ITEMFILE, "wb"); //open input file code, write binary
	//if failed to open return error
	if (file == NULL)
	{
		printf("ERROR: can't create/open file\n");
		exit(1);
	}
	//write out saved
	int flag = 0;
	flag = fwrite(&currentInv, sizeof(Items), 10, file);
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


Items* readItemsList(Items* inv)
{
	FILE* file;
	file = fopen(ITEMFILE, "rb");
	if (file == NULL)return NULL;
	if (fread(inv, sizeof(Items), 10, file) != 1) return NULL;
	Items* here = malloc(sizeof(Items) * 10);
	fread(here, sizeof(Items), 10, file);

	fclose(file);
	return here;
}
