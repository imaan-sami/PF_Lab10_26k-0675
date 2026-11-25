
#include <stdio.h>

int main() {
    FILE *fp;
    char city[11];
    float temp;
    int n, i;
    float newTemp, hottestTemp;
    char hottestCity[11];


    fp = fopen("temperature.txt", "wb");
    if (fp == NULL) {
        printf("Could not create temperature.txt\n");
        return 1;
    }
    for (i = 1; i <= 5; i++) {
        printf("City %d name: ", i);
        scanf("%10s", city);
        printf("City %d temperature: ", i);
        scanf("%f", &temp);
        fprintf(fp, "%-10s %5.1f\n", city, temp);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open temperature.txt\n");
        return 1;
    }

    printf("City number: ");
    scanf("%d", &n);
    if (n < 1 || n > 5) {
        printf("Invalid city number\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (n - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", city, &temp);
    printf("%s %.1f\n", city, temp);


    printf("City number to correct: ");
    scanf("%d", &n);
    printf("New temperature: ");
    scanf("%f", &newTemp);
    if (n < 1 || n > 5) {
        printf("Invalid city number\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (n - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", city, &temp);         

    fseek(fp, (n - 1) * 17, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", city, newTemp);
    printf("%s updated to %.1f\n", city, newTemp);


    rewind(fp);
    hottestTemp = -1000;
    for (i = 0; i < 5; i++) {
        fscanf(fp, "%s %f", city, &temp);
        if (temp > hottestTemp) {
            hottestTemp = temp;
           
            int k = 0;
            while (city[k] != '\0') {
                hottestCity[k] = city[k];
                k++;
            }
            hottestCity[k] = '\0';
        }
    }
    printf("Hottest city: %s (%.1f)\n", hottestCity, hottestTemp);

    fclose(fp);
    return 0;
}
