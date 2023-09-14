//========================================================
//Name: Nicolaas Dyk
//Date: 02-02-2023
//Desc: Parsing through a .txt file, sorting the data, and
//      displaying requested information back to the user
//========================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct Department
{
    //department id
    int depId;
    //department name
    string depName;
    //building letter
    char buildingLetter;
    //building floor
    int buildingFloor;
    //department phone number
    string depPhoneNumber;
};

struct Employee
{
    //social security number
    string ssn;
    //first name
    string fName;
    //last name
    string lName;
    //middle initial
    char mInitial;
    //city
    string city;
    //state
    string state;
    //age
    int age;
    //gender
    char gender;
    //department info
    Department dep;
};

void readTextFile(vector<Employee>&);

//=======================================================
//Display Functions

void displayMenu();
void displayAllEmployees(vector<Employee>);
void displayOldestEmployee(vector<Employee>);
void displayComputerScienceBuilding(vector<Employee>);
void displayBuildingADepartments(vector<Employee>);
void displayEmployeeSSN(vector<Employee>);
void displayAverageAge(vector<Employee>);

//=======================================================
//Misc Functions

string userChoice();
void displayEmployeeData(vector<Employee>, int);
int findOldestEmployee(vector<Employee>);
int findComputerScienceBuilding(vector<Employee>);
vector<string> findBuildingADepartments(vector<Employee>);
string inputSSN();
int findEmployeeSSN(vector<Employee>, string);
string convertSSN(string);


int main()
{
    //=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //=~= Variable Declaration  =~=
    //=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    
    //bool to keep the program running
    bool keepRunning = true;
    //stores the user's choice of options
    string choice;

    //=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //=~= Setting Up The Vector =~=
    //=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    
    //Creates a vector and stores all of the employee's data inside of it
    vector<Employee> listOfEmployees;
    readTextFile(listOfEmployees);
    
    //=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //=~=   Displaying Menus    =~=
    //=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    
    //Displays a menu that shows the user their options on what to display of the data
    displayMenu();

    //Starts a loop to keep the program running as long as necessary
    while (keepRunning)
    {
        //Get the user's choice
        choice = userChoice();

        //Run different functions based on what the user chose
        if (choice == "-999")
        {
            keepRunning = !keepRunning;
        }
        if (choice == "0")
        {
            displayMenu();
        }
        if (choice == "1")
        {
            displayAllEmployees(listOfEmployees);
        }
        if (choice == "2")
        {
            displayOldestEmployee(listOfEmployees);
        }
        if (choice == "3")
        {
            displayComputerScienceBuilding(listOfEmployees);
        }
        if (choice == "4")
        {
            displayBuildingADepartments(listOfEmployees);
        }
        if (choice == "5")
        {
            displayEmployeeSSN(listOfEmployees);
        }
        if (choice == "6")
        {
            displayAverageAge(listOfEmployees);
        }
    }
}

