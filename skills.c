#define _CRT_SECURE_NO_WARNINGS


typedef struct {
	int skill_ID;
	char skillName[20];
	int skillType;
	int skillDmg;
	int maxCharges;
}Skill;

Skill skillLib[20] = {
	{0,"Classic Fireball",2,10,5},
};

typedef struct {
	int slot;
	char skillName[20];
	int skillType;
	int skillDmg;
	int skillCharge;
	int Occupied;
}Skillset;

Skillset defaultset[6];

void learnskill(Skill* learn, Skillset* charslot) {
	for (int i = 0; i < 6; i++) {
		if (charslot->Occupied == 0) {
			strcpy(learn->skillName, charslot->skillName);
			charslot->skillType = learn->skillType;
			charslot->skillDmg = learn->skillDmg;
			charslot->skillCharge = learn->maxCharges;

		}
	}
}

void listSkillset()
{

}