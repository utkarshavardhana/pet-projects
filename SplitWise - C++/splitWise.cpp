// Splitwise - Expense sharing application

#include <bits/stdc++.h>
using namespace std;

class User{
public:
	int id;
	string name;
	map<int, double> owe, credit;
	User(int id, string name) {
		this->id = id;
		this->name = name;
		this->owe = map<int, double> ();
		this->credit = map<int, double> ();
	}
};

int main() {
	int circleSize;
	cout<<"Enter the number of people in circle : ";
	cin>>circleSize;
	
	vector<User*> person(circleSize);
	for(int i=0; i<circleSize; i++) {
		string name;
		cout<<"Enter User "<<i+1<<"'s Name : ";
		cin>>name;
		person[i] = new User(i+1, name);
	}
	
	bool stillSharing = true;
	while(stillSharing) {
		int payee; double amount;
		cout<<"User ";    cin>>payee;
		cout<<"    "<<person[payee-1]->name<<" paid for all Rs.";    cin>>amount;
		
		for(auto user : person) {
			double toPay = amount / circleSize;
			
			if(user->id == payee) {
				for(auto inuser : person) {
					if(inuser->id == user->id)	continue;
					user->owe[inuser->id] -= toPay;
					if(user->owe[inuser->id] >= 0)	continue;
					user->credit[inuser->id] += -1 * user->owe[inuser->id];
					user->owe[inuser->id] = 0;
				}
				continue;
			}
			
			user->credit[payee] -= toPay;
			if(user->credit[payee] >= 0)	continue;
			user->owe[payee] += -1 * user->credit[payee];
			user->credit[payee] = 0;
		}
		
		for(auto user : person) {
			cout<<user->name<<":"<<endl;
			for(auto it=user->owe.begin(); it!=user->owe.end(); it++) {
				cout<<"    owes "<<person[(*it).first-1]->name<<" Rs. "<<(*it).second<<endl;
			}
			for(auto it=user->credit.begin(); it!=user->credit.end(); it++) {
				cout<<"    credits "<<person[(*it).first-1]->name<<" Rs. "<<(*it).second<<endl;
			}
			cout<<endl;
		}
		
		char res;
		cout<<"Want to stop splitting (y/Y) ? ";
		cin>>res;
		if(res == 'y' or res == 'Y')	stillSharing = false;
	}
	return 0;
}
