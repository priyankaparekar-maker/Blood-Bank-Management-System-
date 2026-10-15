
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>
using namespace std;

class Donor
{
public:
    string name;
    int age;
    string bloodGroup;
    string mobile;

    void input()
    {
        cout << "\nEnter Donor Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        while (age < 18)
        {
            cout << "Donor must be 18 years or older!\n";
            cout << "Enter Age Again: ";
            cin >> age;
        }

        cout << "Enter Blood Group (A+/A-/B+/B-/O+/O-/AB+/AB-): ";
        cin >> bloodGroup;

        while (!validBloodGroup(bloodGroup))
        {
            cout << "Invalid Blood Group!\n";
            cout << "Enter Blood Group Again: ";
            cin >> bloodGroup;
        }

        cout << "Enter Mobile Number: ";
        cin >> mobile;

        cout << "\nDonor Added Successfully!\n";
    }

    bool validBloodGroup(string bg)
    {
        return bg == "A+" || bg == "A-" ||
               bg == "B+" || bg == "B-" ||
               bg == "O+" || bg == "O-" ||
               bg == "AB+" || bg == "AB-";
    }

    void display(int number)
    {
        cout << "\n-----------------------------\n";
        cout << "Donor No.     : " << number << endl;
        cout << "Name          : " << name << endl;
        cout << "Age           : " << age << endl;
        cout << "Blood Group   : " << bloodGroup << endl;
        cout << "Mobile        : " << mobile << endl;
        cout << "-----------------------------\n";
    }
};

class BloodBank
{
private:
    Donor donors[100];
    int count;
    string password;

public:

    BloodBank()
    {
        count = 0;
        password = "1234";
    }

    bool login()
    {
        string username;
        string pass;

        cout << "=====================================\n";
        cout << "        BLOOD BANK LOGIN\n";
        cout << "=====================================\n";

        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> pass;

        if (username == "admin" && pass == password)
        {
            cout << "\nLogin Successful!\n";
            return true;
        }

        cout << "\nInvalid Username or Password!\n";
        return false;
    }

    void addDonor()
    {
        if (count >= 100)
        {
            cout << "\nDonor limit reached!\n";
            return;
        }

        donors[count].input();
        count++;
    }

    void searchBlood()
    {
        string bg;
        bool found = false;

        cout << "\n===== SEARCH BY BLOOD GROUP =====\n";
        cout << "Enter Blood Group: ";
        cin >> bg;

        for (int i = 0; i < count; i++)
        {
            if (donors[i].bloodGroup == bg)
            {
                donors[i].display(i + 1);
                found = true;
            }
        }

        if (!found)
            cout << "\nNo Donor Found!\n";
    }

    void viewAll()
    {
        cout << "\n========== ALL DONORS ==========\n";

        if (count == 0)
        {
            cout << "No Donors Available!\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            donors[i].display(i + 1);
        }
    }

    void updateDonor()
    {
        int n;

        cout << "\n===== UPDATE DONOR =====\n";
        cout << "Enter Donor Number: ";
        cin >> n;

        if (n < 1 || n > count)
        {
            cout << "\nInvalid Donor Number!\n";
            return;
        }

        cout << "\nEnter New Details:\n";

        cout << "New Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, donors[n - 1].name);

        cout << "New Age: ";
        cin >> donors[n - 1].age;

        while (donors[n - 1].age < 18)
        {
            cout << "Age must be 18 or above!\n";
            cout << "Enter Age Again: ";
            cin >> donors[n - 1].age;
        }

        cout << "New Blood Group: ";
        cin >> donors[n - 1].bloodGroup;

        while (!donors[n - 1].validBloodGroup(
                   donors[n - 1].bloodGroup))
        {
            cout << "Invalid Blood Group!\n";
            cout << "Enter Again: ";
            cin >> donors[n - 1].bloodGroup;
        }

        cout << "New Mobile Number: ";
        cin >> donors[n - 1].mobile;

        cout << "\nDonor Updated Successfully!\n";
    }

    void deleteDonor()
    {
        int n;

        cout << "\n===== DELETE DONOR =====\n";
        cout << "Enter Donor Number: ";
        cin >> n;

        if (n < 1 || n > count)
        {
            cout << "\nInvalid Donor Number!\n";
            return;
        }

        for (int i = n - 1; i < count - 1; i++)
        {
            donors[i] = donors[i + 1];
        }

        count--;

        cout << "\nDonor Deleted Successfully!\n";
    }

