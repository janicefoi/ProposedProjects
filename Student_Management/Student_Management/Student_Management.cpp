// Student_Management.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<windows.h>
#include<stdlib.h>

typedef struct Student
{
    char studentName[50];
    char studentId[15];
    char studentDept[20];
    char studentCourse[30];
    char studentAddress[100];
    char studentContactNum[15];
    float marksAssignment;
    float marksSmallExam;
    float marksFinalExam;
    float marksTutorial;
    float finalExam;
    int totalClasses;
    int attendedClasses;
} Student;

void createAccount();
void displayInfo();
void updateInfo();
void deleteInfo();
void searchInfo();
void exportToText();
void importFromText();
void showReports();
void sortStudents();
 

void generateNextId(char* buffer, int size);

float calculateFinal(Student s);
float calculateAttendance(Student s);
int idExists(const char* id);

void inputString(const char* label, char* buffer, int size);
float getValidMark(const char* label);
void getValidAttendance(Student* s);
void chooseDepartment(Student* s);
void chooseCourse(Student* s);
void printStudentFull(Student s);
void printStudentRow(Student s);

//void sortByName(Student* students, int count);
//void sortById(Student* students, int count);
//void sortByFinalScore(Student* students, int count);
//void sortByAttendance(Student* students, int count);
//void sortByDepartment(Student* students, int count);
//void sortByCourse(Student* students, int count);
//void displaySortedStudents(Student* students, int count);

//void sortStudents();
void sortByName(Student arr[], int n);
void sortByID(Student arr[], int n);
void sortByFinalScore(Student arr[], int n);
void sortByAttendance(Student arr[], int n);
void sortByDepartment(Student arr[], int n);
void sortByCourse(Student arr[], int n);
void displaySorted(Student arr[], int n, const char* title);



int main()
{
    char option = '9';

    while (option != '0')
    {
        system("cls");
        printf("\t\t====== Student Management Database System ======\n");
        printf("\n\t\t\t1. Create Student Account");
        printf("\n\t\t\t2. Display All Students Information");
        printf("\n\t\t\t3. Update Student Information");
        printf("\n\t\t\t4. Delete Student Information");
        printf("\n\t\t\t5. Search Student Information");
        printf("\n\t\t\t6. Export Data to Text File");
        printf("\n\t\t\t7. Import Edited Text File");
        printf("\n\t\t\t8. Reports & Analytics");
        printf("\n\t\t\t9. Sort Students");
        //printf("\n\t\t\t10. Backup & Restore Data"); // optional if you add option 10


        printf("\n\t\t\t0. Exit");

        printf("\n\n\n\t\t\tEnter Your Option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1': createAccount();   break;
        case '2': displayInfo();     break;
        case '3': updateInfo();      break;
        case '4': deleteInfo();      break;
        case '5': searchInfo();      break;
        case '6': exportToText();    break;
        case '7': importFromText();  break;
        case '8': showReports();     break;
        case '9': sortStudents();    break;


        case '0':
            printf("\n\t\t\t====== Thank You ======");
            break;
        default:
            printf("\n\t\t\tInvalid Option, Please Enter Right Option !\n");
        }
    }
    return 0;
}

// Generate next sequential student ID in format S0001
void generateNextId(char* buffer, int size)
{
    FILE* file = fopen("studentInfo.bin", "rb");
    int maxNum = 0;
    if (file)
    {
        Student s;
        while (fread(&s, sizeof(s), 1, file) == 1)
        {
            if (s.studentId[0] == 'S')
            {
                int num = atoi(s.studentId + 1);
                if (num > maxNum) maxNum = num;
            }
        }
        fclose(file);
    }
    int next = maxNum + 1;
    _snprintf(buffer, size, "S%04d", next);
}


