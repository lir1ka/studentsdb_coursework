#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "class_list.h"
#include "class_student.h"
#include "studentstoflie.h"
#include "actions_with_file.h"



#if defined(max)
#undef max
#endif
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

class DatabaseClient {
private:
    List<Student> studentsdatabase;
    string menubars[5] = {
        "Показать текущую базу данных",
        "Добавить студента в базу данных",
        "Удалить студента из базы данных",
        "Сохранить данные и выйти",
        "Выполнить вариант номер 63"
    };
    string changemenubars[11] = {
        "Изменить имя студента",
        "Изменить фамилию студента",
        "Изменить отчество студента",
        "Изменить год рождения",
        "Изменить год поступления в ВУЗ",
        "Изменить институт",
        "Изменить кафедру",
        "Изменить группу",
        "Изменить номер зачетной книжки",
        "Изменить пол",
        "Изменить/добавить оценки"
    };
    string sessions[9] = {
        "Сессия 1",
        "Сессия 2",
        "Сессия 3",
        "Сессия 4",
        "Сессия 5",
        "Сессия 6",
        "Сессия 7",
        "Сессия 8",
        "Сессия 9"
    };
    string sessionsmenubars[2] = {
        "Добавить информацию о предмете",
        "Удалить предмет/Изменить название предмета/оценку"
    };
    string marks[7]{
        "5",
        "4",
        "3",
        "2",
        "1",
        "Зачтено",
        "Не зачтено"
    };
    string subj_action[3]{
        "Изменить название предмета",
        "Изменить оценку",
        "Удалить информацию о предмете"
    };
   
