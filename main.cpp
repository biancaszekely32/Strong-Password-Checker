#include <iostream>
#include <string>

using namespace std;


int count_characters(char c,string s,int idx) {
    int count = 1;

    for (int i = idx; i < s.length(); i++) {
        if (s[i + 1] == c)
            count++;
        else
            return count;
    }
    return 0;
}

int password_checker(string s) {
    int n = s.length();
    //we assume that the password does not contain at least one lowercase
    //letter, at least one uppercase letter, and at least one digit.
    bool lower = false, upper = false, digit = false;
    int repeat ;//counts the repeating characters
    int changes = 0;//counts the number of changes that we need to make
    for (int i = 0; i < n; i++) {
        char c = s[i];//we save in c each character from s
        if (isdigit(c) != 0)
            digit = true;
        if (islower(c) != 0)
            lower = true;
        if (isupper(c) != 0)
            upper = true;

        repeat=0;
        if (i > 0 && s[i - 1] != s[i])
            repeat = count_characters(s[i], s, i);
        if (repeat >= 3)
            changes = changes + repeat / 3;
    }

    if (!lower)changes++;
    if (!digit)changes++;
    if (!upper)changes++;

    if (n < 6)
        changes = changes + (6 - n);
    if (n > 20)
        changes = changes + (n - 20);

    return changes;
}

int main() {
    string s;
    bool ok=true;
    cout<<"Welcome to the Strong Password Checker!"<<endl;
    cout<<endl;
    while(ok){
        cout<<"Please input the password to be checked. "<<endl;
        cout<<"Press 0 if you want to exit."<<endl;
        cout<<">> ";
        cin >> s;
        if((s.compare("0"))==0){
            cout<<"Exiting the Strong Password Checker...";
            ok=false;
        }
        else {
            int minimum_changes = password_checker(s);
            if (minimum_changes == 0)
                cout << "The password is already strong!"<<endl;
            else
                cout << "MINIMUM change required to make a strong password:" << minimum_changes << endl;
        }
    }
}
