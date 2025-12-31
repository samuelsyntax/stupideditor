#include<stdio.h>
#include<string.h>

void edit_line(char* buffer, int current_line) {
    if (current_line < 1) return;
    char* line_start = buffer;
    for(int i = 1; i < current_line; i++) {
        char* next = strchr(line_start, '\n');
        if (!next) return;
        line_start = next + 1;
    }
    char* line_end = strchr(line_start, '\n');
    if (!line_end) line_end = line_start + strlen(line_start);
    char saved[1024] = {0};
    strcpy(saved, line_end);
    scanf("%s", line_start);
    strcpy(line_start + strlen(line_start), saved);
}
  
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
   FILE *file = fopen(argv[1], "r");
   if (!file) {
       printf("Error opening file\n");
       return 1;
   }
   char buffer[1024] = {0};
   size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
   buffer[bytes_read] = '\0';
   fclose(file);
   printf("Content: \n%s\n", buffer);
   int current_line = 0;
   printf("Enter line number to edit: ");
   if (scanf("%d", &current_line) != 1) {
       printf("Invalid input\n");
       return 1;
   }
   edit_line(buffer, current_line);
   file = fopen(argv[1], "w");
   if (!file) {
       printf("Error opening file for writing\n");
       return 1;
   }
    fwrite(buffer, strlen(buffer), 1, file);
    fclose(file);
    return 0;
}