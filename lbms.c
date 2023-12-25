// PROJECT
//LIBRARY MANAGEMENT SYSTEM 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lbms_structures.c"

// function for Admin.
void Add_Book()
{
    FILE *fptr;
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(books.Date, mydate);

    fptr = fopen("books.txt", "ab");

    printf("Enter book Id :-");
    scanf("%d", &books.Id);

    printf("Enter book name :-");
    fflush(stdin); // here we have used fflush stdin because fgets will read "enter" as input also
                   // whch will not read "Enter" as bookname input and will directly shift to authorname.
    gets(books.BookName);

    printf("Enter book author name :-");
    fflush(stdin);
    gets(books.AuthorName);

    printf("Your book is added successfully");

    fwrite(&books, sizeof(books), 1, fptr);
    fclose(fptr);
}

void Remove_Book()
{
    system("cls");
    int id, f = 0;
    printf("====RETURN BOOK========\n\n");
    printf("Enter Book Id of returning book : ");
    scanf("%d", &id);

    FILE *ptr1;
    FILE *ptr2;

    ptr1 = fopen("books.txt", "rb");
    ptr2 = fopen("temp.txt", "wb");

    while (fread(&books, sizeof(books), 1, ptr1) == 1)
    {
        if (id == books.Id)
        {
            f = 1;
        }
        else
        {
            fwrite(&books, sizeof(books), 1, ptr2);
        }
    }
    if (f == 1)
    {
        printf("\n\nBooks returned successfully");
    }
    else
    {
        printf("\n\nRecord not found");
    }
    fclose(ptr1);
    fclose(ptr2);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void Book_display_Admin()
{
    FILE *ptr;
    system("cls");
    printf("\n========AVAILABLE BOOKS========\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book Id", "Book Name", "Author Name", "Date");

    ptr = fopen("books.txt", "rb");

    while (fread(&books, sizeof(books), 1, ptr) == 1)
    {
        printf("%-10d %-30s %-20s %s\n\n", books.Id, books.BookName, books.AuthorName, books.Date);
    }
    fclose(ptr);
}

void Search_book_Admin()
{
    system("cls");
    int id, f = 0;
    FILE *ptr;

    printf("======SEARCH FOR A BOOK=======\n\n");
    printf("Enter the Book Id:\n");
    scanf("%d", &id);

    ptr = fopen("books.txt", "rb");

    while (fread(&books, sizeof(books), 1, ptr) == 1)
    {
        if (id == books.Id)
        {
            f = 1;
            break;
        }
    }
    fclose(ptr);

    if (f == 1)
    {

        printf("Book is present.\n");
    }
    else
    {
        printf("Book is not present.\n");
    }
}

// User functions

void Issue_Book()
{
    system("cls");
    printf("====== ISSUE BOOKS =======\n\n");
    
    FILE *fptr1;
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(student.Date, mydate);

    int f = 0;

 
    printf("Enter book Id to issue :\n");
    scanf("%d", &student.Id);

    fptr1 = fopen("books.txt", "rb");

    while (fread(&books, sizeof(books), 1, fptr1) == 1)
    {
        if (books.Id == student.Id)
        {
            f = 1;
            strcpy(student.BookName, books.BookName);
            strcpy(student.AuthorName, books.AuthorName);
            break;
        }
    }

    if(f==0){
        printf("No Book Found !!!\n\n");
        return;
    }

    
       
        fptr1 = fopen("Issue.txt", "ab");

        printf("Enter Student Name :\n");
        fflush(stdin);
        gets(student.StudentName);

        printf("Enter Student Roll no.\n");
        fflush(stdin);
        scanf("%d", &student.SRoll);

        printf("Book Issued Successfully!!!!");

        fwrite(&student, sizeof(student), 1, fptr1);
        fclose(fptr1);
    }
    
void Return_Book()
{
     FILE *fptr1;
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    
    int date_exceed=mydate-student.Date;
     if(date_exceed>15){
        int fine=date_exceed*10;
        student.fine=fine;
     }
     else{
        student.fine=0;
     }

    system("cls");
    int id, f = 0;
    printf("\n===========RETURNING BOOK=========\n\n");
    printf("Enter Book Id of returning book : ");
    scanf("%d", &id);

    FILE *ptr1;
    FILE *ptr2;

    ptr1 = fopen("Issue.txt", "rb");
    ptr2 = fopen("temp1.txt", "wb");

    while (fread(&student, sizeof(student), 1, ptr1) == 1)
    {
        if (id == student.Id)
        {
            f = 1;
        }
        else
        {
            fwrite(&student, sizeof(student), 1, ptr2);
        }
    }
    
    if (f == 1)
    {
        printf("\n\nBook returned successfully");
    }
    else
    {
        printf("\n\nRecord not found");
    }
    
    fclose(ptr1);
    fclose(ptr2);

    remove("Issue.txt");
    rename("temp1.txt", "Issue.txt");
}


void Book_display_User()
{
    FILE *ptr;
    system("cls");
    printf("\n========ISSUED BOOKS========\n\n");
    printf("%-10s %-30s %-20s %-20s %s\n\n", "Student Id", "Student Name", "Student Roll", "Book Name","Fine");

    ptr = fopen("Issue.txt", "rb");

    while (fread(&student, sizeof(student), 1, ptr) == 1)
    {
        printf("%-20d %-30s %-20d %-20s %d\n\n", student.Id, student.StudentName, student.SRoll, student.BookName,student.fine);
    }
    fclose(ptr);
}


void search_book_User()
{
    system("cls");
    int id, f = 0;
    FILE *ptr;

    printf("======SEARCH FOR A BOOK=======\n\n");
    printf("Enter the Book Id:\n");
    scanf("%d", &id);

    ptr = fopen("Issue.txt", "rb");

    while (fread(&books, sizeof(books), 1, ptr) == 1)
    {
        if (id == books.Id)
        {
            f = 1;
            break;
        }
    }
    fclose(ptr);

    if (f == 1)
    {

        printf("Book is present.\n");
    }
    else
    {
        printf("Book is not present.\n");
    }
}

int main()
{

    printf("=========LIBRARY MANAGEMENT SYSTEM===========\n");

    int check;
    printf("Choose your designation:- \n\n");
    printf("1: Admin\n");
    printf("2: User\n");
    scanf("%d", &check);

    if (check == 1)
    {
        int admin;
        while (1)
        {
            printf("1:- Add Books\n");
            printf("2:- Remove Books\n");
            printf("3:- Display book list\n");
            printf("4:- Search for any book\n");
            printf("5:- Exit\n");
            printf("Enter your choice :-\n");
            scanf("%d", &admin);

            switch (admin)
            {

            case 1:
                Add_Book();
                break;
            case 2:
                Remove_Book();
                break;

            case 3:
                Book_display_Admin();
                break;

            case 4:

                Search_book_Admin();
                break;

            case 5:

                exit(0);
                break;

            default:
                printf("Invalid Choice.....\n\n");
                break;
            }
            printf("Print any key to continue ....\t");
        }
    }

    else if (check == 2)
    {
        int user;
        while (1)
        {
            printf("1:- Issue Book\n");
            printf("2:- Return Book\n");
            printf("3:- Display Issued Book List\n");
            printf("4:- Search for any book\n");
            printf("5:- Exit\n");
            printf("Enter your choice :-\n");
            scanf("%d", &user);

            switch (user)
            {

            case 1:
                Issue_Book();
                break;
            case 2:
                Return_Book();
                break;

            case 3:
                Book_display_User();
                break;

            case 4:

                search_book_User();
                break;

            case 5:

                exit(0);
                break;

            default:
                printf("Invalid Choice.....\n\n");
                break;
            }
            printf("Print any key to continue ....\t");
        }
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}