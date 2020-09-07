// Library Management System

#include<bits/stdc++.h>
using namespace std;

unordered_map<string/*admin ID*/, string/*admin password*/> students;
unordered_map<string/*student ID*/, set<string>/*Set of Books Issued*/> issueRegister;
unordered_map<string/*book ID*/, long long/*Issue DateTime*/> issueTime;

int main() {
	cout<<endl;
	cout<<"**********Welcome to Library Management System**********"<<endl;
	cout<<endl;
	cout<<"********************************************************"<<endl;
	cout<<endl;
	students.insert({"admin", "password"});
	while(true) {
		char loginSignUp;
		cout<<"Would you like to Login(l/L) or Register(r/R) ? ";	cin>>loginSignUp;
		if(loginSignUp == 'l' or loginSignUp == 'L') {
			string sid, spass;
			cout<<"Please Enter your ID : ";
			cin>>sid;
			cout<<"Now Enter your Password : ";
			cin>>spass;
			if(students.find(sid) != students.end()) {
				if(students[sid] == spass) {
					cout<<"Log in Successful..:)"<<endl;
					int actions;
					cout<<"Type in a number to do following actions :"<<endl; 
					cout<<"1. Issue Books "<<endl;
					cout<<"2. Return Books"<<endl;
					cin>>actions;
					switch(actions) {
						case 1 : {
							int totalFine = 0;
							long long currDate;
							cout<<"Enter current DateTime : ";	cin>>currDate;
							for(auto i=issueRegister[sid].begin(); i!=issueRegister[sid].end(); i++) {
								totalFine += (currDate - issueTime[*i]) / 6000000;
							}
							char willPayFine;
							cout<<"You have to pay fine of Rs."<<totalFine<<", Before you issue any book (y/Y) ? "<<endl;	cin>>willPayFine;
							if(willPayFine == 'y' or willPayFine == 'Y') {
								for(auto i=issueRegister[sid].begin(); i!=issueRegister[sid].end(); i++) {
							    	issueTime[*i] = currDate;
							    }
								cout<<"Fine Paid. ";
								if(issueRegister[sid].size() == 5) {
									cout<<"Can't issue more books. Firstly return the books already issued to you..:("<<endl;
								} else {
									cout<<"Enter Book ID for book to be issued : ";
									string bookToIssue;
									cin>>bookToIssue;
									if(issueTime[bookToIssue]) {
										cout<<"Can't issue. This book is already issued to someone."<<endl;
									} else {
										issueRegister[sid].insert(bookToIssue);
									    issueTime[bookToIssue] = currDate;
									    cout<<"Book : "<<bookToIssue<<" successfully issued..:)"<<endl;
									}
								}
							} else {
								cout<<"Fine not paid. Can't issue Book"<<endl;
							}
							break;
						}
						case 2 : {
							string bookToReturn;
							bool successfullyReturned = false;
							cout<<"Enter the Book ID of book you want to return : ";
							cin>>bookToReturn;
							if(issueRegister[sid].count(bookToReturn)) {
								long long currDate;
								cout<<"Enter current DateTime : ";	cin>>currDate;
								char willPayFine;
								cout<<"You have to pay fine of Rs."<<(currDate - issueTime[bookToReturn]) / 6000000<<" (y/Y) ? "<<endl;	cin>>willPayFine;
								if(willPayFine == 'y' or willPayFine == 'Y')	successfullyReturned = true;
								if(successfullyReturned) {
									issueRegister[sid].erase(bookToReturn);
									issueTime.erase(bookToReturn);
									cout<<"Successfully Returned Book : "<<bookToReturn<<endl;
								} else {
									cout<<"Failed to return Book : "<<bookToReturn<<endl;
								}
								
							} else {
								cout<<"You donot have that book issued"<<endl;
							}
							break;
						}
						default : {
							cout<<"It seems you are lost"<<endl;
							break;
						}
					}
					cout<<"Logging out..."<<endl;
				} else {
					cout<<"Password's incorrect..:("<<endl;
				}
			} else {
				cout<<"You need to get yourself registered before accessing the system. Thank you..:)"<<endl;
			}
		} else if(loginSignUp == 'r' or loginSignUp == 'R') {
			string userid, userpass;
			cout<<"Enter a user ID : ";
			cin>>userid;
			
			if(students.find(userid) != students.end()) {
				cout<<"This User exists in System, Login Instead."<<endl;
			} else {
				cout<<"Enter a strong password : ";
				cin>>userpass;
				students[userid] = userpass;
				cout<<"User Created Successfully"<<endl;
			}
		} else {
			cout<<"You are lost..:/"<<endl;
		}
		cout<<"********************************************************"<<endl;
		cout<<endl;
		
	}	
	return 0;
}