    void bloodStock()
    {
        int ap = 0, an = 0;
        int bp = 0, bn = 0;
        int op = 0, on = 0;
        int abp = 0, abn = 0;

        for (int i = 0; i < count; i++)
        {
            if (donors[i].bloodGroup == "A+") ap++;
            else if (donors[i].bloodGroup == "A-") an++;
            else if (donors[i].bloodGroup == "B+") bp++;
            else if (donors[i].bloodGroup == "B-") bn++;
            else if (donors[i].bloodGroup == "O+") op++;
            else if (donors[i].bloodGroup == "O-") on++;
            else if (donors[i].bloodGroup == "AB+") abp++;
            else if (donors[i].bloodGroup == "AB-") abn++;
        }

        cout << "\n========== BLOOD STOCK ==========\n";
        cout << "A+   : " << ap << endl;
        cout << "A-   : " << an << endl;
        cout << "B+   : " << bp << endl;
        cout << "B-   : " << bn << endl;
        cout << "O+   : " << op << endl;
        cout << "O-   : " << on << endl;
        cout << "AB+  : " << abp << endl;
        cout << "AB-  : " << abn << endl;
    }

    void saveData()
    {
        ofstream file("donor.txt");

        if (!file)
        {
            cout << "\nUnable to save data!\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            file << donors[i].name << "|"
                 << donors[i].age << "|"
                 << donors[i].bloodGroup << "|"
                 << donors[i].mobile << endl;
        }

        file.close();

        cout << "\nData Saved Successfully!\n";
    }

    void loadData()
    {
        ifstream file("donor.txt");

        if (!file)
        {
            cout << "\nNo Saved Data Found!\n";
            return;
        }

        count = 0;

        string ageString;

        while (count < 100 &&
               getline(file, donors[count].name, '|'))
        {
            getline(file, ageString, '|');
            getline(file, donors[count].bloodGroup, '|');
            getline(file, donors[count].mobile);

            donors[count].age = stoi(ageString);

            count++;
        }

        file.close();

        cout << "\nData Loaded Successfully!\n";
    }

    void searchName()
    {
        string search;
        bool found = false;

        cout << "\n===== SEARCH BY NAME =====\n";
        cout << "Enter Name: ";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, search);

        for (int i = 0; i < count; i++)
        {
            if (donors[i].name == search)
            {
                donors[i].display(i + 1);
                found = true;
            }
        }

        if (!found)
            cout << "\nDonor Not Found!\n";
    }

    void totalDonors()
    {
        cout << "\n===== TOTAL DONORS =====\n";
        cout << "Total Donors Available: "
             << count << endl;
    }

    void changePassword()
    {
        string oldPass, newPass;

        cout << "\n===== CHANGE PASSWORD =====\n";

        cout << "Enter Current Password: ";
        cin >> oldPass;

        if (oldPass != password)
        {
            cout << "\nWrong Current Password!\n";
            return;
        }

        cout << "Enter New Password: ";
        cin >> newPass;

        password = newPass;

        cout << "\nPassword Changed Successfully!\n";
    }

    void menu()
    {
        int choice;

        do
        {
            cout << "\n====================================\n";
            cout << "      BLOOD BANK MANAGEMENT SYSTEM\n";
            cout << "====================================\n";

            cout << "1.  Add Donor\n";
            cout << "2.  Search By Blood Group\n";
            cout << "3.  View All Donors\n";
            cout << "4.  Update Donor\n";
            cout << "5.  Delete Donor\n";
            cout << "6.  Blood Stock\n";
            cout << "7.  Save Data\n";
            cout << "8.  Load Data\n";
            cout << "9.  Search By Name\n";
            cout << "10. Total Donors\n";
            cout << "11. Change Password\n";
            cout << "12. Exit\n";

            cout << "\nEnter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addDonor();
                    break;

                case 2:
                    searchBlood();
                    break;

                case 3:
                    viewAll();
                    break;

                case 4:
                    updateDonor();
                    break;

                case 5:
                    deleteDonor();
                    break;

                case 6:
                    bloodStock();
                    break;

                case 7:
                    saveData();
                    break;

                case 8:
                    loadData();
                    break;

                case 9:
                    searchName();
                    break;

                case 10:
                    totalDonors();
                    break;

                case 11:
                    changePassword();
                    break;

                case 12:
                    cout << "\nThank You!\n";
                    cout << "Exiting Blood Bank System...\n";
                    break;

                default:
                    cout << "\nInvalid Choice!\n";
            }

        } while (choice != 12);
    }
};

int main()
{
    BloodBank bank;

    if (bank.login())
    {
        bank.menu();
    }

    return 0;
}
