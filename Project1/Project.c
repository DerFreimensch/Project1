#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dates  // структура для работы с день-месяц-год-событие
{
    int day;
    char month[10];
    int year;
    char event[150];
};
int choose;
struct dates dat;
FILE* fale_1;

void Add() { // функция занесения в БД

    scanf_s("%d %s %d %s", &dat.day, dat.month, (unsigned)_countof(dat.month), &dat.year, dat.event, (unsigned)_countof(dat.month));
    fseek(fale_1, 0, SEEK_END);
    fwrite(&dat.day, sizeof(int), 1, fale_1);
    fwrite(&dat.month, sizeof(char), 10, fale_1);
    fwrite(&dat.year, sizeof(int), 1, fale_1);
    fwrite(&dat.event, sizeof(char), 150, fale_1);
}

void Search() { // фуенкция поиска необходимых дат
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
            fseek(fale_1, 0, SEEK_CUR);
            printf("%d%s%d%s", dat.day, dat.month, dat.year, dat.event);
        }
        
    }

}
void Delete() { // функция удаления определенных записей

}

void Edit() { // функция изменения записи
    printf("%s\n", "Which date you want to see ");
    scanf_s("%d %s %d", &dat.day, dat.month, (unsigned)_countof(dat.month), &dat.year);
    Search();
}

void Choose() {
    printf("%s\n", "What you want to do?");
    printf("%s\n", "1) Add event");
    printf("%s\n", "2) Edit event");
    printf("%s\n", "3) Delete event");
    printf("%s\n", "4) Show the data");
    printf("%s\n", "0) Exit");
    scanf_s("%d", &choose);
    printf("%s\n", (choose < 0) || (choose > 4) ? "Wrong option" : "Loading...    Ready");
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
        break;
    case 4:
        printf("Событие %s назначено на %d %s %d", dat.event, dat.day, dat.month, dat.year);
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