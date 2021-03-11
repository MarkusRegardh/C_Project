#include "projekti.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

 
Game * addcharacter (Game * game, const char *name, int hp, const char *weaponname, int weapondmg)
{
    game->players = realloc (game->players, (game->count + 1) * sizeof (Player));
    strcpy (game->players[game->count].name, name);
    game->players[game->count].HP = hp;
    game->players[game->count].XP = 0;
    strcpy (game->players[game->count].weaponofchoise.name, weaponname);
    game->players[game->count].weaponofchoise.maxdmg = weapondmg;
    game->count++;
    printf ("%s was added to the game.\n", name);
  return game;
}


 
Game* attack (Game * game, const char *attacker, const char *victim)
{
  
    
    int i;
    int one=-1;
    int two=-1;
    int dmgdelt=-1;

    for (i = 0; i < game->count; i++)
    {
        if (strcmp ((const char *) game->players[i].name, attacker) == 0)
	    {
            one =i;
            dmgdelt = rand() % game->players[i].weaponofchoise.maxdmg+1;
        }
        if (strcmp ((const char *) game->players[i].name, victim) == 0)
	    {
	        two =i;
        }
    
    }
    if (dmgdelt!=-1 && one!=-1 && two!=-1){
        if (game->players[two].HP==0){
            printf("%s is already dead.\n",victim);
        } else if (game->players[one].HP==0){
            printf("%s can not attack as he is dead\n",attacker);
        }
        else if (game->players[two].HP>dmgdelt) 
        {
            game->players[two].HP -= dmgdelt;
            game->players[one].XP+=dmgdelt;
            printf ("%s attacked %s with %s and did %d dmg. %s has %d HP left.\n%s gained %d XP.\n", attacker, victim, game->players[one].weaponofchoise.name, dmgdelt, victim, game->players[two].HP,attacker,dmgdelt);
        }else{
            dmgdelt=game->players[two].HP;
            game->players[two].HP=0;
            game->players[one].XP+=dmgdelt;
            game->players[one].XP+=10;
            printf("%s attacked %s with %s and did %d dmg. %s is dead.\n%s gained %d XP plus 10 bonus xp for dealing the killing blow.\n", attacker, victim, game->players[one].weaponofchoise.name,dmgdelt, victim,attacker, dmgdelt);
        }
        }else{
            printf("The attack failed for some reason.\n");
        }
        return game;
} 
 





void printcharacters(Game *game)
{
    int i,j;
    Player tmp;
    for (i=0;i<game->count;i++){
        for(j=i+1;j<game->count;j++){
            if (game->players[j].HP!=0){
                if (game->players[i].XP<game->players[j].XP){
                    tmp = game->players[i];
                    game->players[i]=game->players[j];
                    game->players[j]=tmp;
                } else if (game->players[i].HP==0){
                    tmp=game->players[j];
                    game->players[j]=game->players[i];
                    game->players[i]=tmp;
                }
        }
    }
    }
    for (i=0;i<game->count;i++){
        printf("Name: %s HP: %d XP: %d Weapon: %s Weapondmg: %d\n",game->players[i].name,game->players[i].HP,game->players[i].XP,game->players[i].weaponofchoise.name,game->players[i].weaponofchoise.maxdmg);
    }
    }


void save(Game *game, char *file){
    FILE *f = fopen(file,"w");
    if (!f){
        printf("saving failed.\n");
        return;
    }
    int i;
    for (i=0;i<game->count;i++){
        char temp[50];
        sprintf(temp,"%s %d %d %s %d \n",game->players[i].name,game->players[i].HP,game->players[i].XP,game->players[i].weaponofchoise.name,game->players[i].weaponofchoise.maxdmg);
        fputs(temp,f);
    }
    fclose(f);
    printf("saved\n");
}
 
Game* load(char *file){
    FILE *f;    
    f = fopen(file,"r");
    if (!f){
        printf("load failed, could not find the file\n");
    }
    Game *game;
    game = malloc(sizeof(Game));
    game->count=0;
    game->players=malloc(sizeof(Player));
    int i=0;
    char name[20];
    int HP;
    int XP;
    char gun[20];
    int dmg;
    while (fscanf(f,"%s %d %d %s %d",name,&HP,&XP,gun,&dmg)==5){
        game->players = realloc (game->players, (game->count + 1) * sizeof (Player));
        strcpy(game->players[i].name,(const char*)name);
        strcpy(game->players[i].weaponofchoise.name,(const char*)gun);
        game->players[i].HP=HP;
        game->players[i].XP=XP;
        game->players[i].weaponofchoise.maxdmg=dmg;        
        i++;
        game->count++;
    }
    fclose(f);
    if (i==0){
        printf("The file did not contain a saved Game\n");
        return game;
    } else {
        printf("Game loaded\n");
        return game;
    }
}




int main ()
{
printf("Welcome\n");
Game *game;
game = malloc(sizeof(Game));
game->count=0;
game->players=malloc(sizeof(Player));
char input[80];
fgets(input,sizeof(input),stdin);
while (input[0]!='Q' && !feof(stdin)){
    if (input[0]=='A'){
        char name[20] = "";
        char gun[20] = "";
        int HP = -1;
        int dmg = -1;
        sscanf(input,"A %s %d %s %d",name,&HP,gun,&dmg);
        if (name[0]=='\0' || gun[0]=='\0' || HP==-1 || dmg==-1){
            printf("There was something wrong with your input, please try again\n");
        } else {
            game = addcharacter(game,(const char*)name,HP,(const char*)gun,dmg);
        }
    } else if (input[0]=='H'){
        char attacker[20]="";
        char victim[20]="";
        sscanf(input,"H %s %s",attacker,victim);
        if (attacker[0]=='\0'||victim[0]=='\0'){
            printf("There was something wrong with your input, please try again\n");
        } else {
            game = attack(game,(const char*)attacker,(const char*)victim);
        }
    } else if (input[0]=='L'){
        printcharacters(game);
    } else if (input[0]=='W'){
        char file[40];
        sscanf(input,"W %s",file);
        save(game,file);
    } else if (input[0]=='O'){
        char file[40];
        sscanf(input,"O %s",file);
        FILE *f;
        f=fopen(file,"r");
        if (!f){
            printf("File can not be found\n");
        } else {
            fclose(f);
            free(game->players);
            free(game);
            game = load(file);
        }
    } else {
        printf("unknown command\n");
    }  
        fgets(input,sizeof(input),stdin);
    }
    printf("Thank you for playing");
    free(game->players);
    free(game);
    return 0;
}