#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    int choice, room, nights, i;
    int r, n;
    char status;
    char name[21];
    float rate;

    char guests[10][21];
    int rooms[10];
    char searchName[21];
    int found;

    fp = fopen("hotel.txt", "wb");
    if (fp == NULL) {
        printf("Could not create hotel.txt\n");
        return 1;
    }
    for (room = 101; room <= 110; room++) {
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, 8000.00);
    }
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open hotel.txt\n");
        return 1;
    }

    while (1) {
        printf("\n1. Check-in\n2. Search guest\n3. Check-out\n0. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        if (choice == 1) {

            printf("Check-in room: ");
            scanf("%d", &room);
            printf("Name: ");
            scanf("%20s", name);
            printf("Nights: ");
            scanf("%d", &nights);

            if (room < 101 || room > 110) {
                printf("No such room\n");
                continue;
            }

            fseek(fp, (room - 101) * 39, SEEK_SET);
            fscanf(fp, "%d %c", &r, &status);

            if (status == 'F') {
                fseek(fp, (room - 101) * 39, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', name, nights, 8000.00);
                printf("Room %d booked\n", room);
            } else {
                printf("Room already booked\n");
            }
        }
        else if (choice == 2) {
            rewind(fp);
            for (i = 0; i < 10; i++) {
                fscanf(fp, "%d %c %s %d %f", &rooms[i], &status, guests[i], &n, &rate);
            }

            printf("Search name: ");
            scanf("%20s", searchName);

            found = 0;
            for (i = 0; i < 10; i++) {
                if (strcmp(guests[i], searchName) == 0) {
                    printf("%s is in room %d\n", searchName, rooms[i]);
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                printf("%s not found\n", searchName);
            }
        }
        else if (choice == 3) {
            // ---- Check-out ----
            printf("Check-out room: ");
            scanf("%d", &room);

            if (room < 101 || room > 110) {
                printf("No such room\n");
                continue;
            }

            fseek(fp, (room - 101) * 39, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &r, &status, name, &nights, &rate);

            if (status == 'F') {
                printf("Room %d is already free\n", room);
            } else {
                printf("Bill: %d x %.2f = %.2f\n", nights, rate, nights * rate);

                fseek(fp, (room - 101) * 39, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, 8000.00);
            }
        }
        else {
            printf("Wrong choice\n");
        }
    }

    fclose(fp);
    return 0;
}
