#include<iostream>
#include "bill.h"

using namespace std;
int main()
{
	int ch;
	cout<<"\n\t\t * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ";
	cout<<"\n\t\t * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                             WELCOME !!                                * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                   HOTEL MANAGEMENT SYSTEM PRESENTS                    * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                    press any key to continue!!!......                 * * ";
	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * *                                                                       * * ";
   	cout<<"\n\t\t * *                                                                       * * ";
	cout<<"\n\t\t * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ";
	cout<<"\n\t\t * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ";

	//cin.get();
    //cin.get();
	while(1)
	{
		do
		{
        system("cls");
			cout<<"\n\n\n\n\t\t\tEnter 1 to checkin."<<endl;
			cout<<"\t\t\tEnter 2 for room."<<endl;
			cout<<"\t\t\tEnter 3 for food."<<endl;
			cout<<"\t\t\tEnter 4 for facility."<<endl;
			cout<<"\t\t\tEnter 5 for bill."<<endl;
			cout<<"\n\t\t\tEnter your choice : ";
			cin>>ch;
		}while(ch<1 || ch>5);
		switch(ch)
		{
			case 1: maincheckin();
						break;
			case 2: mainroom();
						break;
			case 3: mainfood();
						break;
			case 4: mainfacility();
						break;
			case 5: mainbill();
						break;
		}
	}
	return 0;
}
