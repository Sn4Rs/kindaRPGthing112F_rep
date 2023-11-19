#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TARGET_ATTR 4

struct A {
	int hitpoints;
	int atk;
	int crit;
	int def;
};

int testingtestwrite()
{
	//declare structure
	static struct A target;
	//the thing to write in
	int targetData[4] = { 0 }; //HP ATK CRIT DEF
	
	targetData[0] = target.hitpoints;
	targetData[1] = target.atk;
	targetData[2] = target.crit;
	targetData[3] = target.def;

	//create pointer for file
	FILE* fptr;
	fptr = fopen("C:\\Users\\USER\\OneDrive\\桌面\\C專題112上\\someRPG\\text2.txt", "w");
	//if failed to open return error
	if (fptr == NULL)
	{
		printf("ERROR: can't create/open file");
		exit(1);
	}

	//(optional) ask for input
	//printf("enter num: "); scanf("%d", &num);

	//write in saved
	for (int i = 0; i < TARGET_ATTR; i++)
	{
		fprintf("%d", targetData[i]);
	}
	
	fclose(fptr);
	return 0;
}