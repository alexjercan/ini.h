# INI Parser in C

Simple ini file type parser in C.

To use it simply define `INI_IMPLEMENTATION` and include the header file
`ini.h` like so

```c
#define INI_IMPLEMENTATION
#include "ini.h"

void main() {
    char *text = "...";

    struct ini_file ini;   // Create the structure
    ini_parse(&ini, text); // Parse from text

    char *value = ini_get_value(&ini, "section", "key"); // Access value using section and key
    printf("The value is: %s\n", value);
    free(value)

    ini_free(&ini);
}
```

## Quickstart

```console
gcc main.c -o main
./main example.ini
```
