#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INI_IMPLEMENTATION
#include "ini.h"

#define MAX_LEN 256
#define PROGRAM_LEN 8192

char *read_input_file(char *name) {
    FILE *f = NULL;
    char *input = calloc(PROGRAM_LEN, sizeof(char));
    unsigned int count = 0;
    unsigned int capacity = PROGRAM_LEN;

    if (name == NULL) {
        f = stdin;
    } else {
        f = fopen(name, "r");
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, f)) {
        unsigned int len = strlen(buffer);

        if (capacity < count + len + 1) {
            capacity *= 2;
            input = realloc(input, capacity * sizeof(char));
        }

        strcat(input, buffer);
        count += len;
        input[count] = '\0';
    }

    if (name != NULL) {
        fclose(f);
    }

    return input;
}

int main(int argc, char *argv[]) {
    char *input_file = read_input_file(argv[1]);

    struct ini_file ini = {0};
    ini_parse(&ini, input_file);

    for (unsigned int i = 0; i < ini.count; i++) {
        printf("Section: %.*s\n", ini.items[i].name.len,
               ini.items[i].name.data);
        for (unsigned int j = 0; j < ini.items[i].count; j++) {
            printf("  %.*s = %.*s\n", ini.items[i].items[j].key.len,
                   ini.items[i].items[j].key.data,
                   ini.items[i].items[j].value.len,
                   ini.items[i].items[j].value.data);
        }
    }

    for (unsigned int i = 0; i < ini.root.count; i++) {
        printf("%.*s = %.*s\n", ini.root.items[i].key.len,
               ini.root.items[i].key.data, ini.root.items[i].value.len,
               ini.root.items[i].value.data);
    }

    char *port = ini_get_value(&ini, "database", "port");
    printf("The port is: %s\n", port);
    free(port);

    ini_free(&ini);
    free(input_file);

    return 0;
}
