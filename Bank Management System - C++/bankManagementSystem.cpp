// Bank Management System

#include<bits/stdc++.h>
using namespace std;

set<long long/*account no.*/> accountsLiveset;
set<long long/*card no.*/> cardsLiveset;

class Card { // Card class containing the skeleton for every card.
public:
	long long cardNo; // 10 digits
	int pin; // 4 digits long
	long long accountNo; // 10 digits
	Card(long long accountNo) {
		this->accountNo = accountNo;
		this->pin = 1000 + rand() % 9000;
		long long proposedCard = 1000000000 + (rand() % 9000000000);
		while(cardsLiveset.count(proposedCard)) {
			proposedCard = 1000000000 + (rand() % 9000000000);
		}
		this->cardNo = proposedCard;
	}
};

class Customer { // Customer class containing the skeleton for every customer.
public:
	string name, signature, address, statement;
	long long accountNo; // 10 digits
	double balance;
	vector<Card*> cards;
	Customer(string name, string signature, string address) {
		this->name = name;
		this->signature = signature;
		this->address = address;
		long long proposedAccount = 1000000000 + (rand() % 9000000000);
		while(accountsLiveset.count(proposedAccount)) {
			proposedAccount = 1000000000 + (rand() % 9000000000);
		}
		this->accountNo = proposedAccount;
		this->balance = 5000;
		this->statement = "Account Created Successfully. ";
		cards = vector<Card*>();
	}
};

map<long long/*account no.*/, Customer*/*Customer*/> accountsLive;
map<long long/*card no.*/, Card*/*Cards*/> cardsLive;

void openAccount() { // Opening an account with the bank
	cout<<"Please Fill the form below to open an account."<<endl;
	string name;	cout<<"Please Enter your name : ";	cin>>name;
	string signature;	cout<<"Now, Enter a strong signature : ";	cin>>signature;
	string address;	cout<<"Finally, Enter your Address : ";	cin>>address;
	
	char willPay;	cout<<"Do you wish to pay Rs. 5000 for opening your account? This money will be stored in your account. Type in (y/Y) to proceed : ";	cin>>willPay;
	if(willPay != 'y' and willPay != 'Y') {
		cout<<"We cannot open account without Rs.5000 ..:("<<endl;
		return;
	}
	
	Customer *newCustomer = new Customer(name, signature, address);
	accountsLive.insert({newCustomer->accountNo, newCustomer});
	cout<<"Account created Successfully...:)"<<endl;
	cout<<"Please note your account Number : "<<newCustomer->accountNo<<endl;
	accountsLiveset.insert(newCustomer->accountNo);
}

long long login() { // Logging into bank system using the account no. and signature
    cout<<endl;
	cout<<"Log in..."<<endl;
	long long accountNumber;	cout<<"Please Enter your Account Number : ";	cin>>accountNumber;
	if(accountsLive.find(accountNumber) != accountsLive.end()) {
		string signature;	cout<<"Please Enter your signature : ";	cin>>signature;
		if(signature == accountsLive[accountNumber]->signature) {
			cout<<"User Authenticated. Logging in..."<<endl;
			return accountNumber;
		} else {
			cout<<"Sorry, the signature is invalid..:/"<<endl;
			return 0;
		}
	} else {
		cout<<"Sorry, we donot have this account. You should Register instead."<<endl;
		return 0;
	}
	return 0;
}