//Parses the text file and stores the data into listOfEmployees
void readTextFile(vector<Employee>& listOfEmployees)
{
    //Declaring Variables
    ifstream inputFile;
    const string fileName = "EmployeeList.txt";
    string lineOfText;
    char delim = ',';
    int commaPos;
    int i = 0;

    //Opening the file, whose name is stored in fileName
    inputFile.open(fileName);

    //Check to see if the file is open
    if (inputFile)
    {
        //cout << "File Open" << endl;
        
        //Runs as long as there is another line of text to get
        while (getline(inputFile, lineOfText))
        {
            //Fields go in order of:
            //ssn, fName, lName, mInitial, city, state, age, gender, dep.depId, dep.depName, dep.buildingLetter, dep.buildingFloor, dep.depPhoneNumber

            //Start by adding a new position in listOfEmployees to store one employee's data
            listOfEmployees.push_back(Employee());

            //Next, find the earliest comma in this line of text
            commaPos = lineOfText.find(delim);
            //Then, add everything before the comma into string ssn in your employee
            listOfEmployees.at(i).ssn = lineOfText.substr(0, commaPos);
            //Finally, delete everything from the beginning of the string to the comma, and store it back into lineOfText
            lineOfText = lineOfText.substr(commaPos + 1);

            //Now we repeat the same process for every other piece of data
            //First Name (fName):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).fName = lineOfText.substr(0, commaPos);
            lineOfText = lineOfText.substr(commaPos + 1);

            //Last Name (lName):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).lName = lineOfText.substr(0, commaPos);
            lineOfText = lineOfText.substr(commaPos + 1);

            //For chars, finding the comma is unnecessary, as it will always be in the same place at this point
            //Middle Initial (mInitial):
            listOfEmployees.at(i).mInitial = (lineOfText.substr(0, 1))[0];
            lineOfText = lineOfText.substr(2);

            //City (city):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).city = lineOfText.substr(0, commaPos);
            lineOfText = lineOfText.substr(commaPos + 1);

            //State (state):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).state = lineOfText.substr(0, commaPos);
            lineOfText = lineOfText.substr(commaPos + 1);

            //Age (age):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).age = stoi(lineOfText.substr(0, commaPos));
            lineOfText = lineOfText.substr(commaPos + 1);

            //Gender (gender):
            listOfEmployees.at(i).gender = lineOfText.substr(0, 1)[0];
            lineOfText = lineOfText.substr(2);

            //Department ID (dep.depId):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).dep.depId = stoi(lineOfText.substr(0, commaPos));
            lineOfText = lineOfText.substr(commaPos + 1);

            //Department Name (dep.depName):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).dep.depName = lineOfText.substr(0, commaPos);
            lineOfText = lineOfText.substr(commaPos + 1);

            //Building Letter (dep.buildingLetter):
            listOfEmployees.at(i).dep.buildingLetter = lineOfText.substr(0, 1)[0];
            lineOfText = lineOfText.substr(2);

            //Building Floor (dep.buildingFloor):
            commaPos = lineOfText.find(delim);
            listOfEmployees.at(i).dep.buildingFloor = stoi(lineOfText.substr(0, commaPos));
            lineOfText = lineOfText.substr(commaPos + 1);

            //Final item on the list does not have a comma
            //Department Phone Number (dep.depPhoneNumber):
            listOfEmployees.at(i).dep.depPhoneNumber = lineOfText;

            i++;
        }

        inputFile.close();
    }
    else
    {
    //cout << "File Not Open" << endl;
    }
}

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=       Display Functions       =~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

//Displays the menu to the user
//=~=~= OPTION 0 =~=~=
void displayMenu()
{
    system("CLS");
    cout << "      EMPLOYEE INFORMATION MANAGER" << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    cout << "   1. Display All Employees" << endl;
    cout << "   2. Display Name Of Oldest Employee" << endl;
    cout << "   3. Display The Building Letter And Floor For Computer Science Department" << endl;
    cout << "   4. Display Department Names Who Are In Building A" << endl;
    cout << "   5. Find An Employee And List Their Information" << endl;
    cout << "   6. Average Age Of Employees Who Live In Michigan" << endl;
    cout << "   0. Display Menu" << endl;
    cout << "-999. Exit The Program" << endl;
}

//Displays all of the information about every employee on the list
//=~=~= OPTION 1 =~=~=
void displayAllEmployees(vector<Employee> listOfEmployees)
{
    system("CLS");
    for (int i = 0; i < listOfEmployees.size(); i++)
    {
        displayEmployeeData(listOfEmployees, i);
    }
}

//Displays the name and age of the oldest employee
//=~=~= OPTION 2 =~=~=
void displayOldestEmployee(vector<Employee> listOfEmployees)
{
    Employee oldest = listOfEmployees.at(findOldestEmployee(listOfEmployees));
    //Displays the name of that employee
    system("CLS");
    cout << "Oldest Employee Data" << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    cout << "Name : " << oldest.fName << " " << oldest.mInitial << ". " << oldest.lName << endl;
    cout << "SSN  : " << oldest.ssn << endl;
    cout << "Age  : " << oldest.age << endl;
}

