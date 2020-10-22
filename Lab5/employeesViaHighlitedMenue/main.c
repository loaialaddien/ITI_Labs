#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Extended -32
#define up 72
#define down 80
#define home 71
#define end 79
#define enter 13
#define esc 27
#define tab 9
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}
void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
typedef struct Emp
{
    int age;
    char name[10];
    int id;
    float salary;
    float commission;
    float deduction;
}Employee;
int main()
{
    int empIndex;
    Employee emp1[10];
    int flag=1;
    char menue[3][10] = {"New","Display by id","Display All","Delete by id","Delete All","Exit"};
    int cursor =0;
    char ch;
    do
    {
        system("cls");
        for(int i=0; i<6; i++)
        {
            if (i==cursor)
            {
                textattr(3);
            }
            else
            {
                textattr(8);
            }
            gotoxy(10,i*3+2);
            _cprintf("%s",menue[i]);
        }
        _flushall();
        ch=getch();
        switch (ch)
        {
        //extended cases
        case Extended:
            ch=getch();
            switch (ch)
            {
            case up:
                cursor--;
                if(cursor<0){
                    cursor=2;
                }
                break;
            case down:
                cursor++;
                if(cursor>2){
                    cursor=0;
                }
                break;
            case home:
                cursor=0;
                break;
            case end:
                cursor=2;
                break;
            }
            break;
        //normal cases
        case enter:
            switch (cursor)
            {
            case 0:
                system("cls");
                printf("please enter your employee id \n");
                _flushall();
                scanf("%i",&empIndex);
                printf("press any key to enter your %i employee data",empIndex);
                getch();
                system("cls");
                //view the fields to get
                gotoxy(10,2);
                printf("id: ");
                gotoxy(50,2);
                printf("name: ");
                gotoxy(10,7);
                printf("age: ");
                gotoxy(50,7);
                printf("salary: ");
                gotoxy(10,12);
                printf("com: ");
                gotoxy(50,12);
                printf("deduct: ");
                //get the data from user
                gotoxy(14,2);
                scanf("%i",&emp1[empIndex].id);
                _flushall();
                gotoxy(57,2);
                scanf("%s",emp1[empIndex].name);
                _flushall();
                gotoxy(14,7);
                scanf("%d",&emp1[empIndex].age);
                _flushall();
                gotoxy(57,7);
                scanf("%f",&emp1[empIndex].salary);
                _flushall();
                gotoxy(14,12);
                scanf("%f",&emp1[empIndex].commission);
                _flushall();
                gotoxy(57,12);
                scanf("%f",&emp1[empIndex].deduction);
                _flushall();
                break;
            case 1:
                system("cls");
                printf("Display Page");
                getch();
                break;
            case 2:
                flag=0;
                break;
            }
            break;
        case esc:
            flag=0;
            break;
        case tab:
            cursor++;
            if(cursor>2){
                cursor=0;
            }
            break;
        }
    } while(flag==1);
    return 0;
}
