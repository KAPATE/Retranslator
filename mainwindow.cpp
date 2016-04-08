#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr unsigned int string2int(const char* str, int h) {
    return !str[h] ? 5381 : (string2int(str, h + 1) * 33) ^ str[h];
}

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nameOfMainTable = "mainTable.txt";
    //ui->tableView->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
     tr("Text Files (*.txt)")).toStdString();

    if (!fileName.empty()) {
        std::ifstream file;
        std::ofstream mainTable;
        std::string buffer {};
        file.open(fileName);
        mainTable.open(nameOfMainTable, std::ios_base::trunc);
        mainTable << std::setw(20) <<"Process" << std::setw(8) << "Memory" << std::setw(10) << "Priority" << std::setw(15) << "User" << std::setw(5) << "id" << std::endl;
        while (file) {
            std::getline(file,buffer);
            std::string command = buffer.substr(0,buffer.find(' '));
            buffer.erase(0,buffer.find(' '));
            char chars[] = "{}- ";
            for (unsigned int i = 0; i < strlen(chars); ++i)
            {
               buffer.erase (std::remove(buffer.begin(), buffer.end(), chars[i]), buffer.end());
            }
            switch (string2int(command.c_str())) {
                case (string2int("add")): { //add process in MAIN table. example syntax: add { ie.exe , 800, 1, user, 2034 }
                std::vector <std::string> code = add(buffer);
                //std::reverse(std::begin(code), std::end(code));
                mainTable << std::setw(20) << code[code.size()-5]<< std::setw(8) << code[code.size()-4] << std::setw(10) << code[code.size()-3] << std::setw(15) << code[code.size()-2] << std::setw(5) << code[code.size()-1]<< std::endl;
                break;
                };

                case (string2int("delete")): { // deletes a row with specified ID. example syntax: delete 2034
                std::ifstream fin(nameOfMainTable.c_str());
                std::ofstream fout("temporary_file.txt");
                std::string line {};
                while (fin) {
                    std::getline(fin,line);
                    if (line.find(buffer.c_str()) == std::string::npos) fout << line << std::endl;
                    else continue;
                }
                fin.close();
                fout.close();
                remove(nameOfMainTable.c_str());
                rename("temporary_file.txt", nameOfMainTable.c_str());
                break;
                }

                case (string2int("sort")): {
                    std::ifstream fin(nameOfMainTable);
                    std::ofstream fout("temporary_file.txt");
                    std::string line {};
                    std::vector <std::string> xz ;
                    QString priority = "priority";
                    QString process = "process";
                    QString memory = "memory";
                    QString user = "user";
                    QString id = "id";
                    QString column = trim(buffer).c_str();

                    std::string header_data{};
                    std::string code {};
                    std::string temp {};

                    std::getline(fin,header_data); // read header data in main table

                    while (fin) {

                        std::getline(fin,line);
                        code.clear();
                        for (int i = 0; i< 5; i++) {
                            if ( i < 4) {
                                temp.append(trim(line));
                                line.clear();
                                line.append(temp);
                                temp.clear();

                                code.append(line.substr(0,line.find(" ")+1));
                                line.erase(0,line.find(" ")+1);
                                //line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
                                //std::cout<<line<<" line after remove"<<std::endl;
                                temp.append(trim(line));
                                line.clear();
                                line.append(temp);
                                temp.clear();
                            }
                        if (i ==4) {
                            temp.append(trim(line));
                            line.clear();
                            line.append(temp);
                            temp.clear();
                            code.append(line.substr(0,line.length()));
                            line.clear();
                        }
                    }
                    if (!code.empty()) xz.push_back(code);
                }
                std::vector <std::string> xz_rezerv;
                for (int i = 0; i < xz.size();i++)
                {
                    xz_rezerv.push_back(xz.at(i));
                }
                if (column == process) {
                    std::sort(xz.begin(), xz.end());
                    for (int i = 0; i < xz.size(); i++)
                    {
                        std::cout << xz.at(i) << std::endl;
                    }
                    std::cout<<"column: process"<<std::endl;
                }

                if (column == memory) {
                    for (int i = 0; i<xz.size();i++){
                        std::string temp {};
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                    }

                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i < xz_rezerv.size(); i++) {
                        std::string buffer = trim(xz_rezerv.at(i));
                        xz_rezerv.at(i).clear();
                        xz_rezerv.at(i).append(buffer);
                        buffer.clear();
                    }

                    for (int i = 0; i < xz.size(); i++) {
                        std::string buffer = trim(xz.at(i));
                        xz.at(i).clear();
                        xz.at(i).append(buffer);
                        buffer.clear();
                    }
                    std::string buffer {};
                    for (int i = 0; i<xz_rezerv.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                buffer.append(xz.at(j));
                                xz.at(j).clear();
                                xz.at(j).append(buffer);
                                buffer.clear();
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                    std::cout << "memory" <<std::endl;
                }

                if (column == priority) {
                    for (int i = 0; i<xz.size();i++){
                        std::string temp {};
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                    }

                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i < xz_rezerv.size(); i++) {
                        std::string buffer = trim(xz_rezerv.at(i));
                        xz_rezerv.at(i).clear();
                        xz_rezerv.at(i).append(buffer);
                        buffer.clear();
                    }

                    for (int i = 0; i < xz.size(); i++) {
                        std::string buffer = trim(xz.at(i));
                        xz.at(i).clear();
                        xz.at(i).append(buffer);
                        buffer.clear();
                    }

                    std::string buffer {};
                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                buffer.append(xz.at(j));
                                xz.at(j).clear();
                                xz.at(j).append(buffer);
                                buffer.clear();
                                break;
                                }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                    std::cout <<"priority"<< std::endl;
                }

                if (column == user) {
                    for (int i = 0; i<xz.size();i++){
                        std::string temp {};
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                    }

                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i < xz_rezerv.size(); i++) {
                        std::string buffer = trim(xz_rezerv.at(i));
                        xz_rezerv.at(i).clear();
                        xz_rezerv.at(i).append(buffer);
                        buffer.clear();
                    }

                    for (int i = 0; i < xz.size(); i++) {
                        std::string buffer = trim(xz.at(i));
                        xz.at(i).clear();
                        xz.at(i).append(buffer);
                        buffer.clear();
                    }

                    std::string buffer {};

                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                buffer.append(xz.at(j));
                                xz.at(j).clear();
                                xz.at(j).append(buffer);
                                buffer.clear();
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                    std::cout << "user" <<std::endl;
                }

                if (column == id) {
                    for (int i = 0; i<xz.size();i++){
                        std::string temp {};
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                        xz.at(i).erase(0, xz.at(i).find(" ") + 1);
                        temp.append(trim(xz.at(i)));
                        xz.at(i).clear();
                        xz.at(i).append(temp);
                        temp.clear();
                    }

                    std::sort(xz.begin(), xz.end());

                    std::string buffer {};

                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz.at(j).c_str());
                                xz.at(j).clear();
                                xz.at(j).append(buffer.c_str());
                                buffer.clear();
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                    std::cout << "id"<<std::endl;
                }
                fin.close();
                fout.close();
                break;
                };

                case (string2int("filter")): {
                break;
                };

            case (string2int("erase")): {
                if (buffer == "mainTable") break;
                else {
                    buffer.append(".txt");
                    remove(buffer.c_str());
                }
                break;
                };

                case (string2int("copy")): { //copy table from mainTable to %nameOfNewTable%. example syntax: copy table2
                std::ifstream fin(nameOfMainTable);
                buffer.append(".txt");
                std::ofstream fout(buffer, std::ios_base::trunc);
                while( std::getline( fin, buffer) ) fout << buffer << std::endl;
                fin.close();
                fout.close();
                break;
                };

                case (string2int("show")): { //show %tableName% in qTextBrowser. example syntax: show   table1
                buffer.append(".txt");
                std::ifstream fin(buffer);
                std::string code;
                while (fin) {
                    std::getline(fin,buffer);
                    code.append(buffer);
                    code.append("\n");
                }
                ui->textBrowser->setText(code.c_str());
                fin.close();
                break;
                };

                case (string2int("append")): { //append %table2% with %table1%. example syntax: append table1,table2
                std::string outputBuffer {};
                std::string name = buffer.substr(0,buffer.find(','));
                name.append(".txt");
                std::ifstream fin(name, std::ios_base::binary);
                buffer.erase(0,buffer.find(',')+1);
                buffer.append(".txt");
                std::ofstream fout(buffer, std::ios_base::binary | std::ios_base::app);
                fout.seekp(0, std::ios_base::end);
                std::getline(fin,buffer);
                while (std::getline(fin, outputBuffer)) { fout << outputBuffer << std::endl; }
                fin.close();
                fout.close();
                break;
                };
                default: { break;}
            }
        }
        file.close();
        mainTable.close();
    }
}