//Displays the Building Letter and Building Floor of the Computer Science building
//=~=~= OPTION 3 =~=~=
void displayComputerScienceBuilding(vector<Employee> listOfEmployees)
{
    //Find the first employee in the Computer Science department
    int employeeNumber = findComputerScienceBuilding(listOfEmployees);

    if (employeeNumber != -1)
    {
        Employee compSci = listOfEmployees.at(employeeNumber);
        //Display the information about the Computer Science building
        system("CLS");
        cout << "Computer Science Building" << endl;
        cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
        cout << "Building Letter : " << compSci.dep.buildingLetter << endl;
        cout << "Building Floor  : " << compSci.dep.buildingFloor << endl;
    }
    else
    {
        system("CLS");
        cout << "Computer Science Building" << endl;
        cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
        cout << "No Valid Computer Science Building Found" << endl;
    }
}

//Displays all departments in building A
//=~=~= OPTION 4 =~=~=
void displayBuildingADepartments(vector<Employee> listOfEmployees)
{
    //Create a vector and store in it the departments in building A
    vector<string> listOfDepartments = findBuildingADepartments(listOfEmployees);

    //Display the departments
    system("CLS");
    cout << "Building A Departments" << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    if (listOfDepartments.size() == 0)
    {
        cout << "No Valid Building A Departments Found" << endl;
    }
    else
    {
        for (int i = 0; i < listOfDepartments.size(); i++)
        {
            cout << listOfDepartments.at(i) << endl;
        }
    }

}

//Displays the details of an employee based off of the user's ssn input
//=~=~= OPTION 5 =~=~=
void displayEmployeeSSN(vector<Employee> listOfEmployees)
{
    //Variable to hold user's inputted social security number
    string ssn, tempSSN;
    //Keeps track of whether the ssn was found
    bool found = false;
    //Stores the vector location of the employee
    int employeeLocation;

    tempSSN = inputSSN();
    ssn = convertSSN(tempSSN);

    employeeLocation = findEmployeeSSN(listOfEmployees, ssn);

    //If the employee is found, it tell the user all of the information
    if (employeeLocation != -1)
    {
        cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
        displayEmployeeData(listOfEmployees, employeeLocation);
    }
    //If the employee is not found, it informs the user that the employee was not found
    else
    {
        cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
        cout << "The employee with an ssn of " << tempSSN << " does not exist" << endl;
    }
}

//Displays the average age of all employees in MI
//=~=~= OPTION 6 =~=~=
void displayAverageAge(vector<Employee> listOfEmployees)
{
    //Keeps count of the total of all of the ages
    int count = 0;
    //Keeps count of all the employees that live in MI
    int miEmployees = 0;

    //Finds all employees in Michigan and adds their age to a counter
    for (int i = 0; i < listOfEmployees.size(); i++)
    {
        if (listOfEmployees.at(i).state == "MI")
        {
            count += listOfEmployees.at(i).age;
            miEmployees++;
        }
    }

    //Display the average age of the employees in MI
    system("CLS");
    cout << "Average Age Of MI Employees" << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    cout << "Average Age: " << double(count) / double(miEmployees) << endl;
}

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=    Miscellaneous Functions    =~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

//Takes the user's input on which option in the menu they wish to run
string userChoice()
{
    string choice;

    cout << "Enter Your Selection (0 for menu, -999 to exit): ";
    cin >> choice;
    return choice;
}

