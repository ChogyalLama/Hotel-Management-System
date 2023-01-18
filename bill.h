#include<fstream>
#include"checkin.h"
#include"leap.h"
#include"facility.h"
#include"food.h"
#include"newroom.h"

#define Pay_status(x) ((x=='y' || x=='Y') ? "Paid" : "Unpaid")
struct Date
{
	int yyyy,mm,dd;
};
class BillDetails
{
	public:
		char aadhaar[13],ph[11];
		Date Billdate;
		int billno;
		char name[20] ,address[30];
};
class BillItem
{
	public:
		char desc[15];
		int billno, slno;
		char status;    // status - bill paid or not
		double rate,qty,amt;
		void billLayout_aadhaar();
};

BillDetails bd;
BillItem bi[7];

void billLayout()
{

	  cout<<"+-----------------------------------------+"<<endl;
	  cout<<"|               BILL /MEMO                |"<<endl;
	  cout<<"+-----------------------------------------+"<<endl;
	  cout<<"|Bill No :            Check Dt:           |"<<endl;
	  cout<<"|Adhar Number :                           |"<<endl;
	  cout<<"|Head_Name :                              |"<<endl;
	  cout<<"|Add :                                    |"<<endl;
	  cout<<"|PHONE :                                  |"<<endl;
	  cout<<"+----+---------------+-----+-----+--------+"<<endl;
	  cout<<"|SrNo|Desc           |Rt   |Qty  |Amt     |"<<endl;
	  cout<<"+----+---------------+-----+-----+--------+"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"|    |               |     |     |        |"<<endl;
	  cout<<"+----+---------------+-----+-----+--------+"<<endl;
	  cout<<"|                     Total Bill |        |"<<endl;
	  cout<<"+--------------------------------+--------+"<<endl;
	  cout<<"|               *THANK YOU*               |"<<endl;
	  cout<<"+-----------------------------------------+"<<endl;
}
void BillItem::billLayout_aadhaar()
{

    cout<<"| "<<setw(5)<<billno
        <<" |"<<setw(20)<<desc
        <<" |"<<setw(5)<<rate
        <<"|"<<setw(5)<<qty
        <<"|"<<setw(8)<<amt
        <<"|"<<setw(7)<<Pay_status(status)<<" |"<<endl;
    cout<<"+-------+---------------------+-----+-----+--------+--------+"<<endl;
}

int genbillno()
{
	ifstream f("C:\\Hotel_management\\billdet.txt", ios::in | ios::binary);
	if(!f)
	{
		cout<<"\tFile error "<<endl;
		return 0;
	}
	BillDetails s;
	int x=0,id=0;
	while(f.read((char*)&s,sizeof(s)))
	{
		if(id<s.billno)
			id=s.billno;
		x++;
	}
	if(x==0)
		id=100;
	else
		id=id+1;
	f.close();
	return id;
}

int bill_details()
{
    system("cls");
	billLayout();

    ifstream fin;
	ofstream fbd("C:\\Hotel_management\\billdet.txt", ios::app | ios::binary);

    int bn=genbillno();
	bd.billno=bn;
	char adno[13];

	int d,m,y;
	gotoxy(11,3);
	cout<<bn;

	gotoxy(45,2);
	cout<<"                          ";
	gotoxy(45,2);
	cout<<"Enter the date : ";
	mainleap(d,m,y);
	int n=0;

	do{
		gotoxy(45,2);
		cout<<"                           ";
		gotoxy(45,3);
		cout<<"                           ";
		gotoxy(45,4);
		cout<<"                           ";
		gotoxy(45,5);
		cout<<"                           ";
		gotoxy(45,2);
		cout<<"Enter the Adhar no : ";
		cin.clear();
		cin.sync();
		cin.getline(adno,13);

		strcpy(bd.aadhaar,adno);
		gotoxy(16,4);
		cout<<adno;
		gotoxy(45,2);
		cout<<"                                   ";

        checkin c;
        fin.open("C:\\Hotel_management\\checkin.txt", ios::in | ios::binary);
		while(fin.read((char*)&c,sizeof(c))){
			if(strcmp(c.adharno,adno)==0){
				gotoxy(13,5);
				cout<<c.hname;
				gotoxy(8,6);
				cout<<c.add;
				gotoxy(9,7);
				cout<<c.pnumber;
				strcpy(bd.aadhaar,adno);

				bd.Billdate.dd=d;
				bd.Billdate.mm=m;
				bd.Billdate.yyyy=y;
				strcpy(bd.name,c.hname);
				strcpy(bd.address,c.add);
				strcpy(bd.ph,c.pnumber);
				n++;
			}
		}
		fin.close();
		if(n==0){
			gotoxy(45,2);
			cout<<"                           ";
			gotoxy(45,2);
			cout<<"No such guest exists.";
			cin.get();
			cin.get();
		}
	}while(n==0);

    fbd.write((char*)&bd,sizeof(bd));
    fbd.close();
    return bn;
}

