#include "array.h"
#include <limits>
#include "polynom.h"
#include <sstream>
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
        cout << "1. ������� 0 �������\n"
                "2. ������� ������� �� n-�� �������\n"
                "3. �������� ������ ������� ������\n"
                "4. �������� �������� � ����� x\n"
                "5. �������� �������� ������������ a\n"
                "6. �������� �������� ������\n"
                "7. ����� �������� 1 ����\n"
                "8. ����� �������� 2 ����\n"
                "0. ����� \n";
    }

    void menu() {
        int count, nom,n;
        string cof_a, n_counts;
        stringstream  iss;
        number value, x, cof_a2, root;
        Array *arr_object;
        Polynom *poly_object = new Polynom(3);
        iss <<"3+0i\n4+0i\n6+0i\n8-6i\n";
        iss >> *poly_object;
        Array *roots_object = new Array;
        while (true) {
            menu_out();
            stringstream iss;

            action = check(0, 8);
            switch (action) {
                case 1:
                    poly_object = new Polynom();
                    cout << *poly_object<<endl;
                    system("pause");
                    break;
                case 2:
                    cout << "������� ���������� ������" << endl;
                    count = check(1, maxlim);
                    poly_object= new Polynom(size_t(count));
                    cout << "������� ����������� a(������ 0+0i)" << endl;
                    cin>>cof_a;
                    iss<<cof_a<<endl;
                    for(int i=0; i<count; i++){
                        cout << "������� �������� "<<i+1<<" �����(0+0i)"<< endl;
                        cin>>n_counts;
                        iss<<n_counts<<endl;
                    }
                    iss >> *poly_object;
                    cout << *poly_object<<endl;
                    system("pause");
                    break;
                case 3:
                    cout << "������� ����� ���������� ��������� ������� ������" << endl;
                    n = check(1, maxlim);
                    poly_object->resize(n);
                    system("pause");
                    break;
                case 4:
                    cout<<"������� �������� �(������ 0+0i)"<<endl;
                    cin>>x;
                    cout<<poly_object->solve_for_x(x)<<endl;
                    system("pause");
                    break;
                case 5:
                    cout<<"������� ����� �������� ������������ �(������ 0+0i)"<<endl;
                    cin>>cof_a2;
                    poly_object->set_a_n(cof_a2);
                    system("pause");
                    break;
                case 6:
                    cout<<"������� ������ �����, ������� ������ ��������"<<endl;
                    nom=check(0, maxlim);
                    cout<<"������� ����� ������"<<endl;
                    cin>>root;
                    poly_object->change_root(nom, root);
                    system("pause");
                    break;
                case 7:
                    poly_object->set_display_format(0);
                    cout<<*poly_object;
                    system("pause");
                    cin.clear();
                    break;
                case 8:
                    poly_object->set_display_format(1);
                    cout<<*poly_object;
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
