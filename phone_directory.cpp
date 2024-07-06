#include <bits/stdc++.h>
using namespace std;

class contact {
public:
    contact* next;
    contact* pre;
    string name;
    string number;

    inline contact() : next(NULL), pre(NULL), name(""), number("") {}
    inline contact(string n, string num) : next(NULL), pre(NULL), name(n), number(num) {}
};

string toLowerCase(string name){
    for (int i = 0; i < name.size(); i++){
        name[i] = tolower(name[i]);
    }
    return name;
}

contact* searchcontact(vector<contact*>& alphabet){
    string tosearch;
    cin >> tosearch;
    tosearch = toLowerCase(tosearch);
    int index = tosearch[0] - 'a';
    contact* temp = alphabet[index];

    while (temp && temp->name != tosearch){
        temp = temp->next;
    }
    return temp;
}

void print(contact* temp){
    string name = temp->name;
    name[0] = toupper(name[0]);
    cout << "Name: " << name << ", Number: " << temp->number << endl;
}

bool validNum(long long number){
    string num = to_string(number);
    return num.size() == 10;
}

void subAdd(vector<contact*>& alphabet, long long number, string name){
    string number_string = to_string(number);
    contact* newcontact = new contact(name, number_string);
    int index = name[0] - 'a';

    if (alphabet[index] == NULL){
        alphabet[index] = newcontact;
    } 
    else{
        contact* temp = alphabet[index];
        contact* prev = NULL;

        while (temp && temp->name < name){
            prev = temp;
            temp = temp->next;
        }

        if(temp && temp->name == name){
            cout << "Already Exists " << name << "\nEnter Y/y to Overwrite\nEnter N/n to Create New Contact\n";
            char c;
            cin >> c;
            if(c == 'y' || c == 'Y'){
                temp->number = number_string;
                delete newcontact;
            }
            else {
                if(prev){
                    prev->next = newcontact;
                    newcontact->pre = prev;
                }
                else{
                    alphabet[index] = newcontact;
                }
                newcontact->next = temp;
                temp->pre = newcontact;
            }
        }
        else{
            if(prev){
                prev->next = newcontact;
                newcontact->pre = prev;
            }
            else{
                alphabet[index] = newcontact;
            }
            newcontact->next = temp;
            if (temp){
                temp->pre = newcontact;
            }
        }
    }
}

bool subDel(vector<contact*>& alphabet, contact* temp){
    if(!temp){
        cout << "Name Not Exist ;) \n";
        return false;
    }
    else{
        int index = temp->name[0] - 'a';
        if (temp->pre){
            temp->pre->next = temp->next;
        }
        else{
            alphabet[index] = temp->next;
        }
        if(temp->next){
            temp->next->pre = temp->pre;
        }
        delete temp;
        return true;
    }
}

void add(vector<contact*>& alphabet){
    string name;
    long long number;
    cout << "Enter Name: ";
    cin >> name;
    name = toLowerCase(name);

    cout << "Enter Number: ";
    cin >> number;

    while(!validNum(number)){
        cout << "Enter Correct Number (10 digits) {@.@} -> ";
        cin >> number;
    }
    subAdd(alphabet, number, name);
}

void del(vector<contact*>& alphabet){
    cout << "Enter Contact Name To Delete: ";
    contact* temp = searchcontact(alphabet);
    if(subDel(alphabet, temp)) cout << "Successfully Deleted {^_^}\n";
}

void edit(vector<contact*>& alphabet){
    cout << "Enter Contact Name For Edit: ";
    contact* temp = searchcontact(alphabet);
    if(!temp){
        cout << "\nContact Does Not Exist {'~'} \n";
    }
    else{
        string nameToEdit;
        long long num;
        cout << "Current Name: " << temp->name << "\nEnter The New Name: ";
        cin >> nameToEdit;
        cout << "Current Number: " << temp->number << "\nEnter The New Number: ";
        cin >> num;
        while(!validNum(num)){
            cout << "Enter Correct Number (10 digits): ";
            cin >> num;
        }
        subDel(alphabet, temp);
        nameToEdit = toLowerCase(nameToEdit);
        subAdd(alphabet, num, nameToEdit);
    }
}

void search(vector<contact*>& alphabet){
    cout << "Enter Name To Search: ";
    contact* temp = searchcontact(alphabet);
    if(!temp){
        cout << "\nContact Does Not Exist {'~'}\n";
    }
    else{
        print(temp);
    }
}

void showAllContacts(vector<contact*>& alphabet){
    bool flag = true;
    for(int i = 0; i < 26; i++){
        contact* temp = alphabet[i];
        while(temp){
            print(temp);
            temp = temp->next;
            flag = false;
        }
    }
    if(flag) cout<<"Directory Id Empty {-.-}\n";
}

void deleteAllContacts(vector<contact*>& alphabet){
    for(int i = 0; i < 26; ++i){
        contact* temp = alphabet[i];
        while(temp){
            contact* next = temp->next;
            delete temp;
            temp = next;
        }
        alphabet[i] = NULL;
    }
}

int main(){
    cout << "Welcome To Phone Directory" << endl;
    vector<contact*> alphabet(26, NULL);

    bool loop = true;
    while(loop){
        int choice;
        cout << "Enter 1 - Add Contact\nEnter 2 - Delete Contact\nEnter 3 - Edit Contact\nEnter 4 - Search\nEnter 5 - Show All Contacts\n";
        cin >> choice;
        switch (choice) {
            case 1:
                add(alphabet);
                break;
            case 2:
                del(alphabet);
                break;
            case 3:
                edit(alphabet);
                break;
            case 4:
                search(alphabet);
                break;
            case 5:
                showAllContacts(alphabet);
                break;
            default:
                cout << "Enter Valid Value" << endl;
                break;
        }
        cout << "To Continue... Press y/Y\nAny Key: ";
        char c;
        cin >> c;
        cout<<endl;
        loop = (c == 'y' || c == 'Y');
    }

    deleteAllContacts(alphabet);
    cout << "All contacts deleted. Exiting..." << endl;
    return 0;
}
