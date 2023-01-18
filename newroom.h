#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
//#include"bill.h"
using namespace std;

class room
{
	public:
		int room_id;
		double price;
		char roomtype[20];
		void showall(int);
};
void room::showall(int i)
{
	cout<<"\t| "<<setw(5)<<i<<"   |"<<setw(8)<<room_id<<"   |"<<setw(21)<<roomtype<<" |"<<setw(6)<<price<<"   |"<<endl;
	cout<<"\t+---------+-----------+----------------------+---------+"<<endl;
}
int genrid()
{
	fstream f("C:\\Hotel_management\\room.txt", ios::in | ios::binary | ios::out);
	if(!f){
		cout<<"\tFile error "<<endl;
		return 0;
	}
	room s;
	int x=0,id=0;
	while(f.read((char*)&s,sizeof(s))){
		if(id<s.room_id)
			id=s.room_id;
		x++;
	}
	if(x==0)
		id=100;
	else
		id=id+1;
	f.write((char*)&s,sizeof(s));
	f.close();
	return id;
}
void update_room()
{
	char ch;
	room s;
	do{
		ofstream fout("C:\\Hotel_management\\room.txt", ios::app | ios::binary);
		if(!fout){
			cout<<"Error"<<endl;
			return;
		}
		cout<<"Enter the room type : ";
		cin.clear();
		cin.sync();
		cin.getline(s.roomtype,25);
		cout<<"Enter the room rate : ";
		cin>>s.price;
		s.room_id=genrid();
		cout<<"Room id is:- "<<s.room_id;

		fout.write((char*)&s,sizeof(s));
		fout.close();

		cout<<"\nDo you want to enter more (Y/N) : ";
		cin>>ch;
		cout<<endl;
	}while(ch=='y' || ch=='Y');
}
void display_room()
{
	ifstream fin("C:\\Hotel_management\\room.txt", ios::in | ios::binary);
	if(!fin){
		cout<<"Error"<<endl;
		return;
	}
	room s;
	int n=1;
	system("cls");
	cout<<"\n\t+---------+-----------+----------------------+---------+"<<endl;
	cout<<"\t|  Sl no. |  Room Id  |      Room Type       |  Price  |"<<endl;
	cout<<"\t+---------+-----------+----------------------+---------+"<<endl;
	while(fin.read((char*)&s,sizeof(s))){
		s.showall(n);
		n++;
	}
	cin.get();
    cin.get();
	fin.close();
}
void del_room()
{
	ifstream fin("C:\\Hotel_management\\room.txt", ios::in | ios::binary);
	ofstream fout("C:\\Hotel_management\\temp.txt", ios::app | ios::binary);
	if(!fin || !fout){
		cout<<"File not found or inacessible"<<endl;
		return;
	}
	room s;
	int n;
	cout<<"Enter the room id to delete : ";
	cin>>n;
	while(fin.read((char*)&s,sizeof(s))){
		if(s.room_id!=n){
			fout.write((char*)&s,sizeof(s));
		}
	}
	cout<<"Record successfully deleted "<<endl;
	cin.get();

	fin.close();
	fout.close();
	remove("C:\\Hotel_management\\room.txt");
	rename("C:\\Hotel_management\\temp.txt","C:\\Hotel_management\\room.txt");
}
/*
void room_bill()
{
    room r;
    char ch;
    int room_id, i=0, qty;
    int bn=bill_details(); // generate bill number
    do{
        int x=0;
        gotoxy(45,2);
		cout<<"                               ";
		gotoxy(45,2);
        cout<<"Enter room id : ";
        cin>>room_id;

        ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\room.txt", ios::in | ios::binary);
        while(fin.read((char*)&r,sizeof(r))){
            if(r.room_id==room_id){
                gotoxy(45,2);
                cout<<"                                ";
                gotoxy(45,2);
                cout<<"Enter number of days stayed : ";
                cin>>qty;

                bill_items(bn, r.price, r.roomtype, qty, i);
                i++;
                x=1;
            }
        }
        if(x==0){
            gotoxy(45,2);
			cout<<"                           ";
			gotoxy(45,2);
            cout<<"Invalid Room Id.";
            ch='y';
            cin.get();
            cin.get();
        }
        else{
            gotoxy(45,2);
            cout<<"                                  ";
            gotoxy(45,2);
            cout<<"More room ? Y/N ";
            cin>>ch;
        }
    }while((ch=='Y' || ch=='y') && i<7);
}
*/

void mainroom()
{
	int ch;
	do{
		system("cls");
		cout<<"+----------------------------------+"<<endl;
		cout<<"|Enter 1 to enter new room type.   |"<<endl;
		cout<<"|Enter 2 to show the price of room.|"<<endl;
		cout<<"|Enter 3 to delete roomtype.       |"<<endl;
		cout<<"+----------------------------------+"<<endl;
		cout<<"\nEnter your choice : ";
		cin>>ch;

		switch(ch)
		{
			case 1:	update_room();
						break;
			case 2:	display_room();
						break;
			case 3:	del_room();
						break;
           // case 4: room_bill();
             //           break;
		}
	}while(ch>0 && ch<4);
}

