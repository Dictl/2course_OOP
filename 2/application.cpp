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
            cout << "�� �����! ������� �����" << endl;
        }
        cout << "�� �����: " << userInput << endl;

        return userInput;
    }

    void menu_out() {
        system("cls");
        cout << "1. ������� 0 ������\n"
                "2. ������� ������ �� n ���������\n"
                "3. �������� ������ �������\n"
                "4. ������� �������������� ��������\n"
                "5. ������������������ ����������\n"
                "6. ���������� �� �����������\n"
                "7. ���������� �� ��������\n"
                "8. ���� �������\n"
                "9. ����� �������\n"
                "10. �������� ������� �������\n"
                "0. ����� \n";
    }

    void menu() {
        int n, nom;
        number value;
        Array *arr_object;
        arr_object = new Array(4);
        for (int i = 0; i < 4; i++) {
            arr_object->setNumbers(i, i+4);
        }
        while (true) {
            menu_out();
            action = check(0, 10);
            switch (action) {
                case 1:
                    arr_object = new Array();
                    cout << *arr_object<<endl;
                    system("pause");
                    break;
                case 2:
                    cout << "������� ���������� ��������� �������" << endl;
                    n = check(0, maxlim);
                    arr_object = new Array(n);
                    cout << *arr_object;
                    system("pause");
                    break;
                case 3:
                    cout << "������� ����� ���������� ��������� �������" << endl;
                    n = check(0, maxlim);
                    arr_object->resize(n);
                    cout << *arr_object;
                    system("pause");
                    break;
                case 4:
                    cout << arr_object->arithmetic_mean() << endl;//�������
                    system("pause");
                    break;
                case 5:
                    cout << arr_object->root_mean_square_deviation() << endl; //������������������ ����������
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
                    cout << "������� " << arr_object->getSize() << " �����" << endl;
                    cin >> *arr_object;
                    system("pause");
                    cin.clear();
                    break;
                case 9:
                    cout << *arr_object<<endl;
                    system("pause");
                    break;
                case 10:
                    cout<<"��� ������ �������� ����� �������� �������"<<endl;
                    nom=check(0,arr_object->getSize()-1);
                    cout<<"����� ��������"<<endl;
                    cin>>value;
                    arr_object->setNumbers(nom, value);
                    cout << *arr_object;
                    system("pause");
                    cin.clear();
                    break;
                case 0:
                    cout << "�����";
                    delete arr_object;
                    abort();
            }
        }

    }
};
