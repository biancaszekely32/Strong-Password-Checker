#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int case1(int n,int missing){
    return max(6 - n, missing);
}

int case3(int n,vector<int> repeat,int changes,int missing){
    int i = 0;
    while (i < n) {
        if (repeat[i] >= 3 && missing > 0) {
            int reduce = min(repeat[i]/3, missing);
            repeat[i] -=reduce;
            missing -= reduce;

            changes++;
        }

        if (repeat[i] >= 3) {
            changes += repeat[i] / 3;
        }
        i++;
    }

    changes += max(missing, 0);
    return changes;
}

int case2(int changes,int n,vector<int> repeat,int missing){
    int delete_count = n - 20,i;
    sort(repeat.begin(), repeat.end());



    for(i=n-1;i >= 1;i--)
        while(delete_count!=0 && repeat[i]>=3) {
            changes++;
            delete_count--;
            repeat[i]--;
        }
/*        if (repeat[i] >= 3 ) {
            changes += repeat[i] / 3;
            repeat[i] /= 3;
            while (delete_count<changes && delete_count!=0)
                delete_count--;
        }*/


    i = n - 1;
    while (delete_count > 0 && i >= 0) {
        if (repeat[i] % 3 == 1) {
            repeat[i]--;
            delete_count--;
            changes++;
        }
        i--;
    }

    i = 0;
    while (delete_count > 0 && i < n) {
        if (repeat[i] % 3 == 2) {
            repeat[i]--;
            delete_count--;
            changes++;
        }
        i++;
    }
    for(i=n-1;i >= 1;i--)
        if(delete_count==0 && repeat[i]>=3)
            return case3(n-delete_count,repeat,changes,missing);
    changes += max(missing, delete_count);

    return changes;
}





int password_checker(string s) {
    int n = s.length();
    int lower = 0, upper = 0, digit = 0;
    int changes = 0;//counts the number of changes that we need to make
    int missing;int i=0;
    vector<int> repeat(n);

    while(i < n) {
        char c = s[i];//we save in c each character from s
        if (isdigit(c) != 0)
            digit = 1;
        if (islower(c) != 0)
            lower = 1;
        if (isupper(c) != 0)
            upper = 1;

        int j = i;
        while (i < n && s[i] == s[j]) {
            i++;
        }
        repeat[j] = i - j;
    }


    //check if s already strong
    missing = 3 - (lower + upper + digit);
    bool has_repeating = false;
    for (int i : repeat) {
        if (i > 2) {
            has_repeating = true;
            break;
        }
    }

    if (n >= 6 && n <= 20 && missing <= 0 && !has_repeating) {
        return 0;
    }

    //case1: n<6
    if (n < 6){
        return case1(n,missing);
    }

    // case 2: n > 20
    if (n > 20) {
        return case2(changes, n, repeat, missing);
    }

    // case 3: length of password is between 6 and 20
    return case3(n,repeat,changes,missing);
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
