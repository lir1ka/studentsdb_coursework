#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>


using namespace std;
void Crypt(string fileName)
{
    srand(time(NULL));
    string fileNAME = fileName.substr(0, fileName.find_last_of('.'));
    char pass[65];
    for (int i = 0; i < 64; ++i)
    {
        switch (rand() % 3)
        {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
        }
    }
    pass[64] = '\0';
    string command = "openssl\\bin\\openssl.exe enc -pbkdf2 -aes-256-cbc -salt -in database.bin -out database.bin.enc -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove(fileName.c_str()) != 0)
    {
        cout << "[ERROR] - deleting file" << endl;
    }
    ofstream file;
    file.open(fileNAME + "_key.bin", ios::binary);
    file.write(pass, 64);
    file.close();
    command = "OpenSSL\\bin\\openssl.exe pkeyutl -encrypt -inkey rsa.public -pubin -in " + fileNAME + "_key.bin -out " + fileNAME + "_key.bin.enc";
    system(command.c_str());
    if (remove((fileNAME + "_key.bin").c_str()) != 0)
    {
        cout << "[ERROR] - deleting file" << endl;
    }
}
void Decrypt(string fileName)
{
    string fileNAME = fileName.substr(0, fileName.find_last_of('.'));
    string command = "OpenSSL\\bin\\openssl.exe pkeyutl -decrypt -inkey rsa.private -in " + fileNAME + "_key.bin.enc -out key.bin";
    system(command.c_str());
    if (remove((fileNAME + "_key.bin.enc").c_str()) != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }
    char pass[65];
    std::ifstream file;
    file.open("key.bin", ios::binary);
    file.read(pass, 65);
    file.close();
    pass[64] = '\0';
    if (remove("key.bin") != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }
    command = "OpenSSL\\bin\\openssl.exe enc -pbkdf2 -aes-256-cbc -d -in " + fileName + ".enc -out " + fileName + " -pass pass:";
    command += pass;
    const char* a = command.c_str();
    system(a);
    if (remove((fileName + ".enc").c_str()) != 0) {
        cout << "[ERROR] - deleting file" << endl;
    }
}

List<StudentsToFile> changeformatstudents(List<Student>& studentsdatabase) {
    List<StudentsToFile> students_to_file;
    for (int i = 0; i < studentsdatabase.size(); i++) {
        students_to_file.pushback(StudentsToFile(*studentsdatabase.getbyindex(i)));
    }
    return students_to_file;
}


List<Student> readfromfile() {

    ifstream in;
    Decrypt("database.bin");
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
        Crypt("database.bin");
        return students;
    }

}
