#include <stdlib.h>
#include <stdio.h>
#include "hashtab.h"

int
main(void)
{
   struct hashtab *z = hashtab_new();

   hashtab_insert(z, "dog", "woof");
   hashtab_insert(z, "cat", "meow");
   hashtab_insert(z, "pig", "oink");
   hashtab_insert(z, "ant", "silence");

   printf("%s says %s\n", "dog", (char *) hashtab_exists(z, "dog"));
   printf("%s says %s\n", "cat", (char *) hashtab_exists(z, "cat"));
   printf("%s says %s\n", "pig", (char *) hashtab_exists(z, "pig"));
   printf("%s says %s\n", "ant", (char *) hashtab_exists(z, "ant"));

   hashtab_free(&z);

   return 0;
}
