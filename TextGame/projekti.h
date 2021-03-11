#ifndef projekti
#define projekti





typedef struct Weapons{
    char name[20];
    int maxdmg;
} Weapon;

typedef struct Players{
    char name[20];
    int HP;
    int XP;
    Weapon weaponofchoise;
} Player;

typedef struct Games{
    Player *players;
    int count;
}Game;

Game* addcharacter(Game *game, const char *name,int hp, const char *weaponname, int weapondmg);

Game* attack(Game *game,const char* attacker,const char* victim);


void save(Game *game,char *file);

Game * load(char *file);

void printcharacters(Game *game);

#endif