#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Database {

public:

    Database(){
        loadData();
    }

    void chooseFunction(){
        string fun;
        bool hasValidFun = false;
        cout<<"Please enter function: ";
        cin>>fun;

        if(fun.compare("close") == 0){
            hasValidFun = true;
            closeFile();
        }
        if(fun.compare("help") == 0){
            hasValidFun = true;
            help();
        }
        if(fun.compare("exit") == 0){
            hasValidFun = true;
            exit();
        }
        if(fun.compare("print") == 0){
            hasValidFun = true;
            print();
        }
        if(fun.compare("import") == 0){
            hasValidFun = true;
            import();
        }
        if(fun.compare("showtables") == 0){
            hasValidFun = true;
            showtables();
        }
        if(fun.compare("describe") == 0){
            hasValidFun = true;
            describe();
        }
        if(fun.compare("print") == 0){
            hasValidFun = true;
            print();
        }
        if(fun.compare("export") == 0){
            hasValidFun = true;
            exportTable();
        }
        if(fun.compare("select") == 0){
            hasValidFun = true;
            select();
        }
        if(fun.compare("addcolumn") == 0){
            hasValidFun = true;
            addColumn();
        }
        if(fun.compare("update") == 0){
            hasValidFun = true;
            update();
        }
        if(fun.compare("delete") == 0){
            hasValidFun = true;
            deleteRows();
        }
        if(fun.compare("insert") == 0){
            hasValidFun = true;
            insertRow();
        }
        if(fun.compare("rename") == 0){
            hasValidFun = true;
            renameDatatable();
        }
        if(fun.compare("innerjoin") == 0){
            hasValidFun = true;
            innerJoin();
        }
        if(fun.compare("aggregate") == 0){
            hasValidFun = true;
            aggregate();
        }
        if(!hasValidFun){
            cout<<"Invalid function"<<endl;
            chooseFunction();
        }
    }
    void closeFile(){

        databaseContent = "";

        int i = 0;
        while(datatableName[i].compare("") != 0){
            datatableName[i] = "";
            datatableContent[i] = "";
            i++;
        }

        datatableIndex = -1;
        currentDatatableIndex = 0;

        cout<<"Successfully closed file\n"<<endl;
    }
    void saveFile(string fileName){
        if(fileName.compare("") != 0){
            ofstream fout;
            fout.open(fileName);

            if(fileName.compare("Database.txt") == 0){
                fout<<databaseContent;
            } else {
                fout<<datatableContent[currentDatatableIndex];
            }

            fout.close();
            cout<<"\nSuccessfully saved file\n"<<endl;
        } else {
            cout<<"\nNo file to save.\n"<<endl;
        }
    }
    void saveAsFile(string content){
        if(databaseContent.compare("") != 0){
            ofstream fout;
            string newFileName;

            cout<<"\nPlease enter desired path for the new file. If path is invalid, the file will be saved within the project: ";
            cin>>newFileName;

            ifstream fin;
            fin.open(newFileName);
            if(fin.is_open()){
                cout<<"\nThere is currently existing file with the same name. Do you wish to replace the existing file (cmd: replace) or choose another name (cmd: new)?"<<endl;
                string cmd;
                cin>>cmd;

                bool hasValidFun = false;
                if(cmd.compare("replace") == 0){
                    hasValidFun = true;
                    fout.open(newFileName);

                    fout<<content<<endl;

                    fout.close();
                    cout<<"Successfully replaced the file!\n"<<endl;
                }
                if(cmd.compare("new") == 0){
                    hasValidFun = true;
                    fout.close();
                    saveAsFile(content);
                }
                if(!hasValidFun){
                    cout<<"Invalid command.\n"<<endl;
                    fout.close();
                    saveAsFile(content);
                }
            } else {
                fout.open(newFileName);

                currentSavedFile = newFileName;

                fout<<content<<endl;
                fout.close();
                fin.close();

                cout<<"Successfully saved the file!\n"<<endl;
            }
        } else {
            cout<<"There is currently no file to be saved.\n"<<endl;
        }
    }
    void help(){
        cout<<"The following commands are supported: \nopen <file name within the project folder> or <file path>    opens <file name within the project folder> or <file path>\nclose    closes the currently opened file\nsave    saves the currently opened file\nsaveAs    saves the currently open file within the project folder with <file> name or saves it in <file path>\nhelp    prints the program's basic functions\nexit    exits the program\nprint    prints the file content\nselect    prints the element with <key> as key and <id> as id\nset    sets new value <value> to the element with <id> as id and <key> as key\nchildren    prints the 1st heirs of an element with <id> as id\nchild    returns all the <n>th heirs of an element with <id> as id\ntext    returns the text of an element with <id> as id\ndelete    deletes an element with <id> as id and <key> as key\nnewChild    adds an empty 1st heir to an element with <id> as id\n"<<endl;
        chooseFunction();
    }
    void exit(){
        cout<<"Exiting the program..."<<endl;
        atexit(0);
    }
    void import(){
        if(databaseContent.compare("") != 0){

            string fileName;
            cout<<"\nPlease enter desired datatable file: ";
            cin>>fileName;

            ifstream fin;
            fin.open(fileName);

            if(fin.fail()){
                cout<<"\nThere is no existing file with name: " + fileName + ". Import failed.\n"<<endl;
                fin.close();
                import();
            } else {

                openFile(fileName);

                if(databaseContent.find(datatableName[datatableIndex] + "    ") != string::npos){
                        cout<<"Datatable with name " + datatableName[datatableIndex] + " has already been imported.\n"<<endl;

                        datatableName[datatableIndex] = "";
                        datatableContent[datatableIndex] = "";
                        datatableIndex--;

                } else {
                    databaseContent += "\n" + datatableName[datatableIndex] + "    " + fileName;
                    saveFile("Database.txt");
                }

                chooseFunction();
            }
        } else {
            cout<<"\nDatabase is not opened. Can't import.\n"<<endl;
            chooseFunction();
        }
    }
    void showtables(){
        if(databaseContent.compare("") != 0){

            int i = 0;
            while(i <= datatableIndex){

                cout<<datatableName[i]<<endl;
                i++;
            }

            chooseFunction();

        } else {
            cout<<"\nDatabase is not opened. Can't show tables.\n"<<endl;
            chooseFunction();
        }
    }
    void describe(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                cout<<datatableContent[i].substr(0, datatableContent[i].find_first_of("######"))<<endl;

                chooseFunction();
            }
        } else {
            cout<<"\nThere isn't a loaded database. Can't describe datatable.\n"<<endl;
            chooseFunction();
        }
    }
    void print(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                doOperation("print", fileName);

                chooseFunction();
            }
        } else {
            cout<<"\nThere isn't a loaded database. Can not print datatable.\n"<<endl;
            chooseFunction();
        }
    }
    void exportTable(){
         if(datatableName[0].compare("") != 0){

             string datatable;
             string fileName;
             bool existDatatable = false;

             cout<<"\nPlease enter desired datatable name: ";
             cin>>datatable;

             int i = 0;
             while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
             }
             if(!existDatatable){
                cout<<"There is not datatable with " + datatable + " name."<<endl;
                chooseFunction();
             } else {

                saveAsFile(datatableName[i] + "\n" + datatableContent[i]);
             }
         } else {
            cout<<"\nThere isn't a loaded datatable. Can't export datatable.\n"<<endl;
            chooseFunction();
        }
    }
    void select(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            string value = "";
            int column;
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;
            cout<<"\nPlease enter desired value: ";
            getline(cin, value);
            getline(cin, value);
            cout<<"\nPlease enter desired column: ";
            cin>>column;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                if(value.compare("NULL") != 0){
                   if(getDatatableColumnType(datatableContent[i], column).compare("string") == 0){
                       value = "\"" + value + "\"";
                   }
                }
                if(value.compare("") == 0){
                    value = "NULL";
                }

                doOperation("select", fileName, column, value);

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not select from datatable.\n"<<endl;
            chooseFunction();
        }
    }
    void addColumn(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            string type = "";
            string newColumnName = "";
            int column;
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;
            cout<<"\nPlease enter the new column name: ";
            cin>>newColumnName;
            cout<<"\nPlease enter the new column type: ";
            cin>>type;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                string columns = "";
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                columns = datatableContent[i].substr(0, datatableContent[i].find_first_of("######") -1);

                datatableContent[i] = "";
                datatableContent[i] += datatableName[i] + "\n" + columns + "    " + newColumnName + "(" + type + ")\n######\n";

                doOperation("addcolumn", fileName);

                datatableContent[i] = datatableContent[i].substr(datatableName[i].length() + 1);

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not add column.\n"<<endl;
            chooseFunction();
        }
    }
    void update(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            string value = "";
            int column;
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;
            cout<<"\nPlease enter desired value: ";
            getline(cin, value);
            getline(cin, value);
            cout<<"\nPlease enter desired column: ";
            cin>>column;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                string columns = "";
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                if(value.compare("NULL") != 0){
                   if(getDatatableColumnType(datatableContent[i], column).compare("string") == 0){
                       value = "\"" + value + "\"";
                   }
                }
                if(value.compare("") == 0){
                    value = "NULL";
                }
                if(value.compare("") == 0){
                    value = "NULL";
                }

                columns = datatableContent[i].substr(0, datatableContent[i].find_first_of("######") -1);

                datatableContent[i] = "";
                datatableContent[i] += datatableName[i] + "\n" + columns + "\n######\n";

                doOperation("update", fileName, column, value);

                datatableContent[i] = datatableContent[i].substr(datatableName[i].length() + 1);

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not update datatable.\n"<<endl;
            chooseFunction();
        }
    }
    void deleteRows(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            string value = "";
            int column;
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                cout<<"\nPlease enter desired value: ";
                getline(cin, value);
                getline(cin, value);
                cout<<"\nPlease enter desired column: ";
                cin>>column;

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                string columns = "";
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                if(value.compare("NULL") != 0){
                   if(getDatatableColumnType(datatableContent[i], column).compare("string") == 0){
                       value = "\"" + value + "\"";
                   }
                }
                if(value.compare("") == 0){
                    value = "NULL";
                }

                columns = datatableContent[i].substr(0, datatableContent[i].find_first_of("######") -1);

                datatableContent[i] = "";
                datatableContent[i] += datatableName[i] + "\n" + columns + "\n######\n";

                doOperation("delete", fileName, column, value);

                datatableContent[i] = datatableContent[i].substr(datatableName[i].length() + 1);

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not delete from datatable.\n"<<endl;
            chooseFunction();
        }
    }
    void insertRow(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string columns = "";
                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                columns = datatableContent[i].substr(0, datatableContent[i].find_first_of("######") -1);

                datatableContent[i] = datatableName[i] + "\n" + datatableContent[i];

                string splitter = columns;
                string value = "";
                bool isEverySecondString = true;
                string textId;
                int id = 0;

                textId = datatableContent[i].substr(0, datatableContent[i].length()-1);
                textId = textId.substr(textId.find_last_of("\n") + 1);

                if(textId.find("    ") != string::npos){
                   textId = textId.substr(0, textId.find("    "));
                   id = stoi(textId);
                   id++;
                }

                datatableContent[i] += to_string(id) + "    ";
                splitter = splitter.substr(splitter.find_first_of("    ") + 4);

                int j = 1;
                while(splitter.compare("") != 0){

                    cout<<"\nPlease enter \"" + splitter.substr(0, splitter.find_first_of("(")) + "\": ";

                    if( getDatatableColumnType(datatableContent[i], j).compare("string") == 0){
                        if(!isEverySecondString){
                            getline(cin, value);
                            isEverySecondString = true;
                        } else {
                            getline(cin, value);
                            getline(cin, value);
                            isEverySecondString = false;
                        }
                        if(value.compare("") == 0){
                            value = "NULL";
                            datatableContent[i] += "" + value + "    ";
                        } else {
                            datatableContent[i] += "\"" + value + "\"    ";
                        }
                    } else {

                        getline(cin, value);
                        isEverySecondString = false;

                        if(value.compare("") == 0){
                            value = "NULL";
                        }
                        datatableContent[i] += value + "    ";
                    }

                    if(splitter.find("    ") != string::npos){
                        splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                    } else {
                        datatableContent[i] = datatableContent[i].substr(0, datatableContent[i].length() - 4);
                        splitter = "";
                    }
                    j++;
                }

                currentDatatableIndex = i;

                saveFile(fileName);

                datatableContent[i] = datatableContent[i].substr(datatableName[i].length() + 1) + "\n";

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not insert.\n"<<endl;
            chooseFunction();
        }
    }
    void renameDatatable(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string newDatatableName;
                bool found = false;
                bool hasDatatableName = false;

                cout<<"\nPlease enter new datatable name: ";
                cin>>newDatatableName;


                int j = 0;
                while(datatableName[j].compare("") != 0){
                    if(datatableName[j].compare(newDatatableName) == 0){
                        hasDatatableName = true;
                        break;
                    }
                    j++;
                }

                if(!hasDatatableName){

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                datatableContent[i] = newDatatableName + "\n" + datatableContent[i];

                currentDatatableIndex = i;

                saveFile(fileName);

                closeFile();

                ifstream fin;
                string fileLine;

                fin.open("Database.txt");

                int i = 0;
                while (getline(fin, fileLine)){

                   if(fileLine.find("    ") != string::npos){
                       if(fileLine.substr(0, fileLine.find("    ")).compare(datatable) == 0){
                           databaseContent += newDatatableName + fileLine.substr(fileLine.find("    "));
                           found = true;
                       }
                   }
                   if(!found){
                      databaseContent += fileLine + "\n";
                   }
                   found = false;
                   i++;
                }
                databaseContent += "\n";

                saveFile("Database.txt");

                fin.clear();
                fin.close();

                loadData();
                } else {
                    cout<<"There is already table with the same name. Can not rename."<<endl;
                }
                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not rename datatable.\n"<<endl;
            chooseFunction();
        }
    }
    int countRows(string datatable, string value, int columnToSelect){
        if(datatableName[0].compare("") != 0){

            bool existDatatable = false;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                return 0;
            } else {

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                ifstream fin;
                string fileLine;
                string cell[100][100];

                fin.open(fileName);

                if(fin.fail()){
                    cout<<"Wrong file Name\n"<<fileName<<endl;
                }

                int y = 0;
                int row = 0;
                int column = 0;
                while (getline(fin, fileLine)){
                    string splitter = fileLine;

                    if(y > 3){
                        column = 0;
                        while(splitter.compare("") != 0){

                            if(splitter.find("    ") != string::npos){

                                if(splitter.substr(0, 1).compare("\"") == 0){

                                    splitter = splitter.substr(1);
                                    cell[row][column] = "\"" + splitter.substr(0, splitter.find_first_of("\"")) + "\"";
                                    splitter = splitter.substr(splitter.find_first_of("\"") + 5);
                                } else {
                                    cell[row][column] = splitter.substr(0, splitter.find_first_of("    "));
                                    splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                                }
                                column++;
                            } else {

                                cell[row][column] = splitter;
                                splitter = "";
                            }
                        }
                        row++;
                    }
                    y++;
                }
                row--;

                int counter = 0;

                int k = 0;
                while(k <= row){

                    int t = 0;
                    while(t <= column){

                        if(t == columnToSelect && cell[k][t].compare("NULL") == 0 && value.compare("") == 0){
                           counter++;
                        }
                        if(t == columnToSelect && cell[k][t].compare(value) == 0){
                           counter++;
                        }
                        t++;
                    }
                    k++;
                }

                return counter;

            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not count rows.\n"<<endl;
            return 0;
        }
    }
    void innerJoin(){
        if(datatableName[0].compare("") != 0){

            string firstDatatable = "";
            string secondDatatable = "";
            bool existFirstDatatable = false;
            bool existSecondDatatable = false;
            int columnFirstDatatable;
            int columnSecondDatatable;

            cout<<"\nPlease enter first datatable name: ";
            cin>>firstDatatable;
            cout<<"\nPlease enter first datatable column: ";
            cin>>columnFirstDatatable;
            cout<<"\nPlease enter second datatable name: ";
            cin>>secondDatatable;
            cout<<"\nPlease enter second datatable column: ";
            cin>>columnSecondDatatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(firstDatatable) == 0){
                    existFirstDatatable = true;
                    break;
                }
                i++;
            }

            int j = 0;
            while(datatableName[j].compare("") != 0){
                if(datatableName[j].compare(secondDatatable) == 0){
                    existSecondDatatable = true;
                    break;
                }
                j++;
            }

            if(!existFirstDatatable && !existSecondDatatable){
                cout<<"\nThere is no datatable with \"" + firstDatatable + "\" or \"" + secondDatatable + "\" name."<<endl;
                chooseFunction();
            } else {

                if(getDatatableColumnType(datatableContent[i], columnFirstDatatable).compare("NULL") == 0 || getDatatableColumnType(datatableContent[j], columnSecondDatatable).compare("NULL") == 0){
                    cout<<"\nInvalid columns."<<endl;
                } else {
                    if(getDatatableColumnType(datatableContent[i], columnFirstDatatable).compare(getDatatableColumnType(datatableContent[j], columnSecondDatatable)) != 0){
                        cout<<"\nIncompatible column types. Can not join " + getDatatableColumnType(datatableContent[i], columnFirstDatatable) + " with " + getDatatableColumnType(datatableContent[j], columnSecondDatatable) + "."<<endl;
                    } else {

                        string fileNameFirst = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                        fileNameFirst = fileNameFirst.substr(0, fileNameFirst.find_first_of("\n"));

                        string fileNameSecond = databaseContent.substr(databaseContent.find(datatableName[j]) + datatableName[j].length() + 4);
                        fileNameSecond = fileNameSecond.substr(0, fileNameSecond.find_first_of("\n"));

                        string newDatatableContent = "";
                        string newDatatableName;
                        int newDatatableRow = 0;

                        newDatatableName = datatableName[i] + "Joined" + datatableName[j];
                        newDatatableContent += newDatatableName + "\n" + datatableContent[i];

                        saveAsFile(newDatatableContent);

                        string columns = newDatatableContent.substr(0, newDatatableContent.find_first_of("######") -1);

                        newDatatableContent = "";
                        newDatatableContent += newDatatableName + "\n" + columns + "\n######\n";

                        cout<<currentSavedFile<<endl;

                        openFile(currentSavedFile);

                        int k = 0;
                        string* pointer = getSelectedElements(fileNameSecond, columnSecondDatatable);
                        string firstColumn[100];
                        string secondColumn[100];
                        string* pointerSecond;


                        int f = 0;
                        while(f < countRows(datatableName[j])){
                           cout<<*(pointer + k)<<endl;
                           firstColumn[f] = *(pointer + k);
                            k++;
                            f++;
                        }

                        pointerSecond = getSelectedElements(fileNameSecond, 1);
                        k = 0;

                        int h = 0;
                        while(h < countRows(datatableName[j])){
                           cout<<*(pointerSecond + k)<<endl;
                           secondColumn[h] = *(pointerSecond + k);
                            k++;
                            h++;
                        }


                        saveFile(currentSavedFile);
                    }
                }

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not inner join.\n"<<endl;
            chooseFunction();
        }
    }
    void aggregate(){
        if(datatableName[0].compare("") != 0){

            string datatable = "";
            bool existDatatable = false;

            cout<<"\nPlease enter datatable name: ";
            cin>>datatable;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                chooseFunction();
            } else {

                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                chooseFunction();
            }
        } else {
            cout<<"\nThere is no loaded datatable. Can not aggregate.\n"<<endl;
            chooseFunction();
        }
    }