int main() {
	
	cout<<endl;
	cout<<"**********Welcome to the Bank Management System**********"<<endl;
	cout<<endl;
	cout<<"*********************************************************"<<endl;
	cout<<endl;
	
	while(true) {
		int isExistingUser;
		cout<<"Please Select an option to proceed further : "<<endl;
		cout<<"1. Open an account - Register."<<endl;
		cout<<"2. Log in as Existing User."<<endl;
		cout<<"3. Use ATM."<<endl;
		cin>>isExistingUser;
		
		switch(isExistingUser) {
			case 1 : {
				openAccount();
				break;
			}
			case 2 : {
				long long accountNo = login();
				if(accountNo) {
					int actions;
					cout<<endl;
					cout<<"Please Select an option to proceed further : "<<endl;
					cout<<"1. Debit"<<endl;
					cout<<"2. Withdrawl"<<endl;
					cout<<"3. Generate Debit Card"<<endl;
					cout<<"4. View Transaction statement"<<endl;
					cin>>actions;
					switch(actions) {
						case 1 : {
							double amount;	cout<<"Enter a amount to debit : ";	cin>>amount;
							accountsLive[accountNo]->balance += amount;
							string statement = "Successfully debited Rs. " + to_string(amount) + " to Account No.: " + to_string(accountNo) + ". ";
							statement += "New Balance is : Rs." + to_string(accountsLive[accountNo]->balance) + ". ";
							accountsLive[accountNo]->statement += statement;
							cout<<statement<<endl;
							break;
						}
						case 2 : {
							double amount;	cout<<"Enter a amount to withdraw : ";	cin>>amount;
							if(accountsLive[accountNo]->balance >= amount)  {
								accountsLive[accountNo]->balance -= amount;
								string statement = "Successfully withdrew Rs. " + to_string(amount) + " from Account No.: " + to_string(accountNo) + ". ";
								statement += "New Balance is : Rs." + to_string(accountsLive[accountNo]->balance) + ". ";
								accountsLive[accountNo]->statement += statement;
								cout<<statement<<endl;
							} else {
								cout<<"Insufficient Balance..:/"<<endl;
							}
							break;
						} 
						case 3 : {
							if(accountsLive[accountNo]->cards.size() == 5) {
								cout<<"You already have 5 cards generated. No more cards can be generated to your account."<<endl;
							} else {
								accountsLive[accountNo]->cards.push_back(new Card(accountNo));
								string statement = "New Card generated. Card No. : " + to_string(accountsLive[accountNo]->cards.back()->cardNo) + ". Pin : " + to_string(accountsLive[accountNo]->cards.back()->pin) + ". ";
								accountsLive[accountNo]->statement += statement;
								cout<<statement<<endl;
								cardsLiveset.insert(accountsLive[accountNo]->cards.back()->cardNo);
								cardsLive.insert({accountsLive[accountNo]->cards.back()->cardNo, accountsLive[accountNo]->cards.back()});
							}
							break;
						}
						case 4 : {
							cout<<"Your Statement : "<<endl;
							cout<<accountsLive[accountNo]->statement<<endl;
							break;
						}
						default : {
							cout<<"Seems like you are lost..:/"<<endl;
							break;
						}
					}
				}
				break;
				cout<<"Logging out..."<<endl;
			}
			case 3 : {
				long long cardNo;	cout<<"Please enter your ATM ID : ";	cin>>cardNo;
				int pin;	cout<<"Now Enter your pin : ";	cin>>pin;
				if(cardsLive.find(cardNo) != cardsLive.end() and cardsLive[cardNo]->pin == pin) {
					long long accountNo = cardsLive[cardNo]->accountNo;
					int atmActions;
					cout<<"Please select an option to proceed further : "<<endl;
					cout<<"1. Withdraw Cash"<<endl;
					cout<<"2. Change Pin"<<endl;
					cout<<"3. Generate Statement"<<endl;
					cin>>atmActions;
					switch(atmActions) {
						case 1 : {
							double amount;	cout<<"Enter a amount to withdraw : ";	cin>>amount;
							if(accountsLive[accountNo]->balance >= amount)  {
								accountsLive[accountNo]->balance -= amount;
								string statement = "Successfully withdrew Rs. " + to_string(amount) + " from Account No.: " + to_string(accountNo) + ". ";
								statement += "New Balance is : Rs." + to_string(accountsLive[accountNo]->balance) + ". ";
								accountsLive[accountNo]->statement += statement;
								cout<<statement<<endl;
							} else {
								cout<<"Insufficient Balance..:/"<<endl;
							}
							break;
						}
						case 2 : {
							string signature;	cout<<"Please Enter your Account Signature : ";	cin>>signature;
							if(accountsLive[accountNo]->signature == signature) {
								int pin;	cout<<"Enter the new pin for your card : ";	cin>>pin;
								cardsLive[cardNo]->pin = pin;
								string statement= "New Pin for ATM Card : " + to_string(cardNo) + " is Pin : " + to_string(pin);
								accountsLive[accountNo]->statement += statement;
								cout<<statement<<endl;
							} else {
								cout<<"Invalid Signature."<<endl;
							}
							break;
						}
						case 3: {
							cout<<"Your Statement : "<<endl;
							cout<<accountsLive[accountNo]->statement<<endl;
							break;
						}
						default : {
							cout<<"Seems like you are lost..:/"<<endl;
							break;
						}
					}
					cout<<"Please take your ATM Card."<<endl;
				} else {
					cout<<"Invalid Credentials..:/"<<endl;
				}
				break;
			}
			default : {
				cout<<"Seems like you are lost..:/"<<endl;
				break;
			}
		}
	    cout<<"*********************************************************"<<endl;
		cout<<endl;
	}
}
