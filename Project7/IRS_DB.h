#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct W2 {
	W2(int i, double s) {
		id = i;
		salary = s;
	}
	int id;
	double salary;
	friend ostream& operator<<(ostream &st, const W2 &w2) {
		st << w2.id << "-" << w2.salary;
		return st;
	}
};
struct account {
	account() {}
	account(string n) {
		name = n;
	}
	string name;
	// Have duplicate values (the id) due to added speed of general access
	unordered_map<int, W2> w2l;
};
//struct company {
//	company(string n) {
//		name = n;
//	}
//	string name;
//};

class IRS_DB {
public:
	// SSN / Account Info
	unordered_map<int, account> data;
	// ID / Name
	unordered_map<int, string> companies;
	bool empty() const { return data.empty(); }  //returns true iff there are no Person entries
	int sizePerson() const { return data.size(); }  //returns number of people
	int sizeCompany() const { return companies.size(); } //returns number of companies
	void print() const; //prints out all person data, details below

	bool getInfo(int ssn, string &name, vector<W2> &w2s) const;
	//if ssn exists then sets name and w2s to that persons data and returns true, else returns false
	bool getCompanyName(int id, string &name) const;//if company id exists set name to its name and return true, else return false

	bool findSSN(const string &name, vector<int> &ids) const;//return false if name isn't a person
															 //else sets ids to be vector of all ssns that have name and returns true
															 //more than one person can have the same name
	bool getTotalSalary(int ssn, double &salary) const; //if ssn exists then
														//set salary = sum of all W2s for ssn and return true else return false

	bool insert(int ssn, const string &name);//insert person with ssn and name, return false if ssn already present
	bool insertCompany(int id, const string &name);//insert company with id and name, return false if id already present

	bool addW2(int ssn, const W2 &w2Info);//add a W2 form for ssn, return false if ssn doesn't exist, w2Info.id doesn't exist, or ssn already has a w2 for w2Info.id
	bool updateW2(int ssn, const W2 &w2info);//return true iff ssn exists and w2info.id is already a w2 of ssn and update salary
	bool removeW2(int ssn, int id); //remove W2 with id from person ssn, return true iff ssn exists and has a W2 with that id 

	bool removePerson(int ssn);  //delete ssn from database, return true iff ssn exist, make sure findSSN(name) no longer lists ssn for name

	bool changeName(int ssn, const string &name); //change name of person to name, return true iff ssn exists, make sure findSSN(name) no longer lists ssn for name
	bool removeCompany(int id);  //Bonus, remove company from database, remove all W2s that reference it, return true iff id exists
};
