/**
 *  @file hashtab.h
 *  @version 0.1.0-dev0
 *  @date Sun Feb 16, 2020 04:39:06 PM CST
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 *  @brief Provides a hash table based on string keys.
 *  @details Hashtab provides a hash table of key-value pairs where <key> is a
 *  character string and <val> is a void * pointer. It manages memory that it
 *  allocates; the management (including freeing) of the <val> pointers is left
 *  to the user.
 */

#ifndef HASHTAB_H
#define HASHTAB_H

struct hashtab;

/**
 *  @brief Constructor.
 *  @details Create and return a new hashtab object.
 *  @returns New hashtab object.
 */
struct hashtab *hashtab_new(void);

/**
 *  @brief Destructor.
 *  @details Clean up and free a hashtab structure.
 *  @param[in, out] pp. A pointer to the struct hashtab* created by hashtab_new().
 *  Used as @code{.c} p = hashtab_new(); hashtab_free(&p);@endcode and p will be
 *  set to NULL on success.
 */
void        hashtab_free(struct hashtab **pp);

/**
 *  @brief Initialize a hashtab object.
 *  @details FIXME longer description here ...
 *  @param[in,out] p Pointer to a hashtab object
 *  @param[in] x FIXME
    @returns FIXME
 */
int         hashtab_init(struct hashtab *p, void *x);

/**
 *  @brief Return the version of this package.
 *  @returns Version string.
 */
const char *hashtab_version(void);

void       *hashtab_delete(struct hashtab *p, char *key);
int         hashtab_exists(struct hashtab *p, char *key, void **valp);
int         hashtab_insert(struct hashtab *p, char *key, void *val);
void       *hashtab_replace(struct hashtab *p, char *key, void *val);
/**
 *  Also need to provide some sort of way to access all the current
 *  table elements so that the pointers can be deleted, if desired.
 *  Could be a pop() ???
 */

#endif