    void ConsoleCursorVisible(bool show, short size) {

        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
        structCursorInfo.bVisible = show; // изменяем видимость
        structCursorInfo.dwSize = size; // изменяем разzмер
        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
    }
    void GoToXY(short x, short y) {
        SetConsoleCursorPosition(hStdOut, { x, y });
    }
    void myCentr(string s, int wLine) {

        int w = s.length();
        int delta = (wLine - w) / 2;
        cout << left;
        cout.width(delta); cout << " ";
        cout << s;
        cout.width(delta + 1); cout << " ";

    }
    void drawmenu_uplines() {
        SetConsoleTextAttribute(hStdOut, 7);
        int width = 40;
        cout << left << "|"; myCentr("Меню действий", 40); cout << "|" << endl;
        cout.fill(' '); cout.width(width + 1); cout << left << "|"; cout << "|";
        GoToXY(0, 2);
        //cout.width(width + 2); cout.fill('-'); cout << "-" << endl;
        cout << "------------------------------------------";
    }
    void escape() {
        GoToXY(65, 27);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "Нажмите 'ESC', чтобы вернуться на предыдущую страницу";
    }
    void showStudentList() {
        system("CLS");
        int x = 0, y = 3;
        int active_student = 0;
        char ch;
        myCentr("ФИО студента", 40);
        GoToXY(50, 0);
        cout << "Группа студента";
        escape();
        while (true) {
            GoToXY(x, y);
            for (int i = 0; i < studentsdatabase.size(); i++) {
                if (i == active_student) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                cout << studentsdatabase.getbyindex(i)->showstudent() << endl;
                GoToXY(50, 3 + i);
                cout << studentsdatabase.getbyindex(i)->showgroup() << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                system("cls");
                showmenu();
            }
            case UP: {
                if (active_student > 0) --active_student;
                break;
            }
            case DOWN: {
                if (active_student < studentsdatabase.size() - 1) ++active_student;
                break;
            }
            case ENTER: {
                showinfo(active_student);

                break;
            }
            }

        }
    }
    void deletestudent() {
        system("CLS");
        short x = 0, y = 3;
        int active_student = 0;
        char ch;
        while (true) {
            system("CLS");
            GoToXY(x, y);
            for (int i = 0; i < studentsdatabase.size(); i++) {
                if (i == active_student) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                cout << studentsdatabase.getbyindex(i)->showstudent() << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                system("cls");
                showmenu();
            }
            case UP: {
                if (active_student > 0) --active_student;
                break;
            }
            case DOWN: {
                if (active_student < studentsdatabase.size() - 1) ++active_student;
                break;
            }
            case ENTER: {
                studentsdatabase.removebyindex(active_student);
                break;
            }
            }

        }
    }
    void showinfo(int active_student) {
        system("CLS");
        short x = 0, y = 3;
        char ch;
        int active_action = 0;
        escape();
        while (true) {
            short x_changestudentsbars = 35, y_changestudentsbars = 15;
            GoToXY(x, y);
            SetConsoleTextAttribute(hStdOut, 7);
            cout << "Имя студента: " << studentsdatabase.getbyindex(active_student)->get_firstname() << endl;
            cout << "Фамилия студента: " << studentsdatabase.getbyindex(active_student)->get_surname() << endl;
            cout << "Отчество студента: " << studentsdatabase.getbyindex(active_student)->get_secondname() << endl;
            cout << "Дата рождения студента: " << studentsdatabase.getbyindex(active_student)->get_birthdate().printdate() << endl;
            cout << "Дата поступления в ВУЗ: " << studentsdatabase.getbyindex(active_student)->get_admissiondate().printdate() << endl;
            cout << "Институт, в котором обучается студент: " << studentsdatabase.getbyindex(active_student)->get_intstitut() << endl;
            cout << "Кафедра, на которой обучается студент: " << studentsdatabase.getbyindex(active_student)->get_department() << endl;
            cout << "Группа студента: " << studentsdatabase.getbyindex(active_student)->get_group() << endl;
            cout << "Номер зачетной книжки студента: " << studentsdatabase.getbyindex(active_student)->get_id() << endl;
            cout << "Пол студента (0 - женский, 1 - мужской): " << studentsdatabase.getbyindex(active_student)->get_gender() << endl;
            for (int i = 0; i < size(changemenubars); i++) {
                GoToXY(x_changestudentsbars, y_changestudentsbars++);
                if (i == active_action) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                cout << changemenubars[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                showStudentList();
            }
            case UP: {
                if (active_action > 0) --active_action;
                break;
            }
            case DOWN: {
                if (active_action < (size(changemenubars) - 1)) ++active_action;
                break;
            }
            case ENTER: {
                switch (active_action) {
                case 0:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setfirstname();
                    system("cls");
                    break;
                case 1:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setsurname();
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setsecondname();
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setbirthdate();
                    break;
                case 4:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setadmissiondate();
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setinstitut();
                    system("cls");
                    break;
                case 6:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setdepartment();
                    system("cls");
                    break;
                case 7:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setgroup();
                    system("cls");
                    break;
                case 8:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setid();
                    system("cls");
                    break;
                case 9:
                    system("cls");
                    studentsdatabase.getbyindex(active_student)->setgender();
                    system("cls");
                    break;
                case 10:
                    marksinfo(active_student);
                }
            }
            }

        }
    }
    void marksinfo(int activestudent) {
        system("cls");
        int active_session = 0;
        char ch;
        escape();
        while (true) {
            int x = 0, y = 3;

            GoToXY(x, y);
            SetConsoleTextAttribute(hStdOut, 7);
            //List<Subject>* sessions11 = studentsdatabase.getbyindex(activestudent)->getsessions();
            for (int i = 0; i < size(sessions); i++) {
                if (i == active_session) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                GoToXY(x, y++);
                cout << sessions[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                showinfo(activestudent);
            }
            case UP: {
                if (active_session > 0) --active_session;
                break;
            }
            case DOWN: {
                if (active_session < size(sessions) - 1) ++active_session;
                break;
            }
            case ENTER: {
                sessioninfo(activestudent, active_session);
            }
            }
        }
    }
    void sessioninfo(int activestudent, int activesession) {
        system("cls");
        escape();
        char ch;
        int active_action = 0;
        while (true) {
            int x = 0, y = 3;
            //system("CLS");
            GoToXY(x, y);
            int counts_subjects = studentsdatabase.getbyindex(activestudent)->getsession(activesession)->size();
            SetConsoleTextAttribute(hStdOut, 7);
            for (int i = 0; i < counts_subjects; i++) {
                cout << studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(i)->gettitle() << "   " << studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(i)->getmark() << endl;
            }
            short x_addsubj = 35, y_addsubj = 15;
            for (int i = 0; i < size(sessionsmenubars); i++) {
                GoToXY(x_addsubj, y_addsubj++);
                if (i == active_action) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                cout << sessionsmenubars[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                marksinfo(activestudent);
            }
            case UP: {
                if (active_action > 0) --active_action;
                break;
            }
            case DOWN: {
                if (active_action < (size(sessionsmenubars) - 1)) ++active_action;
                break;
            }
            case ENTER: {
                switch (active_action) {
                case 0: {
                    system("cls");
                    setsubj(activestudent, activesession);
                }
                case 1: {
                    changesubj(activestudent, activesession);

                }
                }
            }


            }
        }
    }
    void setsubj(int activestudent, int activesession) {
        system("cls");
        Subject* newsubject = new Subject();
        newsubject->setsubj();
        char ch;
        int active_mark = 0;
        while (true) {
            int x = 0, y = 3;
            system("cls");
            GoToXY(x, y);
            for (int i = 0; i < size(marks); i++) {
                if (i == active_mark) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                GoToXY(x, y++);
                cout << marks[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                return;
            }
            case UP: {
                if (active_mark > 0) --active_mark;
                break;
            }
            case DOWN: {
                if (active_mark < size(marks) - 1) ++active_mark;
                break;
            }
            case ENTER: {
                newsubject->setmark(marks[active_mark]);
                studentsdatabase.getbyindex(activestudent)->getsession(activesession)->pushback(*newsubject);
                sessioninfo(activestudent, activesession);
            }
            }
        }
    }
    void changesubj(int activestudent, int activesession) {
        system("cls");
        int active_subj = 0;
        char ch;
        while (true) {
            int x = 0, y = 3;
            system("cls");
            GoToXY(x, y);
            for (int i = 0; i < studentsdatabase.getbyindex(activestudent)->getsession(activesession)->size(); i++) {
                if (i == active_subj) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                GoToXY(x, y++);
                cout << studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(i)->gettitle() << "   " << studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(i)->getmark() << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                sessioninfo(activestudent, activesession);
            }
            case UP: {
                if (active_subj > 0) --active_subj;
                break;
            }
            case DOWN: {
                if (active_subj < studentsdatabase.getbyindex(activestudent)->getsession(activesession)->size() - 1) ++active_subj;
                break;
            }
            case ENTER: {
                subject_info(activestudent, activesession, active_subj);

            }
            }
        }
    }
    void subject_info(int activestudent, int activesession, int active_subj) {
        system("cls");
        int active_act = 0;
        char ch;
        while (true) {
            int x = 0, y = 3;
            short x_changebars = 35, y_changebars = 15;
            system("cls");
            GoToXY(x, y);
            SetConsoleTextAttribute(hStdOut, 7);
            cout << studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(active_subj)->gettitle() << "   " << studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(active_subj)->getmark() << endl;
            for (int i = 0; i < size(subj_action); i++) {
                GoToXY(x_changebars, y_changebars++);
                if (i == active_act) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                cout << subj_action[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                sessioninfo(activestudent, activesession);
            }
            case UP: {
                if (active_act > 0) --active_act;
                break;
            }
            case DOWN: {
                if (active_act < size(subj_action) - 1) ++active_act;
                break;
            }
            case ENTER: {
                switch (active_act) {
                case 0:
                    system("cls");
                    studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(active_subj)->setsubj();
                    break;
                case 1:
                    changemark(activestudent, activesession, active_subj);
                    break;
                case 2:
                    studentsdatabase.getbyindex(activestudent)->getsession(activesession)->removebyindex(active_subj);
                    sessioninfo(activestudent, activesession);
                }


            }
            }
        }
    }
    void changemark(int activestudent, int activesession, int active_subj) {
        char ch;
        int active_mark = 0;
        while (true) {
            int x = 0, y = 3;
            system("cls");
            GoToXY(x, y);
            for (int i = 0; i < size(marks); i++) {
                if (i == active_mark) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                GoToXY(x, y++);
                cout << marks[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                subject_info(activestudent, activesession, active_subj);
            }
            case UP: {
                if (active_mark > 0) --active_mark;
                break;
            }
            case DOWN: {
                if (active_mark < size(marks) - 1) ++active_mark;
                break;
            }
            case ENTER: {
                studentsdatabase.getbyindex(activestudent)->getsession(activesession)->getbyindex(active_subj)->setmark(marks[active_mark]);
                subject_info(activestudent, activesession, active_subj);

            }
            }
        }

    }
    void variant() {
        system("cls");
        SetConsoleTextAttribute(hStdOut, 7);
        char ch;
        int minyear, maxyear;
        List<Student> students_wth_interval;
        cout << "Введите минимальный год рождения: " << endl;
        cin >> minyear;
        cout << "Введите максимальный год рождения: " << endl;
        cin >> maxyear;
        system("cls");
        while (true) {
            myCentr("ФИО", 40);
            GoToXY(40, 0);
            myCentr("Год рождения", 15);
            GoToXY(55, 0);
            myCentr("Кол-во пятерок за 2 семестр", 15);
            GoToXY(0, 3);
            for (int i = 0; i < studentsdatabase.size(); i++) {
                cout << studentsdatabase.getbyindex(i)->showstudent() << endl;
                GoToXY(45, 3 + i);
                cout << studentsdatabase.getbyindex(i)->get_year_birthdate() << endl;
                GoToXY(60, 3 + i);
                cout << studentsdatabase.getbyindex(i)->counts_five_marks() << endl;
            }
            for (int i = 0; i < studentsdatabase.size(); i++) {
                if ((studentsdatabase.getbyindex(i)->get_birthdate().getyear() >= minyear) and (studentsdatabase.getbyindex(i)->get_birthdate().getyear() <= maxyear))
                {
                    students_wth_interval.pushback(*studentsdatabase.getbyindex(i));
                }
            }
            int sizearray = students_wth_interval.size();
            Student* array = new Student[sizearray];
            for (int i = 0; i < sizearray; i++) {
                array[i] = *students_wth_interval.getbyindex(i);
            }
            for (int i = 0; i < sizearray; i++) {
                for (int j = 0; j < sizearray - 1; j++) {
                    if (array[j].counts_five_marks() < array[j + 1].counts_five_marks()) {
                        Student temp = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = temp;
                    }
                }
            }
            GoToXY(0, 17);
            myCentr("ФИО", 40);
            GoToXY(40, 17);
            myCentr("Год рождения", 15);
            GoToXY(55, 17);
            myCentr("Кол-во пятерок за 2 семестр", 15);
            GoToXY(0, 20);
            for (int i = 0; i < sizearray; i++) {
                cout << array[i].showstudent() << endl;
                GoToXY(45, 20 + i);
                cout << array[i].get_year_birthdate() << endl;
                GoToXY(60, 20 + i);
                cout << array[i].counts_five_marks() << endl;
            }
            escape();
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                showmenu();
            }


            }
        }
    }


