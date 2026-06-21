#include <iostream> 
#include <fstream>   
#include <string>    
#include <cstring>   
#include <iomanip>    
using namespace std;

const int MAX = 100;
const int MAX_STR = 100;
const int MAX_CAT = 5;

string ID[MAX];
string Name[MAX];
string CNIC[MAX];
string Phone[MAX];
string Address[MAX];
string Category[MAX];
string Details[MAX];
string Date[MAX];
string Status[MAX];
int Count = 0;
int nextID = 1001;

void pauseScreen()
{
    cout << "Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

string ComplaintID()
{
    string id = "CMP";
    int num = nextID;
    string numStr = "";

    while (num > 0)
    {
        numStr = char((num % 10) + 48) + numStr;
        num = num / 10;
    }

    id = id + numStr;
    nextID++;
    return id;
}

bool ValidCNIC(string cnic)
{
    if (cnic.length() != 13)
    {
        return false;
    }

    for (int i = 0; i < cnic.length(); i++)
    {
        if (cnic[i] < '0' || cnic[i] > '9')
        {
            return false;
        }
    }

    return true;
}

bool ValidPhone(string phone)
{
    if (phone.length() != 11)
    {
        return false;
    }

    for (int i = 0; i < phone.length(); i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return false;
        }
    }

    return true;
}

int findComplaintIndex(string id)
{
    for (int i = 0; i < Count; i++)
    {
        if (ID[i] == id)
        {
            return i;
        }
    }
    return -1;
}

bool ValidDate(string date)
{
    if (date.length() != 10) { return false; }

    for (int i = 0; i < date.length(); i++)
    {
        if (i == 2 || i == 5)
        {
            if (date[i] != '/') return false;
        }
        else
        {
            if (date[i] < '0' || date[i] > '9') return false;
        }
    }
    return true;
}

void showAdminMenu()
{
    cout << "--------------------------------------------------" << endl;
    cout << setw(35) << "ADMIN MENU" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1.  Search Complaint" << endl;
    cout << "2.  Update Case Status" << endl;
    cout << "3.  Delete Complaint Record" << endl;
    cout << "4.  Display All Complaints" << endl;
    cout << "5.  Search by Name" << endl;
    cout << "6.  Category-wise Report" << endl;
    cout << "7.  Pending / Resolved Report" << endl;
    cout << "8.  Load Data From File" << endl;
    cout << "9.  Save Data To File" << endl;
    cout << "0.  Logout" << endl;
    cout << "--------------------------------------------------" << endl;
}

void showPublicMenu()
{
    cout << "--------------------------------------------------" << endl;
    cout << setw(35) << "PUBLIC MENU" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1.  Register New Complaint" << endl;
    cout << "2.  Check Complaint Status" << endl;
    cout << "0.  Exit" << endl;
    cout << "--------------------------------------------------" << endl;
}

void showMainMenu()
{
    cout << "--------------------------------------------------" << endl;
    cout << setw(35) << "MAIN MENU" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1.  Admin Login" << endl;
    cout << "2.  Public Access (Register Complaint)" << endl;
    cout << "0.  Exit" << endl;
    cout << "--------------------------------------------------" << endl;
}

bool adminLogin()
{
    string user, pass;
    int attempts = 0;

    cout << "**************************************************" << endl;
    cout << setw(35) << "ADMIN LOGIN" << endl;
    cout << "**************************************************" << endl;

    while (attempts < 3)
    {
        cout << "Enter Username : ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> pass;

        if (user == "admin" && pass == "1234")
        {
            cout << "\nLogin Successful! Welcome Admin.\n" << endl;
            return true;
        }
        else
        {
            attempts++;
            cout << "\nInvalid credentials! Attempts left : " << (3 - attempts) << endl;
        }
    }

    cout << "\nToo many failed attempts! Returning to main menu...\n" << endl;
    return false;
}

bool checkDuplicateName(string name)
{
    for (int i = 0; i < Count; i++)
    {
        if (Name[i] == name)
        {
            return true;
        }
    }
    return false;
}

