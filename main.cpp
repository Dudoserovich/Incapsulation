#include <iostream>
#include <vector>

using namespace std;

// Отсутствие инкапсуляции (public свойства)
class EvenNumber { // чётные числа
public:
    vector<int> numbers;
};

// Инкапсуляция с помощью set/get
class NewEvenNumber {
    vector<int> numbers;
public:
    void setNum (vector<int> numbers) {
        try {
            for (int i = 0; i < numbers.size(); ++i) {
                if (numbers[i] % 2 != 0)
                    throw "Попытка задать некоректное число для вектора чётных чисел";
                else this->numbers.push_back(numbers[i]);
            }
        } catch (const char* exception) {
            cerr << "Error: " << exception << endl;
        }
    }

    vector<int> getNum () { return numbers; }
};

// Инкапсуляция с помощью специализированных протоколов/методов
class Random {
private: int value;
public:
    void random() { this->value = (rand() % 1000);}
    int getValue() { return value; }
};

enum COLOR {
    RED,
    BLACK,
    BLUE,
    GREEN
};

// Инкапсуляция за счёт абстракций
class IPrint {
public:
    virtual void print(string) = 0;
};

class Print : public IPrint {
public:
    void print(string s) {
        cout << "string: " << s << endl;
    }
};

// Dynamic Binding
void run (IPrint* p) {
    string s;
    cout << "Введите сообщение: " << endl;
    cin >> s;
    p->print(s);
    p->print("done");
}

class ModifyPrint : public IPrint {
private: COLOR c;
    string getColor (COLOR c) {
        switch (c) {
            case RED: return "RED";
            case BLACK: return "BLACK";
            case BLUE: return "BLUE";
            case GREEN: return "GREEN";
        }
    }
public:
    // расширение поведения
    void print(string s) {
        cout << "string: " << s << ", цвета: " << getColor(c) << endl;
    }

    void SetColor(COLOR c) { this->c = c; }
};

// Замена поведения
class PrintNum : public IPrint {
public:
    void print(string num) {
        cout << "число: ";
        for (int i = 0; i < num.size(); ++i) {
            cout << num[i];
        }
        cout << endl;
    }
};

int main() {
    EvenNumber en;
    en.numbers = {0, 1, 2, 3, 4}; // WTF?!

    vector<int> num = {0, 2, 4, 6};
    NewEvenNumber nen;
//    nen.setNum(en.numbers);

    nen.setNum(num);
    num = nen.getNum();
    for (int i = 0; i < num.size(); ++i) {
        cout << num[i] << endl;
    }

    Random R;
    R.random();
    cout << R.getValue() << endl;
    R.random();
    cout << R.getValue() << endl;

    Print p;
    run(&p);
    ModifyPrint p2;
    p2.SetColor(RED);
    run(&p2);

    PrintNum pn;
    run(&pn);

    return 0;
}
