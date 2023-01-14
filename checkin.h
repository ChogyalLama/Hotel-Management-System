#include<fstream>
#include<stdio.h>
#include<iomanip>
#include<string.h>
using namespace std;
class checkin
{
	public:
		char adharno[13],pnumber[11];
		int checkinid;
		char hname[20],add[30];                // hnmae= head guest name, add= address
		char additional;
		char Name[20][20];             				// name=additional guest name (max 20 letters and max 20 add guests)
		int ng;										 	   //number of guest
		void showpar();
		void showid(int);
};
void checkin::showpar()
{
	cout<<"Your Aadhaar no : "<<adharno<<endl;
	cout<<"Your checkin Id : "<<checkinid<<endl;
	cout<<"Your phone no : "<<pnumber<<endl;
	cout<<"The name of the head guest : "<<hname<<endl;
	if(ng!=0){
		for(int i=1;i<=ng;i++){
			cout<<"The name of guest "<<i<<" : "<<Name[i-1]<<endl;
		}
	}
	cout<<"Your resedential address is:- "<<add<<endl;
}
void checkin::showid(int i)
{
	cout<<"| "<<setw(4)<<i
		<<" |"<<setw(13)<<adharno
		<<" |"<<setw(7)<<checkinid
		<<"   |"<<setw(13)<<pnumber
		<<" |"<<setw(20)<<hname
		<<" |"<<setw(5)<<ng
		<<" |"<<endl;
	cout<<"+------+--------------+----------+--------------+---------------------+------+"<<endl;
}

int getcheckinid()
{
	fstream f("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\checkin.txt", ios::in | ios::binary | ios::out);
	if(!f){
		cout<<"\tFile error "<<endl;
		return 0;
	}
	checkin s;
	int x=0,id=0;
	while(f.read((char*)&s,sizeof(s))){
		if(id<s.checkinid)
			id=s.checkinid;
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
void read()
{
	ofstream fout("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\checkin.txt", ios::app | ios::binary);
    ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\checkin.txt", ios::in | ios::binary);
	if(!fout || !fin){
		cout<<"File error."<<endl;
		return;
	}
	char adno[13];
	int i=0;

	do{
        system("cls");
        cout<<"Enter your Aadhaar number:-";
        cin.clear();
        cin.sync();
        cin.getline(adno,13);
	}while(strlen(adno)!=12);

	checkin s;
	while(fin.read((char*)&s,sizeof(s))){
		if(strcmp(s.adharno,adno)==0){
			cout<<"The checkin from the the above Aadhaar number already exists!"<<endl;
			s.showpar();
			i++;
			cin.get();
		}
	}

	if(i==0){
		strcpy(s.adharno,adno);
        cin.clear();
        cin.sync();
		cout<<"Enter the name of head guest:-";
		cin.getline(s.hname,20);
		cout<<"Any additional guest(Y/N):- ";
		cin>>s.additional;
		if(s.additional=='Y' || s.additional=='y'){
			cout<<"Enter the total number of guests [MAX=20]:-";
			cin>>s.ng;
			for(int i=1;i<=s.ng;i++){
				cout<<"Enter the name of guest "<<i<<":-";
				cin.clear();
                cin.sync();
				cin.getline(s.Name[i-1],20);
			}
		}
		else{
			s.ng=0;
		}
		cout<<"Enter your resedential address:- ";
		cin.clear();
        cin.sync();
		cin.getline(s.add,70);
		cout<<"Enter your phone number:-";
		cin>>s.pnumber;
		s.checkinid=getcheckinid();
		cout<<"Your checkin Id is : "<<s.checkinid<<endl;
		fout.write((char*)&s,sizeof(s));
        cin.get();
        cin.get();
    }

	fout.close();
	fin.close();
}
void show()
{
	ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\checkin.txt", ios::in | ios::binary);
	if(!fin){
		cout<<"File error !"<<endl;
		return;
	}
	system("cls");

	int n=1;
	checkin s;
	cout<<"+------+--------------+----------+--------------+---------------------+------+"<<endl;
	cout<<"|Si no |Aadhaar number| check_id | Phone number |  Name of head guest |  nog |"<<endl;
	cout<<"+------+--------------+----------+--------------+---------------------+------+"<<endl;
	while(fin.read((char*)&s,sizeof(s))){
			s.showid(n);
			n++;
	}
	cin.get();
    cin.get();
	fin.close();
}
void maincheckin()
{
	int ch;
	do{
        system("cls");
        cout<<"\n\n\n\tEnter 1 for new checkin";
        cout<<"\n\tEnter 2 to show list of all the checkin(s)";
        cout<<"\n\n\tEnter your choice:-";
        cin>>ch;
        switch(ch){
			case 1:read();
					break;
			case 2:show();
					break;
		}
	}while(ch==1 || ch==2);
}

