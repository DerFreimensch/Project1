#define CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dates  // structure for day-month-year-event-name-classification
{
    int day;
    char month[10];
    int year;
    char event[150];
    char name[50];
    char classification[15];
    char celebration[100];
    
};
struct dates dat;
FILE* fale_1;
FILE* fale_2;

void Add() { // function add in database
    int classificationch;
    printf("write day, month, year\n");
    scanf_s("%d%s%d", &dat.day, dat.month, (unsigned)_countof(dat.month), &dat.year);
    printf("%s\n", "Choose category");
    printf("%s\n", "1) Birth Day");
    printf("%s\n", "2) Celebration");
    printf("%s\n", "3) Event");
    scanf_s("%d", &classificationch);
    switch (classificationch) { // Choose of category
    case 1:
        strcpy_s(dat.classification, _countof(dat.classification), "Birth Day");
        break;
    case 2:
        strcpy_s(dat.classification, _countof(dat.classification), "Celebration");
        break;
    case 3:
        strcpy_s(dat.classification, _countof(dat.classification), "Event");
        break;
    }
    printf("%s\n", "event: ");
    getchar();
    gets(dat.event);
    if (classificationch == 1) {
        printf("%s\n", "Name: ");
   
        gets(dat.name);
        
    }
    if (classificationch == 2) {
        printf("%s\n", "Celebration: ");
        gets(dat.celebration);
        
    }
    
    fseek(fale_1, 0, SEEK_END);
    fwrite(&dat.day, sizeof(int), 1, fale_1);
    fwrite(&dat.month, sizeof(char), 10, fale_1);
    fwrite(&dat.year, sizeof(int), 1, fale_1);
    fwrite(&dat.event, sizeof(char), 150, fale_1);
    fwrite(&dat.classification, sizeof(char), 12, fale_1);
    fwrite(&dat.name, sizeof(char), 50, fale_1);
    
}

void SearchForData() { // function looking for data
    fseek(fale_1, 0, SEEK_SET);
    int d = dat.day;
    char m[10];
    strcpy_s(m, _countof(m), dat.month);
    int y = dat.year;
    while (!feof(fale_1)) {
        fread(&dat.day, sizeof(int), 1, fale_1);
        fread(&dat.month, sizeof(char), 10, fale_1);
        fread(&dat.year, sizeof(int), 1, fale_1);
        fread(&dat.event, sizeof(char), 150, fale_1);
        fread(&dat.classification, sizeof(char), 15, fale_1);
        fread(&dat.name, sizeof(char), 100, fale_1);
        int flag = 1;
        flag = strncmp(dat.month, m, 3);
        if (dat.day == d && dat.year == y && flag == 0) {
            printf("%d %s %d: %s (%s of %s) \n", dat.day, dat.month, dat.year, dat.event, dat.classification, dat.name);
            dat.day = 0;
            }
        
    }
    printf("\n");

}
void SearchForName() { // function of looking for name
    fseek(fale_1, 0, SEEK_SET);
    char n[100];
    strcpy_s(n, _countof(n), dat.name);
    while (!feof(fale_1)) {
        fread(&dat.day, sizeof(int), 1, fale_1);
        fread(&dat.month, sizeof(char), 10, fale_1);
        fread(&dat.year, sizeof(int), 1, fale_1);
        fread(&dat.event, sizeof(char), 150, fale_1);
        fread(&dat.classification, sizeof(char), 15, fale_1);
        fread(&dat.name, sizeof(char), 100, fale_1);
        if (dat.name == n) {
            printf("%d %s %d: %s (%s of %s) \n", dat.day, dat.month, dat.year, dat.event, dat.classification, dat.name);
        }
    }
}
void SearchForCategory() { // function of looking for category
    fseek(fale_1, 0, SEEK_SET);
    char n[15];
    strcpy_s(n, _countof(n), dat.classification);
    while (!feof(fale_1)) {
        fread(&dat.day, sizeof(int), 1, fale_1);
        fread(&dat.month, sizeof(char), 10, fale_1);
        fread(&dat.year, sizeof(int), 1, fale_1);
        fread(&dat.event, sizeof(char), 150, fale_1);
        fread(&dat.classification, sizeof(char), 15, fale_1);
        fread(&dat.name, sizeof(char), 100, fale_1);
        if (dat.classification ==  n) {
            printf("%d %s %d: %s (%s of %s) \n", dat.day, dat.month, dat.year, dat.event, dat.classification, dat.name);
        }
    }
}
void Delete() { // function deleting data

    fseek(fale_1, 0, SEEK_SET);
    fopen_s(&fale_2,"file2.dat", "w+b");
    if (fale_2 == 0)
        printf("error on fopen\n");

    int d, y;
    char n[10];
    printf("%s\n", "which data want you delete?(D/M/Y) ");
    d = scanf_s(" %d", &dat.day);
    scanf_s(" %s", dat.month, (unsigned)_countof(dat.month));
    y = scanf_s(" %d", &dat.year);
    strcpy_s(n, _countof(n), dat.month);
    fseek(fale_2, 0, SEEK_SET);
    while (!feof(fale_1)) {
        fread(&dat.day, sizeof(int), 1, fale_1);
        fread(&dat.month, sizeof(char), 10, fale_1);
        fread(&dat.year, sizeof(int), 1, fale_1);
        fread(&dat.event, sizeof(char), 150, fale_1);
        fread(&dat.classification, sizeof(char), 15, fale_1);
        fread(&dat.name, sizeof(char), 100, fale_1);
        int flag = 1;
        flag = strncmp(dat.month, n, 3);
        
        if (dat.day != d || dat.year != y || flag != 0) {
            fwrite(&dat.day, sizeof(int), 1, fale_2);
            fwrite(&dat.month, sizeof(char), 10, fale_2);
            fwrite(&dat.year, sizeof(int), 1, fale_2);
            fwrite(&dat.event, sizeof(char), 150, fale_2);
            fwrite(&dat.classification, sizeof(char), 12, fale_2);
            fwrite(&dat.name, sizeof(char), 50, fale_2);
        }
    }
    fseek(fale_2, 0, SEEK_SET);
    fclose(fale_1);
    fopen_s(&fale_1, "file.dat", "w+b");
    if (fale_1 == 0)
        printf("error on fopen\n");
    while (!feof(fale_2)) {
        fread(&dat.day, sizeof(int), 1, fale_2);
        fread(&dat.month, sizeof(char), 10, fale_2);
        fread(&dat.year, sizeof(int), 1, fale_2);
        fread(&dat.event, sizeof(char), 150, fale_2);
        fread(&dat.classification, sizeof(char), 15, fale_2);
        fread(&dat.name, sizeof(char), 100, fale_2);
        fwrite(&dat.day, sizeof(int), 1, fale_1);
        fwrite(&dat.month, sizeof(char), 10, fale_1);
        fwrite(&dat.year, sizeof(int), 1, fale_1);
        fwrite(&dat.event, sizeof(char), 150, fale_1);
        fwrite(&dat.classification, sizeof(char), 12, fale_1);
        fwrite(&dat.name, sizeof(char), 50, fale_1);
    }

}

