#include <sstream>
#include <vector>
#include <iomanip>
#include "salesPeople.cpp"
using namespace std;

//Find duplicate records in the data
void checkDuplicate(vector<salesPeople*> v_salesPeople)
{
    int numRecords = v_salesPeople.size();
    int dupCount = 0;

    cout << "Count of records: " << numRecords << endl;

    for (int i = 0; i < numRecords; i++)
    {
        for (int o = 0; o < numRecords; o++)
        {
            if (i >= o) continue;//avoids printing duplicate on two of the same records, and avoids printing duplicate twice
            if (v_salesPeople[i]->getStaffID() != v_salesPeople[o]->getStaffID()) continue;

            dupCount += 1;
            cout << "Duplicate account found, account ID is: " << v_salesPeople[i]->getStaffID() << endl;
            cout << "Details 1 (Entry number [" << i << "] ): ";
            v_salesPeople[i]->list();
            cout << "Details 2 (Entry number [" << o << "] ): ";
            v_salesPeople[o]->list();
            cout << endl;

        }

    }

    cout << "Total duplicate IDs: " << dupCount;

}

//Check for fraudulant entries in data
void checkFraud(vector<salesPeople*> v_salesPeople)
{
    int numRecords = v_salesPeople.size();
    int countFraud = 0; 

    double valTotal = 0;
    double comTotal = 0;

    cout << "Count of records: " << numRecords << endl;

    for (int i = 0; i < numRecords; i++)
    {
     
        valTotal = v_salesPeople[i]->getValPurch();
        comTotal = v_salesPeople[i]->getValComs();

        if (comTotal > (valTotal * 0.11))
        {
            countFraud += 1;
            cout << "Entry [" << i << "] is fraudulant: ";
            v_salesPeople[i]->list();
            cout << "Account value             : " << valTotal << endl;
            cout << "Commission value          : " << comTotal << endl;
            cout << "Reasonable commision value: " << valTotal * 0.11 << "\n" << endl;
            
        }
    }

    cout << "Total amount of fraudulant transactions: " << countFraud;

}

//List files in short form
void listFile(vector<salesPeople*> v_salesPeople)
{
    for (int i = 0; i < v_salesPeople.size(); i++)
    {
        cout << "[" << i << "] = ";
        v_salesPeople[i]->list();
    }
}

//prints count of records, total value, and total commision
void checkFile(vector<salesPeople*> v_salesPeople)
{
    int numRecords = v_salesPeople.size();

    //Count Records
    double valTotal = 0;
    double comTotal = 0;
    for (int i = 0; i < numRecords; i++)
    {
        valTotal += v_salesPeople[i]->getValPurch();
        comTotal += v_salesPeople[i]->getValComs();
    }
    cout << "Count of records: " << numRecords << endl;
    cout << fixed << setprecision(2) << "Total value     : " << valTotal << endl;
    cout << "Total commisions: " << comTotal << endl;

}

//Function for option "r - read", returns a vector of class object pointers that are...
//...filled with data from given input file name.
vector<salesPeople*> readFile(string fileName)
{
    //Declare vector of pointers as v_salesPeople
    vector<salesPeople*> v_salesPeople;

    fstream myFile; //Declare variable as fstream
    myFile.open(fileName, ios::in);//Input mode, (Read mode)
    if (myFile.is_open())
    {

        string line;
        while (getline(myFile, line))//Reads a line from myFile, stores it into line variable
        {
            if (line == "") continue; //ignore blank lines

          //can maybe turn into loop using array of pointers
            stringstream ss(line);
            string staffID, honorific, fname, lname, companyName,
                currentStaff, valOfPurchases, prevStaff, commisionsValue;

            getline(ss, staffID, ',');
            getline(ss, honorific, ',');
            getline(ss, fname, ',');
            getline(ss, lname, ',');
            getline(ss, companyName, ',');
            getline(ss, currentStaff, ',');
            getline(ss, valOfPurchases, ',');
            getline(ss, prevStaff, ',');
            getline(ss, commisionsValue, ',');

            //Convert string to double for valOfPurchases and commisionValue so class can accept it
            if (valOfPurchases == "") continue;
            if (commisionsValue == "") continue;
            double f_valOfPurchases = stod(valOfPurchases);
            double f_commisionsValue = stod(commisionsValue);

            //Populating vector
            v_salesPeople.push_back(new salesPeople(staffID, honorific, fname, lname,
                companyName, currentStaff, f_valOfPurchases, prevStaff, f_commisionsValue));

        }

        myFile.close(); //Close file
        cout << "File opened successfully" << endl;

    }

    //Notfiy user if file cannot be opened
    else
    {
        cout << "Unable to open file/file name does not exist" << endl;
    }

    return v_salesPeople;
}

