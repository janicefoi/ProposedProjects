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
    char studentDept[10];
    char studentCourse[30];
    char studentAddress[100];
    char studentContactNum[15];
    float marksAssignment; 
    float marksSmallExam; 
    float marksFinalExam; 
    float marksTutorial;
    float finalExam;
} Student;

void createAccount();
void displayInfo();
void updateInfo();
void deleteInfo();
void searchInfo();
void exportToText();
void importFromText();
float calculateFinal(Student s);
void displayFinalResult(Student s);

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
        printf("\n\t\t\t0. Exit");

        printf("\n\n\n\t\t\tEnter Your Option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            createAccount();
            break;
        case '2':
            displayInfo();
            break;
        case '3':
            updateInfo();
            break;
        case '4':
            deleteInfo();
            break;
        case '5':
            searchInfo();
            break;
        case '6': 
            exportToText();
            break;
        case '7': 
            importFromText(); 
            break;
        case '0':
            printf("\n\t\t\t====== Thank You ======");
            break;
        default:
            printf("\n\t\t\tInvalid Option, Please Enter Right Option !\n");
        }
    }
    return 0;
}

void createAccount()
{
    FILE* fileOne = fopen("studentInfo.bin", "ab+");

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    Student stundentInformation;

    system("cls");

    printf("\t\t\t====== Create Student Account ======\n");

    printf("\n\t\t\tEnter Student's Name : ");
    getchar();
    gets_s(stundentInformation.studentName);
    printf("\t\t\tEnter Student's ID : ");
    gets_s(stundentInformation.studentId);
    {
        int typeChoice = 0;
        printf("\t\t\tSelect Student Dept:\n\t\t\t1. Local\n\t\t\t2. International\n\t\t\tEnter choice (1-2): ");
        while (1)
        {
            if (scanf("%d", &typeChoice) != 1)
            {
                int c; while ((c = getchar()) != '\n' && c != EOF);
                printf("\n\t\t\tInvalid input. Enter 1 for Local or 2 for International: ");
                continue;
            }
            if (typeChoice == 1)
            {
                strcpy(stundentInformation.studentDept, "Local");
                break;
            }
            else if (typeChoice == 2)
            {
                strcpy(stundentInformation.studentDept, "Int");
                break;
            }
            else
            {
                printf("\n\t\t\tInvalid choice. Enter 1 or 2: ");
            }
        }
        getchar();
    }
    {
        int courseChoice = 0;
        printf("\t\t\tSelect Course:\n\t\t\t1. MSc SE\n\t\t\t2. MSc DSA\n\t\t\t3. MSc CS\n\t\t\t4. MSc AIS\n\t\t\t5. MSc AIMS\n\t\t\tEnter choice (1-5): ");
        while (1)
        {
            if (scanf("%d", &courseChoice) != 1)
            {
                int c; while ((c = getchar()) != '\n' && c != EOF);
                printf("\n\t\t\tInvalid input. Enter a number 1-5: ");
                continue;
            }
            if (courseChoice == 1)
            {
                strcpy(stundentInformation.studentCourse, "MSc SE");
                break;
            }
            else if (courseChoice == 2)
            {
                strcpy(stundentInformation.studentCourse, "MSc DSA");
                break;
            }
            else if (courseChoice == 3)
            {
                strcpy(stundentInformation.studentCourse, "MSc CS");
                break;
            }
            else if (courseChoice == 4)
            {
                strcpy(stundentInformation.studentCourse, "MSc AIS");
                break;
            }
            else if (courseChoice == 5)
            {
                strcpy(stundentInformation.studentCourse, "MSc AIMS");
                break;
            }
            else
            {
                printf("\n\t\t\tInvalid choice. Enter 1-5: ");
            }
        }
        getchar();
    }
    printf("\t\t\tEnter Student's Address : ");
    gets_s(stundentInformation.studentAddress);
    printf("\t\t\tEnter Student's Contact Number : ");
    gets_s(stundentInformation.studentContactNum);

    printf("\t\t\tEnter Assignment Marks : ");
    scanf("%f", &stundentInformation.marksAssignment);
    printf("\t\t\tEnter Small Exam Marks : ");
    scanf("%f", &stundentInformation.marksSmallExam);
    printf("\t\t\tEnter Final Exam Marks : ");
    scanf("%f", &stundentInformation.marksFinalExam);
    printf("\t\t\tEnter Tutorial Marks : ");
    scanf("%f", &stundentInformation.marksTutorial);

    fwrite(&stundentInformation, sizeof(stundentInformation), 1, fileOne);

    printf("\n\n\t\t\tInformations have been stored sucessfully\n");
    printf("\n\n\t\t\tEnter any keys to continue.......");
    _getch();

    fclose(fileOne);
}

float calculateFinal(Student s)
{
	//Calculate final result based on continuous assessment and final exam marks
    
    return (s.marksFinalExam * 0.40f) +
        (s.marksAssignment * 0.20f) +
        (s.marksSmallExam * 0.20f) +
        (s.marksTutorial * 0.20f);
}

void displayFinalResult(Student s)
{
    //float result = calculateFinal(s); 
    printf("\n\t\t\tFinal Result : %.2f\n", calculateFinal(s));
}

void displayInfo()
{
    FILE* fileOne = fopen("studentInfo.bin", "rb");

    if (fileOne == NULL)
    {
        printf("\n\t\t\tError !\n");
    }

    Student stundentInformation;

    system("cls");

    printf("\t\t\t\t====== All Students Information ======\n");

    printf("\n\n\t\t%-20s%-13s%-10s%-25s%-15s\n", "Name", "ID", "Dept", "Address", "Contact", "Final Marks");
    printf("\t\t---------------------------------------------------------------");

    while (fread(&stundentInformation, sizeof(stundentInformation), 1, fileOne) == 1)
    {
        printf("\n\n\t\t%-20s%-13s%-10s%-25s%-15s", stundentInformation.studentName, stundentInformation.studentId, stundentInformation.studentDept, stundentInformation.studentAddress, stundentInformation.studentContactNum);
    }

    printf("\n\n\t\tEnter any keys to continue.......");
    _getch();

    fclose(fileOne);
}

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
                    strcpy(tempInformation.studentDept, "International");
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
                printf("\n\t\t\tEnter Student Assignment Mark to Update: ");
                scanf("%f", &tempInformation.marksAssignment);
                studentInformation.marksAssignment = tempInformation.marksAssignment;

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

                displayFinalResult(studentInformation);

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
                strcpy(studentDept, "International");
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