void showPreviousComplaintsByName(string name)
{
    int count = 0;

    for (int i = 0; i < Count; i++)
    {
        if (Name[i] == name)
        {
            count++;
        }
    }

    if (count > 0)
    {
        cout << "\n*** ALERT: This person already has " << count << " complaint(s) registered! ***\n" << endl;
        cout << "Previous Complaint(s) Details :\n" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int i = 0; i < Count; i++)
        {
            if (Name[i] == name)
            {
                cout << "Complaint ID:    " << ID[i] << endl;
                cout << "CNIC:            " << CNIC[i] << endl;
                cout << "Category:        " << Category[i] << endl;
                cout << "Date:            " << Date[i] << endl;
                cout << "Status:          " << Status[i] << endl;
                cout << "Details:         " << Details[i] << endl;
                cout << "--------------------------------------------------" << endl;
            }
        }
    }
}

void registerComplaint()
{
    if (Count >= MAX)
    {
        cout << "\nError: Maximum complaint limit reached!\n" << endl;
        return;
    }

    string tempName;

    cout << "==================================================" << endl;
    cout << setw(35) << "REGISTER NEW COMPLAINT" << endl;
    cout << "==================================================" << endl;

    cin.ignore();
    cout << "Enter Complainant Name: ";
    getline(cin, tempName);

    if (checkDuplicateName(tempName))
    {
        showPreviousComplaintsByName(tempName);

        char choice;
        cout << "\nDo you still want to register a new complaint ? (Y / N) : ";
        cin >> choice;

        if (choice != 'Y' && choice != 'y')
        {
            cout << "\nRegistration cancelled.\n" << endl;
            return;
        }
        cin.ignore();
    }

    Name[Count] = tempName;

    do
    {
        cout << "Enter CNIC (13 digits without dashes): ";
        cin >> CNIC[Count];
        if (!ValidCNIC(CNIC[Count]))
        {
            cout << "Invalid CNIC! Must be exactly 13 digits.\n" << endl;
        }
    } while (!ValidCNIC(CNIC[Count]));

    do
    {
        cout << "Enter Phone Number (11 digits): ";
        cin >> Phone[Count];
        if (!ValidPhone(Phone[Count]))
        {
            cout << "Invalid Phone! Must be exactly 11 digits.\n" << endl;
        }
    } while (!ValidPhone(Phone[Count]));

    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, Address[Count]);

    int catChoice;
    cout << "\nSelect Complaint Category :\n";
    cout << "1. Theft\n";
    cout << "2. Robbery\n";
    cout << "3. Assault\n";
    cout << "4. Fraud\n";
    cout << "5. Other\n";
    cout << "Enter choice (1-5): ";
    cin >> catChoice;
    while (cin.fail() || catChoice < 1 || catChoice > 5)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter again (1-5): ";
        cin >> catChoice;
    }

    switch (catChoice)
    {
    case 1: Category[Count] = "Theft"; break;
    case 2: Category[Count] = "Robbery"; break;
    case 3: Category[Count] = "Assault"; break;
    case 4: Category[Count] = "Fraud"; break;
    case 5: Category[Count] = "Other"; break;
    }

    cout << "Enter Complaint Details: ";
    cin.ignore();
    getline(cin, Details[Count]);

    do
    {
        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> Date[Count];
        if (!ValidDate(Date[Count]))
        {
            cout << "Invalid Date! Must be exactly 10 digits(DD/MM/YYYY).\n" << endl;
        }
    } while (!ValidDate(Date[Count]));

    ID[Count] = ComplaintID();
    Status[Count] = "Pending";

    

    cout << "\nComplaint registered successfully!\n" << endl;
    cout << "Your Complaint ID is: " << ID[Count] << endl;
    cout << "Please save this ID for future reference.\n" << endl;
    Count++;
}

