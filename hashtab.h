/**
 *  @file hashtab.h
 *  @version 0.0.1-dev0
 *  @date Thu Dec 12 19:37:27 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _HASHTAB_H_
#define _HASHTAB_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "hashtab"

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
 *  @param[in, out] p.
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
void       *hashtab_exists(struct hashtab *p, char *key);
int         hashtab_insert(struct hashtab *p, char *key, void *val);
void       *hashtab_replace(struct hashtab *p, char *key, void *val);
/**
 *  Also need to provide some sort of way to access all the current
 *  table elements so that the pointers can be deleted, if desired.
 *  Could be a pop() ???
 */

#endif
