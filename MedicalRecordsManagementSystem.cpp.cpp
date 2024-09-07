#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct medicine {
    char name[50];
    int quantity;
    float price;
};

void addMedicine() {
    FILE *fp;
    struct medicine m;
    fp = fopen("medicine.dat", "ab");
    printf("Enter name of medicine: ");
    scanf("%s", m.name);
    printf("Enter quantity: ");
    scanf("%d", &m.quantity);
    printf("Enter price: ");
    scanf("%f", &m.price);
    fwrite(&m, sizeof(m), 1, fp);
    printf("\nMedicine added successfully!\n\n");
    fclose(fp);
}

void displayMedicine() {
    FILE *fp;
    struct medicine m;
    fp = fopen("medicine.dat", "rb");
    printf("\nMedicine Details\n\n");
    printf("Name\t\tQuantity\tPrice\n");
    while(fread(&m, sizeof(m), 1, fp) == 1) {
        printf("%s\t\t%d\t\t%.2f\n", m.name, m.quantity, m.price);
    }
    printf("\n");
    fclose(fp);
}

void searchMedicine() {
    FILE *fp;
    struct medicine m;
    char name[50];
    int found = 0;
    fp = fopen("medicine.dat", "rb");
    printf("Enter name of medicine to search: ");
    scanf("%s", name);
    while(fread(&m, sizeof(m), 1, fp) == 1) {
        if(strcmp(name, m.name) == 0) {
            printf("\nMedicine Found\n\n");
            printf("Name\t\tQuantity\tPrice\n");
            printf("%s\t\t%d\t\t%.2f\n\n", m.name, m.quantity, m.price);
            found = 1;
            break;
        }
    }
    if(found == 0) {
        printf("\nMedicine not found!\n\n");
    }
    fclose(fp);
}

void deleteMedicine() {
    FILE *fp, *temp;
    struct medicine m;
    char name[50];
    int found = 0;
    fp = fopen("medicine.dat", "rb");
    temp = fopen("temp.dat", "wb");
    printf("Enter name of medicine to delete: ");
    scanf("%s", name);
    while(fread(&m, sizeof(m), 1, fp) == 1) {
        if(strcmp(name, m.name) != 0) {
            fwrite(&m, sizeof(m), 1, temp);
        } else {
            found = 1;
        }
    }
    if(found == 0) {
        printf("\nMedicine not found!\n\n");
    } else {
        printf("\nMedicine deleted successfully!\n\n");
    }
    fclose(fp);
    fclose(temp);
    remove("medicine.dat");
    rename("temp.dat", "medicine.dat");
}

void updateMedicine() {
    FILE *fp, *temp;
    struct medicine m;
    char name[50];
    int found = 0;
    fp = fopen("medicine.dat", "rb");
    temp = fopen("temp.dat", "wb");
    printf("Enter name of medicine to update: ");
    scanf("%s", name);
    while(fread(&m, sizeof(m), 1, fp) == 1) {
        if(strcmp(name, m.name) == 0) {
            printf("\nEnter new quantity: ");
            scanf("%d", &m.quantity);
            printf("Enter new price: ");
            scanf("%f", &m.price);
            fwrite(&m, sizeof(m), 1, temp);
            found = 1;
        } else {
            fwrite(&m, sizeof(m), 1, temp);
        }
    }
    if(found == 0) {
        printf("\nMedicine not found!\n\n");
    } else {
        printf("\nMedicine updated successfully!\n\n");
    }
    fclose(fp);
    fclose(temp);
    remove("medicine.dat");
    rename("temp.dat", "medicine.dat");
}

int main() {
    int choice;
    printf("\nMedical Record Management System\n");
    do {
        printf("\nMenu\n");
        printf("1. Display Medicine Details\n");
        printf("2. Add new Medicine\n");
        printf("3. Delete Medicine Details\n");
        printf("4. Search a particular Medicine\n");
        printf("5. Update Medicine Details\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: displayMedicine();
                    break;
            case 2: addMedicine();
                    break;
            case 3: deleteMedicine();
                    break;
            case 4: searchMedicine();
                    break;
            case 5: updateMedicine();
                    break;
            case 6: printf("\nExiting...\n\n");
                    break;
            default: printf("\nInvalid Choice!\n\n");
                     break;
        }
    } while(choice != 6);
    return 0;
}