void searchComplaint()
{
    string searchID;
    int index;

    cout << "==================================================" << endl;
    cout << setw(35) << "SEARCH COMPLAINT" << endl;
    cout << "==================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    cout << "\nEnter Complaint ID to search : ";
    cin >> searchID;

    index = findComplaintIndex(searchID);

    if (index == -1)
    {
        cout << "\nComplaint not found!\n" << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Complaint ID:    " << ID[index] << endl;
    cout << "Name:            " << Name[index] << endl;
    cout << "CNIC:            " << CNIC[index] << endl;
    cout << "Phone:           " << Phone[index] << endl;
    cout << "Address:         " << Address[index] << endl;
    cout << "Category:        " << Category[index] << endl;
    cout << "Details:         " << Details[index] << endl;
    cout << "Date:            " << Date[index] << endl;
    cout << "Status:          " << Status[index] << endl;
    cout << "--------------------------------------------------" << endl;
}

void searchByName()
{
    string searchName;
    int count = 0;

    cout << "==================================================" << endl;
    cout << setw(35) << "SEARCH BY NAME" << endl;
    cout << "==================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    cout << "\nEnter Name to search : ";
    cin.ignore();
    getline(cin, searchName);

    for (int i = 0; i < Count; i++)
    {
        if (Name[i] == searchName)
        {
            count++;
        }
    }

    if (count == 0)
    {
        cout << "\nNo complaints found for this name!\n" << endl;
        return;
    }

    cout << "**************************************************" << endl;
    cout << "Found " << count << " complaint(s) for: " << searchName << endl;
    cout << "**************************************************" << endl;

    for (int i = 0; i < Count; i++)
    {
        if (Name[i] == searchName)
        {
            cout << "--------------------------------------------------" << endl;
            cout << "Complaint ID:    " << ID[i] << endl;
            cout << "CNIC:            " << CNIC[i] << endl;
            cout << "Phone:           " << Phone[i] << endl;
            cout << "Address:         " << Address[i] << endl;
            cout << "Category:        " << Category[i] << endl;
            cout << "Details:         " << Details[i] << endl;
            cout << "Date:            " << Date[i] << endl;
            cout << "Status:          " << Status[i] << endl;
            cout << "--------------------------------------------------" << endl;
        }
    }
}

void updateComplaint()
{
    string updateID;
    int index;
    int statusChoice;

    cout << "==================================================" << endl;
    cout << setw(35) << "UPDATE CASE STATUS" << endl;
    cout << "==================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    cout << "\nEnter Complaint ID to update : ";
    cin >> updateID;

    index = findComplaintIndex(updateID);

    if (index == -1)
    {
        cout << "\nComplaint not found!\n" << endl;
        return;
    }

    cout << "\nCurrent Status : " << Status[index] << endl;
    cout << "\nSelect New Status :\n";
    cout << "1. Pending\n";
    cout << "2. In Progress\n";
    cout << "3. Resolved\n";
    cout << "Enter choice (1-3): ";
    cin >> statusChoice;

    while (cin.fail() || statusChoice < 1 || statusChoice > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter again (1-3): ";
        cin >> statusChoice;
    }

    if (statusChoice == 1)
    {
        Status[index] = "Pending";
    }
    else if (statusChoice == 2)
    {
        Status[index] = "In Progress";
    }
    else if (statusChoice == 3)
    {
        Status[index] = "Resolved";
    }

    cout << "\nStatus updated successfully!\n" << endl;
    cout << "New Status: " << Status[index] << endl;
}

void deleteComplaint()
{
    string delID;
    int index;
    char confirm;

    cout << "==================================================" << endl;
    cout << setw(35) << "DELETE COMPLAINT RECORD" << endl;
    cout << "==================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    cout << "\nEnter Complaint ID to delete: ";
    cin >> delID;

    index = findComplaintIndex(delID);

    if (index == -1)
    {
        cout << "\nComplaint not found!\n" << endl;
        return;
    }

    cout << "\nRecord to be deleted :\n";
    cout << "Complaint ID: " << ID[index] << endl;
    cout << "Name:         " << Name[index] << endl;
    cout << "Category:     " << Category[index] << endl;

    cout << "\nAre you sure ? (Y / N) : ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
    {
        for (int i = index; i < Count - 1; i++)
        {
            ID[i] = ID[i + 1];
            Name[i] = Name[i + 1];
            CNIC[i] = CNIC[i + 1];
            Phone[i] = Phone[i + 1];
            Address[i] = Address[i + 1];
            Category[i] = Category[i + 1];
            Details[i] = Details[i + 1];
            Date[i] = Date[i + 1];
            Status[i] = Status[i + 1];
        }

        Count--;
        cout << "\nRecord deleted successfully!\n" << endl;
    }
    else
    {
        cout << "\nDeletion cancelled.\n" << endl;
    }
}

void displayAllComplaints()
{
    cout << "================================================================================" << endl;
    cout << setw(55) << "ALL REGISTERED COMPLAINTS" << endl;
    cout << "================================================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    cout << left;
    cout << setw(12) << "ID"
        << setw(15) << "Name"
        << setw(14) << "CNIC"
        << setw(12) << "Phone"
        << setw(12) << "Category"
        << setw(12) << "Date"
        << setw(12) << "Status" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < Count; i++)
    {
        cout << setw(12) << ID[i]
            << setw(15) << Name[i].substr(0, 14)
            << setw(14) << CNIC[i]
            << setw(12) << Phone[i]
            << setw(12) << Category[i]
            << setw(12) << Date[i]
            << setw(12) << Status[i] << endl;
    }

    cout << "================================================================================" << endl;
    cout << "Total Complaints: " << Count << endl;
}

