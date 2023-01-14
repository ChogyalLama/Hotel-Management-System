#include<iostream>
#include<iomanip>
#include<windows.h>
using namespace std;

int yr[]={31,28,31,30,31,30,31,31,30,31,30,31};

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
void mainleap(int &dd,int &mm,int &yyyy)
{
	int leap=0;

	do{
		gotoxy(45,3);
		cout<<"Enter the year:-";
		cin>>yyyy;
	}while(yyyy<1850 || yyyy>2040);
	leap=(yyyy%400==0 || yyyy%100!=0 && yyyy%4==0)?1:0;
	do{
		gotoxy(45,4);
		cout<<"Enter the month:-";
		cin>>mm;
	}while(mm<1 || mm>12);
	if(mm!=2)
		leap=0;
	do{
		gotoxy(45,5);
		cout<<"Enter the day:-";
		cin>>dd;
	}while(dd>yr[mm-1]+leap || dd<1);
	gotoxy(31,3);
	cout<<yyyy<<"-"<<mm<<"-"<<dd<<endl;
}
