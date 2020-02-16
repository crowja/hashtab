#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "hashtab.h"
#include "t/tinytest.h"

#ifdef  COLOR_CODE
#undef  COLOR_CODE
#endif
#define COLOR_CODE       0x1B

#ifdef  COLOR_RED
#undef  COLOR_RED
#endif
#define COLOR_RED        "[1;31m"

#ifdef  COLOR_GREEN
#undef  COLOR_GREEN
#endif
#define COLOR_GREEN      "[1;32m"

#ifdef  COLOR_YELLOW
#undef  COLOR_YELLOW
#endif
#define COLOR_YELLOW     "[1;33m"

#ifdef  COLOR_RESET
#undef  COLOR_RESET
#endif
#define COLOR_RESET      "[0m"


static void
printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", COLOR_CODE, COLOR_YELLOW, name, COLOR_CODE, COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}


static int
two_doubles_equal(double x, double y)
{
   double      t = fabs(x) + fabs(y);
   return fabs(x - y) < 4 * DBL_EPSILON * t ? 1 : 0;
}


static void
test_constr(void)
{
   struct hashtab *z;

   printf_test_name("test_constr", "hashtab_new, hashtab_free");

   z = hashtab_new();
   ASSERT("Constructor test", z);
   hashtab_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_insert(void)
{
   int         rc;
   struct hashtab *z;
   char       *words[] = { "cat", "dog", "mouse" };
   void       *x = NULL;

   printf_test_name("test_insert", "hashtab_insert");

   /* New hashtab */
   z = hashtab_new();

   /* Check if "cat" exists as a key, expect no, rc == 0 */
   rc = hashtab_exists(z, words[0], &x);
   ASSERT_EQUALS(0, rc);

   /* Insert key="meow", val="cat", expect success, rc == 1 */
   rc = hashtab_insert(z, "meow", words[0]);
   ASSERT_EQUALS(1, rc);

   /* Check if key "meow" exists with val "cat", expect success, rc == 1 */
   rc = hashtab_exists(z, "meow", &x);
   ASSERT_EQUALS(1, rc);
   ASSERT_STRING_EQUALS("cat", x);

   /* Try to reinsert key "meow", val "cat", expect fail, rc == 0 */
   rc = hashtab_insert(z, "meow", "cat");
   ASSERT_EQUALS(0, rc);

   /* See if key "meow" exists with val "cat", expect success, rc == 1 */
   rc = hashtab_exists(z, "meow", &x);
   ASSERT_EQUALS(1, rc);
   ASSERT_STRING_EQUALS("cat", x);
#if 0
   printf("%s --> %s\n", "meow", (char *) x);
#endif

   hashtab_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_delete(void)
{
   struct hashtab *z;
   char       *x;

   printf_test_name("test_delete", "hashtab_delete");

   z = hashtab_new();
   hashtab_insert(z, "dog", "bark");
   hashtab_insert(z, "cat", "meow");
   hashtab_insert(z, "cow", "moo");
   hashtab_insert(z, "tree", "bark");
   x = hashtab_delete(z, "dog");
   ASSERT_EQUALS(x, "bark");
   x = hashtab_delete(z, "dog");
   ASSERT_EQUALS(x, NULL);
   x = hashtab_delete(z, "cat");
   ASSERT_EQUALS(x, "meow");
   x = hashtab_delete(z, "cat");
   ASSERT_EQUALS(x, NULL);
   x = hashtab_delete(z, "cow");
   ASSERT_EQUALS(x, "moo");
   x = hashtab_delete(z, "cow");
   ASSERT_EQUALS(x, NULL);
   x = hashtab_delete(z, "tree");
   ASSERT_EQUALS(x, "bark");
   x = hashtab_delete(z, "tree");
   ASSERT_EQUALS(x, NULL);
   hashtab_insert(z, "dog", "woof");
   x = hashtab_delete(z, "dog");
   ASSERT_EQUALS(x, "woof");
   x = hashtab_delete(z, "dog");
   ASSERT_EQUALS(x, NULL);

   hashtab_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0                                            /* 16 yy */
static void
test_stub(void)
{
   struct hashtab *z;
   double      x = 1.23;                    /* TODO */

   printf_test_name("test_stub", NULL);

   z = hashtab_new();
   ASSERT("Constructor test, pt 1", z);
   ASSERT("Here's a test ...", two_doubles_equal(x, 1.23));
   ASSERT_EQUALS(10, 10);

   hashtab_free(&z);
   ASSERT_EQUALS(NULL, z);
}
#endif


int
main(void)
{
   printf("%s\n", hashtab_version());

   RUN(test_constr);
   RUN(test_insert);
   RUN(test_delete);

   return TEST_REPORT();
}
