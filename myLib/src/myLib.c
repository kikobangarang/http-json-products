#include "myLib.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

// Estrutura auxiliar para armazenar a resposta HTTP
typedef struct {
    char *data;
    size_t size;
} HttpResponse;

// Callback para acumular os dados da resposta
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    HttpResponse *response = (HttpResponse *)userp;

    char *ptr = realloc(response->data, response->size + total_size + 1);
    if (!ptr) {
        return 0;
    }

    response->data = ptr;
    memcpy(&(response->data[response->size]), contents, total_size);
    response->size += total_size;
    response->data[response->size] = '\0';

    return total_size;
}

// Função HTTP GET
json_t *http_get_json(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Erro ao inicializar CURL.\n");
        return NULL;
    }

    HttpResponse response = {NULL, 0};
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Erro ao realizar GET: %s\n", curl_easy_strerror(res));
        free(response.data);
        curl_easy_cleanup(curl);
        return NULL;
    }

    json_t *json = json_loads(response.data, 0, NULL);
    free(response.data);
    curl_easy_cleanup(curl);

    return json;
}

// Função HTTP POST
bool http_post_json(const char *url, json_t *data) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Erro ao inicializar CURL.\n");
        return false;
    }

    char *json_data = json_dumps(data, 0);
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    free(json_data);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Erro ao realizar POST: %s\n", curl_easy_strerror(res));
        return false;
    }

    return true;
}

// Função para obter produtos
Product *products_get(size_t *count) {
    json_t *json = http_get_json("https://dummyjson.com/products");
    if (!json) return NULL;

    json_t *products = json_object_get(json, "products");
    *count = json_array_size(products);

    Product *result = malloc(*count * sizeof(Product));
    for (size_t i = 0; i < *count; i++) {
        json_t *item = json_array_get(products, i);
        result[i].id = json_integer_value(json_object_get(item, "id"));
        result[i].price = json_real_value(json_object_get(item, "price"));
        result[i].description = strdup(json_string_value(json_object_get(item, "description")));
        result[i].category = strdup(json_string_value(json_object_get(item, "category")));
    }

    json_decref(json);
    return result;
}

// Funções auxiliares para liberar memória
void free_products(Product *products, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free((char *)products[i].description);
        free((char *)products[i].category);
    }
    free(products);
}
