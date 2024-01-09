#include<iostream>
#include <fstream>
#include<string.h>
#include<iomanip>
#include "sqlite3.h"
#include<algorithm>

using namespace std;
using std::setw;

char f[10] = "f";

class database {

private:
    sqlite3* db;
public:
    database(const char* dbName) : db(nullptr) {
        // Open the database
        int exit = sqlite3_open(dbName, &db);

        if (exit != SQLITE_OK) {
            cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            //exit(EXIT_FAILURE);
        }
    }
    ~database() {
        // Close the database
        sqlite3_close(db);
    }
	void openDatabase() {
        int exit = sqlite3_open("Train_Management.db", &db);

        if (exit != SQLITE_OK) {
            cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            // Handle the error as needed
        }
    }

    void table() {
        // Create a table if it doesn't exist
        const char* create_signin = "CREATE TABLE SIGN_IN ("
                                    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "USERNAME TEXT NOT NULL,"
                                    "PASSWORD TEXT NOT NULL);";
		const char* create_staff = "CREATE TABLE STAFF ("
                                    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  	"NAME TEXT NOT NULL,"
                                  	"DEPARTMENT TEXT NOT NULL,"
								  	"AGE INTEGER NOT NULL);";
		const char* train = "CREATE TABLE TRAIN ("
                            "TRAIN_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
							"TRAIN_NAME TEXT NOT NULL,"
                          	"DESTINATION_POINT TEXT NOT NULL,"
							"DATE TEXT NOT NULL,"
							"TIME TEXT NOT NULL,"
                          	"PRICE INTEGER NOT NULL,"
							"AVAILABLE_SEAT INTEGER NOT NULL,"
							"SALE_SEAT INTEGER NOT NULL);";
		const char* incident = "CREATE TABLE INCIDENT ("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
							"TRAIN_NAME TEXT NOT NULL,"
                          	"REASON TEXT NOT NULL,"
							"DATE TEXT NOT NULL);";
		const char* train_status = "CREATE TABLE TRAIN_STATUS ("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
							"STATUS TEXT NOT NULL,"
                          	"TIME TEXT NOT NULL,"
							"TRAIN_ID INTEGER);";
		const char* ticket = "CREATE TABLE TICKET ("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
							"TRAIN_ID INTEGER,"
							"STATUS TEXT NOT NULL,"
                          	"PRICE INTEGER NOT NULL);";	
		const char* maintain = "CREATE TABLE MAINTAIN ("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
							"TRAIN_ID INTEGER,"
							"REASON TEXT NOT NULL,"
                          	"DATE TEXT NOT NULL);";			
        executeQuery(create_staff);
        executeQuery(create_signin);
		executeQuery(train);
		executeQuery(incident);
		executeQuery(train_status);
		executeQuery(ticket);
		executeQuery(maintain);
    }

	void open_and_create(){
		openDatabase();
		table();
	}

    void insertsignin_data(const string& username, const string& password) {
        string insertQuery = "INSERT INTO SIGN_IN (USERNAME, PASSWORD) VALUES ('" +
                                  username + "', '" + password + "');";
        executeQuery(insertQuery.c_str());
    }

	void insert_train(const string& destination_point,const string& train_name,const string& date,const string& time){
		string insertQuery = "INSERT INTO TRAIN (TRAIN_NAME, DESTINATION_POINT, DATE, TIME, PRICE, AVAILABLE_SEAT , SALE_SEAT ) VALUES ('" +
                                  train_name + "','" + destination_point + "','" + date + "','" + time + "', 10 , 15, 0 );";
        executeQuery(insertQuery.c_str());
	}

	void insert_staff(const string& name, const string& department, int age){
		string insertQuery = "INSERT INTO STAFF (NAME, DEPARTMENT, AGE) VALUES ('" +
                                  name + "', '" + department + "'," + to_string(age) + ");";
        executeQuery(insertQuery.c_str());
	}

	void insert_incident(const string& name, const string& reason, const string& date){
		string insertQuery = "INSERT INTO INCIDENT (TRAIN_NAME, REASON, DATE) VALUES ('" +
                                  name + "', '" + reason + "'," + date + ");";
        executeQuery(insertQuery.c_str());
	}

	void insert_train_status(const string& status, const string& time,int id){
		string insertQuery = "INSERT INTO TRAIN_STATUS (STATUS, TIME, TRAIN_ID) VALUES ('" +
                                  status + "', '" + time + "'," + to_string(id) + ");";
        executeQuery(insertQuery.c_str());
	}

