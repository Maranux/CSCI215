#include "IRS_DB.h"
#include <iostream>

// Simple Tests
int main() {
	IRS_DB db;
	double test = 0;
	string testName = "";
	vector<W2> vect;
	db.insertCompany(1234, "ThinkForward LTD");
	db.insertCompany(1235, "Testerino");
	db.insert(123456, "Shea Rogers");
	db.insert(654321, "Gary Underwood");
	db.addW2(123456, W2(1234, 1200));
	db.addW2(123456, W2(1234, 1100));
	db.addW2(123456, W2(1235, 1200));
	db.print();
	db.updateW2(123456, W2(1234, 120));
	db.getTotalSalary(123456, test);
	cout << test << endl;
	db.getInfo(123456, testName, vect);
	cout << testName << "\n";
	db.getInfo(156, testName, vect);
	cout << testName << "\n";
	db.getCompanyName(1234, testName);
	cout << testName << "\n";
	db.print();
	db.removeCompany(1234);
	db.print();
	db.insertCompany(1234, "ThinkForward LTD");
	db.removeW2(123456, 1234);
	db.print();
	db.removePerson(123456);
	db.print();
	system("PAUSE");
	return 0;
}