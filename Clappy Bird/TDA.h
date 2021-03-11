#ifndef TDA_H_INCLUDED
#define TDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

typedef struct crect cRect, *cRECT;
typedef struct jucator Jucator, *JUCATOR;

bool RectsCollide(cRECT, cRECT);
JUCATOR newJucator(char *nume, int scor);
void AdaugaScor(JUCATOR j, int scor);
void AfiseazaScoruri(JUCATOR j, FILE *fp);
void PrinteazaScoruri(JUCATOR j);

#endif // TDA_H_INCLUDED
