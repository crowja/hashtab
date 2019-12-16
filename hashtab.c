/**
 *  @file hashtab.c
 *  @version 0.0.1-dev0
 *  @date Sun Dec 15 22:28:35 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uthash.h"
#include "hashtab.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

static unsigned long
hash_sdbm(unsigned char *str)
{
   unsigned long hash = 0;
   int         c;

   while (c = *str++)
      hash = c + (hash << 6) + (hash << 16) - hash;

   return hash;
}

static unsigned long
hash_djb2(unsigned char *str)
{
   unsigned long hash = 5381;
   int         c;

   while (c = *str++)
      hash = ((hash << 5) + hash) + c;           /* hash * 33 + c */

   return hash;
}

/* also see fasthash at https://github.com/ZilongTan/fast-hash */

struct _kv {
   char       *key;
   void       *val;
   UT_hash_handle hh;
};

struct hashtab {
   void       *x;
   size_t      size;
   struct _kv *keyvals;
};

struct hashtab *
hashtab_new(void)
{
   struct hashtab *tp;

   tp = (struct hashtab *) malloc(sizeof(struct hashtab));
   if (_IS_NULL(tp))
      return NULL;

   tp->x = NULL;
   tp->size = 0;
   tp->keyvals = NULL;

   return tp;
}

void
hashtab_free(struct hashtab **pp)
{
   struct _kv *s;
   struct _kv *t;

   if (_IS_NULL(*pp))
      return;

   t = (*pp)->keyvals;

   while (t != NULL) {
      s = t;
      t = s->hh.next;
      _FREE(s->key);
      HASH_DEL((*pp)->keyvals, s);
      _FREE(s);
   }

   _FREE(*pp);
   *pp = NULL;
}

int
hashtab_init(struct hashtab *p, void *x)
{
   /* Do some magic here ... */
   p->x = x;                                     /* FIXME */

   return 0;
}

const char *
hashtab_version(void)
{
   return "0.0.1-dev0";
}

void       *
hashtab_delete(struct hashtab *p, char *s)
{
   struct _kv *t;
   void       *x;

   HASH_FIND_STR(p->keyvals, s, t);

   if (_IS_NULL(t))
      return NULL;

   x = t->val;
   _FREE(t->key);
   HASH_DEL(p->keyvals, t);
   _FREE(t);

   return x;
}

/**
 *  FIXME need to change signature to int hashtab_exists(p, s, val) 
 *  since there is ambiguity now if the key exists and is associated
 *  with a NULL pointer.
 */

void       *
hashtab_exists(struct hashtab *p, char *s)
{
   struct _kv *t;

   HASH_FIND_STR(p->keyvals, s, t);

   return _IS_NULL(t) ? NULL : t->val;
}

int
hashtab_insert(struct hashtab *p, char *s, void *x)
{
   struct _kv *t;

   HASH_FIND_STR(p->keyvals, s, t);

   if (!_IS_NULL(t))
      return 0;                                  /* already exists */

   t = (struct _kv *) malloc(sizeof(struct _kv));
   t->key = malloc((1 + strlen(s)) * sizeof(char));
   strcpy(t->key, s);
   t->val = x;
   HASH_ADD_KEYPTR(hh, p->keyvals, t->key, strlen(t->key), t);
   return 1;
}

void       *
hashtab_replace(struct hashtab *p, char *key, void *val)
{

   return NULL;
}

#undef  _IS_NULL
#undef  _FREE
