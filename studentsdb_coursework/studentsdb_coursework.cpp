#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "class_student.h"
#include "class_database_client.h"
#include "actions_with_file.h"
#include "class_student.h"


using namespace std;
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    List<Student> students = readfromfile();
    DatabaseClient client(students);
    client.showmenu();
  
}