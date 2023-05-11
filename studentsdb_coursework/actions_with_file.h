#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>


using namespace std;


List<StudentsToFile> changeformatstudents(List<Student>& studentsdatabase) {
    List<StudentsToFile> students_to_file;
    for (int i = 0; i < studentsdatabase.size(); i++) {
        students_to_file.pushback(StudentsToFile(*studentsdatabase.getbyindex(i)));
    }
    return students_to_file;
}


List<Student> readfromfile() {

    ifstream in;
    in.open("database.bin", ios::in | ios::binary);
    if (!in)
    {
        cout << "Нeт Файла с данными";
        in.close();
        return List<Student>();
    }
    else
    {
        List<Student> students;
        StudentsToFile newstudtofile;

        while (in.read((char*)(&newstudtofile), sizeof(StudentsToFile)))
        {
            students.pushback(newstudtofile.file_to_database());
            
        }
        in.close();
        return students;
    }

}
