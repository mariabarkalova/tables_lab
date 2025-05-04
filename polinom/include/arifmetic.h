#include<iostream>
#include<stack>
#include<vector>
#include<cctype>
#include<string>
#include <sstream>
#include <algorithm>
#include"monom.h"
#include"polinom.h"
#include <map>
#include <stdexcept>


using namespace std;

template <class T>
class Stack {
private:
    int top;
    vector<T> mem;

public:
    Stack() : top(-1) {}

    size_t size() const {
        return mem.size();
    }

    bool IsEmpty() const {
        return top == -1;
    }

    void Push(const T& val) {
        mem.push_back(val);
        top++;
    }

    T Pop() {
        if (IsEmpty()) {
            throw runtime_error("Stack is empty");
        }
        T res = mem[top];
        mem.pop_back();
        top--;
        return res;
    }

    T Top() const {  //помечено const
        if (IsEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return mem[top];
    }
};


class PolynomArithmetic {
public:
    Polynom add(Polynom& p1, Polynom& p2) {
        Polynom result;
        Node<Monom>* curr = p1.getMonomList().getFirst();
        while (curr != nullptr) {
            result.addMonom(curr->value);
            curr = curr->next;
        }
        Node<Monom>* curr2 = p2.getMonomList().getFirst();
        while (curr2 != nullptr) {
            result.addMonom(curr2->value);
            curr2 = curr2->next;
        }
        return result;
    }

    Polynom subtract( Polynom& p1,  Polynom& p2) {
        Polynom result;
        Node<Monom>* curr = p1.getMonomList().getFirst();
        while (curr != nullptr) {
            result.addMonom(curr->value);
            curr = curr->next;
        }
        Node<Monom>* curr2 = p2.getMonomList().getFirst();
        while (curr2 != nullptr) {
            Monom negMon = curr2->value;
            negMon.coeff = -negMon.coeff;
            result.addMonom(negMon);
            curr2 = curr2->next;
        }
        return result;
    }

    Polynom multiply( Polynom& p1,  Polynom& p2) {
        Polynom result;
        Node<Monom>* curr1 = p1.getMonomList().getFirst();
        while (curr1 != nullptr) {
            Node<Monom>* curr2 = p2.getMonomList().getFirst();
            while (curr2 != nullptr) {
                Monom product = curr1->value * curr2->value;
                result.addMonom(product);
                curr2 = curr2->next;
            }
            curr1 = curr1->next;
        }
        return result;
    }
};

struct Lexem {
    int type; // 1: переменная, 2: число, 3: оператор, 4: полином
    string str;
    double val; // Для чисел
    Polynom poly; // Для полиномов

    Lexem(string s, int t) : str(s), type(t), val(0.0) {}  // Конструктор для чисел и операторов
    Lexem(const Polynom& p) : str(""), type(4), val(0.0), poly(p) {} // Конструктор для полиномов
};

struct Param {
    string name;
    double znach;
};

class Parser {
private:
    vector<Lexem> Lexems;
    vector<Lexem> Postfix;
    Stack<Lexem> stackop; //для функции где записывваем постфиксн.запись
    Stack<Polynom> values; //для вычисления выражения - теперь полиномы
    vector<Param> Parametr;
    map<std::string, Polynom> polynomials; // Храним полиномы по именам
    PolynomArithmetic arithmetic;

public:

    // Добавляем полином для парсера
    void addPolynomial(const std::string& name, const Polynom& poly) {
        polynomials[name] = poly;
    }
    // Конструктор, принимающий выражение
    explicit Parser(const string& expression) {
        MassivLexem(expression);
    }

    int getType(char c) {
        if (isalpha(c)) {
            return 1;
        }
        if (isdigit(c)) {
            return 2;
        }
        if ((c == '+') || (c == '*') || (c == '-') || (c == '/') || (c == '(') || (c == ')')) {
            return 3;
        }
        else {
            return -1; //неизвестный символ
        }
    }

    void MassivLexem(string str) {
        Lexems.clear();

        string token;
        int p = 0;
        while (p < str.size()) {
            char c = str[p];
            int type = getType(c);

            if (isspace(c)) {
                p++;
                continue;
            }

            if (isalpha(c)) { // Буква (переменная или имя полинома)
                token += c;
                p++;
                while (p < str.size() && isalnum(str[p])) {
                    token += str[p];
                    p++;
                }

                // Проверяем, является ли токен именем полинома
                if (polynomials.count(token)) {
                    Lexem lexem(polynomials[token]);
                    Lexems.push_back(lexem);
                }
                else {
                    Lexem lexem(token, 1); // Считаем это переменной
                    Lexems.push_back(lexem);
                }
                token.clear();
            }
            else if (type == 2) { // Число
                token += c;
                p++;
                bool hasDecimalPoint = false;
                while (p < str.size() && (isdigit(str[p]) || str[p] == '.')) {
                    if (str[p] == '.') {
                        if (hasDecimalPoint) {
                            cerr << "Ошибка: Неверный формат числа (несколько десятичных точек)." << endl;
                            return; // Или бросить исключение
                        }
                        hasDecimalPoint = true;
                    }
                    token += str[p];
                    p++;
                }
                Lexem lexem(token, 2);
                Lexems.push_back(lexem);
                token.clear();
            }
            else if (type == 3) { // Оператор или скобка
                token += c;
                Lexem lexem(token, type);
                Lexems.push_back(lexem);
                token.clear();
                p++;
            }
            else { // Недопустимый символ
                cerr << "Ошибка: Недопустимый символ '" << c << "' в выражении." << endl;
                return; // Или бросить исключение
            }
        }
    }

