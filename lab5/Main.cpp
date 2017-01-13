
#include <iostream>
#include <sstream>
#include <string>
#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"

using namespace std;

int main() {
    string line, command;
    TreeDB tree;

    cout << ">";
    getline(cin, line);

    while (!cin.eof()) {
        stringstream linestream(line);
        linestream >> command;
        if (command == "insert") {
            string name, flag;
            unsigned int ip;
            DBentry *db;
            linestream >> name >> ip >> flag;

            //insert node with different statue
            //active = 1
            //inactive = 0
            if (flag == "active") {
                db = new DBentry(name, ip, 1);
            } else {
                db = new DBentry(name, ip, 0);
            }

            //check if the input node already exist
            bool checkFlag = tree.insert(db);
            if (checkFlag)
                cout << "Success" << endl;
            else
                cout << "Error: entry already exists" << endl;
        } else if (command == "remove") {
            string name;
            linestream >> name;
            tree.remove(name);
        } else if (command == "updatestatus") {
            string name, flag;
            bool status = false;
            linestream >> name >> flag;

            if (flag == "active") {
                status = true;
            }

            DBentry *db = tree.find(name);
            if (db == NULL)
                cout << "Error: entry does not exist" << endl;
            else {
                db->setActive(status);
                cout << "Success" << endl;

            }
        } else if (command == "find") {
            string name;
            linestream >> name;

            DBentry *db = tree.find(name);

            if (db == NULL)
                cout << "Error: entry does not exist" << endl;

            else {
                cout << *db;
            }
        } else if (command == "printall") {
            tree.print();
        } else if (command == "printprobes") {
            string name;
            linestream >> name;

            DBentry *db = tree.find(name);

            if (db == NULL) {
                cout << "Error: entry does not exist" << endl;
            } else {
                tree.printProbes();
            }
        } else if (command == "removeall") {
            tree.removeAll();
        } else if (command == "countactive") {
            tree.countActive();
        } else
            cout << "Error: Invalid command" << endl;
        
        
        cout << ">";
        getline(cin, line);
    }

    //clear the entire tree before go out of scope
    tree.clearTree();
    return 0;
}







