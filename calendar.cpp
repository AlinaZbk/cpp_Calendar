#include<iostream>
#include<iomanip>
using namespace std;

void displayCalendar(int, int);
bool checkCalendar(int, int);
bool checkDaysBetween(int, int, int, int);
bool isLeapYear(int);
int daysInMonth(int, int);
int firstDayOfMonth(int, int);
int countDaysBetween(int, int, int, int);
int main();
string choose_programm(int, int, int, int, int, int, int);
string f1(int, int);
string f2(int, int, int, int);

const string MONTH[] = { " ", "ЯНВАРЬ", "ФЕВРАЛЬ", "МАРТ","АПРЕЛЬ","МАЙ","ИЮНЬ", "ИЮЛЬ","АВГУСТ","СЕНТЯБРЬ","ОКТЯБРЬ","НОЯБРЬ","ДЕКАБРЬ" };

int main(){
    int choice, month, year, startMonth, startYear, endMonth, endYear;
    while(true){
        cout << "0 - Выход\n1 - Показать календарь\n2 - Подсчитать дни между месяцами:\nВыберите функцию: ";
        cin >> choice;
        string result = choose_programm(choice, month, year, startMonth, startYear, endMonth, endYear);
        if (result == "exit") break;
        cout << result << "\n";
    }
}

void displayCalendar(int month, int year){
    cout << "Календарь на " << MONTH[month] << "/" << year << endl;
    cout << "ПН ВТ СР ЧТ ПТ СБ ВС" << endl;
    int firstDay = firstDayOfMonth(month, year); //объявляем отступ
    int days = daysInMonth(month, year);//обявляем кол-во дней в месяце
    for (int i=0; i < firstDay; i++){
        cout << "   ";
    }
    for (int day=1; day <= days; day++){
        cout << setw(2) << day << " "; //функция из библиотеки iomanip для красивого оформления, в данной случае ширина для вывода - 2
        if (((firstDay + day) % 7) == 0)
            cout << endl;
    }
}
//проверка введенных данных для календаря
bool checkCalendar(int month, int year) {
    return((month >= 1 && month <= 12) && (year >= 1919 && year <= 2169));
}
//проверка введенных данных для подсчета кол-ва дней
bool checkDaysBetween(int startMonth, int startYear, int endMonth, int endYear) {
    bool usl1 = ((startMonth >= 1) && (startMonth <= 12)) && ((endMonth >= 1) && (endMonth <= 12));
    bool usl2 = ((startYear >= 1919) && (startYear <= 2169)) && ((endYear >= 1919) && (endYear <= 2169));
    bool usl3 = (startYear < endYear) || ((startYear == endYear) && (startMonth <= endMonth));
    return (usl1 && usl2 && usl3);
}
//функция для проверки високостности года
bool isLeapYear(int year){
    return(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
//функция подсчёта дней в месяце
int daysInMonth(int month, int year){
    int DAYS[]={31, 28+isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//создание списка, с количеством дней месяцев
    return DAYS[month-1];
}
//функция подсчёта отступа
int firstDayOfMonth(int month, int year) {
    int totalDays = 0;
    for (int y = 1919; y < year; ++y) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < month; ++m) {
        totalDays += daysInMonth(m, year);
    }
    // Поскольку 01.01.1919 - это среда, добавляем 2 (среда = 0, четверг = 1, пятница = 2, суббота = 3, воскресенье = 4, понедельник = 5, вторник = 6)
    return (totalDays + 2) % 7;
}
// Функция для подсчета дней между двумя месяцами
int countDaysBetween(int startMonth, int startYear, int endMonth, int endYear) {
    int totalDays = 0;
    for (int y = startYear; (y < endYear || (y == endYear && startMonth < endMonth)); ) {
        if (startMonth > 12) {
            startMonth = 1;
            y++;
            continue;
        }
        totalDays += daysInMonth(startMonth, y);
        startMonth++;
    }
    return totalDays;
}
//
string f1(int month, int year){
        cout<<"Введите месяц (1-12): ";
        cin >> month;
        cout<< "Введите год (1919-2169): ";
        cin >> year;
        if (!(checkCalendar(month, year))) {
                return "Ошибка ввода! Попробуйте снова.";
        }
        displayCalendar(month, year);
        return  " ";
} 
string f2(int startMonth, int startYear, int endMonth, int endYear){
        cout <<  "Введите начальный месяц (1-12): ";
        cin >> startMonth;
        cout <<  "Введите начальный год (1919-2169): ";
        cin >> startYear;
        cout << "Введите конечный месяц (1-12): ";
        cin >> endMonth;
        cout << "Введите конечный год (1919-2169): ";
        cin >> endYear;
        if ((checkDaysBetween(startMonth,startYear,endMonth,endYear))==0){
            cout<< "Ошибка ввода! Попробуйте снова.";
            return " ";
        }
        int daysResult = countDaysBetween(startMonth, startYear, endMonth, endYear);
        cout << "Количество дней между " << startMonth << "/" << startYear << " и " << endMonth << "/" << endYear << " : " << daysResult << endl;
        return " ";
}
//функция выбора программы: 1 - календарь, 2 - кол-во дней между месяцами
string choose_programm(int choice, int month, int year, int startMonth, int startYear, int endMonth, int endYear){
    switch(choice){
        case 0: return "exit";
        case 1: return f1(month, year);
        case 2: return f2(startMonth, startYear, endMonth, endYear);
        default: return "Oшибка ввода, Попробуйте ещё раз";
    }
    return "";
}

