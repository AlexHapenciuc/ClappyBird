#include "TDA.h"

struct crect
{
    int x, y, w, h;
};

struct jucator
{
    char *nume;
    int scor;
    JUCATOR *urm;
};

bool valueInRange(int value, int min, int max)
{
    return (value >= min) && (value <= max);
}

bool RectsCollide(cRECT A, cRECT B)
{
    bool xOverlap = valueInRange(A->x, B->x, B->x + B->w) ||
                    valueInRange(B->x, A->x, A->x + A->w);

    bool yOverlap = valueInRange(A->y, B->y, B->y + B->h) ||
                    valueInRange(B->y, A->y, A->y + A->h);

    return xOverlap && yOverlap;
}

JUCATOR newJucator(char *nume, int scor)
{
    JUCATOR j = malloc(sizeof(Jucator));
    j->nume = nume;
    j->scor = scor;
    j->urm = NULL;
    assert(j!=NULL);
    return j;
}

void AdaugaScor(JUCATOR j, int scor)
{
    if(j->scor == -1)
    {
        j->scor = scor;
        return;
    }
    while(j->urm != NULL)
        j = j->urm;
    JUCATOR n = newJucator(NULL, scor);
    j->urm = n;
}

void AfiseazaScoruri(JUCATOR j, FILE *fp)
{
    if(j == NULL)
        return;
    fprintf(fp, "%d ", j->scor);
    while(j->urm != NULL)
    {
        j = j->urm;
        fprintf(fp, "%d ", j->scor);
    }
}

void PrinteazaScoruri(JUCATOR j)
{
    FILE *fout;
    if(access(j->nume, F_OK ) != -1 )
        fout = fopen(j->nume, "at");
    else
        fout = fopen(j->nume, "wt");
    AfiseazaScoruri(j, fout);
}

