#include <stdio.h>

#include <time.h>

#include <string.h>

#include <stdlib.h>

#include <conio.h>

//---------------------------------------------------------------------------------------------------------

#define MAX_YR  9999

#define MIN_YR  1900

#define MAX_SIZE_USER_NAME 30

#define MAX_SIZE_PASSWORD  20

//---------------------------------------------------------------------------------------------------------

#define FILE_NAME  "l.bin"

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
// Macro related to the books info
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

#define MAX_BOOK_NAME   50

#define MAX_AUTHOR_NAME 50

#define MAX_STUDENT_NAME 50

#define MAX_STUDENT_ADDRESS 300

#define FILE_HEADER_SIZE  sizeof(sFileHeader)

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//structure to store date
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

//---------------------------------------------------------------------------------------------------------

typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;


//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
// to call in program
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


typedef struct
{
    // declare the integer data type
    unsigned int books_id;
    // declare the character data type
    char bookName[MAX_BOOK_NAME];
    // declare the character data type
    char authorName[MAX_AUTHOR_NAME];
    // declare the charecter data type
    char studentName[MAX_STUDENT_NAME];
    // declare the character data type
    char studentAddr[MAX_STUDENT_ADDRESS];
    // declare the integer data type
    Date bookIssueDate;
} s_BooksInfo;



//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//print the group members name
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    //printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
    printf("\nDate:\t\t\t\t\t\t\t\t\tTime:\t%s\t\t\t\t\t\t\t\t%s",__DATE__,__TIME__);
    printf("\n\t\t       1. HIMANSHU DIXIT - B10 - B64178");
    printf("\n\n\t\t       2. ASHUTOSH PRADHAN - B10 - B61308");
    printf("\n\n\t\t       3. ARYAMAN VISHNOI - B10 - B63816");
    printf("\n\n\t\t       4. ARYAN RAZDAN - B10 - BJ61567\n");

}


//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//print the head message always show in above
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

void headMessage(const char *message)
{
    system("cls");
    printf("\n###########################################################################");
    printf("\n############                                                   ############");
    printf("\n############      LIBRARY MANAGEMENT SYSTEM PROJECT IN C       ############");
    printf("\n############                                                   ############");
    printf("\n###########################################################################");
    printf("\n---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n----------------------------------------------------------------------------\n\n");
}



//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//loading page after loading press key to start
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


void loadingpage()
{
    printf("\t\t\tPLEASE WAIT\n");
    printf("\t\t\tSYSTEM IS LOADING\n");
    printf("\n\npress any key to start now : ");
    getch();
}




//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//function to print the welcome message
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

void welcomeMessage()
{
    headMessage("CREATED BY :-");
    loadingpage();
    printf("\n\n\n\n\n");
    printf("\n\t    **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t          =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t          =                 WELCOME                   =");
    printf("\n\t          =                   TO                      =");
    printf("\n\t          =                 LIBRARY                   =");
    printf("\n\t          =                MANAGEMENT                 =");
    printf("\n\t          =                 SYSTEM                    =");
    printf("\n\t          =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\n\t    **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n Enter any key to continue.....");
    getch();
}



//---------------------------------------------------------------------------------------------------------
//function to check name is valid has alphabet or not
//---------------------------------------------------------------------------------------------------------

int check(char a)
{
    if(a>='a' && a<='z' || a>='A' && a<='Z')
        return 1;
    else
        return 0;
}



//---------------------------------------------------------------------------------------------------------
//function to check name
//---------------------------------------------------------------------------------------------------------

int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        int l = check(name[index]);
        if((l == 0) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}



//---------------------------------------------------------------------------------------------------------
// Function to check leap year.
//Function returns 1 if leap year
//---------------------------------------------------------------------------------------------------------


int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}




//---------------------------------------------------------------------------------------------------------
// returns 1 if given date is valid.
//---------------------------------------------------------------------------------------------------------


int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}



//---------------------------------------------------------------------------------------------------------
// Add books in list
//---------------------------------------------------------------------------------------------------------