void categoryReport()
{
    string categories[MAX_CAT] = { "Theft", "Robbery", "Assault", "Fraud", "Other" };
    int catCount;

    cout << "==================================================" << endl;
    cout << setw(35) << "CATEGORY-WISE REPORT" << endl;
    cout << "==================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    for (int c = 0; c < MAX_CAT; c++)
    {
        catCount = 0;

        for (int i = 0; i < Count; i++)
        {
            if (Category[i] == categories[c])
            {
                catCount++;
            }
        }

        if (catCount > 0)
        {
            cout << "--------------------------------------------------" << endl;
            cout << "Category: " << categories[c] << " (Total: " << catCount << ")" << endl;
            cout << "--------------------------------------------------" << endl;

            cout << left;
            cout << setw(12) << "ID"
                << setw(15) << "Name"
                << setw(12) << "Date"
                << setw(12) << "Status" << endl;
            cout << "--------------------------------------------------" << endl;

            for (int i = 0; i < Count; i++)
            {
                if (Category[i] == categories[c])
                {
                    cout << setw(12) << ID[i]
                        << setw(15) << Name[i].substr(0, 14)
                        << setw(12) << Date[i]
                        << setw(12) << Status[i] << endl;
                }
            }
        }
    }
}

void pendingResolvedReport()
{
    int pendingCount = 0;
    int resolvedCount = 0;
    int inprogressCount = 0;

    cout << "==================================================" << endl;
    cout << setw(35) << "PENDING / RESOLVED REPORT" << endl;
    cout << "==================================================" << endl;

    if (Count == 0)
    {
        cout << "\nNo complaints registered yet!\n" << endl;
        return;
    }

    for (int i = 0; i < Count; i++)
    {
        if (Status[i] == "Pending")
        {
            pendingCount++;
        }
        else if (Status[i] == "In Progress")
        {
            inprogressCount++;
        }
        else if (Status[i] == "Resolved")
        {
            resolvedCount++;
        }
    }

    cout << "----------------------------------------" << endl;
    cout << "STATUS SUMMARY" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Pending Complaints:    " << pendingCount << endl;
    cout << "In Progress Complaints: " << inprogressCount << endl;
    cout << "Resolved Complaints:   " << resolvedCount << endl;
    cout << "Total Complaints:      " << Count << endl;
    cout << "----------------------------------------" << endl;

    if (pendingCount > 0)
    {
        cout << "**************************************************" << endl;
        cout << "PENDING COMPLAINTS (" << pendingCount << ")" << endl;
        cout << "**************************************************" << endl;

        cout << left;
        cout << setw(12) << "ID"
            << setw(15) << "Name"
            << setw(12) << "Category"
            << setw(12) << "Date" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int i = 0; i < Count; i++)
        {
            if (Status[i] == "Pending")
            {
                cout << setw(12) << ID[i]
                    << setw(15) << Name[i].substr(0, 14)
                    << setw(12) << Category[i]
                    << setw(12) << Date[i] << endl;
            }
        }
    }
    if (inprogressCount > 0)
    {
        cout << "**************************************************" << endl;
        cout << "In Progress COMPLAINTS (" << inprogressCount << ")" << endl;
        cout << "**************************************************" << endl;

        cout << left;
        cout << setw(12) << "ID"
            << setw(15) << "Name"
            << setw(12) << "Category"
            << setw(12) << "Date" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int i = 0; i < Count; i++)
        {
            if (Status[i] == "In Progress")
            {
                cout << setw(12) << ID[i]
                    << setw(15) << Name[i].substr(0, 14)
                    << setw(12) << Category[i]
                    << setw(12) << Date[i] << endl;
            }
        }
    }

    if (resolvedCount > 0)
    {
        cout << "**************************************************" << endl;
        cout << "RESOLVED COMPLAINTS (" << resolvedCount << ")" << endl;
        cout << "**************************************************" << endl;

        cout << left;
        cout << setw(12) << "ID"
            << setw(15) << "Name"
            << setw(12) << "Category"
            << setw(12) << "Date" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int i = 0; i < Count; i++)
        {
            if (Status[i] == "Resolved")
            {
                cout << setw(12) << ID[i]
                    << setw(15) << Name[i].substr(0, 14)
                    << setw(12) << Category[i]
                    << setw(12) << Date[i] << endl;
            }
        }
    }
}