	void insert_ticket(int id){
		string insertQuery = "INSERT INTO TICKET (TRAIN_ID,STATUS, PRICE) VALUES ( " + to_string(id) + ",'Booking', 10);";
        executeQuery(insertQuery.c_str());
	}
	
	void insert_maintain(int id,const string& reason, const string& date){
		string insertQuery = "INSERT INTO MAINTAIN (TRAIN_ID,REASON, DATE) VALUES ( " + to_string(id) + ",'" +
                                  reason + "', '" + date + "');";
        executeQuery(insertQuery.c_str());
	}
	
	bool check_train(int id){
		const char* query = "SELECT COUNT(TRAIN_ID) FROM TRAIN WHERE TRAIN_ID = ?;";
		sqlite3_stmt* statement;
		int exit = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);

		int count=0;

		if (exit == SQLITE_OK) {
			sqlite3_bind_int(statement, 1, id);
			exit = sqlite3_step(statement);

			if (exit == SQLITE_ROW) {
				count = sqlite3_column_int(statement, 0);
			}

			sqlite3_finalize(statement);
		}
		return count;
	}

	bool check_ticket(int id){
		const char* query = "SELECT COUNT(ID) FROM TICKET WHERE ID = ?;";
		sqlite3_stmt* statement;
		int exit = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);

		int count=0;
		if (exit == SQLITE_OK) {
			sqlite3_bind_int(statement, 1, id);
			exit = sqlite3_step(statement);

			if (exit == SQLITE_ROW) {
				count = sqlite3_column_int(statement, 0);
			}

			sqlite3_finalize(statement);
		}
		return count;
	}

    void update_staff(int id, const string& columnName, const string& newValue) {
        string updateQuery = "UPDATE STAFF SET " + columnName + " = '" + newValue + "' WHERE ID = " + to_string(id) + ";";
        executeQuery(updateQuery.c_str());
    }

	bool check_staff(int id){
		const char* query = "SELECT COUNT(ID) FROM STAFF WHERE ID = ?;";
		sqlite3_stmt* statement;
		int exit = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);

		int count=0;
		if (exit == SQLITE_OK) {
			sqlite3_bind_int(statement, 1, id);
			exit = sqlite3_step(statement);

			if (exit == SQLITE_ROW) {
				count = sqlite3_column_int(statement, 0);
			}

			sqlite3_finalize(statement);
		}
		return count;
	}

	void update_train(int id, const string& columnName, const string& newValue){
		string updateQuery = "UPDATE TRAIN SET " + columnName + " = '" + newValue + "' WHERE TRAIN_ID = " + to_string(id) + ";";
        executeQuery(updateQuery.c_str());
	}

	void sale_train_seat(int id){
		string updateQuery1 = "UPDATE TRAIN SET AVAILABLE_SEAT = AVAILABLE_SEAT - 1 WHERE TRAIN_ID = " + to_string(id) + ";";
		string updateQuery2 = "UPDATE TRAIN SET SALE_SEAT = SALE_SEAT + 1 WHERE TRAIN_ID = " + to_string(id) + ";";
        executeQuery(updateQuery1.c_str());
        executeQuery(updateQuery2.c_str());
	}

	void cancel_train_seat(int id){
		string updateQuery1 = "UPDATE TRAIN SET AVAILABLE_SEAT = AVAILABLE_SEAT + 1 WHERE TRAIN_ID = " + to_string(id) + ";";
		string updateQuery2 = "UPDATE TRAIN SET SALE_SEAT = SALE_SEAT - 1 WHERE TRAIN_ID = " + to_string(id) + ";";
        executeQuery(updateQuery1.c_str());
        executeQuery(updateQuery2.c_str());
	}

    void delete_staff(int id) {
        string deleteQuery = "DELETE FROM STAFF WHERE ID = " + to_string(id) + ";";
        executeQuery(deleteQuery.c_str());
    }

	void delete_train(int id) {
        string deleteQuery = "DELETE FROM TRAIN WHERE TRAIN_ID = " + to_string(id) + ";";
        executeQuery(deleteQuery.c_str());
    }

	void update_ticket(int id){
		string updateQuery = "UPDATE TICKET SET STATUS = 'Cancel' WHERE ID = " + to_string(id) + ";";
        executeQuery(updateQuery.c_str());
	}

    void read_sign_in() {
        const char* selectQuery = "SELECT * FROM SIGN_IN;";
        executeQuery(selectQuery);
    }

	void read_staff() {
        const char* selectQuery = "SELECT * FROM STAFF;";
        executeQuery(selectQuery);
    }

	void read_train() {
        const char* selectQuery = "SELECT * FROM TRAIN;";
        executeQuery(selectQuery);
    }

	void read_incident() {
        const char* selectQuery = "SELECT * FROM INCIDENT;";
        executeQuery(selectQuery);
    }

	void read_train_status(){
		const char* selectQuery = "SELECT * FROM TRAIN_STATUS;";
        executeQuery(selectQuery);
	}

	void read_booking_ticket(){
		string Query="SELECT *FROM TICKET WHERE STATUS = 'Booking' ;";
		const char* selectQuery = Query.c_str();
		executeQuery(selectQuery);
	}

	void read_cancel_ticket(){
		string Query="SELECT *FROM TICKET WHERE STATUS = 'Cancel' ;";
		const char* selectQuery = Query.c_str();
		executeQuery(selectQuery);
	}

	void read_all_ticket(){
		const char* selectQuery = "SELECT * FROM TICKET;";
        executeQuery(selectQuery);
	}

	void read_maintain(){
		const char* selectQuery = "SELECT * FROM MAINTAIN;";
        executeQuery(selectQuery);
	}