//Displays all of an employee's data when given the list of employees
//and the employee's number in the vector
void displayEmployeeData(vector<Employee> listOfEmployees, int empNum)
{
    cout << "Employee #" << setfill('0') << setw(log10(listOfEmployees.size()) + 1) << empNum << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    cout << "SSN             : " << listOfEmployees.at(empNum).ssn << endl;
    cout << "First Name      : " << listOfEmployees.at(empNum).fName << endl;
    cout << "Last Name       : " << listOfEmployees.at(empNum).lName << endl;
    cout << "Middle Initial  : " << listOfEmployees.at(empNum).mInitial << endl;
    cout << "City            : " << listOfEmployees.at(empNum).city << endl;
    cout << "State           : " << listOfEmployees.at(empNum).state << endl;
    cout << "Age             : " << listOfEmployees.at(empNum).age << endl;
    cout << "Gender          : " << listOfEmployees.at(empNum).gender << endl;
    cout << "Department ID   : " << listOfEmployees.at(empNum).dep.depId << endl;
    cout << "Department Name : " << listOfEmployees.at(empNum).dep.depName << endl;
    cout << "Building Letter : " << listOfEmployees.at(empNum).dep.buildingLetter << endl;
    cout << "Building Floor  : " << listOfEmployees.at(empNum).dep.buildingFloor << endl;
    cout << "Phone Number    : " << listOfEmployees.at(empNum).dep.depPhoneNumber << endl;
    cout << endl << endl;
}

//Finds the oldest employee, and returns the vector position of the employee
int findOldestEmployee(vector<Employee> listOfEmployees)
{
    int oldestEmployeeNumber = 0;
    int oldestEmployeeAge = listOfEmployees.at(0).age;
    for (int i = 0; i < listOfEmployees.size(); i++)
    {
        if (listOfEmployees.at(i).age > oldestEmployeeAge)
        {
            oldestEmployeeAge = listOfEmployees.at(i).age;
            oldestEmployeeNumber = i;
        }
    }
    return oldestEmployeeNumber;
}

//Finds the first employee in the vector that works in the Computer Science
//building, and returns the vector position of that employee
int findComputerScienceBuilding(vector<Employee> listOfEmployees)
{
    //Find the first employee that works in the Computer Science department
    int employeeNumber = -1;
    for (int i = 0; i < listOfEmployees.size() && i != -999; i++)
    {
        if (listOfEmployees.at(i).dep.depName == "Computer Science")
        {
            employeeNumber = i;
            i = -999;
        }
    }
    return employeeNumber;
}

//Finds all of the departments in building A, and returns them in a vector
vector<string> findBuildingADepartments(vector<Employee> listOfEmployees)
{
    //Create a vector to store the departments in building A
    vector<string> listOfDepartments;

    //Add any departments to the list as long as they have not been added before
    for (int i = 0; i < listOfEmployees.size(); i++)
    {
        if (listOfEmployees.at(i).dep.buildingLetter == 'A')
        {
            bool unentered = true;
            for (int j = 0; j < listOfDepartments.size(); j++)
            {
                if (listOfDepartments.at(j) == listOfEmployees.at(i).dep.depName)
                {
                    unentered = false;
                }
            }
            if (unentered)
            {
                listOfDepartments.push_back(listOfEmployees.at(i).dep.depName);
            }
        }
    }

    return listOfDepartments;
}

//Asks the user to input a social security number for Option 5
string inputSSN()
{
    string ssn;
    //Asks the user to enter the ssn of the employee
    system("CLS");
    cout << "Employee Finder" << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    cout << "Enter the ssn for the employee: ";
    cin >> ssn;

    return ssn;
}

//Finds an employee based on the inputted ssn, 
//and returns the vector position of the employee
int findEmployeeSSN(vector<Employee> listOfEmployees, string ssn)
{
    int employeeLocation = -1;
    for (int i = 0; i < listOfEmployees.size() && i != -999; i++)
    {
        string currentSSN = convertSSN(listOfEmployees.at(i).ssn);
        if (currentSSN == ssn)
        {
            employeeLocation = i;
            i = -999;
        }
    }

    return employeeLocation;
}

//Takes an SSN and turns it into only numbers, to avoid mistakes when inputting an employee's SSN
string convertSSN(string ssn)
{
    string newSSN;
    for (int i = 0; i < ssn.length(); i++)
    {
        if (isdigit(ssn.at(i)))
        {
            newSSN = newSSN + ssn.at(i);
        }
    }
    return newSSN;
}