//Iterates through vector of class object pointers and deletes all instances of class objects
void closeFile(vector<salesPeople*> v_salesPeople)
{
    int numRecords = v_salesPeople.size();

    //Delete vector
    for (int i = 0; i < numRecords; i++)
    {
        delete v_salesPeople[i]; v_salesPeople[i] = nullptr;
    }
}

//Prints data sorted by staff ID
vector<salesPeople*> sortList(vector<salesPeople*> v_salesPeople)
{
    //This is basically poorly implemented insertion sort that i wrote before watching the
    //lecture on sorting algorithms, but I also can't be bothered rewriting it. Would probably opt
    //for a bubble sort next time
    int numRecords = v_salesPeople.size();
    vector<salesPeople*> sortv_salesPeople = v_salesPeople;
    int comparisons = 0;

    //Basic sorting, compares 1 element to all others and assigns it a number, then moves it
    //to that place in the vector, repeats for all elements
    for (int i = 0; i < numRecords; i++)
    {
        int elementPos = numRecords - 1; //element position starts at size of vector
        int equalID = 0;


        for (int o = 0; o < numRecords; o++)
        {

            if (stoi(v_salesPeople[i]->getStaffID()) < stoi(v_salesPeople[o]->getStaffID()))
            {
                elementPos -= 1; //position goes down 1 for each elements ID that the current elements ID is less than
            }

            //check if ID number is equal
            if (stoi(v_salesPeople[i]->getStaffID()) == stoi(v_salesPeople[o]->getStaffID()))
            {
                //Store names of the identical ID entries
                string name1 = v_salesPeople[i]->getFName();
                string name2 = v_salesPeople[o]->getFName();

                if (name1.compare(name2) < 0) { equalID += 1; } //If name 1 is alphabetically lower than...
                //...name 2 then add 1 to equalID (which will place it -1 in the vector later)

                if (name1.compare(name2) == 0) //If names are equal just place one below the other, but only on the first find that they are duplicate
                {
                    if (o < i) equalID += 1;
                } 

            }

            comparisons += 2; //+ 2 because it's doing 2 compares (2 if statements)
        }

        sortv_salesPeople[elementPos - equalID] = v_salesPeople[i]; //Place element from salesPeople to sorted position in sortv_salesPeople

        //Cool code for updating line without printing new one every time!!!
        cout << "Sorting files: " << i + 1 << "/" << numRecords << "\r"; 
        std::cout.flush(); 
        
    }
    cout << endl;
    //listFile(sortv_salesPeople); this line use to print the sorted vecttor
    cout << "Sorting complete " << endl;
    cout << "First record: [0] "; sortv_salesPeople[0]->list();
    cout << "Last record : [" << numRecords << "] ";  sortv_salesPeople[numRecords - 1]->list();
    if (numRecords >= 9)
    {
        cout << "Ninth record: [9] "; sortv_salesPeople[8]->list();
    }
    if (numRecords >= 499)
    {
        cout << "499th record: [499] "; sortv_salesPeople[498]->list();
    }
    
    cout << "Number of comparisons: " << comparisons << endl;

    return sortv_salesPeople;

}

