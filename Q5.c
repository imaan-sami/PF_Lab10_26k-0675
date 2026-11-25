#include <stdio.h>

int main() {
    FILE *fp;
    char category[13];
    float amount, total = 0;
    int entry;

    fp = fopen("expenses.txt", "wb");
    if (fp == NULL) {
        printf("Could not create expenses.txt\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", "Food",      1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport",  500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books",      850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile",     300.00);
    fclose(fp);

    printf("Category: ");
    scanf("%12s", category);
    printf("Amount: ");
    scanf("%f", &amount);

    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) {
        printf("Could not open expenses.txt\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", category, amount);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open expenses.txt\n");
        return 1;
    }
    fseek(fp, -2 * 23, SEEK_END);

    printf("Latest two: ");
    fscanf(fp, "%s %f", category, &amount);
    printf("%s %.2f, ", category, amount);
    fscanf(fp, "%s %f", category, &amount);
    printf("%s %.2f\n", category, amount);

    printf("Entry to fix: ");
    scanf("%d", &entry);
    printf("Correct amount: ");
    scanf("%f", &amount);

    fseek(fp, (entry - 1) * 23, SEEK_SET);
    fscanf(fp, "%s %f", category, &total);     
    fseek(fp, (entry - 1) * 23, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", category, amount);

    total = 0;
    rewind(fp);
    while (fscanf(fp, "%s %f", category, &amount) == 2) {
        printf("%s %.2f\n", category, amount);
        total = total + amount;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}
