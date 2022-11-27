#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class salesPeople
{
public:

	//Class attributes
	string staffID;
	string honorific;
	string fName;
	string lName;
	string companyName;
	string currentStaff;
	double valOfPurchases;
	string prevStaff;
	double commisionsValue;

	//Methods

	//Constructor to assign values given when called
	salesPeople(string staffID, string honorific, string fName, string lName, string companyName,
		string currentStaff, double valOfPurchases, string prevStaff, double commisionsValue)
	{
		this->staffID = staffID;
		this->honorific = honorific;
		this->fName = fName;
		this->lName = lName;
		this->companyName = companyName;
		this->currentStaff = currentStaff;
		this->valOfPurchases = valOfPurchases;
		this->prevStaff = prevStaff;
		this->commisionsValue = commisionsValue;


	}

	//Print all atrributes of the Class instance
	void list()
	{
		cout << staffID << " " << honorific << " " << fName << " " << lName << " " << companyName << endl;
		//	<< currentStaff << ", " << ", " << valOfPurchases << ", " << prevStaff << ", " << commisionsValue << endl;
	}

	void listAll()
	{
		cout << staffID << " " << honorific << " " << fName << " " << lName << " " << companyName
			<< currentStaff << ", " << ", " << valOfPurchases << ", " << prevStaff << ", " << commisionsValue << endl;
	}

	//Getters (can't remember proper name lol)
	double getValPurch() { return valOfPurchases; }
	double getValComs() { return commisionsValue; }
	string getStaffID() { return staffID; }
	string getHonorific() { return honorific; }
	string getFName() { return fName; }
	string getLName() { return lName; }
	string getCompanyName() { return companyName; }
	string getCurrentStaff() { return currentStaff; }
	string getPrevStaff() { return prevStaff; }

};
