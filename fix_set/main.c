#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

int main()
{
    set* set = new_set(4);
    print_set(set);

    char* a = "a er";
    char* b = "b dfdfb";
    char* c = "c zfgc";
    char* d = "d jozvd";
    char* e = "e frezg";
    char* f = "f rge";
    char* g = "g aevd";
    char* h = "h mop";
    char* i = "i ivezrv";
    char* j = "j ezvds";
    char* k = "k zev";
    char* l = "l vezfvds";
    char* m = "m aQCX<";
    char* n = "n zfdsw";
    char* o = "o zae";
    char* p = "p WWaQ";
    char* q = "q mpzvsd";
    char* r = "r juzsqd";
    char* s = "s cvbn,";
    char* t = "t azsdcg";
    char* u = "u pmlkjikol";
    char* v = "v zedszed";
    char* w = "w pmp";
    char* x = "x nhjk,";
    char* y = "y ascc";
    char* z = "z qsdsqsd";

    char* zero = "0";

    insert_set(&set,zero);
    insert_set(&set,a);
    insert_set(&set,b);
    insert_set(&set,c);

    /*insert_set(&set, a);
    insert_set(&set,b);
    insert_set(&set,c);
    insert_set(&set,d);
    insert_set(&set,e);
    insert_set(&set,f);
    insert_set(&set,g);
    insert_set(&set,h);
    insert_set(&set,i);
    insert_set(&set,j);
    insert_set(&set,k);
    insert_set(&set,l);
    insert_set(&set,m);
    insert_set(&set,n);
    insert_set(&set,o);
    insert_set(&set,p);
    insert_set(&set,q);
    insert_set(&set,r);
    insert_set(&set,s);
    insert_set(&set,t);
    insert_set(&set,u);
    insert_set(&set,v);
    insert_set(&set,w);
    insert_set(&set,x);
    insert_set(&set,y);
    insert_set(&set,z);*/
    return 0;
}
