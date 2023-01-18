#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;

class service
{
	public:
		int service_id;
		double price;
		char service[20];
		void showall(int);
};
void service::showall(int i)
{
	cout<<"\t| "<<setw(5)<<i
		<<"   |"<<setw(8)<<service_id
		<<"     |"<<setw(21)<<service
		<<" |"<<setw(6)<<price
		<<"   |"<<endl;
	cout<<"\t+---------+-------------+----------------------+---------+"<<endl;
}
int gen_sid()
{
	ifstream fin("C:\\Hotel_management\\fac.txt", ios::in | ios::binary);
	if(!fin){
		cout<<"\tFile error "<<endl;
		return 0;
	}
	service s;
	int x=0,id=0;
	while(fin.read((char*)&s,sizeof(s))){
		if(id<s.service_id)
			id=s.service_id;
		x++;
	}
	if(x==0)
		id=100;
	else
		id=id+1;
	fin.close();
	return id;
}
void update_service()
{
	char ch;
	service s;
	do{
		ofstream fout("C:\\Hotel_management\\fac.txt", ios::app | ios::binary);
		if(!fout){
			cout<<"Error"<<endl;
			return;
		}
		cout<<"Enter the service name : ";
		cin.clear();
		cin.sync();
		cin.get(s.service,25);

		cout<<"Enter the rate : ";
		cin>>s.price;

		s.service_id=gen_sid();
		cout<<"Service id is:- "<<s.service_id;

		fout.write((char*)&s,sizeof(s));
		fout.close();

		cout<<"\nDo you want to enter more (Y/N) : ";
		cin>>ch;
		cout<<endl;
	}while(ch=='y' || ch=='Y');
}
void display_service()
{
	ifstream fin("C:\\Hotel_management\\fac.txt", ios::in | ios::binary);
	if(!fin){
		cout<<"Error"<<endl;
		return;
	}
	service s;
	int n=1;
	system("cls");
	cout<<"\n\t+---------+-------------+----------------------+---------+"<<endl;
	cout<<"\t|  Sl no. |  Service Id |        Service       |   Rate  |"<<endl;
	cout<<"\t+---------+-------------+----------------------+---------+"<<endl;
	while(fin.read((char*)&s,sizeof(s))){
		s.showall(n);
		n++;
	}
	cin.get();
	cin.get();
	fin.close();
}
void delete_service()
{
	ifstream fin("C:\\Hotel_management\\fac.txt", ios::in | ios::binary);
	ofstream fout("C:\\Hotel_management\\temp.txt", ios::app | ios::binary);
	if(!fin || !fout){
		cout<<"File not found or inacessible"<<endl;
		return;
	}
	service s;
	int n;
	cout<<"Enter the service id to delete : ";
	cin>>n;
	while(fin.read((char*)&s,sizeof(s))){
		if(s.service_id!=n){
			fout.write((char*)&s,sizeof(s));
		}
	}
	cout<<"Record successfully deleted "<<endl;
	cin.get();
	cin.get();
	fin.close();
	fout.close();
	remove("C:\\Hotel_management\\fac.txt");
	rename("C:\\Hotel_management\\temp.txt","C:\\Hotel_management\\fac.txt");

}
void mainfacility()
{
	int ch;
	do{
		system("cls");
		cout<<"+-----------------------------------+"<<endl;
		cout<<"|Enter 1 to enter new services.     |"<<endl;
		cout<<"|Enter 2 to show available services.|"<<endl;
		cout<<"|Enter 3 to delete services.        |"<<endl;
		cout<<"+-----------------------------------+"<<endl;
		cout<<"\nEnter your choice : ";
		cin>>ch;

		switch(ch){
			case 1:	update_service();
						break;
			case 2:	display_service();
						break;
			case 3:	delete_service();
						break;
		}
	}while(ch>0 && ch<4);
}