void bill_items(int bill_no, double price, char* desc, int qty, int i)
{
    ofstream fbi("C:\\Hotel_management\\billitem.txt", ios::app | ios::binary);

    bi[i].billno=bill_no;

    gotoxy(1,i+11);
    bi[i].slno=i+1;
    cout<<bi[i].slno;

    gotoxy(6,i+11);
    strcpy(bi[i].desc,desc);
    cout<<bi[i].desc;

    gotoxy(22,i+11);
    bi[i].rate=price;
    cout<<bi[i].rate;

    gotoxy(28,i+11);
    bi[i].qty=qty;
    cout<<bi[i].qty;

    gotoxy(34,i+11);
    bi[i].amt=bi[i].rate*qty;
    cout<<bi[i].amt;

    gotoxy(45,2);
    cout<<"                               ";
    gotoxy(45,2);
    cout<<"Paid (Y/N) : ";
    cin>>bi[i].status;

    fbi.write((char*)&bi,sizeof(bi));
}

void show_bill_id()
{
	system("cls");
	billLayout();
	int bn,i=0,j=0;
	int tot_amt=0, paid_amt=0;
	ifstream fbd;
	ifstream fbi;

  top:
	fbd.open("C:\\Hotel_management\\billdet.txt", ios::in | ios::binary);
	fbi.open("C:\\Hotel_management\\billitem.txt", ios::in | ios::binary);
	if(!fbd || !fbi){
		cout<<"File error...Bill cannot be shown"<<endl;
		return;
	}
	gotoxy(45,2);
	cout<<"                                 ";
	gotoxy(45,2);
	cout<<"Enter Bill no to display : ";
	cin>>bn;

	while(fbd.read((char*)&bd,sizeof(bd))) {
			if(bd.billno==bn){
				gotoxy(13,5);
				cout<<bd.name;
				gotoxy(8,6);
				cout<<bd.address;
				gotoxy(9,7);
				cout<<bd.ph;
				gotoxy(32,3);
				cout<<bd.Billdate.yyyy<<"-"<<bd.Billdate.mm<<"-"<<bd.Billdate.dd<<endl;
				gotoxy(16,4);
				cout<<bd.aadhaar;
				gotoxy(11,3);
				cout<<bd.billno;
				j=1;
			}
		}
	 while(fbi.read((char*)&bi,sizeof(bi))) {
			if(bi[i].billno==bn){
				gotoxy(1,i+11);
				cout<<bi[i].slno;
				gotoxy(6,i+11);
				cout<<bi[i].desc;
				gotoxy(22,i+11);
				cout<<bi[i].rate;
				gotoxy(28,i+11);
				cout<<bi[i].qty;
				gotoxy(34,i+11);
				cout<<bi[i].amt;

				tot_amt+=bi[i].amt;
				if(bi[i].status=='y' || bi[i].status=='Y')
                    paid_amt+=bi[i].amt;
				i++;
			}
		}
	if(j==0){       // invalid bill no
		fbd.close();
		fbi.close();
		goto top;
	}
    gotoxy(34,19);
    cout<<tot_amt<<endl;
	gotoxy(45,2);
    cout<<"                              ";
	gotoxy(45,2);
	cout<<"Total Amount   : "<<tot_amt;
    gotoxy(45,3);
	cout<<"Paid Amount    : "<<paid_amt;
    gotoxy(45,4);
	cout<<"Amount Pending : "<<tot_amt-paid_amt;

	if(tot_amt-paid_amt==0){
        gotoxy(4,19);
        cout<<"Paid";
	}
	cin.get();
    cin.get();
}

