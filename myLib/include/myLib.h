#ifndef MYLIB_H
#define MYLIB_H

#include <stdbool.h>
#include <jansson.h>

// Estruturas
typedef struct {
    int id;
    float price;
    const char *description;
    const char *category;
} Product;

typedef struct {
    int id;
    const char *name;
} User;

typedef struct {
    int user_id;
    size_t n_products;
    struct {
        int id;
        size_t quantity;
    } products[];
} Cart;

// Funções principais
json_t *http_get_json(const char *url);
bool http_post_json(const char *url, json_t *data);

Product *products_get(size_t *count);
User *users_get(size_t *count);
bool cart_put(Cart *cart);

// Funções auxiliares
void free_products(Product *products, size_t count);
void free_users(User *users, size_t count);

#endif
