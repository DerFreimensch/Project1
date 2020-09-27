#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dates  // structure for day-month-year-event
{
    int day;
    char month[10];
    int year;
    char event[150];
};
char garbage[2];// garbage for '\n'
char eve[150];
struct dates dat;
FILE* fale_1;

void Add() { // function add in database
    printf("write day, month, year, event\n");
    scanf_s("%d%s%d", &dat.day, dat.month, (unsigned)_countof(dat.month), &dat.year);
    gets(garbage);
    gets(dat.event);
    fseek(fale_1, 0, SEEK_END);
    fwrite(&dat.day, sizeof(int), 1, fale_1);
    fwrite(&dat.month, sizeof(char), 10, fale_1);
    fwrite(&dat.year, sizeof(int), 1, fale_1);
    fwrite(&dat.event, sizeof(char), 150, fale_1);
    
}

void Search() { // function looking for data
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
        int flag = 1;
        flag = strncmp(dat.month, m, 3);
        if (dat.day == d && dat.year == y && flag == 0) {
            printf("%d %s %d: %s\n", dat.day, dat.month, dat.year, dat.event);
            dat.day = 0;
            }
        
    }
    printf("\n");

}
void Delete() { // function deleting data

}

void Edit() { // function editing data
    printf("%s\n", "Which date you want to see ");
    scanf_s(" %d", &dat.day);
    scanf_s(" %s", dat.month, (unsigned)_countof(dat.month));
    scanf_s(" %d", &dat.year);
    printf("\nThere are events: \n");
    Search();
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
        printf("something");
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