    vector<Lexem> GetLexems() {
        return Lexems;
    }

    int Prioritet(Lexem l) {
        int res = 0;
        if (l.str == "(") {
            res = 0;
        }
        if (l.str == "+") {
            res = 1;
        }
        if (l.str == "-") {
            res = 1;
        }
        if (l.str == "*") {
            res = 2;
        }
        if (l.str == "/") {
            res = 2;
        }
        return res;
    }

    void Parser_Postfix() {
        Postfix.clear();
        stackop = Stack<Lexem>(); // Очищаем стек
        for (int i = 0; i < Lexems.size(); i++) {
            if (Lexems[i].str == "(") {
                stackop.Push(Lexems[i]);
            }
            else if (Lexems[i].type == 2 || Lexems[i].type == 4) { // Число или полином
                Postfix.push_back(Lexems[i]);
            }
            else if (Lexems[i].str == ")") {
                while (!stackop.IsEmpty() && stackop.Top().str != "(") {
                    Postfix.push_back(stackop.Pop());
                }
                if (!stackop.IsEmpty()) {
                    stackop.Pop(); // Удаляем "("
                }
                else {
                    cerr << "Ошибка: Несоответствие скобок." << endl;
                    return;
                }
            }
            else {
                while (!stackop.IsEmpty() && Prioritet(stackop.Top()) >= Prioritet(Lexems[i])) {
                    Postfix.push_back(stackop.Pop());
                }
                stackop.Push(Lexems[i]);
            }
        }

        while (!stackop.IsEmpty()) {
            if (stackop.Top().str == "(") {
                cerr << "Ошибка: Несоответствие скобок." << endl;
                return;
            }
            Postfix.push_back(stackop.Pop());
        }
    }

    void printPostfix() {
        cout << "Постфиксная запись: ";
        for (const Lexem& lexem : Postfix) {
            if (lexem.type == 4)
                cout << "Poly(" << ")";
            else
                cout << lexem.str << "   ";
        }
        cout << endl;
    }

    vector<Lexem> GetPostfix() {
        return Postfix;
    }

    Polynom Arifmetic() {
        values = Stack<Polynom>(); // Очищаем стек значений
        for (int i = 0; i < Postfix.size(); i++) {
            if (Postfix[i].type == 4) { // Полином
                values.Push(Postfix[i].poly);
            }
            else if (Postfix[i].type == 2) { // Число
                // Преобразуем число в моном, а затем в полином
                Monom m(Postfix[i].val);
                Polynom p;
                p.addMonom(m);
                values.Push(p);
            }
            else if (Postfix[i].type == 3) { // Оператор
                if (values.size() < 2) {
                    throw runtime_error("Недостаточно значений в стеке для выполнения операции");
                }

                Polynom val2 = values.Pop();
                Polynom val1 = values.Pop();

                Polynom result;
                if (Postfix[i].str == "+") {
                    result = arithmetic.add(val1, val2);
                }
                else if (Postfix[i].str == "*") {
                    result = arithmetic.multiply(val1, val2);
                }
                else if (Postfix[i].str == "-") {
                    result = arithmetic.subtract(val1, val2);
                }
                else if (Postfix[i].str == "/") {
                    cout << "Операция деления еще не поддерживается." << endl; //Т.к. требуется деление на моном.
                    //result = arithmetic.divide(val1, val2);
                    return Polynom();
                }
                values.Push(result);
            }
        }

        if (values.size() != 1) {
            throw runtime_error("Некорректное выражение");
        }

        return values.Top();
    }
};


//было раньше
/*double Arifmetic() {
		Parametr.clear();
		int flag = 0;
		for (int i = 0;i < Postfix.size();i++) {
			if (Postfix[i].type == 2) {
				values.Push(Postfix[i].val);
			}
			else if (Postfix[i].type == 1) {
				int flag = 0;
				for (const Param& param : Parametr) {
					if (param.name == Postfix[i].str) {
						values.Push(param.znach);
						flag = 1;
					}
				}
				if (flag == 0) {
					double znachenie;
					cout << "Введите значение для переменной " << Postfix[i].str << ": ";
					cin >> znachenie;
					Param newParam{ Postfix[i].str, znachenie };
					Parametr.push_back(newParam); // Сохраняем переменную в параметры
					values.Push(znachenie); // Добавляем значение переменной в стек
				}
			}
			if (Postfix[i].type == 3) {
				if (values.size() < 2) {
					throw "Недостаточно значений в стеке для выполнения операции";
				}
				// Извлечение двух верхних значений из стека
				double val2 = values.Pop();
				double val1 = values.Pop();

				double result = 0.0;
				if (Postfix[i].str == "+") {
					result = val1 + val2;
				}
				if (Postfix[i].str == "*") {
					result = val1 * val2;
				}
				if (Postfix[i].str == "-") {
					result = val1 - val2;
				}
				if (Postfix[i].str == "/") {
					if (val2 == 0) {
						throw runtime_error("На ноль не делим");
					}
					result = val1 / val2;
				}
				values.Push(result);
			}
		}
		return values.Top();
	}*/