public:
    DatabaseClient(List<Student>& studentsdatabase) {
        this->studentsdatabase = studentsdatabase;
    }
    void showmenu() {
        
        system("cls");
        drawmenu_uplines();
        ConsoleCursorVisible(false, 100);
        int active_menu = 0;
        char ch;
        while (true) {
            int x = 0, y = 3;
            GoToXY(x, y);
            for (int i = 0; i < size(menubars); i++) {
                if (i == active_menu) { SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
                else SetConsoleTextAttribute(hStdOut, 7);
                //GoToXY(x, y++);
                cout << menubars[i] << endl;
            }
            ch = _getch();
            if (ch == -32) ch = _getch();
            switch (ch) {
            case ESC: {
                exit(0);
            }
            case UP: {
                if (active_menu > 0) --active_menu;
                break;
            }
            case DOWN: {
                if (active_menu < size(menubars) - 1) ++active_menu;
                break;
            }
            case ENTER: {
                switch (active_menu) {
                case 0:
                    showStudentList();
                    break;
                case 1: {
                    system("CLS");
                    Student* newstudent = new Student();
                    newstudent->fillStudent();
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    studentsdatabase.pushback(*newstudent);
                    system("cls");
                    break;
                }
                case 2: {
                    deletestudent();
                }
                case 3: {
                    system("CLS");
                    List<StudentsToFile> students_to_file = changeformatstudents(studentsdatabase);
                    ofstream out;
                    out.open("database.bin", ios_base::out | ios_base::binary);
                    for (int i = 0; i < students_to_file.size(); i++) {
                        out.write((char*)students_to_file.getbyindex(i), sizeof(StudentsToFile));
                    }
                    out.close();
                    cout << "База данных успешно сохранена";
                    break;
                }
                case 4: {
                    variant();
                    break;
                }

                }
            }
            }
        }
    }

};