// Creates a new student account and saves it to the binary file.
void createAccount()
{
    FILE* fileOne = fopen("studentInfo.bin", "ab+");

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    Student studentInformation;

    system("cls");

    printf("\t\t\t====== Create Student Account ======\n");

    getchar();

    inputString("\tEnter Name: ", studentInformation.studentName, 50);
    // Generate sequential student ID automatically
    generateNextId(studentInformation.studentId, 15);
    printf("\tAssigned Student ID: %s\n", studentInformation.studentId);

    chooseDepartment(&studentInformation);
    chooseCourse(&studentInformation);

    getchar();

    inputString("\tEnter Address: ", studentInformation.studentAddress, 100);
    inputString("\tEnter Contact: ", studentInformation.studentContactNum, 15);


    // Read marks with validation (0-100)
    studentInformation.marksAssignment = getValidMark("\tEnter Assignment Marks");
    studentInformation.marksSmallExam = getValidMark("\tEnter Small Exam Marks");
    studentInformation.marksFinalExam = getValidMark("\tEnter Final Exam Marks");
    studentInformation.marksTutorial = getValidMark("\tEnter Tutorial Marks");



    getValidAttendance(&studentInformation);

    fwrite(&studentInformation, sizeof(studentInformation), 1, fileOne);

    printf("\n\n\t\t\tInformations have been stored sucessfully\n");
    printf("\n\n\t\t\tEnter any keys to continue.......");
    _getch();

    fclose(fileOne);
}

// Displays all stored student records in a formatted table.
void displayInfo()
{
    FILE* fileOne = fopen("studentInfo.bin", "rb");

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
        return;
    }

    Student stundentInformation;

    system("cls");

    printf("\t\t\t\t====== All Students Information ======\n");

    // Table header matching row widths so columns line up
    printf("\n\n\t\t| %-12s %-10s %-16s %-8s %-16s  %-11s %10s %8s |\n",
        "Name", "ID", "Address", "Dept", "Course", "Contact", "Final", "Attend%");

    printf("\t\t+------------------------------------------------------------------------------------+\n");

    while (fread(&stundentInformation, sizeof(stundentInformation), 1, fileOne) == 1)
    {
        printStudentRow(stundentInformation);
    }

    printf("\n\n\t\tEnter any keys to continue.......");
    _getch();

    fclose(fileOne);
}

