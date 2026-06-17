#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "UBUDEHE.txt"
#define MAX_LINE  512
#define ID_LEN    20
#define NAME_LEN  60
#define GENDER_LEN 10
#define PHONE_LEN  16
#define CELL_LEN   40
#define VILLAGE_LEN 40
#define DATE_LEN   20

typedef struct {
    char nationalID[ID_LEN];
    char names[NAME_LEN];
    char gender[GENDER_LEN];
    char phone[PHONE_LEN];
    char cell[CELL_LEN];
    char village[VILLAGE_LEN];
    char startingDate[DATE_LEN];
} Person;

/* ── helpers ── */

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readString(const char *prompt, char *buf, int size) {
    printf("%s", prompt);
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

void printDivider(void) {
    printf("============================================================\n");
}

void printHeader(void) {
    printDivider();
    printf("       MAYANGE SECTOR - UBUDEHE PROGRAM MANAGEMENT\n");
    printf("              Bugesera District, Rwanda\n");
    printDivider();
}

/* Encode one record as a single CSV line */
void encodeLine(const Person *p, char *line) {
    sprintf(line, "%s|%s|%s|%s|%s|%s|%s\n",
            p->nationalID, p->names, p->gender,
            p->phone, p->cell, p->village, p->startingDate);
}

/* Decode a CSV line into a Person struct; returns 1 on success */
int decodeLine(const char *line, Person *p) {
    char tmp[MAX_LINE];
    strncpy(tmp, line, MAX_LINE - 1);
    tmp[strcspn(tmp, "\n")] = '\0';

    char *tok = strtok(tmp, "|");
    if (!tok) return 0;
    strncpy(p->nationalID, tok, ID_LEN - 1);

    tok = strtok(NULL, "|"); if (!tok) return 0;
    strncpy(p->names, tok, NAME_LEN - 1);

    tok = strtok(NULL, "|"); if (!tok) return 0;
    strncpy(p->gender, tok, GENDER_LEN - 1);

    tok = strtok(NULL, "|"); if (!tok) return 0;
    strncpy(p->phone, tok, PHONE_LEN - 1);

    tok = strtok(NULL, "|"); if (!tok) return 0;
    strncpy(p->cell, tok, CELL_LEN - 1);

    tok = strtok(NULL, "|"); if (!tok) return 0;
    strncpy(p->village, tok, VILLAGE_LEN - 1);

    tok = strtok(NULL, "|"); if (!tok) return 0;
    strncpy(p->startingDate, tok, DATE_LEN - 1);
    return 1;
}

void printPerson(const Person *p, int idx) {
    printf("\n  Record #%d\n", idx);
    printf("  National ID   : %s\n", p->nationalID);
    printf("  Names         : %s\n", p->names);
    printf("  Gender        : %s\n", p->gender);
    printf("  Phone         : %s\n", p->phone);
    printf("  Cell          : %s\n", p->cell);
    printf("  Village       : %s\n", p->village);
    printf("  Starting Date : %s\n", p->startingDate);
}

/* ── CRUD operations ── */

void addRecord(void) {
    printDivider();
    printf("  ADD NEW UBUDEHE RECORD\n");
    printDivider();

    Person p = {0};
    readString("  National ID   : ", p.nationalID,   ID_LEN);
    readString("  Full Names    : ", p.names,         NAME_LEN);
    readString("  Gender (M/F)  : ", p.gender,        GENDER_LEN);
    readString("  Phone Number  : ", p.phone,          PHONE_LEN);
    readString("  Cell          : ", p.cell,           CELL_LEN);
    readString("  Village       : ", p.village,        VILLAGE_LEN);
    readString("  Starting Date : ", p.startingDate,   DATE_LEN);

    /* Check for duplicate ID */
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp) {
        char line[MAX_LINE];
        Person tmp;
        while (fgets(line, sizeof(line), fp)) {
            if (decodeLine(line, &tmp) &&
                strcmp(tmp.nationalID, p.nationalID) == 0) {
                fclose(fp);
                printf("\n  [!] Record with National ID '%s' already exists.\n\n",
                       p.nationalID);
                return;
            }
        }
        fclose(fp);
    }

    fp = fopen(FILE_NAME, "a");
    if (!fp) { perror("  [!] Cannot open file"); return; }

    char line[MAX_LINE];
    encodeLine(&p, line);
    fputs(line, fp);
    fclose(fp);

    printf("\n  [+] Record added successfully.\n\n");
}

