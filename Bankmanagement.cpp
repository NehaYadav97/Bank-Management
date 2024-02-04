#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

class bank
{
    int acc_no;
    long phone;
    char name[20], type, city[20], st;
    float bal;

public:
    void getdata();
    void putdata();
    void create();
    void display();
    int search(int);
    void append();
    void delect();
    void modify();
    int getacc_no() { return acc_no; };
} obj;

void bank::getdata()
{
    cout << "\nEnter the account number : ";
    cin >> acc_no;
    cin.ignore(); // Ignore the newline character left by cin
    cout << "\nEnter your name : ";
    cin.getline(name, 20);
    cout << "\nEnter the bank type (Saving(s) or current(c) : ";
    cin >> type;
    cout << "\nEnter your phone no. : ";
    cin >> phone;
    cout << "\nEnter your city : ";
    cin >> city;
    cout << "\nEnter the balance : ";
    cin >> bal;
}

void bank::putdata()
{
    cout << "\nAcc_no.\tName\tAcc_Type\tPhoneno.\tCity\tBalance";
    cout << "\n" << acc_no << "\t" << name << "\t" << type << "\t\t" << phone << "\t" << city << "\t" << bal;
}

void bank::create()
{
    ofstream file;
    char ch = 'y';
    file.open("bank.txt", ios::binary);
    while (ch == 'y' || ch == 'Y')
    {
        obj.getdata();
        file.write(reinterpret_cast<char *>(&obj), sizeof(obj));
        cout << "\nDo you want to enter more account ( yes (y) or no (n)) : ";
        cin >> ch;
    }
    file.close();
}

void bank::display()
{
    ifstream file;
    file.open("bank.txt", ios::binary);
    while (file.read(reinterpret_cast<char *>(&obj), sizeof(obj)))
    {
        obj.putdata();
    }
    file.close();
}

int bank::search(int acc)
{
    int found = 0;
    ifstream file;
    file.open("bank.txt", ios::binary);
    while (file.read(reinterpret_cast<char *>(&obj), sizeof(obj)))
    {
        if (obj.getacc_no() == acc)
        {
            found = 1;
            break;
        }
        else
            found = -1;
    }
    return found;
}

void bank::append()
{
    ofstream file;
    char ch = 'y';
    file.open("bank.txt", ios::binary | ios::app);
    while (ch == 'y' || ch == 'Y')
    {
        obj.getdata();
        file.write(reinterpret_cast<char *>(&obj), sizeof(obj));
        cout << "\nDo you wish to append the data further(yes (y) or no (n)) : ";
        cin >> ch;
    }
    file.close();
}

void bank::delect()
{
    ifstream file("bank.txt", ios::in);
    ofstream fil("temp.txt", ios::out);
    int acc;
    char found = 'f', confirm = 'n';
    cout << "\nEnter account number which you want to delete : ";
    cin >> acc;
    while (file.read(reinterpret_cast<char *>(&obj), sizeof(obj)))
    {
        if (obj.getacc_no() == acc)
        {
            obj.putdata();
            found = 't';
            cout << "\nAre you sure you want to delete this record (y/n) : ";
            cin >> confirm;
            if (confirm == 'n')
                fil.write(reinterpret_cast<char *>(&obj), sizeof(obj));
        }
        else
            fil.write(reinterpret_cast<char *>(&obj), sizeof(obj));
    }
    if (found == 'f')
    {
        cout << "Account number not found!!\n";
    }
    file.close();
    fil.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
    file.open("bank.txt", ios::in);
    cout << "Now the file contains \n";
    while (file.read(reinterpret_cast<char *>(&obj), sizeof(obj)))
    {
        obj.putdata();
    }
    file.close();
}

void bank::modify()
{
    fstream file("bank.txt", ios::in | ios::out | ios::binary);
    int acc;
    long pos;
    char found = 'f';
    cout << "\nEnter account number you want to modify : ";
    cin >> acc;
    while (file.read(reinterpret_cast<char *>(&obj), sizeof(obj)))
    {
        if (obj.getacc_no() == acc)
        {
            int choice;
            cout<<"Update"<<endl;
            cout<<"1.City"<<endl;
            cout<<"2.Phone no."<<endl;
            cout<<"3.Both"<<endl;
            cout<<"Enter your choice :";
            cin>>choice;
            switch(choice){
            case 1:
              cout << "\nEnter the new city: ";
              cin >> city;
              break;
            case 2:
              cout << "\nEnter the new phone no. :";
              cin >> phone;
              break;
            case 3:
              cout << "\nEnter the new city: ";
              cin >> city;
              cout << "\nEnter the new phone no. :";
              cin >> phone;
              break;
            }  
            pos = file.tellg();
            file.seekg(pos - sizeof(obj));
            file.write(reinterpret_cast<char *>(&obj), sizeof(obj));
            found = 't';
            break;  
        }
    }
    if (found == 'f')
        cout << "Account not found !!\n";
    file.seekg(0);
    cout << "Now the file contains \n";
    while (file.read(reinterpret_cast<char *>(&obj), sizeof(obj)))
    {
        obj.putdata();
    }
    file.close();
}

int main()
{
    int choice;
    char opt;
    do
    {
        cout << "\n\n\t\t\t\t    MAIN MENU ";
        cout << "\n\n\t\t\t\t1.Create Account";
        cout << "\n\t\t\t\t2.Display Account ";
        cout << "\n\t\t\t\t3.Search Account";
        cout << "\n\t\t\t\t4.Append Account ";
        cout << "\n\t\t\t\t5.Delete Account ";
        cout << "\n\t\t\t\t6.Modify Account ";
        cout << "\n\t  Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            obj.create();
            break;
        }
        case 2:
        {
            obj.display();
            break;
        }
        case 3:
        {
            int acc, found = 0;
            cout << "\nEnter the account no. you want to search  : ";
            cin >> acc;
            found = obj.search(acc);
            if (found == 1)
            {
                cout << "\nElement found !!!";
                obj.putdata();
            }
            else
                cout << "\nElement not found ";
            break;
        }
        case 4:
        {
            obj.append();
            break;
        }
        case 5:
        {
            obj.delect();
            break;
        }
        case 6:
        {
            obj.modify();
            break;
        }
        default:
            cout << "Wrong choice";
        }
        cout << "\nDo you wish to continue( yes (y) or no (n) : ";
        cin >> opt;
    } while (opt == 'y' || opt == 'Y');
    return 0;
}

