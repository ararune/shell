#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


#define MAX_COMMAND_LENGTH 100

void execute_command(char **args);
void tokenize_command(char *command, char **args);
void print_prompt();

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[10];

    while(1) {
        print_prompt();

        // Read the command from the user
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove the newline character from the command
        command[strcspn(command, "\n")] = 0;

        // Tokenize the command into arguments
        tokenize_command(command, args);

        // Execute the command
        execute_command(args);
    }

    return 0;
}

void print_prompt() {
    printf("shell> ");
}

void tokenize_command(char *command, char **args) {
    char *token = strtok(command, " ");
    int i = 0;
    while(token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}

void execute_command(char **args) {
    if(args[0] == NULL) {
        // Empty command, do nothing
        return;
    }

    if(strcmp(args[0], "ls") == 0) {
        DIR *dir;
        struct dirent *ent;
        if((dir = opendir(".")) != NULL) {
            while((ent = readdir(dir)) != NULL) {
                printf("%s\n", ent->d_name);
            }
            closedir(dir);
        }
        else {
            perror("ls error");
        }
    }
    else if(strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        else {
            perror("pwd error");
        }
    }
    else if(strcmp(args[0], "touch") == 0) {
        if(args[1] == NULL) {
            printf("Usage: touch <filename>\n");
        }
        else {
            int fd = open(args[1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
            if(fd == -1) {
                perror("touch error");
            }
            else {
                close(fd);
            }
        }
    }
    else if(strcmp(args[0], "rm") == 0) {
        if(args[1] == NULL) {
            printf("Usage: rm <filename>\n");
        }
        else {
            if(remove(args[1]) == 0) {
                printf("%s removed successfully\n", args[1]);
            }
            else {
                perror("rm error");
            }
        }
    }
    else if(strcmp(args[0], "mkdir") == 0) {
        if(args[1] == NULL) {
            printf("Usage: mkdir <dirname>\n");
        }
        else {
            if(mkdir(args[1], S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
                perror("mkdir error");
            }
            else {
                printf("%s created successfully\n", args[1]);
            }
        }
    }
     else if(strcmp(args[0], "rmdir") == 0) {
        if(args[1] == NULL) {
            printf("Usage: rmdir <directory>\n");
        }
        else {
            if(rmdir(args[1]) == -1) {
                perror("rmdir error");
            }
        }
    }
    else if(strcmp(args[0], "wc") == 0) {
        if(args[1] == NULL) {
            printf("Usage: wc [-wcl] <filename>\n");
        }
        else {
            int word_count = 0;
            int char_count = 0;
            int line_count = 0;
            int file_descriptor;

            if((file_descriptor = open(args[2], O_RDONLY)) < 0) {
                perror("wc error");
            }
            else {
                char buffer;
                int in_word = 0;

                while(read(file_descriptor, &buffer, 1) > 0) {
                    char_count++;
                    if(buffer == ' ' || buffer == '\n' || buffer == '\t') {
                        if(in_word) {
                            in_word = 0;
                            word_count++;
                        }
                        if(buffer == '\n') {
                            line_count++;
                        }
                    }
                    else {
                        in_word = 1;
                    }
                }

                if(in_word) {
                    word_count++;
                }

                close(file_descriptor);

                if(strstr(args[1], "-w") != NULL) {
                    printf("Word count: %d\n", word_count);
                }
                if(strstr(args[1], "-c") != NULL) {
                    printf("Character count: %d\n", char_count);
                }
                if(strstr(args[1], "-l") != NULL) {
                    printf("Line count: %d\n", line_count);
                }
            }
        }
    }
    else if(strcmp(args[0], "exit") == 0) {
        exit(0);
    }
    else {
        printf("Unknown command: %s\n", args[0]);
    }
}

