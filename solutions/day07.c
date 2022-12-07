#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LINE_LENGTH 100
#define MAX_OBJECT_NAME_LENGTH 20
#define MAX_CHILD_DIRECTORIES 20
#define MAX_FILES_IN_DIRECTORY 100

struct Directory {
    char *name;
    size_t amount_of_files;
    size_t amount_of_child_directories;
    struct Directory **child_directories;
    struct File **files;
    struct Directory *parent;
};

struct Directory *create_new_directory(struct Directory *parent, char *name) {
    struct Directory *new_dir = malloc(sizeof(struct Directory));
    *new_dir = (struct Directory) {
        name,
        0, // #files
        0, // #child dirs
        NULL, // child dirs
        NULL, // files
        parent
    };
    return new_dir;
}

struct File {
    size_t size;
    char *filename;
};


size_t calculate_answer_q1(size_t *sum, struct Directory *dir) {
    size_t total_dir_size = 0;
    for (size_t i = 0; i < dir->amount_of_child_directories; i++) {
        total_dir_size += calculate_answer_q1(sum, dir->child_directories[i]);
    }
    for (size_t i = 0; i < dir->amount_of_files; i++) {
        total_dir_size += dir->files[i]->size;
    }
    
    printf("total size of %s is %u\n", dir->name, total_dir_size);
    if (total_dir_size <= 100000) {
        *sum = (*sum) + total_dir_size;
    }
    return total_dir_size;
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day07.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    char current_line[MAX_INPUT_LINE_LENGTH];
    struct Directory* active_directory = create_new_directory(NULL, "root");
    size_t line_ctr = 0;

    while (fgets(current_line, MAX_INPUT_LINE_LENGTH, puzzle_input_file_ptr) != NULL) {
        line_ctr++;
        if (current_line[0] == '$') {
            printf("%u: [command ] ", line_ctr);
            // found a command!
            if (current_line[2] == 'c' && current_line[3] == 'd') {
                // change directory
                if (current_line[5] == '.' && current_line[6] == '.') {
                    // move one dir up
                    printf("move one directory up | %s", current_line);
                    if (active_directory->parent == NULL) {
                        printf("ERROR can't move up to nonexistent parent of directory\n");
                        printf("we are in directory %s\n", active_directory->name);
                        exit(1);
                    }
                    active_directory = active_directory->parent;
                    continue;
                }
                if (current_line[5] != '/') {
                    // move one dir down
                    printf("move to child directory | %s", current_line);
                    
                    char name_of_directory[MAX_OBJECT_NAME_LENGTH];
                    sscanf(current_line, "$ cd %s", name_of_directory);
                    
                    for (size_t i = 0; i < active_directory->amount_of_child_directories; i++) {
                        if (!strcmp(active_directory->child_directories[i]->name, name_of_directory)) {
                            active_directory = active_directory->child_directories[i];
                            break;
                        }                            
                    }
                    continue;
                }
                // move to root
                printf("move to root directory | %s", current_line);
                while (active_directory->parent != NULL) {
                    active_directory = active_directory-> parent;
                }
                continue;
            }
            if (current_line[2] == 'l' && current_line[3] == 's') {
                // list directory contents
                printf("list directory contents | %s", current_line);
                continue;
            }
        }
        printf("%u: [contents] ", line_ctr);
        if (current_line[0] == 'd' && current_line[1] == 'i' && current_line[2] == 'r') {
            // shows a directory (add it if it doesn't exist in the tree)
            printf("a directory | %s", current_line);
            
            char *dirname = malloc(sizeof(char) * MAX_OBJECT_NAME_LENGTH);
            sscanf(current_line, "dir %s", dirname);
            struct Directory *new_directory = create_new_directory(active_directory, dirname);
            
            if (active_directory->child_directories == NULL) {
                struct Directory **child_directories = malloc(sizeof(struct Directory *) * MAX_CHILD_DIRECTORIES);
                child_directories[0] = new_directory;
                active_directory->child_directories = child_directories;
                active_directory->amount_of_child_directories += 1;
                continue;
            }
            
            int already_exists = 0;
            for (int i = 0; i < active_directory->amount_of_child_directories; i++) {
                already_exists = already_exists || (!strcmp(active_directory->child_directories[i]->name, dirname));
            }
            
            if (!already_exists) {
                active_directory->child_directories[active_directory->amount_of_child_directories] = new_directory;
                active_directory->amount_of_child_directories += 1;
            } else {
                printf("directory %s already exists.\n", dirname);
                free(new_directory);
            }
            continue;
        }
        // shows a file
        printf("a file | %s", current_line);
        
        char *filename = malloc(sizeof(char) * MAX_OBJECT_NAME_LENGTH);
        size_t file_size = 0;
        sscanf(current_line, "%d %s", &file_size, filename);
        struct File *new_file = malloc(sizeof(struct File));
        *new_file = (struct File) {
            file_size,
            filename
        };
        
        if (active_directory->files == NULL) {
            struct File **files = malloc(sizeof(struct File *) * MAX_FILES_IN_DIRECTORY);
            files[0] = new_file;
            active_directory->files = files;
            active_directory->amount_of_files += 1;
            continue;
        }
        
        int already_exists = 0;
        for (int i = 0; i < active_directory->amount_of_files; i++) {
            already_exists = already_exists || (!strcmp(active_directory->files[i]->filename, filename));
        }
        if (!already_exists) {
            active_directory->files[active_directory->amount_of_files] = new_file;
            active_directory->amount_of_files += 1;
        } else {
            printf("file %s already exists.\n", filename);
            free(new_file);
        }
        
    }
    
    // done parsing, return to root and do the math.
    while (active_directory->parent != NULL) {
        active_directory = active_directory->parent;
    }
    
    printf("\n\n");
    size_t *sum = malloc(sizeof(size_t));
    *sum = 0;
    calculate_answer_q1(sum, active_directory);
    printf("q1 sum: %u\n", *sum);
    
    fclose(puzzle_input_file_ptr);
    return 0;
}