void Edit() { // function editing data
    int classificationch;
    int look;
    printf("%s\n", "Look for with: ");
    printf("%s\n", "1) Data");
    printf("%s\n", "2) Name");
    printf("%s\n", "3) Category");
    scanf_s("%d", &look);
    switch (look){
    case 1:
        printf("%s\n", "Which date you want to see(D/M/Y): ");
        scanf_s(" %d", &dat.day);
        scanf_s(" %s", dat.month, (unsigned)_countof(dat.month));
        scanf_s(" %d", &dat.year);
        printf("\nThere are events: \n");
        SearchForData();
        break;
    case 2:
        printf("%s\n", "Print Name: ");
        scanf_s("%s", dat.name, (unsigned)_countof(dat.name));
        printf("There are events: \n");
        SearchForName();
        break;
    case 3:
        printf("%s\n", "Shoose category: ");
        printf("%s\n", "1) Birth Day");
        printf("%s\n", "2) Celebration");
        printf("%s\n", "3) Event");
        scanf_s("%d", &classificationch);
        switch (classificationch) { // Choose of category
        case 1:
            strcpy_s(dat.classification, _countof(dat.classification), "Birth Day");
            break;
        case 2:
            strcpy_s(dat.classification, _countof(dat.classification), "Celebration");
            break;
        case 3:
            strcpy_s(dat.classification, _countof(dat.classification), "Event");
            break;
        }
        printf("\nThere are events: \n");
        SearchForCategory();
        break;
    }

    
}

void Choose() { //function of menu
    int choose;
    printf("%s\n", "What you want to do?");
    printf("%s\n", "1) Add event");
    printf("%s\n", "2) Edit event");
    printf("%s\n", "3) Delete event");
    printf("%s\n", "4) Show the data");
    printf("%s\n", "0) Exit");
    scanf_s("%d", &choose);
    //printf("%s\n", (choose  < 0) || (choose > 4)? "Wrong option" : "Loading...    Ready");
    switch (choose) {
    case 1:
        Add();
        Choose();
        break;
    case 2:
        Edit();
        Choose();
        break;
    case 3:
        Delete();
        Choose();
        break;
    case 4:
        printf("Событие %s назначено на %d %s %d", dat.event, dat.day, dat.month, dat.year);
        Choose();
        break;
    case 0:
        fclose(fale_1);
        exit(1);
    }
}

void main() {
    fopen_s(&fale_1, "file.dat", "r+b");
    Choose();
}