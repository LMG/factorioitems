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
  
float demand(Item* obj, Item* cpnt);
float nbFact(Item* obj, Item* cpnt);

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
  printf("On a besoin de %.2f usines rouges pour consommer la totalité d'1 usine de gear wheels\n", 
          (redScience.cpnts[0]->item->nbOut / redScience.cpnts[0]->item->tps)/
          (redScience.cpnts[0]->nb / redScience.tps));
  printf("On produit %.2f science vertes par seconde avec 1 usine\n", greenScience.nbOut / greenScience.tps);
  printf("On consomme %.2f gear wheels par seconde avec 1 usine de science verte\n", 
        ( greenScience.cpnts[0]->nb *
            (greenScience.cpnts[0]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps)
          + greenScience.cpnts[1]->nb * 
            (greenScience.cpnts[1]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps) )
        / greenScience.tps);
  printf("On a besoin de %.2f usines vertes pour consommer la totalité d'1 usine de gear wheels\n", 
        ( greenScience.cpnts[0]->item->cpnts[0]->item->nbOut / greenScience.cpnts[0]->item->cpnts[0]->item->tps ) /
        ( ( greenScience.cpnts[0]->nb *
              (greenScience.cpnts[0]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps)
            + greenScience.cpnts[1]->nb * 
              (greenScience.cpnts[1]->item->cpnts[0]->nb / greenScience.cpnts[1]->item->tps) )
          / greenScience.tps ) );
  printf("On a besoin de %.2f usines vertes pour consommer la totalité d'1 usine de gear wheels\n", nbFact(&greenScience,&gearwheel));

  return EXIT_SUCCESS;
}

// returns the number of factories to fully consume one factory worth of chosen component
float nbFact(Item* obj, Item* cpnt)
{
  // The number of factories of obj needed to fully use the output of one factory producing cpnt
  // is the output of cpnt divided by the demand for cpnt (both in items/sec) of obj
  return (cpnt->nbOut / cpnt-> tps) / demand(obj, cpnt);
}

// returns the demand of cpnt in items per sec to produce obj and its components
float demand(Item* obj, Item* cpnt)
{
  // The demand for cpnt is the sum of the direct demand for cpnt (i.e. the number required per second)
  // and the demand for cpnt in the other components times the demand for those in obj over the production
  // As such, we iterate over the list of components to test wether it's the cpnt or another one

  float sum = 0;
  printf(">\n");
  for(int i=0; obj->cpnts[i]!=NULL; i++)
  {
    Cpnt* c=obj->cpnts[i];
    if(c->item == cpnt)
    {
      sum += (c->nb/obj->tps) / obj->nbOut;
    }
    else if(c != NULL)
    {
      sum += demand(c->item, cpnt) * (c->nb/obj->tps) / obj->nbOut;
    }
    else
    {
      printf("Unexpected error\n");
      exit(EXIT_FAILURE);
    }
  }
  printf("<%f GW/s\n", sum);
  return sum;
}

