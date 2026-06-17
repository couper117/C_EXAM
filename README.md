# UBUDEHE Program Records Management System
**Mayange Sector, Bugesera District – Rwanda**

A C application that manages people's records for the UBUDEHE road-work program.  
Records are stored in a plain-text file (`UBUDEHE.txt`) using a pipe-delimited format.

---

## Fields stored per person

| Field | Description |
|-------|-------------|
| National ID | 16-digit Rwandan national identity number |
| Names | Full names of the participant |
| Gender | M or F |
| Phone | Mobile phone number |
| Cell | Cell name within Mayange Sector |
| Village | Village name within the cell |
| Starting Date | Date they joined the program (YYYY-MM-DD) |

---

## How to compile & run

```bash
gcc -Wall -Wextra -o ubudehe.exe ubudehe.c
./ubudehe.exe
```

---

## Features & Output

### Menu

```
============================================================
       MAYANGE SECTOR - UBUDEHE PROGRAM MANAGEMENT
              Bugesera District, Rwanda
============================================================
  1. Add New Record
  2. View All Records
  3. Edit Existing Record
  4. Delete Record
  5. Exit
============================================================
  Enter choice [1-5]:
```

---

### 1. Add New Record

Prompts for all fields. Prevents duplicate National IDs.

```
============================================================
  ADD NEW UBUDEHE RECORD
============================================================
  National ID   : 2000050456789012
  Full Names    : HABIMAN A Paul
  Gender (M/F)  : M
  Phone Number  : 0711567890
  Cell          : Ntarama
  Village       : Rubona
  Starting Date : 2024-04-05

  [+] Record added successfully.
```

---

### 2. View All Records

Displays every record in the file with a running count.

```
============================================================
  ALL UBUDEHE RECORDS
============================================================

  Record #1
  National ID   : 1198780123456789
  Names         : KAMANA Jean Pierre
  Gender        : M
  Phone         : 0788123456
  Cell          : Nyamata
  Village       : Kabuye
  Starting Date : 2024-01-15
  ----------------------------------------------------------

  Record #2
  National ID   : 1199900234567890
  Names         : MUKAMURINZI Alice
  Gender        : F
  Phone         : 0722345678
  Cell          : Ruhuha
  Village       : Kiziba
  Starting Date : 2024-02-20
  ----------------------------------------------------------

  Record #3
  National ID   : 1200010345678901
  Names         : NIYONSENGA Eric
  Gender        : M
  Phone         : 0733456789
  Cell          : Mwogo
  Village       : Gatare
  Starting Date : 2024-03-10
  ----------------------------------------------------------

  Record #4
  National ID   : 2000050456789012
  Names         : HABIMAN A Paul
  Gender        : M
  Phone         : 0711567890
  Cell          : Ntarama
  Village       : Rubona
  Starting Date : 2024-04-05
  ----------------------------------------------------------

  Total records: 4
```

---

### 3. Edit Existing Record

Search by National ID. Shows current values in brackets – press ENTER to keep, or type a new value.

```
============================================================
  EDIT EXISTING RECORD
============================================================
  Enter National ID to edit: 1198780123456789

  Current record:

  Record #1
  National ID   : 1198780123456789
  Names         : KAMANA Jean Pierre
  Gender        : M
  Phone         : 0788123456
  Cell          : Nyamata
  Village       : Kabuye
  Starting Date : 2024-01-15

  Enter new values (press ENTER to keep current):

  Full Names    [KAMANA Jean Pierre]:
  Gender (M/F)  [M]:
  Phone Number  [0788123456]: 0799999999
  Cell          [Nyamata]:
  Village       [Kabuye]:
  Starting Date [2024-01-15]:

  [+] Record updated successfully.
```

---

### 4. Delete Record

Search by National ID, shows the record, and asks for confirmation before deleting.

```
============================================================
  DELETE RECORD
============================================================
  Enter National ID to delete: 2000050456789012

  Record to delete:

  Record #4
  National ID   : 2000050456789012
  Names         : HABIMAN A Paul
  Gender        : M
  Phone         : 0711567890
  Cell          : Ntarama
  Village       : Rubona
  Starting Date : 2024-04-05

  Confirm deletion? (yes/no): yes

  [-] Record deleted successfully.
```

---

### UBUDEHE.txt (after all operations)

```
1198780123456789|KAMANA Jean Pierre|M|0799999999|Nyamata|Kabuye|2024-01-15
1199900234567890|MUKAMURINZI Alice|F|0722345678|Ruhuha|Kiziba|2024-02-20
1200010345678901|NIYONSENGA Eric|M|0733456789|Mwogo|Gatare|2024-03-10
```

---

## Author
Developed for the C Programming Practical Exam – Mayange Sector UBUDEHE Program.
