#include <stdio.h>
#include "myLib.h"

int main() {
    size_t count;
    Product *products = products_get(&count);
    if (products) {
        for (size_t i = 0; i < count; i++) {
            printf("Produto %d: %s (%.2f)\n", products[i].id, products[i].description, products[i].price);
        }
        free_products(products, count);
    } else {
        fprintf(stderr, "Erro ao obter produtos.\n");
    }

    return 0;
}
