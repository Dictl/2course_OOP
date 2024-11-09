#include "array.h"
#include <limits>
#define maxlim 2147483647

class basis {
private:
    int action;
public:
    int check(int lim_min, int lim_max) {
        int userInput;
        while (!(cin >> userInput) || userInput < lim_min || userInput > lim_max || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "НЕ ВЕРНО! Введите число" << endl;
        }
        cout << "Вы ввели: " << userInput << endl;

        return userInput;
    }

    void menu_out() {
        system("cls");
        cout << "1. Создать 0 массив\n"
                "2. Создать массив из n элементов\n"
                "3. Изменить размер массива\n"
                "4. Среднее алгебраическое значение\n"
                "5. Среднеквадратичное отклонение\n"
                "6. Сортировка по возрастанию\n"
                "7. Сортировка по убыванию\n"
                "8. Ввод массива\n"
                "9. Вывод массива\n"
                "10. Заменить элемент массива\n"
                "0. Выход \n";
    }

    void menu() {
        int n, nom, value;
        Array *arr_object;
        arr_object = new Array(4);
        number *num = new number[4]();
        for (int i = 0; i < 4; i++) {
            num[i] = i + 3;
        }
        arr_object->numbers = num;
        while (true) {
            menu_out();
            action = check(0, 10);
            switch (action) {
                case 1:
                    arr_object = new Array();
                    cout << *arr_object;
                    system("pause");
                    break;
                case 2:
                    cout << "Введите количество элементов массива" << endl;
                    n = check(0, maxlim);
                    arr_object = new Array(n);
                    cout << *arr_object;
                    system("pause");
                    break;
                case 3:
                    cout << "Введите НОВОЕ количество элементов массива" << endl;
                    n = check(0, maxlim);
                    arr_object->resize(n);
                    cout << *arr_object;
                    system("pause");
                    break;
                case 4:
                    cout << arr_object->arithmetic_mean() << endl;//Среднее
                    system("pause");
                    break;
                case 5:
                    cout << arr_object->root_mean_square_deviation() << endl; //Среднеквадратичное отклонение
                    system("pause");
                    break;
                case 6:
                    arr_object->sort(1);
                    cout << *arr_object;
                    system("pause");
                    break;
                case 7:
                    arr_object->sort(0);
                    cout << *arr_object;
                    system("pause");
                    break;
                case 8:
                    cout << "Введите " << arr_object->size << " чисел" << endl;
                    cin >> *arr_object;
                    system("pause");
                    break;
                case 9:
                    cout << *arr_object<<endl;
                    system("pause");
                    break;
                case 10:
                    cout<<"Для замены ввведите номер элемента массива"<<endl;
                    nom=check(0,arr_object->size-1);
                    cout<<"Новое значение"<<endl;
                    value=check(0,maxlim);
                    arr_object->numbers[nom] = value;
                    cout << *arr_object;
                    system("pause");
                    break;
                case 0:
                    cout << "ВЫХОД";
                    delete arr_object;
                    abort();
            }
        }

    }
};
