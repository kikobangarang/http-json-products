# http-json-products-c

A simple C library that uses **libcurl** and **Jansson** to perform HTTP GET/POST requests and parse JSON data into custom C structs. Designed for retrieving product data from a sample API.

## Features

- HTTP GET and POST requests using `libcurl`
- JSON parsing with `jansson`
- Dynamic memory handling for product lists
- Easy integration into other C projects as a shared library

---

## Project Structure

```
project/
├── include/        # Header files
│   └── myLib.h
├── src/            # Source code
│   └── myLib.c
├── test/           # Test files
│   └── main.c
├── Makefile
└── README.md
```

---

## Dependencies

Ensure the following libraries are installed:

- [libcurl](https://curl.se/libcurl/)
- [jansson](https://digip.org/jansson/)

### On Debian/Ubuntu:

```bash
sudo apt-get install libcurl4-openssl-dev libjansson-dev
```

---

## Build Instructions

### Compile the shared library:

```bash
make
```

### Build and run the test executable:

```bash
make test
./test/test
```

### Clean build artifacts:

```bash
make clean
```

---

## Example Usage

Example code (`test/main.c`) calls `products_get()` and prints data retrieved from:

```
https://dummyjson.com/products
```

You can use the returned `Product*` array and `count` to access individual product details like ID, price, description, and category.


