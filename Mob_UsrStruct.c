//data file locations
#define S_DUMMY "..\\DummyStats.bin"
#define USRSAVE  "..\\UserSave.bin"

//entity info
#define TARGET_ATTR 5
#define DEFAULT_HP 40
#define DEFAULT_ATK 5
#define DEFAULT_CRITC 60
#define DEFAULT_DEF 2
//declare structs
// USER structure
typedef struct
{
	char UsrName[50]; //1
	int hitpoints; //2
	int hitpoints_max; //3
	int atk; //4
	int hitC; //5
	int critC; //6
	float critD; //7
	int def; //8
	int totalExp; //9
	int bpcurrency; //10
	int bpInv[10]; //11
}Usr;

//target structure
typedef struct
{
	char MobName[50];
	int hitpoints;
	int atk;
	int critC;
	float critD;
	int def;
	int dropGold;
	int dropExp;
	int allowRetreat;
}Mob;


Mob cur_target;//data of the current target
Usr cur_user;//this is you