// Updates a specific student's information based on their ID.
void updateInfo()
{
    FILE* fileOne = fopen("studentInfo.bin", "rb");
    FILE* temp = fopen("temp.bin", "wb");

    Student studentInformation, tempInformation;

    int choice, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Update Students Information ======\n");

    printf("\n\t\t\tEnter Student's ID : ");
    getchar();
    gets_s(tempInformation.studentId);

    while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
    {
        if (strcmp(studentInformation.studentId, tempInformation.studentId) == 0)
        {
            flag++;
            /*printf("\n\t\t\tChoose your option :\n\t\t\t1.Update Student Name\n\t\t\t2.Update Student Dept\n\t\t\t3.Update Student Address\n\t\t\t4.Update Student Contact No.\n\t\t\t5.Update Student CPGA");
            printf("\n\t\t\t6.Update Student Course");*/
            printf("\n\t\t\tChoose your option :");
            printf("\n\t\t\t1.Update Student Name");
            printf("\n\t\t\t2.Update Student Dept");
            printf("\n\t\t\t3.Update Student Course");
            printf("\n\t\t\t4.Update Student Address");
            printf("\n\t\t\t5.Update Student Contact No.");
            printf("\n\t\t\t6.Update Student Assignment Marks");
            printf("\n\t\t\t7.Update Student Small Exam Marks");
            printf("\n\t\t\t8.Update Student Final Exam Marks");
            printf("\n\t\t\t9.Update Student Tutorial Marks");
            printf("\n\n\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\t\t\tEnter Student's Name to Update: ");
                getchar();
                gets_s(tempInformation.studentName);
                strcpy(studentInformation.studentName, tempInformation.studentName);

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 2)
            {
                int tchoice = 0;
                printf("\n\t\t\tEnter Student's Dept to Update:\n\t\t\t1. Local\n\t\t\t2. International\n\t\t\tEnter choice (1-2): ");
                if (scanf("%d", &tchoice) != 1)
                {
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("\n\t\t\tInvalid input. Keeping previous type.\n");
                    strcpy(tempInformation.studentDept, studentInformation.studentDept);
                }
                else if (tchoice == 1)
                {
                    strcpy(tempInformation.studentDept, "Local");
                }
                else if (tchoice == 2)
                {
                    strcpy(tempInformation.studentDept, "Int");
                }
                else
                {
                    printf("\n\t\t\tInvalid choice. Keeping previous type.\n");
                    strcpy(tempInformation.studentDept, studentInformation.studentDept);
                }
                getchar();
                strcpy(studentInformation.studentDept, tempInformation.studentDept);

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 3)
            {
                int cchoice = 0;
                printf("\n\t\t\tSelect Course to Update:\n\t\t\t1. MSc Computer Science - SE\n\t\t\t2. MSc Computer Science - DSA\n\t\t\t3. MSc Computer Science - CS\n\t\t\t4. MSc Artificial Intelligence Systems - AIS\n\t\t\t5. MSc Artificial Intelligence for Marketing Strategy - AIMS\n\t\t\tEnter choice (1-5): ");
                if (scanf("%d", &cchoice) != 1)
                {
                    int cc; while ((cc = getchar()) != '\n' && cc != EOF);
                    printf("\n\t\t\tInvalid input. Keeping previous course.\n");
                    strcpy(tempInformation.studentCourse, studentInformation.studentCourse);
                }
                else if (cchoice == 1) strcpy(tempInformation.studentCourse, "MSc Computer Science - SE");
                else if (cchoice == 2) strcpy(tempInformation.studentCourse, "MSc Computer Science - DSA");
                else if (cchoice == 3) strcpy(tempInformation.studentCourse, "MSc Computer Science - CS");
                else if (cchoice == 4) strcpy(tempInformation.studentCourse, "MSc Artificial Intelligence Systems - AIS");
                else if (cchoice == 5) strcpy(tempInformation.studentCourse, "MSc Artificial Intelligence for Marketing Strategy - AIMS");
                else
                {
                    printf("\n\t\t\tInvalid choice. Keeping previous course.\n");
                    strcpy(tempInformation.studentCourse, studentInformation.studentCourse);
                }
                getchar();
                strcpy(studentInformation.studentCourse, tempInformation.studentCourse);

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 4)
            {
                printf("\n\t\t\tEnter Student's Address to Update: ");
                getchar();
                gets_s(tempInformation.studentAddress);
                strcpy(studentInformation.studentAddress, tempInformation.studentAddress);

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 5)
            {
                printf("\n\t\t\tEnter Student's Contact No. to Update: ");
                getchar();
                gets_s(tempInformation.studentContactNum);
                strcpy(studentInformation.studentContactNum, tempInformation.studentContactNum);

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 6)
            {
                tempInformation.marksAssignment = getValidMark("\n\t\t\tEnter Student Assignment Mark to Update");
                studentInformation.marksAssignment = tempInformation.marksAssignment;

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 7)
            {
                tempInformation.marksSmallExam = getValidMark("\n\t\t\tEnter Student Small Exam Mark to Update");
                studentInformation.marksSmallExam = tempInformation.marksSmallExam;

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 8)
            {
                tempInformation.marksFinalExam = getValidMark("\n\t\t\tEnter Student Final Exam Mark to Update");
                studentInformation.marksFinalExam = tempInformation.marksFinalExam;

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else if (choice == 9)
            {
                tempInformation.marksTutorial = getValidMark("\n\t\t\tEnter Student Tutorial Mark to Update");
                studentInformation.marksTutorial = tempInformation.marksTutorial;

                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
                printf("\n\n\t\t\tUpdated successfully!\n\n");
            }
            else
            {
                printf("\n\t\t\tInvalid Option.");
                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
        }
    }

    fclose(fileOne);
    fclose(temp);

    remove("studentInfo.bin");
    rename("temp.bin", "studentInfo.bin");

    if (flag == 0)
    {
        printf("\n\t\t\tStudent Id is not found");
    }

    printf("\n\n\t\t\tEnter any keys to continue.......");
    _getch();
}

// Deletes a student record from the database using their ID.
void deleteInfo()
{
    FILE* fileOne = fopen("studentInfo.bin", "rb");
    FILE* temp = fopen("temp.bin", "wb");

    Student studentInformation, tempInformation;

    int choice, flag = 0;

    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Delete Student Information ======\n");

    printf("\n\t\t\tEnter Student's ID : ");
    getchar();
    gets_s(tempInformation.studentId);

    while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
    {
        if (strcmp(studentInformation.studentId, tempInformation.studentId) == 0)
        {
            flag++;
            printf("\n\t\t\tAre you sure to delete ??\n\t\t\t\t1.Yes\n\t\t\t\t2.Back\n\t\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\n\t\t\tInformation has been deleted successfully!\n\n");
            }
            else if (choice == 2)
            {
                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
            }
            else
            {
                printf("\n\t\t\tInvalid Option");
                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
        }
    }

    fclose(fileOne);
    fclose(temp);

    remove("studentInfo.bin");
    rename("temp.bin", "studentInfo.bin");

    if (flag == 0)
    {
        printf("\n\t\t\tStudent Id is not found");
    }

    printf("\n\n\t\t\tEnter any keys to continue.......");
    _getch();
}

// Searches for student information by ID or department.
void searchInfo()
{
    FILE* fileOne = fopen("studentInfo.bin", "rb");

    Student studentInformation;

    int choice, flag = 0;
    char studentID[20], studentDept[10];

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    system("cls");

    printf("\t\t\t\t====== Search Student Information ======\n");

    printf("\n\t\t\tChoose your option :\n\t\t\t1.Search by Student ID\n\t\t\t2.Search by Student Dept.");
    printf("\n\n\t\t\tEnter Your Option : ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        system("cls");
        printf("\t\t\t\t====== Search Student Information ======\n");
        printf("\n\n\t\t\tEnter Student ID : ");
        getchar();
        gets_s(studentID);
        while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
        {
            if (strcmp(studentInformation.studentId, studentID) == 0)
            {
                flag++;
                printf("\n\t\t\tStudent Name : %s", studentInformation.studentName);
                printf("\n\t\t\tStudent ID : %s", studentInformation.studentId);
                printf("\n\t\t\tStudent Dept : %s", studentInformation.studentDept);
                printf("\n\t\t\tStudent Course : %s", studentInformation.studentCourse);
                printf("\n\t\t\tStudent Address : %s", studentInformation.studentAddress);
                printf("\n\t\t\tStudent Contact No. : %s", studentInformation.studentContactNum);

                printf("\n\t\t\tAssignment Marks : %.2f", studentInformation.marksAssignment);
                printf("\n\t\t\tSmall Exam Marks : %.2f", studentInformation.marksSmallExam);
                printf("\n\t\t\tFinal Exam Marks : %.2f", studentInformation.marksFinalExam);
                printf("\n\t\t\tTutorial Marks : %.2f", studentInformation.marksTutorial);

                printf("\n\t\t\tAttendance: %.2f%%", calculateAttendance(studentInformation));

                float att = calculateAttendance(studentInformation);
                if (att < 50)
                    printf("\n\t\t\tStatus: CRITICAL (Below 50%%)");
                else if (att < 75)
                    printf("\n\t\t\tStatus: WARNING (Below 75%%)");
                else
                    printf("\n\t\t\tStatus: OK");


                calculateFinal(studentInformation);

            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\tStudent Id is not found");
        }
    }
    else if (choice == 2)
    {
        system("cls");
        printf("\t\t\t\t====== Search Student Information ======\n");
        {
            int schoice = 0;
            printf("\n\n\t\t\tSelect Student Dept to search:\n\t\t\t1. Local\n\t\t\t2. International\n\t\t\tEnter choice (1-2): ");
            if (scanf("%d", &schoice) != 1)
            {
                int c; while ((c = getchar()) != '\n' && c != EOF);
                printf("\n\t\t\tInvalid input. Returning to menu.\n");
                fclose(fileOne);
                printf("\n\n\n\t\t\tEnter any keys to continue.......");
                _getch();
                return;
            }
            if (schoice == 1)
                strcpy(studentDept, "Local");
            else if (schoice == 2)
                strcpy(studentDept, "Int");
            else
            {
                printf("\n\t\t\tInvalid choice. Returning to menu.\n");
                fclose(fileOne);
                printf("\n\n\n\t\t\tEnter any keys to continue.......");
                _getch();
                return;
            }
            getchar();
        }
        printf("\n\n\t\t%-20s%-13s%-10s%-15s%-25s%-15s\n", "Name", "ID", "Dept", "Course", "Address", "Contact");
        printf("\t\t----------------------------------------------------------------------");
        while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
        {
            if (_stricmp(studentInformation.studentDept, studentDept) == 0)
            {
                flag++;
                printf("\n\n\t\t%-20s%-13s%-10s%-15s%-25s%-15s", studentInformation.studentName, studentInformation.studentId, studentInformation.studentDept, studentInformation.studentCourse, studentInformation.studentAddress, studentInformation.studentContactNum);
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\tStudent Id is not found");
        }
    }
    else
    {
        printf("\n\t\t\tInvalid Option");
    }

    fclose(fileOne);

    printf("\n\n\n\t\t\tEnter any keys to continue.......");
    _getch();
}

// Exports all student data into a readable text (CSV-style) file.
void exportToText()
{
    FILE* fileOne = fopen("studentInfo.bin", "rb");
    FILE* out = fopen("students.txt", "w");

    if (fileOne == NULL || out == NULL)
    {
        printf("\n\t\t\tError opening file!\n");
        return;
    }

    Student s;

    //fprintf(out, "Name,ID,Type,Course,Address,Contact,FinalExam\n");
    fprintf(out, "Name,ID,Type,Course,Address,Contact,Assignment,SmallExam,FinalExam,Tutorial,FinalResult\n");


    while (fread(&s, sizeof(Student), 1, fileOne) == 1)
    {
        fprintf(out, "%s,%s,%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            s.studentName,
            s.studentId,
            s.studentDept,
            s.studentCourse,
            s.studentAddress,
            s.studentContactNum,
            s.marksAssignment,
            s.marksSmallExam,
            s.marksFinalExam,
            s.marksTutorial,
            calculateFinal(s)
        );
    }

    fclose(fileOne);
    fclose(out);

    printf("\n\t\t\tExport completed! Open 'students.txt' to view the data.\n");
    printf("\n\t\t\tPress any key to continue...");
    _getch();
}

// Imports edited student data from a text file and rebuilds the binary file.
void importFromText()
{
    FILE* in = fopen("students.txt", "r");
    FILE* out = fopen("studentInfo.bin", "wb");

    if (in == NULL || out == NULL)
    {
        printf("\n\t\t\tError opening file!\n");
        return;
    }

    Student s;
    char line[512];

    // Skip header line
    fgets(line, sizeof(line), in);

    while (fgets(line, sizeof(line), in))
    {
        // Parse CSV line
        sscanf(line, "%49[^,],%14[^,],%9[^,],%29[^,],%99[^,],%14[^,],%f,%f,%f,%f,%f",
            s.studentName,
            s.studentId,
            s.studentDept,
            s.studentCourse,
            s.studentAddress,
            s.studentContactNum,
            &s.marksAssignment,
            &s.marksSmallExam,
            &s.marksFinalExam,
            &s.marksTutorial,
            &s.finalExam
        );

        fwrite(&s, sizeof(Student), 1, out);
    }

    fclose(in);
    fclose(out);

    printf("\n\t\t\tImport completed! New binary file created.\n");
    printf("\n\t\t\tPress any key to continue...");
    _getch();
}

// Generates analytics reports such as highest score, averages, and counts.
void showReports()
{
    FILE* file = fopen("studentInfo.bin", "rb");
    if (!file)
    {
        printf("\n\t\t\tError opening file!\n");
        _getch();
        return;
    }

    Student s;
    int total = 0;
    float sumFinal = 0;

    float highestScore = -1;
    float lowestScore = 9999;

    Student topStudent, lowStudent;

    int countLocal = 0, countInternational = 0;
    int countSE = 0, countDSA = 0, countCS = 0, countAIS = 0, countAIMS = 0;

    while (fread(&s, sizeof(Student), 1, file) == 1)
    {
        float final = calculateFinal(s);

        // Track highest
        if (final > highestScore)
        {
            highestScore = final;
            topStudent = s;
        }

        // Track lowest
        if (final < lowestScore)
        {
            lowestScore = final;
            lowStudent = s;
        }

        // Sum for average
        sumFinal += final;
        total++;

        // Count departments
        if (_stricmp(s.studentDept, "Local") == 0)
            countLocal++;
        else
            countInternational++;

        // Count courses
        if (strcmp(s.studentCourse, "MSc SE") == 0) countSE++;
        else if (strcmp(s.studentCourse, "MSc DSA") == 0) countDSA++;
        else if (strcmp(s.studentCourse, "MSc CS") == 0) countCS++;
        else if (strcmp(s.studentCourse, "MSc AIS") == 0) countAIS++;
        else if (strcmp(s.studentCourse, "MSc AIMS") == 0) countAIMS++;
    }

    fclose(file);

    system("cls");
    printf("\t\t====== Reports & Analytics ======\n\n");

    if (total == 0)
    {
        printf("\t\tNo student data available.\n");
        _getch();
        return;
    }

    printf("\t\tTotal Students: %d\n", total);
    printf("\t\tAverage Final Score: %.2f\n\n", sumFinal / total);

    printf("\t\t--- Highest Scorer ---\n");
    printf("\t\tName: %s\n", topStudent.studentName);
    printf("\t\tID: %s\n", topStudent.studentId);
    printf("\t\tFinal Score: %.2f\n\n", highestScore);

    printf("\t\t--- Lowest Scorer ---\n");
    printf("\t\tName: %s\n", lowStudent.studentName);
    printf("\t\tID: %s\n", lowStudent.studentId);
    printf("\t\tFinal Score: %.2f\n\n", lowestScore);

    printf("\t\t--- Department Count ---\n");
    printf("\t\tLocal: %d\n", countLocal);
    printf("\t\tInternational: %d\n\n", countInternational);

    printf("\t\t--- Course Count ---\n");
    printf("\t\tMSc SE: %d\n", countSE);
    printf("\t\tMSc DSA: %d\n", countDSA);
    printf("\t\tMSc CS: %d\n", countCS);
    printf("\t\tMSc AIS: %d\n", countAIS);
    printf("\t\tMSc AIMS: %d\n", countAIMS);

    printf("\n\n\t\tPress any key to continue...");
    _getch();
}



int isBlank(const char* str)
{
    if (str == NULL || str[0] == '\0')
        return 1;

    // Check if string is only spaces
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return 0;
    }
    return 1;
}

// Safely inputs a non-empty string with validation.
void inputString(const char* label, char* buffer, int size)
{
    while (1)
    {
        printf("%s", label);
        fgets(buffer, size, stdin);

        buffer[strcspn(buffer, "\n")] = 0; // remove newline

        if (!isBlank(buffer))
            break;

        printf("\t\t\tInput cannot be blank. Please try again.\n");
    }
}

// Checks if a student ID already exists in the database.
int idExists(const char* id)
{
    FILE* file = fopen("studentInfo.bin", "rb");
    if (!file) return 0;

    Student s;
    while (fread(&s, sizeof(s), 1, file) == 1)
    {
        if (strcmp(s.studentId, id) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Lets the user choose a department (Local/International).
void chooseDepartment(Student* s)
{
    int choice;
    do {
        printf("\tSelect Dept:\n\t1. Local\n\t2. International\n\tEnter choice: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 2);

    strcpy(s->studentDept, (choice == 1) ? "Local" : "Int");
}

// Lets the user choose a course from predefined MSc programs.
void chooseCourse(Student* s)
{
    int choice;
    const char* courses[] = { "MSc SE", "MSc DSA", "MSc CS", "MSc AIS", "MSc AIMS" };

    do {
        printf("\tSelect Course:\n");
        printf("\t1. MSc SE\n\t2. MSc DSA\n\t3. MSc CS\n\t4. MSc AIS\n\t5. MSc AIMS\n");
        printf("\tEnter choice: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 5);

    strcpy(s->studentCourse, courses[choice - 1]);
}

// Calculates the final weighted score for a student.
float calculateFinal(Student s)
{
    return (s.marksFinalExam * 0.40f) +
        (s.marksAssignment * 0.20f) +
        (s.marksSmallExam * 0.20f) +
        (s.marksTutorial * 0.20f);
}


// Gets a validated mark between 0 and 100.
float getValidMark(const char* label)
{
    float m;
    do {
        printf("%s (0-100): ", label);
        scanf("%f", &m);
    } while (m < 0 || m > 100);
    return m;
}

// Inputs and validates attendance values.
void getValidAttendance(Student* s)
{
    printf("\tEnter Total Classes Conducted: ");
    scanf("%d", &s->totalClasses);

    do {
        printf("\tEnter Classes Attended: ");
        scanf("%d", &s->attendedClasses);
    } while (s->attendedClasses < 0 || s->attendedClasses > s->totalClasses);
}


// Computes attendance percentage for a student.
float calculateAttendance(Student s)
{
    if (s.totalClasses == 0) return 0;
    return (s.attendedClasses * 100.0f) / s.totalClasses;
}

// Prints full detailed information of a student.
void printStudentFull(Student s)
{
    printf("\n\tName: %s", s.studentName);
    printf("\n\tID: %s", s.studentId);
    printf("\n\tDept: %s", s.studentDept);
    printf("\n\tCourse: %s", s.studentCourse);
    printf("\n\tAddress: %s", s.studentAddress);
    printf("\n\tContact: %s", s.studentContactNum);

    printf("\n\tAssignment: %.2f", s.marksAssignment);
    printf("\n\tSmall Exam: %.2f", s.marksSmallExam);
    printf("\n\tFinal Exam: %.2f", s.marksFinalExam);
    printf("\n\tTutorial: %.2f", s.marksTutorial);

    float att = calculateAttendance(s);
    printf("\n\tAttendance: %.2f%%", att);

    printf("\n\tFinal Result: %.2f\n", calculateFinal(s));
}

// Prints a compact row of student info for table display.
void printStudentRow(Student s)
{
    float att = calculateAttendance(s);

    float finalScore = calculateFinal(s);
    // Print row with separators matching the header widths. Truncate long strings to keep alignment.
    printf("\n\t\t| %-12s %-10.10s %-16.16s %-8.8s %-16.16s  %-11.11s %10.2f %8.2f%% |",
        s.studentName,
        s.studentId,
        s.studentAddress,
        s.studentDept,
        s.studentCourse,
        s.studentContactNum,
        finalScore,
        att);
}

// Sorts the student records based on various criteria and displays the sorted list.
void sortStudents() {
    FILE* file = fopen("studentInfo.bin", "rb");
    if (!file) {
        printf("\n\t\t\tError opening file!\n");
        _getch();
        return;
    }

    Student arr[500];
    int count = 0;

    while (fread(&arr[count], sizeof(Student), 1, file) == 1) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("\n\t\t\tNo student data available.\n");
        _getch();
        return;
    }

    int choice;
    do {
        system("cls");
        printf("\t\t====== Sort Students ======\n");
        printf("\n\t\t1. Sort by Name (A-Z)");
        printf("\n\t\t2. Sort by Student ID");
        printf("\n\t\t3. Sort by Final Score (High to Low)");
        printf("\n\t\t4. Sort by Attendance (High to Low)");
        printf("\n\t\t5. Sort by Department");
        printf("\n\t\t6. Sort by Course");
        printf("\n\t\t0. Back to Main Menu");

        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: sortByName(arr, count); break;
        case 2: sortByID(arr, count); break;
        case 3: sortByFinalScore(arr, count); break;
        case 4: sortByAttendance(arr, count); break;
        case 5: sortByDepartment(arr, count); break;
        case 6: sortByCourse(arr, count); break;
        }
    } while (choice != 0);
}

// Sort by Name
void sortByName(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].studentName, arr[j + 1].studentName) > 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

    displaySorted(arr, n, "Sorted by Name (A-Z)");
}

//Sort by ID
void sortByID(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].studentId, arr[j + 1].studentId) > 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

    displaySorted(arr, n, "Sorted by Student ID");
}

//Sort by Final Score (High → Low)
void sortByFinalScore(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (calculateFinal(arr[j]) < calculateFinal(arr[j + 1])) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

    displaySorted(arr, n, "Sorted by Final Score (High to Low)");
}

//Sort by Attendance (High → Low)
void sortByAttendance(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (calculateAttendance(arr[j]) < calculateAttendance(arr[j + 1])) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

    displaySorted(arr, n, "Sorted by Attendance (High to Low)");
}

//Sort by Department
void sortByDepartment(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].studentDept, arr[j + 1].studentDept) > 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

    displaySorted(arr, n, "Sorted by Department");
}

// Sort by Course
void sortByCourse(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].studentCourse, arr[j + 1].studentCourse) > 0) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

    displaySorted(arr, n, "Sorted by Course");
}

// Displays the sorted list of students in a formatted table.
void displaySorted(Student arr[], int n, const char* title) {
    system("cls");
    printf("\t\t====== %s ======\n\n", title);

    printf("\n\n\t\t| %-12s %-10s %-16s %-8s %-16s %-11s %10s %8s |\n",
        "Name", "ID", "Address", "Dept", "Course", "Contact", "Final", "Attend%");

    printf("\t\t+------------------------------------------------------------------------------------+\n");

    /*printf("\n\n\t\t| %-12s %-10s %-16s %-8s %-16s  %-11s %10s %8s |\n",
        "Name", "ID", "Address", "Dept", "Course", "Contact", "Final", "Attend%");

    printf("\t\t+------------------------------------------------------------------------------------+\n");*/

    for (int i = 0; i < n; i++) {
        printStudentRow(arr[i]);
    }

    printf("\n\n\t\tPress any key to continue...");
    _getch();
}








// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
