#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINDINGS 256

struct Binding {
    char key_action[100];
    char command[200];
};

char* center_string(char* str, int space) {
    int len = strlen(str);
    if (len >= space) {
        return strdup(str);
    }

    char* new_str = (char*)malloc(space + 1);

    if (new_str == NULL) {
        return NULL;
    }

    int left_spaces = (space - len) / 2;

    for (int i = 0; i < left_spaces; i++) {
        new_str[i] = ' ';
    }

    strcpy(&new_str[left_spaces], str);

    for (int i = left_spaces + len; i < space; i++) {
        new_str[i] = ' ';
    }

    new_str[space] = '\0';
    return new_str;
}

void render_key(char* str, char* command) {
    char* tokenized_str = strdup(str);
    char* token = strtok(tokenized_str, " ");
    int tokens = 0;
    char* tokens_array[10];

    while (token != NULL) {
        tokens_array[tokens++] = token;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < tokens; i++) {
        if (strlen(tokens_array[i]) <= 3) {
            printf("┏━━━┓");
        } else {
            printf("┏━━━━━━━━━━━┓");
        }
    }
    printf("\n");

    for (int i = 0; i < tokens; i++) {
        char* centered_string;
        if (strlen(tokens_array[i]) <= 3) {
            centered_string = center_string(tokens_array[i], 3);
        } else {
            centered_string = center_string(tokens_array[i], 11);
        }

        if (centered_string != NULL) {
            printf("┃%s┃", centered_string);
            free(centered_string);
        } else {
            perror("Memory issue");
        }
    }
    printf("  %s", command);

    for (int i = 0; i < tokens; i++) {
        if (strlen(tokens_array[i]) <= 3) {
            printf("┗━━━┛");
        } else {
            printf("┗━━━━━━━━━━━┛");
        }
    }
    printf("\n");

    free(tokenized_str);
}

int main() {
    struct Binding bindings[MAX_BINDINGS];
    FILE *pf;
    char script[256];
    char data[1028];
    int count = 0;

    sprintf(script, "./keys.sh");

    pf = popen(script, "r");

    if (pf == NULL) {
        perror("popen");
        return 1;
    }

    while (fgets(data, sizeof(data), pf) != NULL) {
        data[strcspn(data, "\n")] = 0;
        char* line = strdup(data);
        char* comment = strtok(line, "#"); // Remove if no comments appreciated and change data to line
        char* key = strtok(data, ",");
        char* action = strtok(NULL, ",");
        char* command = strtok(NULL, "#");

        if (key && action && command) {
            sprintf(bindings[count].key_action, "%s %s", key, action);
            sprintf(bindings[count].command, "%s\n", command);

            render_key(bindings[count].key_action, bindings[count].command);

            count++;
            if (count >= MAX_BINDINGS) {
                printf("Max bindings exceeded. Increase MAX_BINDINGS.\n");
                break;
            }

        } else {
            printf("%s\n", comment); // Remove if no comments appreciated
        }
    }

    if (pclose(pf) != 0) {
        perror("pclose");
    }

//    for (int i = 0; i < count; i++) {
//        render_key(bindings[i].key_action, bindings[i].command);
//    }

    return 0;
}
