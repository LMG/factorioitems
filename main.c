#include <stdio.h>
#include <stdlib.h>

struct Item;

typedef struct Cpnt {
  struct Item* item;
  int nb;
} Cpnt;

typedef struct Item {
  float tps;
  int nbOut;
  Cpnt* cpnts[6];
} Item;
  

int main(int argc, char* argv[])
{
  //Definitions: we only consider those items that can't be provided by the bus
  //Red science
  Item gearwheel = { .cpnts = {NULL}, .tps = 0.5, .nbOut = 1};
  Cpnt redScienceCpnt1 = (Cpnt) {.item = &gearwheel, .nb = 1};
  Item redScience = { .cpnts = {&redScienceCpnt1}, .tps = 5, .nbOut = 1};
  //Green science
  Cpnt yellowArmCpnt1 = (Cpnt) {.item = &gearwheel, .nb = 1};
  Item yellowArm = { .cpnts = {&yellowArmCpnt1}, .tps = 0.5, .nbOut = 1};
  Cpnt transportBeltCpnt1 = (Cpnt) {.item = &gearwheel, .nb = 1};
  Item transportBelt = { .cpnts = {&transportBeltCpnt1}, .tps = 0.5, .nbOut = 2};
  Cpnt greenScienceCpnt1 = (Cpnt) {.item = &yellowArm, .nb = 1};
  Cpnt greenScienceCpnt2 = (Cpnt) {.item = &transportBelt, .nb = 1};
  Item greenScience = { .cpnts = {&greenScienceCpnt1, &greenScienceCpnt2}, .tps = 6, .nbOut = 1};

  printf("On produit %.2f science rouge par seconde avec 1 usine\n", redScience.nbOut / redScience.tps);
  printf("On produit %.2f gear wheels par seconde avec 1 usine\n", gearwheel.nbOut / gearwheel.tps);
  printf("On consomme %.2f gear wheels par seconde avec 1 usine de science rouge\n", redScience.cpnts[0]->nb / redScience.tps);
  printf("On a besoin de %f usines rouges pour consommer la totalité d'1 usine de gear wheels\n", 
          (redScience.cpnts[0]->item->nbOut / redScience.cpnts[0]->item->tps)/
          (redScience.cpnts[0]->nb / redScience.tps));
  printf("On produit %.2f science verte par seconde avec 1 usine\n", greenScience.nbOut / greenScience.tps);
  printf("On consomme %.2f gear wheels par seconde avec 1 usine de science verte\n", 
        ( greenScience.cpnts[0]->nb *
            (greenScience.cpnts[0]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps)
          + greenScience.cpnts[1]->nb * 
            (greenScience.cpnts[1]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps) )
        / greenScience.tps);
  printf("On a besoin de %f usines verte pour consommer la totalité d'1 usine de gear wheels\n", 
        ( greenScience.cpnts[0]->item->cpnts[0]->item->nbOut / greenScience.cpnts[0]->item->cpnts[0]->item->tps ) /
        ( ( greenScience.cpnts[0]->nb *
              (greenScience.cpnts[0]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps)
            + greenScience.cpnts[1]->nb * 
              (greenScience.cpnts[1]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps) )
          / greenScience.tps ) );

  return EXIT_SUCCESS;
}

// returns the number of factories to fully consume one factory worth of chosen component
int nbFact(Item* obj, Item* cpnt)
{
  int nbFact = 1;
  for(Item* o = obj; o != cpnt; )
  {/*
    float cpntPs = i->nbOut/i->tps;
    float nbFactC = cpntPs / (o->cpnts[item]/o->tps);
 */ }
  return nbFact;
}