private:
    string databaseContent = "";
    string currentSavedFile = "";
    string datatableName[100];
    string datatableContent[100];
    int datatableIndex = -1;
    int currentDatatableIndex = 0;

    int countRows(string datatable){

    if(datatableName[0].compare("") != 0){

            bool existDatatable = false;

            int i = 0;
            while(datatableName[i].compare("") != 0){
                if(datatableName[i].compare(datatable) == 0){
                    existDatatable = true;
                    break;
                }
                i++;
            }
            if(!existDatatable){
                cout<<"There is no datatable with " + datatable + " name."<<endl;
                return 0;
            } else {
                string fileName = databaseContent.substr(databaseContent.find(datatableName[i]) + datatableName[i].length() + 4);
                fileName = fileName.substr(0, fileName.find_first_of("\n"));

                ifstream fin;
                string fileLine;
                string cell[100][100];

                fin.open(fileName);

                if(fin.fail()){
                    cout<<"Wrong file Name\n"<<fileName<<endl;
                }

                int y = 0;
                int row = 0;
                int column = 0;
                while (getline(fin, fileLine)){
                    string splitter = fileLine;

                    if(y > 3){
                        column = 0;
                        while(splitter.compare("") != 0){

                            if(splitter.find("    ") != string::npos){

                                if(splitter.substr(0, 1).compare("\"") == 0){

                                    splitter = splitter.substr(1);
                                    cell[row][column] = "\"" + splitter.substr(0, splitter.find_first_of("\"")) + "\"";
                                    splitter = splitter.substr(splitter.find_first_of("\"") + 5);
                                } else {
                                    cell[row][column] = splitter.substr(0, splitter.find_first_of("    "));
                                    splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                                }
                                column++;
                            } else {

                                cell[row][column] = splitter;
                                splitter = "";
                            }
                        }
                        row++;
                    }
                    y++;
                }

                return row;
            }
        }
    }
    void openFile(string fileName){
         ifstream fin;
         string fileLine;

         fin.open(fileName);

         if(fin.is_open()){

         cout<<"Successfully opened: " + fileName + "\n"<<endl;

         if(fileName.compare("Database.txt") == 0){

             while (getline(fin, fileLine)){
                 databaseContent += fileLine + "\n";
             }
             databaseContent = databaseContent.substr(0, databaseContent.size()-1);

         } else {

             datatableIndex++;
             int i = 0;
             while (getline(fin, fileLine)){
                 if(i == 0){
                     datatableName[datatableIndex] = "";
                     datatableName[datatableIndex] += fileLine;
                     currentDatatableIndex = datatableIndex;
                 } else {
                     datatableContent[datatableIndex] += fileLine + "\n";
                 }
                 i++;
             }
         }
         fin.clear();
         fin.close();

         } else {
            cout<<"No file found. Creating new file.\n"<<endl;
            saveAsFile("");
         }
         fin.clear();
         fin.close();
    }
    void loadData(){
         ifstream fin;
         string fileLine;

         fin.open("Database.txt");

         int i = 0;
         while (getline(fin, fileLine)){
             databaseContent += fileLine + "\n";
             if(i > 1){
                openFile(fileLine.substr(fileLine.find("    ") + 4));
             }
             i++;
         }
         databaseContent = databaseContent.substr(0, databaseContent.size()-1);

         fin.clear();
         fin.close();
    }
    void doOperation(string operation, string fileName){

         ifstream fin;
         string fileLine;
         string datatable;
         string cell[100][100];

         fin.open(fileName);

         if(fin.fail()){
            cout<<"Wrong file Name\n"<<fileName<<endl;
         }

         int i = 0;
         int row = 0;
         int column = 0;
         while (getline(fin, fileLine)){
             string splitter = fileLine;

             if(i == 0){
                datatable = fileLine;
             }

             if(i > 3){
                column = 0;
                while(splitter.compare("") != 0){

                    if(splitter.find("    ") != string::npos){

                       if(splitter.substr(0, 1).compare("\"") == 0){

                            splitter = splitter.substr(1);
                            cell[row][column] = "\"" + splitter.substr(0, splitter.find_first_of("\"")) + "\"";
                            splitter = splitter.substr(splitter.find_first_of("\"") + 5);
                       } else {
                            cell[row][column] = splitter.substr(0, splitter.find_first_of("    "));
                            splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                       }
                       column++;
                    } else {

                        cell[row][column] = splitter;
                        splitter = "";
                    }
                }
                row++;
             }
             i++;
         }
         row--;

         if(operation.compare("print") == 0){

            string command = "";
            string page[100];
            int pageIndex = 0;

            int k = 0;
            while(k <= row){

                page[pageIndex] += "\n";

                int t = 0;
                while(t <= column){

                    page[pageIndex] += cell[k][t] + "    ";
                    t++;
                }
                k++;
                if(k % 5 ==0){
                    pageIndex++;
                }
            }
            pageIndex = 0;

            while(command.compare("exit") != 0){
               bool hasValidFun = false;
               cout<<page[pageIndex] + "\n"<<endl;

               cout<<"Please enter action (cmd: <nextPage>, <prevPage> or <exit>): ";
               cin>>command;

               if(command.compare("nextPage") == 0){
                    hasValidFun = true;
                    pageIndex++;
                    if(page[pageIndex].compare("") == 0){
                        cout<<"This is the last page\n"<<endl;
                        pageIndex--;
                    }
               }
               if(command.compare("prevPage") == 0){
                    hasValidFun = true;
                    pageIndex--;
                    if(pageIndex < 0){
                        cout<<"This is the first page\n"<<endl;
                        pageIndex++;
                    }
               }
               if(command.compare("exit") == 0){
                    cout<<endl;
                    hasValidFun = true;
               }
               if(!hasValidFun){
                    cout<<"\nInvalidCommand"<<endl;
               }
            }
         }
         if(operation.compare("addcolumn") == 0){

            int p = 0;
            while(datatableName[p].compare("") != 0){
                if(datatableName[p].compare(datatable) == 0){
                    currentDatatableIndex = p;
                    break;
                }
                p++;
            }

            int k = 0;
            while(k <= row){

                int t = 0;
                while(t <= column){

                    datatableContent[p] += cell[k][t] + "    ";
                    if(t == column){
                        datatableContent[p] += "NULL\n";
                    }
                    t++;
                }
                k++;
            }

            saveFile(fileName);
         }

         fin.clear();
         fin.close();
    }
    void doOperation(string operation, string fileName, int columnToSelect, string value){

         ifstream fin;
         string fileLine;
         string datatable;
         string cell[100][100];

         fin.open(fileName);

         if(fin.fail()){
            cout<<"Wrong file Name\n"<<fileName<<endl;
         }

         int i = 0;
         int row = 0;
         int column = 0;
         while (getline(fin, fileLine)){
             string splitter = fileLine;

             if(i == 0){
                datatable = fileLine;
             }

             if(i > 3){
                column = 0;
                while(splitter.compare("") != 0){

                    if(splitter.find("    ") != string::npos){

                       if(splitter.substr(0, 1).compare("\"") == 0){

                            splitter = splitter.substr(1);
                            cell[row][column] = "\"" + splitter.substr(0, splitter.find_first_of("\"")) + "\"";
                            splitter = splitter.substr(splitter.find_first_of("\"") + 5);
                       } else {
                            cell[row][column] = splitter.substr(0, splitter.find_first_of("    "));
                            splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                       }
                       column++;
                    } else {

                        cell[row][column] = splitter;
                        splitter = "";
                    }
                }
                row++;
             }
             i++;
         }
         row--;

         if(operation.compare("print") == 0){

            string command = "";
            string page[100];
            int pageIndex = 0;

            int k = 0;
            while(k <= row){

                page[pageIndex] += "\n";

                int t = 0;
                while(t <= column){

                    page[pageIndex] += cell[k][t] + "    ";
                    t++;
                }
                k++;
                if(k % 5 ==0){
                    pageIndex++;
                }
            }
            pageIndex = 0;

            while(command.compare("exit") != 0){
               bool hasValidFun = false;
               cout<<page[pageIndex] + "\n"<<endl;

               cout<<"Please enter action (cmd: <nextPage>, <prevPage> or <exit>): ";
               cin>>command;

               if(command.compare("nextPage") == 0){
                    hasValidFun = true;
                    pageIndex++;
                    if(page[pageIndex].compare("") == 0){
                        cout<<"This is the last page\n"<<endl;
                        pageIndex--;
                    }
               }
               if(command.compare("prevPage") == 0){
                    hasValidFun = true;
                    pageIndex--;
                    if(pageIndex < 0){
                        cout<<"This is the first page\n"<<endl;
                        pageIndex++;
                    }
               }
               if(command.compare("exit") == 0){
                    cout<<endl;
                    hasValidFun = true;
               }
               if(!hasValidFun){
                    cout<<"\nInvalidCommand"<<endl;
               }
            }
         }

         if(operation.compare("select") == 0){

            string command = "";
            string page[100];
            int pageIndex = 0;
            int rowsInPage = 0;
            bool isValidRow = false;

            int k = 0;
            while(k <= row){

                isValidRow = false;

                int t = 0;
                while(t <= column){

                    if(t == columnToSelect && cell[k][t].compare(value) == 0){
                       isValidRow = true;
                       break;
                    }
                    t++;
                }
                if(isValidRow){
                    page[pageIndex] += "\n";

                    int p = 0;
                    while(p <= column){
                       page[pageIndex] += cell[k][p] + "    ";
                       p++;
                    }
                    rowsInPage++;
                }
                k++;
                if(rowsInPage == 4){
                    rowsInPage = 0;
                    pageIndex++;
                }
            }
            pageIndex = 0;

            if(page[pageIndex].compare("") != 0){
            while(command.compare("exit") != 0){
               bool hasValidFun = false;
               cout<<page[pageIndex] + "\n"<<endl;

               cout<<"Please enter action (cmd: <nextPage>, <prevPage> or <exit>): ";
               cin>>command;

               if(command.compare("nextPage") == 0){
                    hasValidFun = true;
                    pageIndex++;
                    if(page[pageIndex].compare("") == 0){
                        cout<<"This is the last page\n"<<endl;
                        pageIndex--;
                    }
               }
               if(command.compare("prevPage") == 0){
                    hasValidFun = true;
                    pageIndex--;
                    if(pageIndex < 0){
                        cout<<"This is the first page\n"<<endl;
                        pageIndex++;
                    }
               }
               if(command.compare("exit") == 0){
                    cout<<endl;
                    hasValidFun = true;
               }
               if(!hasValidFun){
                    cout<<"\nInvalidCommand"<<endl;
               }
            }
         } else {
             cout<<"\nInvalid entry data. Could not find rows with value " + value + " on \"" + to_string(columnToSelect) + "\" column.\n"<<endl;
         }
         }

         if(operation.compare("update") == 0){

            string newValue = "";
            bool isValidRow = false;

            cout<<"\nPlease enter the new value: ";
            getline(cin, newValue);
            getline(cin, newValue);

            int p = 0;
            while(datatableName[p].compare("") != 0){
                if(datatableName[p].compare(datatable) == 0){
                    currentDatatableIndex = p;
                    break;
                }
                p++;
            }

            if(value.compare("NULL") == 0){
                if(getDatatableColumnType(datatableContent[p], columnToSelect).compare("string") == 0){
                    newValue = "\"" + newValue + "\"";
                }
            }
            if(value.substr(0, 1).compare("\"") == 0){
                newValue = "\"" + newValue + "\"";
                if(newValue.compare("\"\"") == 0){
                    newValue = "NULL";
                }
            }
            if(newValue.compare("") == 0){
                newValue = "NULL";
            }

            int k = 0;
            while(k <= row){

                int t = 0;
                while(t <= column){

                    if(t == columnToSelect && cell[k][t].compare(value) == 0){
                       isValidRow = true;
                       cell[k][t] = newValue;
                    }

                    datatableContent[p] += cell[k][t];

                    if(t != column){
                        datatableContent[p] += "    ";
                    } else {
                        datatableContent[p] += "\n";
                    }

                    t++;
                }
                k++;
            }

            if(!isValidRow){
                cout<<"\nInvalid entry data. Could not find rows with value " + value + " on \"" + to_string(columnToSelect) + "\" column.\n"<<endl;
            } else {
                saveFile(fileName);
            }
         }

         if(operation.compare("delete") == 0){

            bool isValidRow = false;
            bool hasValidRow = false;

            int p = 0;
            while(datatableName[p].compare("") != 0){
                if(datatableName[p].compare(datatable) == 0){
                    currentDatatableIndex = p;
                    break;
                }
                p++;
            }

            int k = 0;
            while(k <= row){

                int t = 0;
                while(t <= column){

                    if(t == columnToSelect && cell[k][t].compare(value) == 0){
                       isValidRow = true;
                       hasValidRow = true;
                    }
                    t++;
                }

                if(isValidRow){

                    int y = 0;
                    while(y <= column){
                       cell[k][y] = "";
                       y++;
                    }
                } else {

                    int y = 0;
                    while(y <= column){

                       datatableContent[p] += cell[k][y];

                       if(y != column){
                           datatableContent[p] += "    ";
                       } else {
                           datatableContent[p] += "\n";
                       }
                       y++;
                    }
                }
                isValidRow = false;

                k++;
            }

            if(!hasValidRow){
                cout<<"\nInvalid entry data. Could not find rows with value " + value + " on \"" + to_string(columnToSelect) + "\" column.\n"<<endl;
            } else {
                saveFile(fileName);
            }
         }


         fin.clear();
         fin.close();
    }
    void doOperation(string operation, string fileName, int columnToSelect, string value, string newValue, string content){
        ifstream fin;
         string fileLine;
         string datatable;
         string cell[100][100];

         fin.open(fileName);

         if(fin.fail()){
            cout<<"Wrong file Name\n"<<fileName<<endl;
         }

         int i = 0;
         int row = 0;
         int column = 0;
         while (getline(fin, fileLine)){
             string splitter = fileLine;

             if(i == 0){
                datatable = fileLine;
             }

             if(i > 3){
                column = 0;
                while(splitter.compare("") != 0){

                    if(splitter.find("    ") != string::npos){

                       if(splitter.substr(0, 1).compare("\"") == 0){

                            splitter = splitter.substr(1);
                            cell[row][column] = "\"" + splitter.substr(0, splitter.find_first_of("\"")) + "\"";
                            splitter = splitter.substr(splitter.find_first_of("\"") + 5);
                       } else {
                            cell[row][column] = splitter.substr(0, splitter.find_first_of("    "));
                            splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                       }
                       column++;
                    } else {

                        cell[row][column] = splitter;
                        splitter = "";
                    }
                }
                row++;
             }
             i++;
         }
         row--;

         if(operation.compare("update") == 0){

            bool isValidRow = false;

            if(value.compare("NULL") == 0){
                if(getDatatableColumnType(content, columnToSelect).compare("string") == 0){
                    newValue = "\"" + newValue + "\"";
                }
            }
            if(value.substr(0, 1).compare("\"") == 0){
                newValue = "\"" + newValue + "\"";
                if(newValue.compare("\"\"") == 0){
                    newValue = "NULL";
                }
            }
            if(newValue.compare("") == 0){
                newValue = "NULL";
            }

            int k = 0;
            while(k <= row){

                int t = 0;
                while(t <= column){

                    if(t == columnToSelect && cell[k][t].compare(value) == 0){
                       isValidRow = true;
                       cell[k][t] = newValue;
                    }

                    content += cell[k][t];

                    if(t != column){
                        content += "    ";
                    } else {
                        content += "\n";
                    }

                    t++;
                }
                k++;
            }

            if(!isValidRow){
                cout<<"\nInvalid entry data. Could not find rows with value " + value + " on \"" + to_string(columnToSelect) + "\" column.\n"<<endl;
            } else {
                saveFile(fileName);
            }
         }

         fin.clear();
         fin.close();
    }
    string* getSelectedElements(string fileName, int columnToSelect){

         ifstream fin;
         string fileLine;
         string datatable;
         static string result[100];
         string cell[100][100];
         int resultRow = 0;

         fin.open(fileName);

         if(fin.fail()){
            cout<<"Wrong file Name\n"<<fileName<<endl;
         }

         int i = 0;
         int row = 0;
         int column = 0;
         while (getline(fin, fileLine)){
             string splitter = fileLine;

             if(i == 0){
                datatable = fileLine;
             }

             if(i > 3){
                column = 0;
                while(splitter.compare("") != 0){

                    if(splitter.find("    ") != string::npos){

                       if(splitter.substr(0, 1).compare("\"") == 0){

                            splitter = splitter.substr(1);
                            cell[row][column] = "\"" + splitter.substr(0, splitter.find_first_of("\"")) + "\"";
                            splitter = splitter.substr(splitter.find_first_of("\"") + 5);
                       } else {
                            cell[row][column] = splitter.substr(0, splitter.find_first_of("    "));
                            splitter = splitter.substr(splitter.find_first_of("    ") + 4);
                       }
                       column++;
                    } else {

                        cell[row][column] = splitter;
                        splitter = "";
                    }
                }
                row++;
             }
             i++;
         }
         row--;

         int k = 0;
         while(k <= row){

            int t = 0;
            while(t <= column){

                if(t == columnToSelect){
                    result[resultRow] += cell[k][t];
                    resultRow ++;
                }
                t++;
            }
            k++;
         }

         fin.clear();
         fin.close();

         return result;
    }
    string getDatatableColumnType(string datatableContent, int column){

        string type= "";
        string splitter = "";
        splitter = datatableContent.substr(0, datatableContent.find_first_of("######"));
        bool isLastColumn = false;

        int i = 0;
        while(i <= column){
            if(isLastColumn){
                type = "NULL";
            }
            if(splitter.find("    ") != string::npos){

                type = splitter.substr(0, splitter.find_first_of("    "));
                splitter = splitter.substr(splitter.find_first_of("    ") + 4);
            } else {
                if(!isLastColumn){
                    type = splitter;
                }
                isLastColumn = true;
            }
            i++;
        }
        bool isValidType = false;
        if(type.find("string") != string::npos){
            type = "string";
            isValidType = true;
        }
        if(type.find("int") != string::npos){
            type = "int";
            isValidType = true;
        }
        if(type.find("double") != string::npos){
            type = "double";
            isValidType = true;
        }
        if(type.find("NULL") != string::npos){
            type = "NULL";
            isValidType = true;
        }
        if(!isValidType){
            cout<<"\nInvalid column type!"<<endl;
        }
        return type;
    }
    string getDatatableColumnName(string datatableContent, int column){


        string columnName= "";
        string splitter = "";
        splitter = datatableContent.substr(0, datatableContent.find_first_of("######"));
        bool isLastColumn = false;

        int i = 0;
        while(i <= column){
            if(isLastColumn){
                columnName = "NULL";
            }
            if(splitter.find("    ") != string::npos){

                columnName = splitter.substr(0, splitter.find_first_of("    "));
                splitter = splitter.substr(splitter.find_first_of("    ") + 4);
            } else {
                if(!isLastColumn){
                    columnName = splitter.substr(0, splitter.length() - 1);
                }
                isLastColumn = true;
            }
            i++;
        }
        return columnName;
    }
};

int main()
{
    cout<<"Function list:\nclose\nsave\nsaveAs\nhelp\nexit\nshowtables\ndescribe\nprint\nexport\nselect\naddcolumn\nupdate\ndelete\ninsert\nrename\ncount\ninnerjoin\naggregate\n"<<endl;

    Database test;
    test.chooseFunction();

    return 0;
}