private:
    void executeQuery(const char* query) {
        // Execute the SQL query
        char* errorMessage = nullptr;
        int exit = sqlite3_exec(db, query, callback, nullptr, &errorMessage);

        if (exit != SQLITE_OK) {
            cerr << "Error executing query: " << errorMessage << endl;
            sqlite3_free(errorMessage);
        }
    }
    static int callback(void* notUsed, int argc, char** argv, char** azColName) {
        // Callback function for SELECT queries
        for (int i = 0; i < argc; i++) {
            cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        	
        }cout << endl;
        return 0;
    }

	int executeCountQuery(const char* query) {
    // Execute the SQL query and return the count of rows
    int count = 0;
    char* errorMessage = nullptr;
    int exit = sqlite3_exec(db, query, callbackForCount, &count, &errorMessage);
		if (exit != SQLITE_OK) {
			cerr << "Error executing count query: " << errorMessage << endl;
			sqlite3_free(errorMessage);
		}
		return count;
	}
	static int callbackForCount(void* data, int argc, char** argv, char** azColName) {
		int* count = static_cast<int*>(data);
		*count = atoi(argv[0]);
		return 0;
	}
};

struct User {
    string username;
    string password;
};
bool user_sign_in(const User& user) {
    ofstream file("sign_in.txt", ios::app);
    if (file.is_open()) {
        file << user.username << " " << user.password << endl;
        file.close();
        return true;
    } else {
        cerr << "Error opening users.txt for writing." << endl;
        return false;
    }
}
bool login(const string& username, const string& password) {
    ifstream file("sign_in.txt");
    if (file.is_open()) {
        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                file.close();
                return true; // Login successful
            }
        }
        file.close();
    }

    return false; // Login failed
}

class feedback_node {
public:
    int id;
    string notice;
    feedback_node* next;

    feedback_node(int _id, const string& _notice) : id(_id), notice(_notice), next(nullptr) {}
};
class passenger_node {
public:
    string name;
    int age;
    string gender;
	int contact_number;
    passenger_node* next;

    passenger_node(const string& _name, int _age, const string& _gender,int _contact_number): name(_name), age(_age), gender(_gender),contact_number(_contact_number), next(nullptr) {}
};
class lost_and_found_node {
public:
    string item_name;
    int id;
    string details;
	string email;
    lost_and_found_node* next;

    lost_and_found_node(const string& _item_name, int _id, const string& _details,const string& _email): item_name(_item_name), id(_id), details(_details),email(_email), next(nullptr) {}
};

class linkedlist_feedback {
private:
    feedback_node* head;

public:
    linkedlist_feedback() : head(nullptr) {}