void addBookInDataBase()
{
    int days;
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW BOOKS");
    printf("\n\n\tENTER YOUR DETAILS BELOW:");
    printf("\n---------------------------------------------------------------------------\n");
    printf("\n\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u",&addBookInfoInDataBase.books_id);
    do
    {
        printf("\n\tBook Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.bookName,MAX_BOOK_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.bookName);
        if (!status)
        {
            printf("\n\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\tAuthor Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.authorName,MAX_AUTHOR_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.authorName);
        if (!status)
        {
            printf("\n\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addBookInfoInDataBase.bookIssueDate.dd,&addBookInfoInDataBase.bookIssueDate.mm,&addBookInfoInDataBase.bookIssueDate.yyyy);
        //check date validity
        status = isValidDate(&addBookInfoInDataBase.bookIssueDate);
        if (!status)
        {
            printf("\n\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    printf("\n\tBook added successfully....\n");
    getch();
    fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
}

//---------------------------------------------------------------------------------------------------------

void sBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH BOOKS");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\tEnter Book Name to search:");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(addBookInfoInDataBase.bookName, bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\tBook id = %u\n",addBookInfoInDataBase.books_id);
        printf("\tBook name = %s",addBookInfoInDataBase.bookName);
        printf("\tBook authorName = %s",addBookInfoInDataBase.authorName);
        printf("\tBook issue date(day/month/year) =  (%d/%d/%d)",addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);
    }
    else
    {
        printf("\n\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\tPress any key to go to main menu.....");
    getchar();
}



//---------------------------------------------------------------------------------------------------------
//book issue
//---------------------------------------------------------------------------------------------------------


void bookissue()
{
    int found = 0;
    int bookIssue = 0;
    sFileHeader fileHeaderInfo = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Book Issue");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\tEnter Book ID NO. for Issue:");
    scanf("%d",&bookIssue);
    do
    {
        printf("\n\tStudent Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.studentName,MAX_STUDENT_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(addBookInfoInDataBase.books_id != bookIssue)
        {
            fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }

    (found)? printf("\n\tBook Issued successfully....."):printf("\n\tBook not found");
    getch();
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}



//---------------------------------------------------------------------------------------------------------
// book deposit
//---------------------------------------------------------------------------------------------------------


void bookdeposit()
{
    int days;
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("BOOKS DEPOSIT");
    printf("\n\n\tENTER YOUR DETAILS BELOW:");
    printf("\n---------------------------------------------------------------------------\n");
    printf("\n\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u",&addBookInfoInDataBase.books_id);
    do
    {
        printf("\n\tBook Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.bookName,MAX_BOOK_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.bookName);
        if (!status)
        {
            printf("\n\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\tAuthor Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.authorName,MAX_AUTHOR_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.authorName);
        if (!status)
        {
            printf("\n\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\tStudent Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.studentName,MAX_STUDENT_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addBookInfoInDataBase.bookIssueDate.dd,&addBookInfoInDataBase.bookIssueDate.mm,&addBookInfoInDataBase.bookIssueDate.yyyy);
        //check date validity
        status = isValidDate(&addBookInfoInDataBase.bookIssueDate);
        if (!status)
        {
            printf("\n\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    printf("\n\tSUCCESSFULLY DEPOSIT ");
    getch();
    fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
}



//---------------------------------------------------------------------------------------------------------
// search books
//---------------------------------------------------------------------------------------------------------


void searchBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH BOOKS");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\tEnter Book Name to search:");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(addBookInfoInDataBase.bookName, bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\tBook id = %u\n",addBookInfoInDataBase.books_id);
        printf("\tBook name = %s",addBookInfoInDataBase.bookName);
        printf("\tBook authorName = %s",addBookInfoInDataBase.authorName);
        printf("\tBook issue date(day/month/year) =  (%d/%d/%d)",addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);
    }
    else
    {
        printf("\n\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\tPress any key to go to main menu.....");
    getchar();
}




//---------------------------------------------------------------------------------------------------------
// view books function
//---------------------------------------------------------------------------------------------------------


void viewBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase ;
    FILE *fp = NULL;
    int status = 0;
    unsigned int countBook = 1;
    headMessage("VIEW BOOKS DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        printf("\n\tBook Count = %d\n\n",countBook);
        printf("\tBook id = %u",addBookInfoInDataBase.books_id);
        printf("\n\tBook name = %s",addBookInfoInDataBase.bookName);
        printf("\n\tBook authorName = %s",addBookInfoInDataBase.authorName);
        printf("\n\tBook issue date(day/month/year) =  (%d/%d/%d)\n\n",addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);
        found = 1;
        ++countBook;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\tNo Record");
    }
    printf("\n\n\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}




//---------------------------------------------------------------------------------------------------------
// delete function
//---------------------------------------------------------------------------------------------------------


void deleteBooks()
{
    int found = 0;
    int bookDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Delete Books Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\tEnter Book ID NO. for delete:");
    scanf("%d",&bookDelete);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(addBookInfoInDataBase.books_id != bookDelete)
        {
            fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\tRecord deleted successfully....."):printf("\n\tRecord not found");
    getch();
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}


//---------------------------------------------------------------------------------------------------------
//function to update password
//---------------------------------------------------------------------------------------------------------


void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again from starting ");
    fflush(stdin);
    getchar();
    exit(1);
}




//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//administrator menu function of the program
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------



void administratormenu()
{
    int choice = 0;
    do
    {
        headMessage("ADMINISTRATOR MENU");
        printf("\n\n\n\t\t\t1.Add Books");
        printf("\n\t\t\t2.Search Books");
        printf("\n\t\t\t3.View Books");
        printf("\n\t\t\t4.Delete Book");
        printf("\n\t\t\t5.Book Issue");
        printf("\n\t\t\t6.Book Deposit");
        printf("\n\t\t\t7.Update Password");
        printf("\n\t\t\t8.Back");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addBookInDataBase();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            viewBooks();
            break;
        case 4:
            deleteBooks();
            break;
        case 5:
            bookissue();
            break;
        case 6:
            bookdeposit();
            break;
        case 7:
            updateCredential();
            break;
        case 8:
            menu();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }
         //Switch Ended
    }
    while(choice!=0);
    //Loop Ended
}


//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//menu function of the program
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------



void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Book Issue");
        printf("\n\t\t\t2.Book Deposit");
        printf("\n\t\t\t3.Administrator Menu");
        printf("\n\t\t\t4.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            bookissue();
            break;
        case 2:
            bookdeposit();
            break;
        case 3:
            administratormenu();
            break;
        case 4:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }
         //Switch Ended
    }
    while(choice!=0);
    //Loop Ended
}



//---------------------------------------------------------------------------------------------------------
//login password
//---------------------------------------------------------------------------------------------------------


void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        int ch=0;
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\n\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            printf("\n\t\t\t\t1. For Try again\n\n");
            printf("\n\t\t\t\t2. Forgot Username and Password\n\n");
            printf("\t\t\t  Enter your choice => ");
            scanf("%d",&ch);
            fflush(stdin);
            if(ch==2)
            {
                updateCredential();
            }
            fflush(stdin);
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}


//---------------------------------------------------------------------------------------------------------
//function to check file exist or not
//---------------------------------------------------------------------------------------------------------


int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}


//---------------------------------------------------------------------------------------------------------
//to change password
//---------------------------------------------------------------------------------------------------------


void defpassword()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="library\n";
    const char defaultPassword[] ="library\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"w");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}


//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//---------------------------------------START OF THE PROGRAM----------------------------------------------
//---------------------------------------------------------------------------------------------------------


int main()
{
    defpassword();
    welcomeMessage();
    login();
    return 0;
}


//---------------------------------------------------------------------------------------------------------
//---------------------------------------END OF THE PROGRAM------------------------------------------------
//---------------------------------------------------------------------------------------------------------



