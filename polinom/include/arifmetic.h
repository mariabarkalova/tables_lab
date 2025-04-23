#include<iostream>
#include<stack>
#include<vector>
#include<cctype>
#include<string>
#include <sstream>
#include <algorithm>
#include"monom.h"
#include"polinom.h"

//#include <stdexcept> //�����-�� ���������� ��� ������ ���� ���������
/*
using namespace std;
template<typename T>

class Stack
{
private:
	int top; //������ �����
	vector<T> mem; // ������ ��� �������� ��������� �����
public:
	Stack()
	{
		top = -1;
	}
	size_t size() const {
		return top + 1;
	}
	bool IsEmpty() const {
		return top == -1;
	}
	void Push(const T& val)
	{
		mem.push_back(val);
		top++;
	}
	T Pop()
	{
		if (IsEmpty()) {
			throw runtime_error("Stack is empty");
		}
		T res = mem[top];
		top--;
		mem.pop_back();
		return res;
	}
	T Top()
	{
		if (IsEmpty()) {
			throw runtime_error("Stack is empty");
		}
		return mem[top];
	}
};

struct Lexem
{
	int type;
	string str;
	double val;
	Lexem(string s, int t) //�����������
	{
		str = s;
		type = t;
		if (type == 2) {
			val = stod(s); // ��� stoi
		}
	}
};
struct Param
{
	string name;
	double znach;
};


class Calculator
{
private:
	vector<Lexem> Lexems;
	vector<Lexem> Postfix;
	Stack<Lexem> stackop; //��� ������� ��� ����������� ���������.������
	//Stack<double> values; //��� ���������� ���������
	Stack<Monom> values; // ���� ������ ������ Monom
	//Stack<Polynom> values; // ���� ������ ������ Polynom
	vector<Param> Parametr;


	// Helper function: Parse a polynomial string into a Monom data structure
	Polynom parsePolynom(const std::string& polyStr) {
		return Polynom(polyStr);
	}

public:
	int getType(char c)
	{
		if (isalpha(c)) {
			return 1;
		}
		if ((isdigit(c)) || (c == '.') || (c == ',')) {
			return 2;
		}
		if ((c == '+') || (c == '*') || (c == '-') || (c == '/') || (c == '+') || (c == '(') || (c == ')'))
			return 3;
		else {
			return -1; //����������� ������
		}
	}

	void MassivLexem(string str) {
		string token;
		int p = 0, k = 0;
		for (p = 0; p < str.size(); p++) {

			char current = str[p];
			int type = getType(current);
			if ((type == 2) || (type == 1)) {
				token += current;
				while ((p + 1 < str.size()) && (isdigit(str[p + 1]) || str[p + 1] == '.' || str[p + 1] == ',')) {
					p++;
					token += str[p]; // ��������� � ������
				}
				Lexems.emplace_back(token, type); // ������� ������� � ��������� � ������
				token.clear(); // ������� ����� ��� ��������� �������
			}
			else if (type == 3) {
				token += current;
				Lexems.emplace_back(token, type);
				token.clear();
			}
			else if (type == -1) {
				throw runtime_error("����������� ������ � ������");
			}
		}

	}
	vector<Lexem> GetLexems()
	{
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
		for (int i = 0;i < Lexems.size();i++) {
			if (Lexems[i].str == "(") {
				stackop.Push(Lexems[i]);
			}
			else {
				if ((Lexems[i].type == 2) || (Lexems[i].type == 1)) {
					Postfix.push_back(Lexems[i]);
				}
				else {
					if (Lexems[i].str == ")") {
						while (stackop.Top().str != "(") {
							Postfix.push_back(stackop.Pop());
						}
						stackop.Pop();
					}
					else {
						while (Prioritet(stackop.Top()) >= Prioritet(Lexems[i])) {
							Postfix.push_back(stackop.Pop());
						}
						stackop.Push(Lexems[i]);
					}
				}
			}
		}
	}

	void printPostfix() {
		for (const Lexem& lexem : Postfix) {
			cout << lexem.str << "   ";
		}
		cout << endl;
	}

	vector<Lexem> GetPostfix()
	{
		return Postfix;
	}

	Monom Arifmetic() {
		values = Stack<Monom>(); // ������� ���� ��� ����� ����������
		Parametr.clear();

		for (size_t i = 0; i < Postfix.size(); ++i) {
			const Lexem& lexem = Postfix[i];

			if (lexem.type == 2) { // �����
				values.Push(Monom(lexem.val)); // ����������� ����� � �����
			}
			else if (lexem.type == 1) { // ����� (����������)
				bool found = false;
				for (const auto& param : Parametr)
				{
					if (param.name == lexem.str)
					{
						values.Push(Monom(param.znach)); // ���� �������, ���������� ����������� �������� (������)
						found = true;
						break;
					}
				}

				if (!found) // ���� ���������� �� �������, ����������� ����� � ������������
				{
					// ���������� ���������������� ������
					Monom monom;
					if (lexem.str == "a") {
						monom = Monom("2x1y1z0"); // ������ ��� ���������� 'a'
					}
					else if (lexem.str == "b") {
						monom = Monom("3x0y0z1"); // ������ ��� ���������� 'b'
					}
					else {
						throw runtime_error("���������� " + lexem.str + " �� ����������");
					}
					values.Push(monom); // ��������� � ����
				}
			}

			else if (lexem.type == 3) { // ��������
				if (values.size() < 2) {
					throw std::runtime_error("������������ ������� � ����� ��� �������� " + lexem.str);
				}
				Monom val2 = values.Pop();
				Monom val1 = values.Pop();

				Monom result(0);
				if (lexem.str == "+") {
					try {
						result = val1 + val2;
					}
					catch (const std::runtime_error& e) {
						throw std::runtime_error("���������� ������� ������: " + string(e.what()));
					}
				}
				else if (lexem.str == "*") {
					result = val1 * val2;
				}
				else if (lexem.str == "-") {
					// ����������� ��������� � �������� � ������������� �������
					result = val1 + Monom(-1) * val2;
				}
				else if (lexem.str == "/") {
					if (val2.getCoeff() == 0) {
						throw std::runtime_error("������� �� ����!");
					}
					if (val1.getPowX() - val2.getPowX() < 0 || val1.getPowY() - val2.getPowY() < 0 || val1.getPowZ() - val2.getPowZ() < 0)
					{
						throw std::runtime_error("������� ���� ������������� �������!");
					}
					result = Monom(val1.getCoeff() / val2.getCoeff(), val1.getPowX() - val2.getPowX(), val1.getPowY() - val2.getPowY(), val1.getPowZ() - val2.getPowZ());
				}

				values.Push(result);
			}
		}

		if (values.size() != 1) {
			throw std::runtime_error("�������� ���������: ������� ����� ������� �������� � �����.");
		}

		return values.Pop();
	}

};*/

//���� ������
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
					cout << "������� �������� ��� ���������� " << Postfix[i].str << ": ";
					cin >> znachenie;
					Param newParam{ Postfix[i].str, znachenie };
					Parametr.push_back(newParam); // ��������� ���������� � ���������
					values.Push(znachenie); // ��������� �������� ���������� � ����
				}
			}
			if (Postfix[i].type == 3) {
				if (values.size() < 2) {
					throw "������������ �������� � ����� ��� ���������� ��������";
				}
				// ���������� ���� ������� �������� �� �����
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
						throw runtime_error("�� ���� �� �����");
					}
					result = val1 / val2;
				}
				values.Push(result);
			}
		}
		return values.Top();
	}*/