void viewRecords(void) {
    printDivider();
    printf("  ALL UBUDEHE RECORDS\n");
    printDivider();

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("\n  No records found (file does not exist yet).\n\n");
        return;
    }

    char line[MAX_LINE];
    Person p;
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (decodeLine(line, &p)) {
            printPerson(&p, ++count);
            printf("  ----------------------------------------------------------\n");
        }
    }
    fclose(fp);

    if (count == 0)
        printf("\n  No records found.\n");
    printf("\n  Total records: %d\n\n", count);
}

void editRecord(void) {
    printDivider();
    printf("  EDIT EXISTING RECORD\n");
    printDivider();

    char searchID[ID_LEN];
    readString("  Enter National ID to edit: ", searchID, ID_LEN);

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("\n  [!] No records file found.\n\n"); return; }

    /* Load all records into memory */
    Person records[1000];
    int total = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp) && total < 1000) {
        if (decodeLine(line, &records[total]))
            total++;
    }
    fclose(fp);

    int found = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(records[i].nationalID, searchID) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\n  [!] Record with National ID '%s' not found.\n\n", searchID);
        return;
    }

    printf("\n  Current record:\n");
    printPerson(&records[found], found + 1);
    printf("\n  Enter new values (press ENTER to keep current):\n\n");

    Person updated = records[found];
    char buf[NAME_LEN];

    #define EDIT_FIELD(prompt, field, size) \
        printf("  " prompt " [%s]: ", updated.field); \
        fgets(buf, size, stdin); \
        buf[strcspn(buf, "\n")] = '\0'; \
        if (strlen(buf) > 0) strncpy(updated.field, buf, size - 1);

    EDIT_FIELD("Full Names   ", names,        NAME_LEN);
    EDIT_FIELD("Gender (M/F) ", gender,       GENDER_LEN);
    EDIT_FIELD("Phone Number ", phone,         PHONE_LEN);
    EDIT_FIELD("Cell         ", cell,          CELL_LEN);
    EDIT_FIELD("Village      ", village,       VILLAGE_LEN);
    EDIT_FIELD("Starting Date", startingDate,  DATE_LEN);

    records[found] = updated;

    /* Rewrite file */
    fp = fopen(FILE_NAME, "w");
    if (!fp) { perror("  [!] Cannot write file"); return; }
    for (int i = 0; i < total; i++) {
        char out[MAX_LINE];
        encodeLine(&records[i], out);
        fputs(out, fp);
    }
    fclose(fp);

    printf("\n  [+] Record updated successfully.\n\n");
}

void deleteRecord(void) {
    printDivider();
    printf("  DELETE RECORD\n");
    printDivider();

    char searchID[ID_LEN];
    readString("  Enter National ID to delete: ", searchID, ID_LEN);

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("\n  [!] No records file found.\n\n"); return; }

    Person records[1000];
    int total = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp) && total < 1000) {
        if (decodeLine(line, &records[total]))
            total++;
    }
    fclose(fp);

    int found = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(records[i].nationalID, searchID) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\n  [!] Record with National ID '%s' not found.\n\n", searchID);
        return;
    }

    printf("\n  Record to delete:\n");
    printPerson(&records[found], found + 1);

    char confirm[4];
    readString("\n  Confirm deletion? (yes/no): ", confirm, sizeof(confirm));
    if (strcmp(confirm, "yes") != 0) {
        printf("\n  Deletion cancelled.\n\n");
        return;
    }

    /* Shift records to remove the deleted one */
    for (int i = found; i < total - 1; i++)
        records[i] = records[i + 1];
    total--;

    fp = fopen(FILE_NAME, "w");
    if (!fp) { perror("  [!] Cannot write file"); return; }
    for (int i = 0; i < total; i++) {
        char out[MAX_LINE];
        encodeLine(&records[i], out);
        fputs(out, fp);
    }
    fclose(fp);

    printf("\n  [-] Record deleted successfully.\n\n");
}

/* ── main menu ── */

int main(void) {
    int choice;

    while (1) {
        printHeader();
        printf("  1. Add New Record\n");
        printf("  2. View All Records\n");
        printf("  3. Edit Existing Record\n");
        printf("  4. Delete Record\n");
        printf("  5. Exit\n");
        printDivider();
        printf("  Enter choice [1-5]: ");

        if (scanf("%d", &choice) != 1) { clearBuffer(); continue; }
        clearBuffer();
        printf("\n");

        switch (choice) {
            case 1: addRecord();    break;
            case 2: viewRecords();  break;
            case 3: editRecord();   break;
            case 4: deleteRecord(); break;
            case 5:
                printf("  Goodbye!\n\n");
                return 0;
            default:
                printf("  [!] Invalid choice. Try again.\n\n");
        }
    }
}
