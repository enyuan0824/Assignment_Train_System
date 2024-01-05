#include<iostream>
#include <cstdlib>
#include <fstream>
#include<vector>
#include<string.h>
#include<iomanip>
//#include "sqlite3.h"
#include<algorithm>

using namespace std;
using std::setw;

char f[10] = "f";
char s[10] = "s";

class table{

};

class login {
	public:
	char id[100];
	char pass[100];
	char password[10];
	void inputid()
	{
		cout << "\nEnter your id:";
		cin >> id;
		cout << "Enter the Password: ";
		cin >> password;
		cout << "\n";
		strcpy(pass,password);
	}
	void displayid()
	{
	    cout << "\n|" << "User ID" << "\t" << "|" << "Password\n";
		cout << "|" << id << "\t\t" << "|" << pass << "\n\n";
	}
};
class train_detail{
		public:
		int id1,id2;
		string reason;
		char name[100];
		char op[100];
		char dp[100];

		int c1,c1fare;
		int c2,c2fare;
		int d1,m1,y1;
		int d2,m2,y2;
		void add_new_train()
		{
			cout << "\n--Add New Train--\nTrain ID: ";
			cin >> id1;
			cout << "Train Name: ";
			cin >> name;
			cout << "Originate point: ";
			cin >> op;
			cout << "Destination point: ";
			cin >> dp;
			cout << "Number of seats in first class: ";
			cin >> c1;
			cout << "Price per ticket for first class: ";
			cin >> c1fare;
			cout << "Number of seats in second class: ";
			cin >> c2;
			cout << "Price per ticket for second class: ";
			cin >> c2fare;
			cout << "--Date of travel--\nDay: ";
			cin >> d1;
			cout << "Month: ";
			cin >> m1;
			cout << "Year: ";
			cin >> y1;
		}
		void display_train_detail()
		{
		    cout << "\n|Train ID" << "\t" << "|Train Name" << "\t" << "|Originate pt." << "\t" << "|Destination pt."  <<"\t";
			cout << "|F-Class" << "\t"<< "|F-Class Price" << "\t" << "|S-Class" << "\t" << "|S-Class Price" <<"\t";
			cout << "|Day" << "-" << "Month" << "-" << "Year" << "\n";

			cout << "|" << id1 << "\t\t" << "|" << name << "\t\t" << "|" << op << "\t\t" << "|" << dp <<"\t\t\t";
			cout << "|" << c1 << "\t\t" << "|"<< c1fare << "\t\t" << "|" << c2<< "\t\t" << "|" << c2fare <<"\t\t";
			cout << "|" << d1 << "-" << m1 << "-" << y1 << "\n";
		}
		void add_new_maintain_train()
		{
			cout << "\n--Add New Maintain Train--\nTrain ID: ";
			cin >> id2;
			cout << "Reason: ";
			getline(cin,reason);
			cout << "--Date of Maintain--\n";
			cout << "Day: ";
			cin >> d2;
			cout << "Month: ";
			cin >> m2;
			cout << "Year: ";
			cin >> y2;
		}
		void display_maintain_record()
		{
			cout << "\n|Train ID" << "\t" << "|Train Name" << "\t" << "|Day" << "-" << "Month" << "-" << "Year" << "\n";

			cout << "|" << id2 << "\t\t" << "|" << reason << "\t" << "|" << d2 << "-" << m2 << "-" << y2 << "\n";
		}
};
class crew_details {
	public:
		int id;
		char name[100];
		char department[100];
		int age[100];

		void add_new_crew_details(){
			cout<< "\n--Add New Crew--\nCrew ID: ";
			cin >> id;
			cout<< "Name: ";
			cin >> name;
			cout<< "Age:";
			cin >> age;
			cout<< "Department:";
			cin >> department;
		}
		void display_crew_details(){
			cout<< "\n|Crew ID\t|Name\t\t|Age\t\t|Department\t\n";

			cout<<"|"<<id<<"\t\t"<<name<<"\t"<<age<<"\t\t"<<department<<"\n";
		}
};
class train_status{
	public:
		int id1,id2,id3;
		int h1,m1;
		int h2,m2;
		int h3,m3;

