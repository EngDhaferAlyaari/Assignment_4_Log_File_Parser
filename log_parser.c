#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Read one complete line using small chunks. */
static int read_line(FILE *file, char **line, size_t *capacity)
{
    char part[512];
    size_t length = 0;

    (*line)[0] = '\0';

    while (fgets(part, sizeof(part), file) != NULL) {
        size_t count = strlen(part);
        size_t required;

        if (count > (size_t)-1 - length - 1)
            return -1;

        required = length + count + 1;
        if (required > *capacity) {
            size_t new_capacity = *capacity;
            char *new_line;

            while (new_capacity < required) {
                if (new_capacity > (size_t)-1 / 2)
                    return -1;
                new_capacity *= 2;
            }

            new_line = (char *)realloc(*line, new_capacity);
            if (new_line == NULL)
                return -1;

            *line = new_line;
            *capacity = new_capacity;
        }

        memcpy(*line + length, part, count + 1);
        length += count;

        if (count > 0 && part[count - 1] == '\n')
            return 1;
    }

    if (ferror(file))
        return -2;

    return length > 0 ? 1 : 0;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char *line;
    const char *keyword;
    size_t capacity = 512;
    unsigned long line_number = 0;
    unsigned long alerts = 0;
    int result;
    int exit_code = 0;

    if (argc != 3 || argv[2][0] == '\0') {
        printf("Usage: %s <log_file> <keyword>\n", argv[0]);
        printf("Example: %s security.log FAILED\n", argv[0]);
        return 1;
    }

    keyword = argv[2];
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Could not open file: %s\n", argv[1]);
        return 1;
    }

    line = (char *)malloc(capacity);
    if (line == NULL) {
        printf("Error: Not enough memory.\n");
        fclose(file);
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Keyword: %s\n\n", keyword);

    while ((result = read_line(file, &line, &capacity)) == 1) {
        size_t length;
        line_number++;

        if (strstr(line, keyword) == NULL)
            continue;

        alerts++;
        printf("Line %lu: %s", line_number, line);
        length = strlen(line);
        if (length == 0 || line[length - 1] != '\n')
            printf("\n");
    }

    if (result == -1) {
        printf("Error: Not enough memory to read a line.\n");
        exit_code = 1;
    } else if (result == -2) {
        printf("Error: File read failed.\n");
        exit_code = 1;
    }

    if (fclose(file) != 0) {
        printf("Error: Could not close the file.\n");
        exit_code = 1;
    }

    if (exit_code == 0)
        printf("\nTotal alerts: %lu\n", alerts);

    free(line);
    return exit_code;
}
