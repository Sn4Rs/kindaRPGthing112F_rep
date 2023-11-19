#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//data file locations
#define MOBSTATS "C:\\Users\\USER\\OneDrive\\桌面\\C專題112上\\someRPG\\MobStats.bin"
#define USRSAVE  "C:\\Users\\USER\\OneDrive\\桌面\\C專題112上\\someRPG\\UserSave.bin"

#define TARGET_ATTR 5
#define DEFAULT_HP 20
#define DEFAULT_ATK 5
#define DEFAULT_CRITC 60
#define DEFAULT_DEF 2

//declare structs
// USER structure
struct Usr {
	char UsrName[50];
	int hitpoints;
	int atk;
	int critC;
	float critD;
	int def;
}userdefault = { "John Doe",10,5,60,1.4,2 };
//target structure
struct Mob {
	char MobName[50];
	int hitpoints;
	int atk;
	int critC;
	float critD;
	int def;
}targetdefault = { "dummy",DEFAULT_HP,DEFAULT_ATK,DEFAULT_CRITC,DEFAULT_DEF };

struct Mob cur_target;//data of the current target

//save a Mob struct into a file, input filecode, func will read the code contents
void writeTargetData(struct Mob input, const char* filename)
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
	flag = fwrite(&input, sizeof(struct Mob), 1, file);
	//check
	if (flag) printf("save successful\n");
	else printf("save error\n");
	fclose(file);
	return 0;
}

//read Mob struct into struct of current target
void readTargetData(const char* filename)
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
	fread(&cur_target, sizeof(struct Mob), 1, file);
	return 0;
}

//list target data
int listTargetData() {
	printf("%s\n", cur_target.MobName);
	printf("Hitpoints: ");
	for (int i = 0; i < cur_target.hitpoints; i++) {
		printf("\u2665");
		Sleep(20);
	}
	printf("%3d\n", cur_target.hitpoints);
	return 0;
}
//user critical hit to target!
int usrAction_HitCritical(struct Usr* user, struct Mob* target)
{
	int damage = user->atk * user->critD;
	target->hitpoints -= damage;
	return 0;
}


int main()
{
	//testing
	writeTargetData(targetdefault, MOBSTATS);
	readTargetData(MOBSTATS);
	listTargetData();

	return 0;
}