		void train_arrive(){
			cout<<"\n-- Add Train Status --\nTrain ID : ";
			cin>>id1;
			cout<<"Time (Hour) : ";
			cin>>h1;
			cout<<"Time (Minute) : ";
			cin>>m1;
		}
		void train_departure(){
			cout<<"\n-- Add Train Status --\nTrain ID : ";
			cin>>id2;
			cout<<"Time (Hour) : ";
			cin>>h2;
			cout<<"Time (Minute) : ";
			cin>>m3;
		}
		void train_delay(){
			cout<<"\n-- Add Train Status --\nTrain ID : ";
			cin>>id3;
			cout<<"Time (Hour) : ";
			cin>>h3;
			cout<<"Time (Minute) : ";
			cin>>m3;
		}

		void display_train_arrive(){
			cout<<"\n|Train ID\t\t|Hour-Minute\n";
			cout<< "|"<<id1<<"\t\t|" << h1 << "-" << m1 <<"\n";
		}
		void display_train_departure(){
			cout<<"\n|Train ID\t\t|Hour-Minute\n";
			cout<< "|"<<id2<<"\t\t|" << h2 << "-" << m2 <<"\n";
		}
		void display_train_delay(){
			cout<<"\n|Train ID\t\t|Hour-Minute\n";
			cout<< "|"<<id3<<"\t\t|" << h3 << "-" << m3 <<"\n";
		}
};
class incident_record{
	public:
		int id;
		char reason[100];
		char name[100];
		int d,m,y;

		void add_incident_record(){
			cout<<"\n--Add New Incident Record--\nTrain ID : ";
			cin>>id;
			cout << "Train Name: ";
			cin >> name;
			cout << "Reason: ";
			cin>>reason;
			cout << "--Date of incident occur--\nDay: ";
			cin >> d;
			cout << "Month: ";
			cin >> m;
			cout << "Year: ";
			cin >> y;
		}
		void display_incident_record(){
			cout<<"\n|Train ID\t\t|Train Name\t\t|Reason\t\t|Day-Month-Year";
			cout<<"|"<<id<<"\t\t|"<<name<<"\t\t|"<<reason<<"\t\t|"<<d<<"-"<<m<<"-"<<y<<"-";
		}
};

void admin();
void select_train_status();

int main(){
    int code;
    cout << "----- RAILWAY RESERVATION SYSTEM ----- \n";
	do{
        cout << "\n MAIN MENU \n";
		cout << "1.Admin mode\n2.User mode\n3.Exit \n";
		cout << "Enter your identity : ";
		cin >> code;
		switch(code){
			case 1:
				admin();
				break;
			//case 2:
			//	user();
			//	break;
			default:
				exit(0);}
	}while(code<3);
}

