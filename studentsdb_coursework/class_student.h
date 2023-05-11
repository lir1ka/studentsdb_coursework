#pragma once
#include <string>
#include "class_date.h"
#include "class_list.h"
#if defined(max)
#undef max
#endif

using namespace std;



class Subject {
private:
    char title[35];
    char mark[15];
    bool empty;
public:
    //bool empty;
    Subject() {
        title[0] = '\0';
        mark[0] = '\0';
        
    }
    void setsubj() {
        cout << "¬ведите название предмета: ";
        cin.getline(this->title, 35);
    }
    void setmark(string _mark) { 
        strcpy_s(this->mark, _mark.c_str());
    }
    void setsubj(string _title) {
        strcpy_s(this->title, _title.c_str());
    }
    string gettitle() {
        return this->title;
    }
    string getmark() {
        return this->mark;
    }
    char* get_char_title() {
        return this->title;
    }
    char* get_char_mark() {
        return this->mark;
    }
};
class Student {
private:
    char surname[20]; char firstname[20], secondname[20];
    Date birthdate;
    Date admissiondate;
    char institut[35];
    char department[35];
    char group[20];
    char ID[20];
    List<Subject> sessions[9];
    bool gender; // 0 - female, 1 - male.
public:
    Student() {
        surname[0] = '\0';
        firstname[0] = '\0';
        secondname[0] = '\0';
        birthdate = Date();
        admissiondate = Date();
        institut[0] = '\0';
        department[0] = '\0';
        group[0] = '\0';
        ID[0] = '\0';
        gender = 0;
    }
    void fillStudent() {
        this->setname();
        this->setbirthdate();
        this->setadmissiondate();
        this->setinstitut();
        this->setdepartment();
        this->setgroup();
        this->setid();
        this->setgender();

    }
    void setname() {
        cout << "¬ведите фамилию студента: ";
        cin.getline(this->surname, 20);
        cout << "¬ведите им€ студента: ";
        cin.getline(this->firstname, 20);
        cout << "¬ведите отчество студента: ";
        cin.getline(this->secondname, 20);
    }
    void setfirstname() {
        cout << "¬ведите им€ студента: ";
        cin.getline(this->firstname, 20);
    }
    void setfirstname(string _firstname) {
        strcpy_s(this->firstname, _firstname.c_str());
    }
    void setsurname() {
        cout << "¬ведите фамилию студента: ";
        cin.getline(this->surname, 20);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void setsurname(string _surname) {
        strcpy_s(this->surname, _surname.c_str());
    }
    void setsecondname() {
        cout << "¬ведите отчество студента: ";
        cin.getline(this->secondname, 20);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void setsecondname(string _secondname) {
        strcpy_s(this->secondname, _secondname.c_str());
    }
    void setbirthdate() {
        int day, month, year;
        cout << "¬ведите день рождени€ студента: ";
        cin >> day;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "¬ведите мес€ц рождени€ студента: ";
        cin >> month;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "¬ведите год рождени€ студента: ";
        cin >> year;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (birthdate.setdate(day, month, year) == 0) {
            cout << "¬ведена некорректна€ дата" << endl;
        }
    }
    void setadmissiondate() {
        int day, month, year;
        cout << "¬ведите день поступлени€ студента в ¬”«: ";
        cin >> day;
        cout << "¬ведите мес€ц поступлени€ студента в ¬”«: ";
        cin >> month;
        cout << "¬ведите год постулпени€ студента в ¬”«: ";
        cin >> year;
        if (admissiondate.setdate(day, month, year) == 0) {
            cout << "¬ведена некорректна€ дата";
        }
        
    }
    void setbirthdate(Date _birthdate) {
        this->birthdate = _birthdate;
    }
    void setadmissiondate(Date _admissiondate) {
        this->admissiondate = _admissiondate;
    }
    void setinstitut() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "¬ведите институт, в котором обучаетс€ студент: ";
        cin.getline(this->institut, 35);

    }
    void setinstitut(string _institut) {
        strcpy_s(this->institut, _institut.c_str());
    }
    void setdepartment() {
        cout << "¬ведите кафедру, на которой обучаетс€ студент: ";
        cin.getline(this->department, 35);

    }
    void setdepartment(string _department) {
        strcpy_s(this->department, _department.c_str());
    }
    void setgroup() {
        cout << "¬ведите группу, в которой обучаетс€ студент: ";
        cin.getline(this->group, 20);
    }
    void setgroup(string _group) {
        strcpy_s(this->group, _group.c_str());
    }
    void setid() {
        cout << "¬ведите номер зачетной книжки студента: ";
        cin.getline(this->ID, 20);;
    }
    void setid(string _id) {
        strcpy_s(this->ID, _id.c_str());
    }
    void setgender() {
        int g;
        cout << "¬ведите пол студента(0-женский, 1-мужской): ";
        cin >> g;
        this->gender = g;
    }
    void setgender(bool _gender) {
        this->gender = _gender;
    }
    char* get_char_surname() {
        return this->surname;
    }
    char* get_char_firstname() {
        return this->firstname;
    }
    char* get_char_secondname() {
        return this->secondname;
    }
    char* get_char_institut() {
        return this->institut;
    }
    char* get_char_department() {
        return this->department;
    }
    char* get_char_group() {
        return this->group;
    }
    char* get_char_id() {
        return this->ID;
    }
    string get_surname() {
        char result[100];
        strcpy_s(result, this->surname);
        return result;
    }
    string get_firstname() {
        char result[100];
        strcpy_s(result, this->firstname);
        return result;
    }
    string get_secondname() {
        char result[100];
        strcpy_s(result, this->secondname);
        return result;
    }
    Date get_birthdate() {
        return this->birthdate;
    }
    Date get_admissiondate() {
        return this->admissiondate;
    }
    int get_year_birthdate() {
        return this->birthdate.getyear();
    }
    string get_intstitut() {
        char result[100];
        strcpy_s(result, this->institut);
        return result;
    }
    string get_department() {
        char result[100];
        strcpy_s(result, this->department);
        return result;
    }
    string get_group() {
        char result[100];
        strcpy_s(result, this->group);
        return result;
    }
    string get_id() {
        char result[100];
        strcpy_s(result, this->ID);
        return result;
    }
    bool get_gender() {
        return this->gender;
    }
    //void printstudent() {
    //    cout << this->surname << " " << this->firstname << " " << this->secondname << endl;
    //}
    string showstudent() {
        char result[84];
        strcpy_s(result, surname);
        strcat_s(result, " ");
        strcat_s(result, firstname);
        strcat_s(result, " ");
        strcat_s(result, secondname);
        return  result;
    }
    string showgroup() {
        char result[84];
        strcpy_s(result, group);
        return result;
    }
    
    List<Subject>* getsession(int index) {
        return sessions+index;
    }
    int getsessionssize() {
        return size(sessions);
    }
    short counts_five_marks() {
        short count = 0;
        for (int i = 0; i < this->getsession(1)->size(); i++) {
            if (this->getsession(1)->getbyindex(i)->getmark() == "5") {
                count++;
            }
        }
        return count;
    }
    bool compare(Student& stud1, Student& stud2) {
        if (stud1.counts_five_marks() > stud2.counts_five_marks()) {
            return true;
        }
        return false;
    }
};