void show_bill_aadhaar()
{
    system("cls");
    ifstream fbd("C:\\Hotel_management\\billdet.txt", ios::in | ios::binary);
    ifstream fbi("C:\\Hotel_management\\billitem.txt", ios::in | ios::binary);

    char aadhaar[13];
    int i=0;
    cout<<"Enter Aadhaar number : ";
    cin.clear();
    cin.sync();
    cin.getline(aadhaar,13);

    cout<<"+-------+---------------------+-----+-----+--------+--------+"<<endl;
    cout<<"|Bill No| Desc                |Rt   |Qty  |Amt     | Status |"<<endl;
    cout<<"+-------+---------------------+-----+-----+--------+--------|"<<endl;
    while(fbd.read((char*)&bd,sizeof(bd))) {
        if(strcmpi(aadhaar,bd.aadhaar)==0) {
            while(fbi.read((char*)&bi,sizeof(bi)) && i<7) {
                if(bi[i].billno==bd.billno) {
                    bi[i].billLayout_aadhaar();
                    i++;
                }
            }
            i=0;
        }
    }
    cin.get();
    fbd.close();
    fbi.close();
}
void bill()
{
	system("cls");
	billLayout();

	ifstream fin;
	ofstream fbd("C:\\Hotel_management\\billdet.txt", ios::app | ios::binary);
	ofstream fbi("C:\\Hotel_management\\billitem.txt", ios::app | ios::binary);

	int bn=genbillno();
	bd.billno=bn;
	char adno[13];

	checkin c;
	room r;
	menu f;
	service l;
	int d,m,y;
	gotoxy(11,3);
	cout<<bn;

	gotoxy(45,2);
	cout<<"                          ";
	gotoxy(45,2);
	cout<<"Enter the date : ";
	mainleap(d,m,y);
	int n=0;

	do{
		gotoxy(45,2);
		cout<<"                           ";
		gotoxy(45,3);
		cout<<"                           ";
		gotoxy(45,4);
		cout<<"                           ";
		gotoxy(45,5);
		cout<<"                           ";
		gotoxy(45,2);
		cout<<"Enter the Adhar no : ";
		cin.clear();
		cin.sync();
		cin.getline(adno,13);

		strcpy(bd.aadhaar,adno);
		gotoxy(16,4);
		cout<<adno;
		gotoxy(45,2);
		cout<<"                                   ";

        fin.open("C:\\Hotel_management\\checkin.txt", ios::in | ios::binary);
		while(fin.read((char*)&c,sizeof(c))){
			if(strcmp(c.adharno,adno)==0){
				gotoxy(13,5);
				cout<<c.hname;
				gotoxy(8,6);
				cout<<c.add;
				gotoxy(9,7);
				cout<<c.pnumber;
				strcpy(bd.aadhaar,adno);
				bd.Billdate.dd=d;
				bd.Billdate.mm=m;
				bd.Billdate.yyyy=y;
				strcpy(bd.name,c.hname);
				strcpy(bd.address,c.add);
				strcpy(bd.ph,c.pnumber);
				n++;
			}
		}
		fin.close();
		if(n==0){
			gotoxy(45,2);
			cout<<"                           ";
			gotoxy(45,2);
			cout<<"No such guest exists.";
			cin.get();
			cin.get();
		}
	}while(n==0);

	fbd.write((char*)&bd,sizeof(bd));
	char ch;
	int x=0,i=0,qty,id;
	//ifstream fr;

	gotoxy(45,2);
	cout<<"Room Bill (Y\N) ? : ";
	cin>>ch;
	while(ch=='Y' || ch=='y'){
		gotoxy(45,2);
		cout<<"                               ";
		gotoxy(45,2);
		cout<<"Enter your roomid : ";
		cin>>id;

		fin.open("C:\\Hotel_management\\room.txt", ios::in | ios::binary);
        while(fin.read((char*)&r,sizeof(r))){
            if(r.room_id==id){
				bi[i].slno=i+1;
				bi[i].billno=bn;
				bi[i].rate=r.price;
				strcpy(bi[i].desc,r.roomtype);
				gotoxy(45,2);
                cout<<"                                ";
                gotoxy(45,2);
                cout<<"Enter the number of days stayed :";
                cin>>qty;
                bi[i].qty=qty;
                bi[i].amt=bi[i].rate*qty;
                gotoxy(1,i+11);
                cout<<bi[i].slno;
                gotoxy(6,i+11);
                cout<<bi[i].desc;
                gotoxy(22,i+11);
                cout<<bi[i].rate;
                gotoxy(28,i+11);
                cout<<qty;
                gotoxy(34,i+11);
                cout<<bi[i].amt;
                x++;
                i++;
			}
		}
		fin.close();
		if(x>0){

		}
		if(x==0){
			gotoxy(45,2);
			cout<<"                            ";
			gotoxy(45,2);
			cout<<"No such room exists.";
            cin.get();
            cin.get();
		}
		gotoxy(45,2);
		cout<<"                                  ";
		gotoxy(45,2);
		cout<<"Booked another room?(Y/N):";
		cin>>ch;
		fbi.write((char*)&bi,sizeof(bi));
		gotoxy(45,2);
		cout<<"                             ";
		fin.close();

		if(i>7){
			cout<<"Create new bill."<<endl;
			return;
		}
    }

	gotoxy(45,2);
	cout<<"Food ordered (Y/N) : ";
	cin>>ch;
	while(ch=='Y' || ch=='y'){

		ifstream ff("C:\\Hotel_management\\menu.txt", ios::in | ios::binary);

		gotoxy(45,2);
		cout<<"                               ";
		gotoxy(45,2);
		cout<<"Enter food id : ";
		cin>>id;

		m=0;
		while(ff.read((char*)&f,sizeof(f))){
			if(f.food_id==id)
			{
				m=1;
				bi[i].billno=bn;
				bi[i].slno=i+1;
				bi[i].rate=f.price;
				strcpy(bi[i].desc,f.food);
			}
		}
		if(m==1){
			gotoxy(45,2);
			cout<<"                               ";
			gotoxy(45,2);
			cout<<"Enter the quantity :";
			cin>>qty;

			bi[i].amt=f.price*qty;
			bi[i].qty=qty;
			gotoxy(1,i+11);
			cout<<bi[i].slno;
			gotoxy(6,i+11);
			cout<<bi[i].desc;
			gotoxy(22,i+11);
			cout<<bi[i].rate;
			gotoxy(28,i+11);
			cout<<qty;
			gotoxy(34,i+11);
			cout<<bi[i].amt;
			i++;
		}
		else{
			gotoxy(45,2);
			cout<<"                       ";
			gotoxy(45,2);
			cout<<"No such Food available.";
			cin.get();
            cin.get();
		}
		gotoxy(45,2);
		cout<<"                                  ";
		gotoxy(45,2);
		cout<<"Do you want more food (Y/N):-";
		cin>>ch;

		gotoxy(45,2);
		cout<<"                                ";
		ff.close();
		fbi.write((char*)&bi,sizeof(bi));
		if(i>7){
			cout<<"Create new bill."<<endl;
			return;
		}
	}

	gotoxy(45,2);
	cout<<"Other service (Y/N): ";
	cin>>ch;

	while(ch=='Y' || ch=='y'){
		ifstream fl("C:\\Hotel_management\\fac.txt", ios::in | ios::binary);

		gotoxy(45,2);
		cout<<"                               ";
		gotoxy(45,2);
		cout<<"Enter service id : ";
		cin>>id;

		m=0;
		while(fl.read((char*)&l,sizeof(l))){
			if(l.service_id==id){
				m=1;
				bi[i].billno=bn;
				bi[i].slno=i+1;
				bi[i].rate=l.price;
				strcpy(bi[i].desc,l.service);
			}
		}
		if(m==1){
			gotoxy(45,2);
			cout<<"                               ";
			gotoxy(45,2);
			cout<<"Enter the quantity :";
			cin>>qty;

			bi[i].amt=l.price*qty;
			bi[i].qty=qty;
			gotoxy(1,i+11);
			cout<<bi[i].slno;
			gotoxy(6,i+11);
			cout<<bi[i].desc;
			gotoxy(22,i+11);
			cout<<bi[i].rate;
			gotoxy(28,i+11);
			cout<<qty;
			gotoxy(34,i+11);
			cout<<bi[i].amt;
			i++;
		}
		else{
			gotoxy(45,2);
			cout<<"                              ";
			gotoxy(45,2);
			cout<<"No such service available.";
			cin.get();
			cin.get();
		}
		gotoxy(45,2);
		cout<<"                                     ";
		gotoxy(45,2);
		cout<<"more service (Y/N) ? ";
		cin>>ch;

		gotoxy(45,2);
		cout<<"                                ";
		fl.close();
			fbi.write((char*)&bi,sizeof(bi));
		if(i>7){
			cout<<"Create new bill."<<endl;
			return;
		}
	}
	fbi.write((char*)&bi,sizeof(bi));
    fbi.close();
}
void mainbill()
{
	int ch;
	do{
		system("cls");
		cout<<"Enter 1 to create bill."<<endl;
		cout<<"Enter 2 to search bill by bill no."<<endl;
		cout<<"Enter 3 to search bill by Aadhaar id."<<endl;
		cout<<"Enter your choice : ";
		cin>>ch;
		switch(ch){
			case 1 : bill();
                       break;
			case 2 : show_bill_id();
						break;
            case 3 : show_bill_aadhaar();
                        break;
		}
	}while(ch==1 || ch==2 || ch==3);
}



