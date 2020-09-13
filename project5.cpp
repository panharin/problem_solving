#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void funcInitValue(string **labNumber);
void funcDisplayMenu(string **labNumber);
void funcMenu(int menu, string **labNumber);
void funcLogin(string **datasheet, string id, int station, int lab);
void funcLogout(string **datasheet, string id, int station, int lab);
void funcGetvalue(string &idNum, int &stationNum, int &labNum);
bool funcCheck(const string &column, const string &row);
void funcDisplayLog(string **labNumber);
void funcSearch(string **labNumber);
void funcDisplaySearch(string **labNumber, int column, int row);

int main() {
    //number of lab 4.
    //Number of stations 5,6,4,3
    string *labNumber[4] = {new string[5], new string[6], new string[4], new string[3]};
    funcInitValue(labNumber);

    funcDisplayMenu(labNumber);

    return 0;
}

void funcInitValue(string **labNumber){
    for (int index = 0; index < 5; index++) { labNumber[0][index] = "empty"; }
    for (int index = 0; index < 6; index++) { labNumber[1][index] = "empty"; }
    for (int index = 0; index < 4; index++) { labNumber[2][index] = "empty"; }
    for (int index = 0; index < 3; index++) { labNumber[3][index] = "empty"; }
}

void funcDisplayMenu(string **labNumber){
    int menu;
    cout << "MENU: "
            "\n0: Log off."
            "\n1: log in."
            "\n2: Search."
            "\n3: Display Log."
            "\n4: EXIT.\n";
    cout << "\tI choose: ";
    cin >> menu;
    funcMenu(menu, labNumber);
}

void funcMenu(int menu, string **labNumber){
    switch (menu){
        case 0:
            cout<< "Doing logoff\n";
                funcLogout(labNumber, "", 0,0);
            break;
        case 1:
            cout<< "Doing login\n";
            funcLogin(labNumber, "", 0, 0);
            break;
        case 2:
            cout<< "Doing search\n";
            funcSearch(labNumber);
            break;
        case 3:
            cout<< "Displaying the LOG...\n";
            funcDisplayLog(labNumber);
        case 4:
            exit(1);
        default:
            ;
    }
}

void funcLogin(string **datasheet, string id, int station, int lab){
    funcGetvalue(id, station, lab);

    if (datasheet[lab][station] != "empty"){
        cout << "Login failed... The station is occupied...\n\n";
    }else{
        datasheet[lab][station] = id;
        cout<<"Login successful...\n\n";
    }

    funcDisplayMenu(datasheet);
}

void funcLogout(string **datasheet, string id, int station, int lab) {
    funcGetvalue(id, station, lab);

    if (datasheet[lab][station] != "empty"){
        datasheet[lab][station] = "empty";
        cout << "Logoff successful...\n\n";
    }else{
        cout<< "Logoff failed... The station is never login...\n\n";
    }

    funcDisplayMenu(datasheet);
}

void funcSearch(string **labNumber) {
    string id;
    cout << "Enter user id to search:";
    cin >> id;
    int column, row;
    bool found = false;
    for (int index = 0; index < 5; index++) {   //display lab1
        if (labNumber[0][index] == id) {
            column = 0;
            row = index;
            found = true;
            funcDisplaySearch(labNumber, column, row);
        }
    }

    for (int index = 0; index < 6; index++) {   //lab2
        if (labNumber[1][index] == id) {
            column = 1;
            row = index;
            found = true;
            funcDisplaySearch(labNumber, column, row);
        }

    }

    for (int index = 0; index < 4; index++) {   //lab3
        if (labNumber[2][index] == id) {
            column = 2;
            row = index;
            found = true;
            funcDisplaySearch(labNumber, column, row);
        }

    }

    for (int index = 0; index < 3; index++) {   //lab4
        if (labNumber[3][index] == id) {
            column = 3;
            row = index;
            found = true;
            funcDisplaySearch(labNumber, column, row);
        }

    }
    if (!found) {    //found == false
        cout<< "No id found!" <<endl<<endl;
    }
    funcDisplayMenu(labNumber);
}

void funcDisplaySearch(string **labNumber, int column, int row){
    static bool flag = false;   //appear only once
    while (!flag){  //!flag always = false. flag always == true.
        cout<< "id found..." <<endl;
        cout << "Lab Number" << "\tComputer Stations" << endl;
        flag = true;
    }
    cout << column + 1 << "\t\t" << row + 1 << ": " << labNumber[column][row] << endl << endl;
}

void funcDisplayLog(string **labNumber){
    cout << "Lab Number" << "\tComputer Stations" <<endl;
    int column=1;
    {
        cout<< column++ <<'\t';     //display lab1
        for (int index = 0; index < 5; index++) { cout<<"\t" <<index+1 <<": " <<labNumber[0][index];}

        cout<<endl <<column++ <<'\t';   //display lab2
        for (int index = 0; index < 6; index++) { cout<<"\t" <<index+1 <<": " << labNumber[1][index];}

        cout<<endl <<column++ <<'\t';   //display lab3
        for (int index = 0; index < 4; index++) { cout<<"\t" << index+1 <<": " << labNumber[2][index]; }

        cout<<endl <<column++ <<'\t';   //display lab4
        for (int index = 0; index < 3; index++) { cout<<"\t" << index+1 <<": " << labNumber[3][index]; }
        cout<<"\n\n";
    }
    funcDisplayMenu(labNumber);

}

void funcGetvalue(string &idNum, int &stationNum, int &labNum){

    string getinfo;
    while (true) {
        cout << "Enter your INFO as 5digits ID, station number, lab number"
             <<" in FORMAT(#####, #, #): ";
        cin.ignore(10, '\n');   //ignore \n
        getline(cin, getinfo, ')');  //(12345, 8, 1) length 9
        int size = getinfo.length();
        string getcolumn, getrow;
        bool check;
        if (size != 12) {
            cout << "Invalid Input" << endl;
        } else {
            getcolumn = getinfo.substr(11, 1);
            getrow = getinfo.substr(8, 1);
            check = funcCheck(getcolumn, getrow);
            if (check) {
                idNum = getinfo.substr(1, 5);     //get position and get string value
                stationNum = stoi(getinfo.substr(8, 1)); //get value
                stationNum = stationNum - 1;
                labNum = stoi(getinfo.substr(11, 1));    //get value
                labNum = labNum - 1;
                break;
            }
        }
    }
}

bool funcCheck(const string &column, const string &row) {
    //lab = column =  1-4 = 0-3

    if (column == "1") {
        if (row <= "5" && row >= "0")     //station1 = 1-5    = 0 4
            return true;
    } else if (column == "2") {
        if (row <= "6" && row >= "0")     //station2 = 1-6    = 1 5
            return true;
    } else if (column == "3") {
        if (row <= "4" && row >= "0")     //station3 = 1-4    = 2 3
            return true;
    } else if (column == "4") {
        if (row <= "3" && row >= "0")     //station4 = 1-3    = 3 2
            return true;
    } else {
        return false;
    }
    return false;
}