void saveDataToFile()
{
    ofstream outFile;
    outFile.open("complaints.txt");

    if (!outFile)
    {
        cout << "\nError: Could not open file for writing!\n" << endl;
        return;
    }

    outFile << nextID << endl;
    outFile << Count << endl;

    for (int i = 0; i < Count; i++)
    {
        outFile << ID[i] << endl;
        outFile << Name[i] << endl;
        outFile << CNIC[i] << endl;
        outFile << Phone[i] << endl;
        outFile << Address[i] << endl;
        outFile << Category[i] << endl;
        outFile << Details[i] << endl;
        outFile << Date[i] << endl;
        outFile << Status[i] << endl;
    }

    outFile.close();
    cout << "\nData saved successfully to 'complaints.txt'!\n" << endl;
}

void loadDataFromFile()
{
    ifstream inFile;
    inFile.open("complaints.txt");

    if (!inFile)
    {
        cout << "\nNote: No existing data file found. Starting fresh.\n" << endl;
        return;
    }

    inFile >> nextID;
    inFile.ignore();

    inFile >> Count;
    inFile.ignore();

    if (Count > MAX)
    {
        Count = MAX;
    }

    for (int i = 0; i < Count; i++)
    {
        getline(inFile, ID[i]);
        getline(inFile, Name[i]);
        getline(inFile, CNIC[i]);
        getline(inFile, Phone[i]);
        getline(inFile, Address[i]);
        getline(inFile, Category[i]);
        getline(inFile, Details[i]);
        getline(inFile, Date[i]);
        getline(inFile, Status[i]);
    }

    inFile.close();
    cout << "\nData loaded successfully from 'complaints.txt'!\n" << endl;
    cout << "Total records loaded: " << Count << endl;
}

void adminMenuLoop()
{
    int choice;
    do
    {
        showAdminMenu();
        cout << "Enter your choice(0 - 9) : ";
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 9)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Enter again (0-9): ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            searchComplaint();
            break;
        case 2:
            updateComplaint();
            break;
        case 3:
            deleteComplaint();
            break;
        case 4:
            displayAllComplaints();
            break;
        case 5:
            searchByName();
            break;
        case 6:
            categoryReport();
            break;
        case 7:
            pendingResolvedReport();
            break;
        case 8:
            loadDataFromFile();
            break;
        case 9:
            saveDataToFile();
            break;
        case 0:
            cout << "\nSaving data before logout...\n" << endl;
            saveDataToFile();
            cout << "Logged out successfully.\n" << endl;
            break;
        }

        if (choice != 0)
        {
            pauseScreen();
        }

    } while (choice != 0);
}

void publicMenuLoop()
{
    int choice;
    do
    {
        showPublicMenu();
        cout << "Enter your choice(0 - 2) : ";
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Enter again (0-2): ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            registerComplaint();
            saveDataToFile();
            break;
        case 2:
            searchComplaint();
            break;
        case 0:
            cout << "\nReturning to Main Menu...\n" << endl;
            break;
        }

        if (choice != 0)
        {
            pauseScreen();
        }

    } while (choice != 0);
}

int main()
{
    int choice;

    loadDataFromFile();

    cout << "============================================================" << endl;
    cout << setw(45) << "POLICE COMPLAINT SYSTEM" << endl;
    cout << "============================================================" << endl;

    do
    {
        showMainMenu();
        cout << "Enter your choice(0 - 2) : ";
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Enter again (0-2): ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            if (adminLogin())
            {
                adminMenuLoop();
            }
            break;
        case 2:
            publicMenuLoop();
            break;
        case 0:
            cout << "\nThank you for using Police Complaint System!\n" << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}