    void pushBack(int id, const string& notice) {
        feedback_node* newNode = new feedback_node(id, notice);
        if (head == nullptr) {
            head = newNode;
        } else {
            feedback_node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
	string display() const {
        string result;
        feedback_node* temp = head;
        while (temp != nullptr) {
            result += "ID: " + to_string(temp->id) + ", Notice: " + temp->notice +"\n";
            temp = temp->next;
        }
        result+="\n--- Display End ---";
        return result;
    }

    ~linkedlist_feedback() {
        feedback_node* temp = head;
        feedback_node* nextNode;
        while (temp != nullptr) {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};
class linkedlist_passenger {
private:
    passenger_node* head;

public:
    linkedlist_passenger() : head(nullptr) {}

    void pushBack(const string& name, int age, const string& gender,int contact_number) {
        passenger_node* newNode = new passenger_node(name,age,gender,contact_number);
        if (head == nullptr) {
            head = newNode;
        } else {
            passenger_node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
	string display() const {
        string result;
        passenger_node* temp = head;
        while (temp != nullptr) {
            result += "Name : " + temp->name +"\nAge : " + to_string(temp->age) +"\nGender : " + temp->gender + "\nContact NUmber : " + to_string(temp->contact_number)+"\n";
            temp = temp->next;
        }
        result+="\n--- Display End ---";
        return result;
    }

    ~linkedlist_passenger() {
        passenger_node* temp = head;
        passenger_node* nextNode;
        while (temp != nullptr) {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};
class linkedlist_lost_and_found {
private:
    lost_and_found_node* head;

public:
    linkedlist_lost_and_found() : head(nullptr) {}

    void pushBack(const string& item_name, int id, const string& details,const string& email) {
        lost_and_found_node* newNode = new lost_and_found_node(item_name,id,details,email);
        if (head == nullptr) {
            head = newNode;
        } else {
            lost_and_found_node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
	string display() const {
        string result;
        lost_and_found_node* temp = head;
        while (temp != nullptr) {
            result +="Item name : " + temp->item_name +"\nTrain id : "+ to_string(temp->id) +"\nItem details : " + temp->details + "\nEmail : " + temp->email+"\n";
            temp = temp->next;
        }
        result+="\n--- Display End ---";
        return result;
    }

    ~linkedlist_lost_and_found() {
        lost_and_found_node* temp = head;
        lost_and_found_node* nextNode;
        while (temp != nullptr) {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

class train_detail{
	private:
    database train;
    
	public:
		int id_b,id_c,id_m;
		int id1,id2;
		string date,time,a;
		char name[100];
		char reason[100];
		char dp[100];
		string new_value;

		int h1,mu1;
		int d1,m1,y1;
		int d2,m2,y2;

		train_detail() : train("Train_Management.db") {
        // open the database without creating tables
        train.openDatabase();
    	}
	public:
		void add_new_train()
		{
			cout << "\n--Add New Train--\n";
			cout << "Train Name: ";
			cin.clear();
			cin.ignore();
			cin.getline(name,100);
			cout << "Destination point: ";
			cin.clear();
			cin.getline(dp,100);
			cout << "--Date of travel--\nDay: ";
			cin >> d1;
			cout << "Month: ";
			cin >> m1;
			cout << "Year: ";
			cin >> y1;
			cout<<"Hour:";
			cin>>h1;
			cout<<"Minute:";
			cin>>mu1;
			time =  to_string(h1) + "." + to_string(mu1);
			date = to_string(d1) + "-" + to_string(m1) + "-" + to_string(y1);
			train.insert_train(dp, name,date,time);
		}
		void display_train_detail()
		{
		    train.read_train();
		}
		void update_train_details(){
			int id,code;

			while(true){
				cout<<"\nEnter train ID you need to update : ";
				if (cin >> id) {
				// Check if the entered train ID is valid
					if (train.check_train(id)) {
						do{
						cout<<"1. Name\n2. Date\n3. Time\nEnter code you need to update : ";
						cin>>code;
						switch(code){
							case 1:
								cout<<"Entre new train name : ";
								cin.clear();
								cin.ignore();
								getline(cin,new_value); 
								a="TRAIN_NAME";
								break;
							case 2 :
								cout<<"Entre new travel date : ";
								cin.clear();
								cin.ignore();
								getline(cin,new_value); 
								a="DATE";
								break;
							case 3 :
								cout<<"Entre new travel time : ";
								cin.clear();
								cin.ignore();
								getline(cin,new_value); 
								a="TIME";
								break;
							default:
								cout<<"Please enter valid code.\n";
								break;
							}
						}while(code>=3);
						train.update_train(id,a,new_value);
						break;// Valid train ID, exit the loop
					}else {
						cout << "Invalid train ID. Please enter a valid number." << endl;
					}
				}
			}			
		}
		void sale_train_seat(){
			while (true) {
			cout << "Enter train ID you need to booking : ";
			if (cin >> id_b) {
				// Check if the entered train ID is valid
				if (train.check_train(id_b)) {
						train.insert_ticket(id_b);
						train.sale_train_seat(id_b);
						break;// Valid train ID, exit the loop
					} else {
						cout << "Invalid train ID. Please enter a valid number." << endl;
					}
				}
			}
		}
		void cancel_train_seat(){
		int id;
		while(true){
		cout<<"\nEnter ticket ID you need to cancel : ";
			if (cin >> id_c) {
			// Check if the entered train ID is valid
				if (train.check_ticket(id_c)) {
					train.cancel_train_seat(id_c);
					train.update_ticket(id_c);
					break;// Valid train ID, exit the loop
				}else {
					cout << "Invalid train ID. Please enter a valid number." << endl;
				}
			}
			}
		}
		void display_ticket(){
			train.read_booking_ticket();
		}
		void display_cancel_ticket(){
			train.read_cancel_ticket();
		}
		void display_all_ticket(){
			train.read_all_ticket();
		}
		void add_new_maintain_train()
		{
			while (true) {
			cout << "Enter train ID you need to maintain : ";
			if (cin >> id_m) {
				// Check if the entered train ID is valid
				if (train.check_train(id_m)) {
						cout << "\n--- Add New Maintain Train ---\n";
						cout << "Reason: ";
						cin.clear();
						cin.ignore();
						cin.getline(reason,100);
						cout << "--Date of Maintain--\n";
						cout << "Day: ";
						cin >> d2;
						cout << "Month: ";
						cin >> m2;
						cout << "Year: ";
						cin >> y2;

						date=to_string(d2)+"-"+to_string(m2)+"-"+to_string(y2);

						train.insert_maintain(id_m,reason,date);
						break;// Valid train ID, exit the loop
					} else {
						cout << "Invalid train ID. Please enter a valid number." << endl;
					}
				}
			}
		}
		void display_maintain_record()
		{
			train.read_maintain();
		}
};
class crew_details {
	private:
    database crew;
	
	public:
		int id;
		string name,department,new_value;
		string a;
		int age,code;
		crew_details() : crew("Train_Management.db") 
		{
			// open the database and create tables
			crew.openDatabase();
		}
		
		void add_new_crew_details(){
			cout<< "\n--Add New Crew--\n";
			cout<< "Name: ";
			cin.clear();
			cin.ignore();
			getline(cin,name); 
			cout<< "Age:";
			cin>>age;
			cout<< "Department:";
			cin.clear();
			cin.ignore();
			getline(cin,department); 

			crew.insert_staff(name, department,age);
		}
		void display_crew_details(){
			crew.read_staff();
		}
		void update_crew_details(){
			while (true) {
			cout<<"Entre staff ID you need to update : ";
			if (cin >> id) {
				// Check if the entered train ID is valid
				if (crew.check_staff(id)) {
					do{
						cout<<"1. Name\n2. Department\n3. Age\nEnter code you need to update : ";
						cin>>code;
						switch(code){
							case 1:
								cout<<"Entre new name : ";
								cin.clear();
								cin.ignore();
								getline(cin,new_value); 
								a="NAME";
								break;
							case 2:
								cout<<"Entre new department : ";
								cin.clear();
								cin.ignore();
								getline(cin,new_value); 
								a="DEPARTMENT";
								break;
							case 3 :
								cout<<"Entre new age : ";
								cin.clear();
								cin.ignore();
								getline(cin,new_value); 
								a="AGE";
								break;
							default :
								cout<<"Please enter valid code.\n";
								break;}
					}while(code>4);
					crew.update_staff(id,a,new_value);
					break;// Valid train ID, exit the loop
					} else {
						cout << "Invalid train ID. Please enter a valid number." << endl;
					}
				}
			}
		}
		void delete_crew(){
			while (true) {
			cout<<"Entre staff ID you need to delete : ";
			if (cin >> id) {
				// Check if the entered train ID is valid
				if (crew.check_staff(id)) {
						crew.delete_staff(id);
						break;// Valid train ID, exit the loop
					} else {
						cout << "Invalid train ID. Please enter a valid number." << endl;
					}
				}
			}
		}
};
class train_status{
	private:
	database dt_train_status;
	public:
		int id;
		int st;
		string status;
		string time;
		int h,m;

		train_status() : dt_train_status("Train_Management.db")
		{
			// open the database and create tables
			dt_train_status.openDatabase();
		}

		void get_train_status_details(){
			cout<<"\n --- Train Status --- \n";
			while (true) {
			cout << "Enter train ID you need to booking : ";
			if (cin >> id) {
				// Check if the entered train ID is valid
				if (dt_train_status.check_train(id)) {
						do{
							cout<<"\n1. Train Arrive\n2. Train Departure\n3. Train Delay\nSelect train status : ";
							cin>>st;
							switch (st){
							case 1 :
							status="Arrive";
							break;
							case 2 :
							status="Departure";
							break;
							case 3 :
							status="Delay";
							break;
							default :
							cout<<"Please enter valid number.\n";
							break;}
						}while(st>4);
						cout<<"\n--- Entre train "<<status<<" time ---\n";
						cout<<"Time (Hour) : ";
						cin>>h;
						cout<<"Time (Minute) : ";
						cin>>m;
						time =  to_string(h) + "." + to_string(m);
						dt_train_status.insert_train_status(status,time,id);
						break;// Valid train ID, exit the loop
					} else {
						cout << "Invalid train ID. Please enter a valid number." << endl;
					}
				}
			}
			
		}
		void display_train_status() {
			dt_train_status.read_train_status();
		}
};
class incident_record{
	private : 
	database incident;
	public:
		int id;
		string date;
		char reason[100];
		char name[100];
		int d,m,y;

		incident_record() : incident("Train_Management.db") 
		{
			// open the database and create tables
			incident.openDatabase();
		}

		void add_incident_record(){
			cout<<"\n--- Add New Incident Record ---\nTrain ID : ";
			cin>>id;
			cout << "Train Name: ";
			cin.clear();
			cin.ignore();
			cin.getline(name,100);
			cout << "Reason: ";
			cin.clear();
			cin.getline(reason,100);
			cout << "--- Date of incident occur ---\nDay: ";
			cin >> d;
			cout << "Month: ";
			cin >> m;
			cout << "Year: ";
			cin >> y;

			date = to_string(d) + "-" + to_string(m) + "-" + to_string(y);

			incident.insert_incident(name, reason,date);
		}
		void display_incident_record(){
			incident.read_incident();
		}
};

class payment{
	public:
	string payment_type;
	int code;
	
	void select_payment(){
		cout<<"\n--- Payment type ---\n1. Tng\n2. Card\nSelect code of the payment type : ";
		cin>>code;
		if(code ==1) 
			payment_type="Tng";
		else if(code ==2) 
			payment_type="Card";
	} 

	void disply_resit(){
		cout<<"\n--- Receipt ----\n";
		cout<< "Payment type : "<< payment_type<<endl;
		cout<< "Amount : RM 10\n";
	}
};
class feedback{
	public:
		linkedlist_feedback a;
		int id;
		string notice;

		void write_new_feeback(){
			cout<<"\nTrain id : ";
			cin.clear();
			cin>>id;
			cout<<"Add new notice : ";
			cin.clear();
			cin.ignore();
			getline(cin,notice);
			a.pushBack(id,notice);
		}
		string display_feeback() const{
			return a.display();
		}
};
class passenger
{
    public:
		linkedlist_passenger a;
        int age;
        string name;
        int contact_number;
        string gender;

        void getpassenger()
        {
            cout << "\n--- Passenger --\n";
			cout << "Passenger Name:";
			cin.clear();
			cin.ignore();
			getline(cin,name);
            cout << "Passenger Age:";
            cin >> age;
            cout << "Passenger Contact Number:";
			cin>>contact_number;
            cout << "Passenger Gender:";
            cin.clear();
			cin.ignore();
			getline(cin,gender);
			a.pushBack(name,age,gender,contact_number);
        }
        string displaypassenger()const{
			return a.display();
        }

};
class lost_and_found
{
    public:
		linkedlist_lost_and_found a;
        int train_id;
        string item_name;
        string item_detials;
        string passenger_email;

        void getlost_and_found()
        {
			cout << "Train ID:";
            cin >> train_id;
            cout << "Item Name:";
			cin.clear();
			cin.ignore();
			getline(cin,item_name);
            cout << "Item detials:";
            cin.clear();
			cin.ignore();
			getline(cin,item_detials);
            cout << "Passenger Email:";
            cin.clear();
			cin.ignore();
			getline(cin,passenger_email);
			a.pushBack(item_name,train_id,item_detials,passenger_email);
        }
        string displaylost_and_found()const{
            return a.display();
        }
};

void customer();
void login();
void select_feeback(feedback& a);
void select_lost_and_found(lost_and_found& a);
void entre_new_profile(passenger& a);
void cancel();

void admin();
void select_train_status();
void select_train_detail();
void add_crew_details();
void select_incident();
void sign_in_details();
void user_details(feedback& a, passenger& b, lost_and_found& c);

int main(){
	database dt("Train_Management.db");
	dt.open_and_create();
    int code;
    cout << "\n----- RAILWAY RESERVATION SYSTEM ----- \n";
	do{
        cout << "\n MAIN MENU \n";
		cout << "1.Admin\n2.User\n3.Exit \n";
		cout << "Enter your identity : ";
		cin >> code;
		switch(code){
			case 1:
				admin();
				break;
			case 2:
				login();
				break;
			case 3:
				exit(0);
				break;
			default : 
			cout<<"Please enter valid number.\n";
			break;}
	}while(code<3);
}

void admin(){
	passenger b;
    lost_and_found c;
    feedback a;

    char password[10];
	char pass[50] = "admin123";
	cout << "\nEnter the Admin Password: ";
	cin >> password;
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
			cout << "1. Train Details\n";
			cout << "2. Train Status \n";
			cout << "3. Incident\n";
			cout << "4. Crew\n";
			cout << "5. User\n";
			cout << "6. Return to Main Menu \n";
			cout << "Please select your choice : ";
			cin >> code;

			switch(code)
			{
				case 1:
					select_train_detail();
					break;
				case 2:
					select_train_status();
					break;
				case 3:
					select_incident();
					break;
				case 4:
					add_crew_details();
					break;
				case 5:
					user_details(a,b,c);
					break;
			}
		}while(code<6);
	}
}
void select_train_status(){
	train_detail b;
	train_status a;
	int code;
	char y;
	do{
		cout<<"\n--- Entre train status ---\n1. Add new train status\n2. Display train status\n3. Exit";
		cout<<"\nPlease select the code : ";
		cin>>code;
		switch(code) {
			case 1 :
			cout<<"\n";
			b.display_train_detail();
			a.get_train_status_details();
			break;
			case 2 :
			a.display_train_status();
			break;;
		}
	}while (code<3);
}
void select_train_detail(){
	fstream f;
	train_detail a;

	int code;
	char y;
	do{
		cout<<"\n--Select train details--\n1. Add new train\n2. Display train details\n3. Update train details\n4. Add Train Maintenance Time\n5. Display Train Maintenance Time\n6. Back to admin menu";
		cout<<"\nPlease select the code : ";
		cin>>code;
		switch(code) {
			case 1 :
				do
				{
					a.add_new_train();
					cout << "\nDo you want to continue add more train details (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				break;
			case 2:
					a.display_train_detail();
				break;
			case 3:
					a.display_train_detail();
					a.update_train_details();
				break;
			case 4 :
				do
				{
					a.display_train_detail();
					a.add_new_maintain_train();
					cout << "\nDo you want to continue add more train maintain (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				break;
			case 5:
					a.display_maintain_record();
				break;
		}
	}while (code<6);
}
void add_crew_details(){
	fstream f;
	crew_details a;

	int code;
	char y;
	do{
		cout<<"\n--- Crew ---\n1. Add Crew Details\n2. Display Crew Details\n3. Update Crew Details\n4. Delete Crew Details\n5. Back to admin menu";
		cout<<"\nPlease select the code : ";
		cin>>code;
		switch(code) {
			case 1 :
				do
				{
					a.add_new_crew_details();
					cout << "\nDo you want to continue add more crew details (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				break;
			case 2:
				a.display_crew_details();
				break;
			case 3:
				a.display_crew_details();
				a.update_crew_details();
				break;
			case 4:
				a.delete_crew();
				break;
		}
	}while (code<5);
}
void select_incident(){
	fstream f;
	incident_record a;

	int code;
	char y;
	do{
		cout<<"\n--- Incident ---\n1. Add New Incident Record\n2. Display Incident Record\n3. Back to admin menu";
		cout<<"\nPlease select the code : ";
		cin>>code;
		switch(code) {
			case 1 :
				do
				{
					a.add_incident_record();
					cout << "\nDo you want to continue add train incident record (Y/N): \n";
					cin >> y;
				}while(y=='y' || y =='Y');
				break;
			case 2:
				a.display_incident_record();
				break;
		}
	}while (code<3);
}
void sign_in_details() {
    ifstream file("sign_in.txt");
    if (file.is_open()) {
        cout << "\n---User Records---\nUsername"<<setw(20)<<"Password\n";
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                string username = line.substr(0, pos);
                string password = line.substr(pos + 1);
                cout << setw(20) << left << username << "|" << password << endl;
            }
        }
        file.close();
    } else {
        cerr << "Error opening sign_in.txt for reading." << endl;
    }
}
void user_details(feedback& a, passenger& b, lost_and_found& c){
	train_detail t;
	fstream f;

	int code;
	do{
		cout << "\n --- User --- \n";
		cout << "1. Passenger\n";
		cout << "2. Feeback\n";
		cout << "3. Lost and Found\n";
		cout << "4. Ticket View\n";
		cout << "5. Sign in\n";
		cout << "6. Return to Main Menu \n";
		cout << "Please select your choice : ";
		cin >> code;

		switch(code)
		{
			case 1:
					cout<<b.displaypassenger();
				break;
			case 2:
					cout<<a.display_feeback();
				break;
			case 3:
					cout<<c.displaylost_and_found();
				break;
			case 4:
					t.display_all_ticket();
				break;
			case 5:
					sign_in_details();
				break;
		}
	}while(code<6);
}

void login()
{
	const char* dbName = "Train_Management.db";
    database dbManager(dbName);

	while (true) {
		string code;
        cout << "1. Sign Up\n2. Login\n3. Exit\nPlease select your code : ";
        cin>>code;

        if (code == "1") {
            User newUser;
			cin.clear();
        	cin.ignore();
            cout << "Enter username: ";
            getline(cin, newUser.username);
            cout << "Enter password: ";
			cin.clear();
            getline(cin, newUser.password);

			string username=newUser.username;
			string password=newUser.password;

            if (user_sign_in(newUser)) {
                cout << "Account registered successfully." << endl;
				dbManager.insertsignin_data(newUser.username, newUser.password);
            } else {
                cerr << "Failed to register account." << endl;
            }
        } else if (code == "2") {
            string username, password;
			cin.clear();
        	cin.ignore();
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
			cin.clear();
            getline(cin, password);

            if (login(username, password)) {
                cout << "Login successful." << endl;
				customer();
            } else {
                cerr << "Login failed." << endl;
            }

        } else if (code == "3") {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void customer(){
	int code;
	train_detail a;
	payment b;
	feedback c;
	passenger d;
	lost_and_found e;
	do{
	cout<<"\n--- Customer ---\n1. Booking Train\n2. FeedBack\n3. Lost and found\n4. Profile\n5. Ticket\n6. Cancel train booking\n7. Exit\nPlease choose the code : ";
	cin>>code;
	switch(code){
		case 1: 
			a.display_train_detail();
			a.sale_train_seat();
			b.select_payment();
			b.disply_resit();
		break;
		case 2:
			select_feeback(c);
		break;
		case 3:
			select_lost_and_found(e);
		break;
		case 4:
			entre_new_profile(d);
		break;
		case 5:
			a.display_ticket();
		break;
		case 6:
			cancel();
		break;
	}
	}while (code<7);
}

void select_feeback(feedback& a){
	int code;

	cout<<"\n--- Add Feedback ---\n";
	cin>>code;
	char y;
	do
	{
		a.write_new_feeback();
		cout << "\nDo you want to continue add train incident record (Y/N): \n";
		cin >> y;
	}while(y=='y' || y =='Y');
}
void select_lost_and_found(lost_and_found& a){
	char y;
	cout<<"\n--- Lost and Found ---\n---- Entre a new item details ----\n";
	do
	{
		a.getlost_and_found();
		cout << "\nDo you want to continue add more train status (Y/N): \n";
		cin >> y;
	}while(y=='y' || y =='Y');
}
void entre_new_profile(passenger& a){
	char y;
	cout<<"\n--- Profile ---\n";
	do
	{
		a.getpassenger();;
		cout << "\nDo you want to continue add more train status (Y/N): \n";
		cin >> y;
	}while(y=='y' || y =='Y');
}
void cancel(){
	train_detail a;
	a.display_ticket();
	a.cancel_train_seat();
	cout<<"\n--- Cancel ticket ---\n";
	a.display_cancel_ticket();
}
