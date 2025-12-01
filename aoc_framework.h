// aoc_framework.h
#ifndef AOC_FRAMEWORK_H
#define AOC_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function to check if a file exists
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Function to read session cookie from file
char* read_session_cookie() {
    FILE *file = fopen("session.txt", "r");
    if (!file) {
        printf("Error: session.txt not found. Create it with your AOC session cookie.\n");
        return NULL;
    }
    
    char *cookie = malloc(256);
    if (fgets(cookie, 256, file)) {
        // Remove newline
        cookie[strcspn(cookie, "\n")] = 0;
    }
    fclose(file);
    return cookie;
}

// Function to down™load input from Advent of Code
int download_input(int year, int day) {
    char url[256];
    char filename[64];
    char command[512];
    
    sprintf(filename, "inputs/day%02d.txt", day);
    
    // Check if already downloaded
    if (file_exists(filename)) {
        printf("Input for day %d already exists.\n", day);
        return 1;
    }
    
    // Read session cookie
    char *session_cookie = read_session_cookie();
    if (!session_cookie) {
        return 0;
    }
    
    // Create inputs directory if it doesn't exist
    system("mkdir -p inputs");
    
    // Build curl command
    sprintf(url, "https://adventofcode.com/%d/day/%d/input", year, day);
    sprintf(command, "curl -s -b \"session=%s\" -o \"%s\" \"%s\"", 
            session_cookie, filename, url);
    
    printf("Downloading input for day %d...\n", day);
    int result = system(command);
    
    free(session_cookie);
    
    if (result == 0 && file_exists(filename)) {
        printf("Successfully downloaded input for day %d\n", day);
        return 1;
    } else {
        printf("Failed to download input for day %d\n", day);
        return 0;
    }
}

// Function to read entire input file into a string
char* read_input(int day) {
    char filename[64];
    sprintf(filename, "inputs/day%02d.txt", day);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate buffer and read
    char *content = malloc(size + 1);
    if (content) {
        fread(content, 1, size, file);
        content[size] = '\0';
    }
    
    fclose(file);
    return content;
}

// Function to read input line by line
char** read_input_lines(int day, int *line_count) {
    char filename[64];
    sprintf(filename, "inputs/day%02d.txt", day);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        *line_count = 0;
        return NULL;
    }
    
    // Count lines
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') count++;
    }
    // Handle files without trailing newline
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n') count++;
    
    rewind(file);
    
    // Allocate array of string pointers
    char **lines = malloc(count * sizeof(char*));
    char buffer[4096];
    int i = 0;
    
    while (fgets(buffer, sizeof(buffer), file) && i < count) {
        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;
        lines[i] = strdup(buffer);
        i++;
    }
    
    fclose(file);
    *line_count = count;
    return lines;
}

// Function to free lines array
void free_lines(char **lines, int count) {
    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
}

#endif // AOC_FRAMEWORK_H
