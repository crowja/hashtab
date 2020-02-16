#include <stdlib.h>
#include <stdio.h>
#include "hashtab.h"

int
main(void)
{
   int         rc;
   void       *valp;
   struct hashtab *z = hashtab_new();

   hashtab_insert(z, "dog", "woof");
   hashtab_insert(z, "cat", "meow");
   hashtab_insert(z, "pig", "oink");
   hashtab_insert(z, "ant", "silence");

   rc = hashtab_exists(z, "dog", &valp);
   printf("%s says %s\n", "dog", (char *) valp);
   rc = hashtab_exists(z, "ant", &valp);
   printf("%s says %s\n", "ant", (char *) valp);

   hashtab_free(&z);

   return 0;
}