void admin(){
    char password[10];
	char pass[50] = "admin123";
	cout << "\nEnter the Admin Password: ";
	cin >> password;

	train_detail a;
	crew_details b;
	incident_record c;
	fstream f;

	int code;
	if(strcmp(pass,password)!=0)
	{
		cout << "Please enter the password again.\n";
		cout << "You are not permitted to login this mode.\n";
	}
	if(strcmp(pass,password)==0)
	{
		char y;
		do
		{
			cout << "\n --- ADMINISTRATOR MENU --- \n";
			cout << "1. Add new train detail\n";
			cout << "2. Display train details \n";
			cout << "3. Add train maintain schedule\n";
			cout << "4. Dislpay train maintain schedule\n";
			cout << "5. Add crew details\n";
			cout << "6. Display crew details\n";
			cout << "7. Ttrain status\n";
			cout << "8. Add incident record\n";
			cout << "9. Display incident record\n";
			cout << "10. Return to Main Menu \n";
			cout << "Please select your choice : ";
			cin >> code;

			switch(code)
			{
				case 1:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					do
					{
						a.add_new_train();
						f.write((char *) & a,sizeof(a));
						cout << "\nDo you want to continue add more train details (Y/N): \n";
						cin >> y;
					}while(y=='y' || y =='Y');
					f.close();
					break;
				case 2:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					f.seekg(0);
					while(f.read((char *) & a,sizeof(a)))
					{
						a.display_train_detail();
					}
					f.close();
					break;
				case 3:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					do
					{
						a.add_new_maintain_train();
						f.write((char *) & a,sizeof(a));
						cout << "\nDo you want to continue add more maintaning train schedule (Y/N): \n";
						cin >> y;
					}while(y=='y' ||y =='Y');
					f.close();
					break;
				case 4:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					f.seekg(0);
					while(f.read((char *) & a,sizeof(a)))
					{
						a.display_maintain_record();
					}
					f.close();
					break;
				case 5:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					do
					{
						b.add_new_crew_details();
						f.write((char *) & a,sizeof(a));
						cout << "\nDo you want to continue add more maintaning train schedule (Y/N): \n";
						cin >> y;
					}while(y=='y' ||y =='Y');
					f.close();
					break;
				case 6:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					f.seekg(0);
					while(f.read((char *) & a,sizeof(a)))
					{
						b.display_crew_details();
					}
					f.close();
					break;
				case 7:
					select_train_status();
					break;
				case 8:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					do
					{
						c.add_incident_record();
						f.write((char *) & a,sizeof(a));
						cout << "\nDo you want to continue add more maintaning train schedule (Y/N): \n";
						cin >> y;
					}while(y=='y' ||y =='Y');
					f.close();
					break;
				case 9:
					f.open("t.txt",ios::out|ios::app|ios::ate);
					f.seekg(0);
					while(f.read((char *) & a,sizeof(a)))
					{
						c.display_incident_record();
					}
					f.close();
					break;
			}
		}while(code<=9);
	}
}
void select_train_status(){
	fstream f;
	train_status a;

	int code;
	char y;
	do{
		cout<<"\n--Select train status--\n1. Add train arrive\n2. Display train arrive\n3. Add Train Departure\n4. Display Train Departure\n5. Add Train Delay\n6. Display Train Delay\n7. Back to admin menu";
		cout<<"Please select the code : ";
		cin>>code;
		switch(code) {
			case 1 :
				f.open("t.txt",ios::out|ios::app|ios::ate);
				do
				{
					a.train_arrive();
					f.write((char *) & a,sizeof(a));
					cout << "\nDo you want to continue add more train details (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				f.close();
				break;
			case 2:
				f.open("t.txt",ios::out|ios::app|ios::ate);
				f.seekg(0);
				while(f.read((char *) & a,sizeof(a)))
				{
					a.display_train_arrive();
				}
				f.close();
				break;
			case 3 :
				f.open("t.txt",ios::out|ios::app|ios::ate);
				do
				{
					a.train_departure();
					f.write((char *) & a,sizeof(a));
					cout << "\nDo you want to continue add more train details (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				f.close();
				break;
			case 4:
				f.open("t.txt",ios::out|ios::app|ios::ate);
				f.seekg(0);
				while(f.read((char *) & a,sizeof(a)))
				{
					a.display_train_departure();
				}
				f.close();
				break;
			case 5 :
				f.open("t.txt",ios::out|ios::app|ios::ate);
				do
				{
					a.train_delay();
					f.write((char *) & a,sizeof(a));
					cout << "\nDo you want to continue add more train details (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				f.close();
				break;
			case 6 :
				f.open("t.txt",ios::out|ios::app|ios::ate);
				f.seekg(0);
				while(f.read((char *) & a,sizeof(a)))
				{
					a.display_train_delay();
				}
				f.close();
				break;
		}
	}while (code<=5);
}
	

void signin()
{
	int ch;
	fstream f;
	char c;
	login a;
	do
	{
		cout << "1. Create id\n";
		cout << "2. Return to the main menu\n";
		cout << "Please select code: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				f.open("id.txt",ios::in|ios::out|ios::binary);
				f.seekg(0);
				while(f.read((char *) & a,sizeof(a)))
				{
					a.displayid();
				}
				f.close();
				break;
			}
		}while(ch<=1);
}