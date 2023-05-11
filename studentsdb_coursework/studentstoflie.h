#pragma once
#include <string>


using namespace std;
class StudentsToFile {

private:
    char surname[20]; char firstname[20], secondname[20];
    Date birthdate;
    Date admissiondate;
    char institut[35];
    char department[35];
    char group[20];
    char ID[20];
    Subject data[9][10];
    bool gender; // 0 - female, 1 - male.
public:
    StudentsToFile() {
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

    StudentsToFile(Student& student) {
        strcpy_s(this->surname, student.get_char_surname());
        strcpy_s(this->firstname, student.get_char_firstname());
        strcpy_s(this->secondname, student.get_char_secondname());
        this->birthdate = student.get_birthdate();
        this->admissiondate = student.get_admissiondate();
        strcpy_s(this->institut, student.get_char_institut());
        strcpy_s(this->department, student.get_char_department());
        strcpy_s(this->group, student.get_char_group());
        strcpy_s(this->ID, student.get_char_id());
        this->gender = student.get_gender();
        for (int i = 0; i < student.getsessionssize(); i++) {
            List<Subject>* session = student.getsession(i);
            for (int k = 0; k < session->size(); k++) {
                data[i][k].setmark(session->getbyindex(k)->get_char_mark());
                data[i][k].setsubj(session->getbyindex(k)->get_char_title());
            }
        }
    }
    string chartostring(char* a) {
        string s(a);
        return s;
    }
    Student file_to_database() {
        Student student;
        student.setsurname(chartostring(this->surname));
        student.setfirstname(chartostring(this->firstname));
        student.setsecondname(chartostring(this->secondname));
        student.setbirthdate(this->birthdate);
        student.setadmissiondate(this->admissiondate);
        student.setinstitut(chartostring(this->institut));
        student.setdepartment(chartostring(this->department));
        student.setgroup(chartostring(this->group));
        student.setid(chartostring(this->ID));
        student.setgender(this->gender);
        for (int i = 0; i < size(data); i++) {
            for (int k = 0; k < size(data[i]); k++) {
               if (data[i][k].get_char_title()[0] != '\0') {
                   student.getsession(i)->pushback(data[i][k]);
               }
                
            }
        }
        return student;
    }
    
};