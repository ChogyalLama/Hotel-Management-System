#include<fstream>
#include<string.h>
#include<iomanip>

using namespace std;

class menu
{
	public:
		int food_id;
		double price;
		char food[20],food_category[15];
		void showall(int);
};
void menu::showall(int i)
{
	cout<<"\t| "<<setw(5)<<i
		<<"   |"<<setw(8)<<food_id
		<<"   |"<<setw(29)<<food_category
		<<"   |"<<setw(29)<<food
		<<" |"<<setw(6)<<price
		<<"   |"<<endl;
	cout<<"\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
}
int genfid()
{
	fstream f("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt", ios::in | ios::binary | ios::out);
	if(!f){
		cout<<"\tFile error "<<endl;
		return 0;
	}
	menu s;
	int x=0,id=0;
	while(f.read((char*)&s,sizeof(s)))
	{
		if(id<s.food_id)
			id=s.food_id;
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
void update()
{
	char ch;
	menu s;
	do{
		ofstream fout("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt", ios::app | ios::binary);
		if(!fout)
		{
			cout<<"Error"<<endl;
			return;
		}
		cout<<"Enter the new food name : ";
		cin.clear();
		cin.sync();
		cin.getline(s.food,25);

		cout<<"Enter food category : ";
		cin.getline(s.food_category,25);

		cout<<"Enter the price : ";
		cin>>s.price;

		s.food_id=genfid();
		cout<<"Food id is:- "<<s.food_id;

		fout.write((char*)&s,sizeof(s));
		fout.close();

		cout<<"\nDo you want to enter more (Y/N) : ";
		cin>>ch;
		cout<<endl;
	}while(ch=='y' || ch=='Y');
}
void display()
{
	ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt", ios::in | ios::binary);
	if(!fin){
		cout<<"Error"<<endl;
		return;
	}
	menu s;
	int n=1;
	system("cls");
	cout<<"\n\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
	cout<<"\t|  Sl no. |  Food Id  |           Category             |          Food Name           |  Price  |"<<endl;
	cout<<"\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
	while(fin.read((char*)&s,sizeof(s))){
		s.showall(n);
		n++;
	}
	cin.get();
    cin.get();
	fin.close();
}
void del()
{
	ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt", ios::in | ios::binary);
	ofstream fout("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\temp.txt", ios::app | ios::binary);
	if(!fin || !fout){
		cout<<"File not found or inacessible"<<endl;
		return;
	}
	menu s;
	int n;
	cout<<"Enter the food id to delete : ";
	cin>>n;
	while(fin.read((char*)&s,sizeof(s))) {
		if(s.food_id!=n){
			fout.write((char*)&s,sizeof(s));
		}
	}
	cout<<"Record successfully deleted "<<endl;
	cin.get();
    cin.get();
	fin.close();
	fout.close();
	remove("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt");
	rename("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\temp.txt","C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt");

}
void search_food()
{
	ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt", ios::in | ios::binary);
    if(!fin){
		cout<<"Error"<<endl;
		return;
	}
	menu s;
    int ch;
	cout<<"\n+------------------------------------+"<<endl;
	cout<<"|Enter 1 to search by food id.       |"<<endl;
	cout<<"|Enter 2 to search by food category. |"<<endl;
	cout<<"+------------------------------------+"<<endl;
	cout<<"\nEnter your choice : ";
	cin>>ch;

    int n=1;
	if(ch==1){
        system("cls");
        int id;
        cout<<"Enter food id : ";
        cin>>id;

        cout<<"\n\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
        cout<<"\t|  Sl no. |  Food Id  |           Category             |          Food Name           |  Price  |"<<endl;
        cout<<"\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
        while(fin.read((char*)&s,sizeof(s))){
            if(s.food_id==id){
                s.showall(n);
                n++;
            }
        }
	}
	else if(ch==2){
        system("cls");
        char category[25];
        cout<<"Enter food category : ";
        cin.clear();
        cin.sync();
        cin.getline(category,25);

        cout<<"\n\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
        cout<<"\t|  Sl no. |  Food Id  |           Category             |          Food Name           |  Price  |"<<endl;
        cout<<"\t+---------+-----------+--------------------------------+------------------------------+---------+"<<endl;
        while(fin.read((char*)&s,sizeof(s))){
            if(strcmpi(category,s.food_category)==0){
                s.showall(n);
                n++;
            }
        }
	}
	cin.get();
    cin.get();
    system("cls");
	fin.close();
}

void mainfood()
{
	int ch;
	do{
        system("cls");
        cout<<"+-----------------------------+"<<endl;
        cout<<"|Enter 1 to enter new dishes. |"<<endl;
        cout<<"|Enter 2 to show the menu.    |"<<endl;
        cout<<"|Enter 3 to search for dish.  |"<<endl;
        cout<<"|Enter 4 to delete the dish.  |"<<endl;
        cout<<"+-----------------------------+"<<endl;
        cout<<"\nEnter your choice : ";
        cin>>ch;

        switch(ch){
            case 1:	update();
                break;
            case 2:	display();
                break;
            case 3: search_food();
                break;
            case 4: del();
                break;
        }
	}while(ch>=1 && ch<=4);
}

/*void food_bill()
{
    menu m;
    char ch;
    int food_id, i=0, qty;
    int bn=bill_details(); // generate bill number
    do{
        int x=0;
        gotoxy(45,2);
		cout<<"                               ";
		gotoxy(45,2);
        cout<<"Enter food id : ";
        cin>>food_id;

        ifstream fin("C:\\Users\\lamac\\OneDrive\\Documents\\Documents imp\\class 11\\Hotel_management\\menu.txt", ios::in | ios::binary);
        while(fin.read((char*)&m,sizeof(m))){
            if(m.food_id==food_id){
                gotoxy(45,2);
                cout<<"                                ";
                gotoxy(45,2);
                cout<<"Enter quantity : ";
                cin>>qty;

                bill_items(bn, m.price, m.food, qty, i);
                i++;
                x=1;
            }
        }
        if(x==0){
            gotoxy(45,2);
			cout<<"                           ";
			gotoxy(45,2);
            cout<<"Invalid food id.";
            ch='y';
            cin.get();
            cin.get();
        }
        else{
            gotoxy(45,2);
            cout<<"                                  ";
            gotoxy(45,2);
            cout<<"More food ? Y/N ";
            cin>>ch;
        }
    }while((ch=='Y' || ch=='y') && i<7);
}*/
