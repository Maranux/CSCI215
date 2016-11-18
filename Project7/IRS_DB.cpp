#include "IRS_DB.h"

// Print all info
void IRS_DB::print() const
{
	string comp = "";
	bool comma = false;
	// For each account, output the data
	for (pair<int, account> accItr : data) {
		cout << accItr.first << ": " << accItr.second.name << ", ";
		if (accItr.second.w2l.empty()) cout << "No W2 Forms";
		else {
			for (pair<int, W2> w2Itr :  accItr.second.w2l) {
				getCompanyName(w2Itr.second.id, comp);
				if (!comma) {
					cout << "(" << w2Itr.second << " " << comp << ")";
					comma = true;
				}
				else
				cout << ",(" << w2Itr.second << " " << comp << ")";
			}
		}
		cout << "\n";
		comma = false;
	}
}

// Get info based on an SSN, return a name and the w2s
bool IRS_DB::getInfo(int ssn, string & name, vector<W2>& w2s) const
{
	// SSN not found
	unordered_map<int, account>::const_iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	if (iter == data.end()) { return false; } 
	// SSN found set returns and return true
	name = iter->second.name;
	// Clear in case of previous use
	w2s.clear();
	// For each W2, add it to the vector
	for (pair<int, W2> itr : iter->second.w2l) { // O(1) average, worst case linear with size of container
		w2s.push_back(itr.second);
	}
	return true;
}

// Return the name based on the id
bool IRS_DB::getCompanyName(int id, string & name) const
{
	// ID not found
	unordered_map<int, string>::const_iterator iter = companies.find(id); // O(1) average, worst case linear with size of container
	if (iter == companies.end()) { return false; }
	// ID found set returns and return true
	name = iter->second;
	return true;
}

// Find an SSN based on name
bool IRS_DB::findSSN(const string & name, vector<int>& ids) const
{
	bool ret = false;
	// Iterate through and add all SSNs to the return
	for (pair<int, account> iter : data) {
		if (iter.second.name == name) {
			ids.push_back(iter.first);
			ret = true;
		}
	}
	return ret;
}

// Get the salary based on SSN
bool IRS_DB::getTotalSalary(int ssn, double & salary) const
{
	// Locate the account and save the iterator
	unordered_map<int, account>::const_iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	if (iter == data.end()) return false;
	salary = 0;
	// Add all salaries to salary
	for (unordered_map<int, W2>::const_iterator start = iter->second.w2l.begin(), end = iter->second.w2l.end(); start != end; ++start) {
		salary += start->second.salary;	
	}
	return true;
}
// Insert a person
bool IRS_DB::insert(int ssn, const string & name)
{
	// Inserts the person at the slot with their SSN, returns true if the insert was successful (no duplicate SSN)
	return data.insert({ ssn, account(name) }).second;
}

// Insert a company
bool IRS_DB::insertCompany(int id, const string & name)
{
	return companies.insert({ id, name }).second;
}

// Add a W2 form to a person based on SSN
bool IRS_DB::addW2(int ssn, const W2 & w2Info)
{
	unordered_map<int, account>::iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	W2 temp = w2Info;
	if (iter == data.end()) return false;
	// The input ID is null
	if (w2Info.id == NULL) { return false; }
	// The w2info exists OR company ID does NOT exist
	if (iter->second.w2l.find(w2Info.id) != iter->second.w2l.end() || companies.find(w2Info.id) == companies.end() ) { return false; }
	// Insert the info
	iter->second.w2l.insert({ temp.id, temp });
	return true;
}

// Update a W2 based on SSN
bool IRS_DB::updateW2(int ssn, const W2 & w2info)
{
	// If either the account or the W2 is missing return false
	unordered_map<int, account>::iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	if (iter == data.end()) return false;
	unordered_map<int, W2>::iterator w2 = iter->second.w2l.find(ssn); // O(1) average, worst case linear with size of container
	if (w2 == iter->second.w2l.end()) return false;
	// Update the salary
	w2->second.salary = w2info.salary;
	return true;
}

// Remove a W2 based on SSN and ID
bool IRS_DB::removeW2(int ssn, int id)
{
	// If either the account or the W2 is missing return false
	unordered_map<int, account>::iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	if (iter == data.end()) return false;
	unordered_map<int, W2>::iterator w2 = iter->second.w2l.find(id); // O(1) average, worst case linear with size of container
	if (w2 == iter->second.w2l.end()) return false;
	// Delete the w2
	iter->second.w2l.erase(w2);
	return true;
}

// Remove a person based on SSN
bool IRS_DB::removePerson(int ssn)
{
	unordered_map<int, account>::iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	if (iter == data.end()) return false;
	string name = iter->second.name;
	// Will always be found because it is looking for a pointer, not the contents of the string
	data.erase(iter);
	return true;
}

// Change a name based on SSN
bool IRS_DB::changeName(int ssn, const string &name)
{
	unordered_map<int, account>::iterator iter = data.find(ssn); // O(1) average, worst case linear with size of container
	if (iter == data.end()) return false;	
	return true;
}

// Remove a company based on ID
bool IRS_DB::removeCompany(int id)
{
	// If there is no company with the ID, return false
	unordered_map<int, string>::iterator iter = companies.find(id); // O(1) average, worst case linear with size of container
	if (iter == companies.end()) return false;
	// For each account in data
	for (pair<int, account> accIter : data) {
		// For each W2 in the account, delete any W2 that matches the ID
		for (pair<int, W2> w2Iter : accIter.second.w2l) {
			if (w2Iter.first == id) {
				removeW2(accIter.first, id);
			}
		}
	}
	// Delete the company
	companies.erase(iter);
	return true;
}