void auditFile(vector<salesPeople*> v_salesPeople)
{
    int countBadData = 0; //track number of bad records

    for (int i = 0; i < v_salesPeople.size(); i++) //for each element in vector v_salesPeople
    {
        if (v_salesPeople[i]->getPrevStaff().compare("") == 0) continue;

        string prevStaff = v_salesPeople[i]->getPrevStaff();
        string possibleStaff[6] = { "Brad", "Janet", "Dr Scott", "Rifraf", "Nell", "Eddie" };
        //vector<string> currentStaff = { "Brad", "Janet", "Dr Scott", "Rifraf", "Nell", "Eddie" }; //only works with c++11 :(
        vector<string> v_staffCurrentObj;
        stringstream ss(prevStaff);

        bool goodData = 0;

        while (ss.good()) {
            string substr;
            getline(ss, substr, ':');
            if (substr.compare("") != 0) v_staffCurrentObj.push_back(substr); //this comparison is done because there is a :
            //at end of each previous staff name, so it prevents the program putting an empty string in the vector

        }

        //Iterate through each staff name and check if it matches the possible staff names
        for (int x = 0; x < v_staffCurrentObj.size(); x++) //For each staff name in current class object
        {
            goodData = 0; //reset after each check so program doesn't pass bad data that is in the same line as good data

            for (int y = 0; y < (sizeof(possibleStaff) / sizeof(possibleStaff[0])); y++) //for each possible staff member name...

            {

                if (v_staffCurrentObj[x].compare(possibleStaff[y]) == 0) goodData = 1; //...check if names are equal, if at least 1 matches set goodData to true

            }

            if (goodData == 0) break; //break instead of notifying here so that if theres multiple bad
            //entries for the same line it'll only notify the user once

        }

        if (goodData == 0) //if goodData is false (ie if there wasn't a match in names)
        {
            countBadData += 1;
            cout << "Entry [" << i << "] likely contains bad data: " << endl;
            cout << "Account details        : "; 
            v_salesPeople[i]->list();
            cout << "Potential rubbish data : " << v_salesPeople[i]->getPrevStaff();
            cout << "\n" << endl;
        }
    }

    cout << "Total count of bad data : " << countBadData;
}

void debugListAll(vector<salesPeople*> v_salesPeople)
{
    for (int i = 0; i < v_salesPeople.size(); i++)
    {
        cout << "[" << i << "] = ";
        v_salesPeople[i]->listAll();
    }
}

int main()
{
    //Variables
    string nameOfFile = ""; //code a file selection menu later, if no files don't run readFile()
    vector<salesPeople*> fileLoaded;

    do
    {
        char userInput;
        cout << "How would you like to handle this file?" << endl;
        cout << "E - Exit" << endl;
        cout << "R - Read" << endl;
        cout << "C - Check" << endl;
        cout << "L - List" << endl;
        cout << "F - Fraud" << endl;
        cout << "A - Audit" << endl;
        cout << "D - Duplicates" << endl;
        cout << "S - Sort" << endl;
        cout << "/ - Debug list all" << endl;
        cout << "\nPlease input option: ";
        cin >> userInput;

        cout << "\n------------------------------------------------------------\n" << "\nOption " <<  
            userInput << " selected..." << endl;
        cout << endl;

        if (fileLoaded.size() < 1 && userInput != 'r' && userInput != 'R' && userInput != 'E' && userInput != 'e')
        {
            cout << "File not loaded or file loaded is empty. \nTry reading in a different file or add .txt extension" << endl;
        }
        else 
        {
            switch (userInput)
            {

            case 'E': case 'e':
                cout << "Closing program";
                closeFile(fileLoaded); //Delete class objects before closing program

                return 0;

            case 'R': case 'r':
                //Could have used some directory handling here, but didn't really like doing it...
                //because the directory would be different on someone elses machine. Directory handling code...
                //that looks into the current dir of the c++ file seems to be c++17 only OR is extremely complex 
                cout << "Input file name: ";
                cin >> nameOfFile;
                closeFile(fileLoaded); //Delete class objects before...
                fileLoaded = readFile(nameOfFile); //... creating new class objects, and storing into fileLoaded
                break;

            case 'C': case 'c':
                checkFile(fileLoaded);
                break;

            case 'L': case 'l':
                listFile(fileLoaded);
                break;

            case 'A': case 'a':
                auditFile(fileLoaded);
                break;

            case 'F': case 'f':
                checkFraud(fileLoaded);
                break;

            case 'D': case'd':
                checkDuplicate(fileLoaded);
                break;

            case 'S': case 's':
                fileLoaded = sortList(fileLoaded);
                break;

            case '/':
                debugListAll(fileLoaded);
                break;

            default:
                cout << "Please enter a valid command" << endl;
            }

            
        }
        cout << "\n------------------------------------------------------------\n" << endl;

    } while (true);
}
