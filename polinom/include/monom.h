#pragma once
#include<iostream>
#include<string>
#include <cctype>
using namespace std;

class Monom
{
	double coeff;
	//int pow; 
    int pow_x;
    int pow_y;
    int pow_z;
public:
    Monom(double c, int px = 0, int py = 0, int pz = 0) : coeff(c), pow_x(px), pow_y(py), pow_z(pz) {} // Конструктор по числам 
  
    Monom(const string& s) : coeff(0), pow_x(0), pow_y(0), pow_z(0) {   // Конструктор по строке ("3x1y2z1")
        size_t i = 0;
        while (i < s.length() && isdigit(s[i])) {
            coeff = coeff * 10 + (s[i] - '0');
            //coeff = coeff * 10 + s[i];
            i++;
        }
        while (i < s.length()) {
            char var = s[i++]; // Считываем переменную
            int pow = 0;
            if (i < s.length() && isdigit(s[i])) {
                
                while (i < s.length() && isdigit(s[i])) {
                    pow = pow * 10 + (s[i] - '0');
                    //pow = pow * 10 + s[i];
                    i++;
                }
            }
            switch (var) {
            case 'x':
                pow_x = pow;
                break;
            case 'y':
                pow_y = pow;
                break;
            case 'z':
                pow_z = pow;
                break;
            }
        }
    }

    int getPowX() 
    { 
        return pow_x; 
    }
    int getPowY() 
    { 
        return pow_y; 
    }
    int getPowZ() 
    { 
        return pow_z; 
    }
    double getCoeff() 
    { 
        return coeff; 
    }

    Monom operator+(const Monom& m) const {
        if (pow_x == m.pow_x && pow_y == m.pow_y && pow_z == m.pow_z) {
            return Monom(coeff + m.coeff, pow_x, pow_y, pow_z);
        }
        return *this; // Если степени не совпадают, возвращаем текущий моном
    }

    Monom operator*(const Monom& other) const {
        return Monom(coeff * other.coeff, pow_x + other.pow_x, pow_y + other.pow_y, pow_z + other.pow_z);
    }

	bool operator==(const Monom& m) const {
		return (coeff == m.coeff && pow_x == m.pow_x && pow_y == m.pow_y && pow_z == m.pow_z);
	}

    // Сравнение по сумме степеней, затем по коэффициентам
    bool operator<(const Monom& m) const {
        if (pow_x + pow_y + pow_z != m.pow_x + m.pow_y + m.pow_z) {
            return (pow_x + pow_y + pow_z) < (m.pow_x + m.pow_y + m.pow_z);
        }
        // Если степени одинаковые, сравниваем коэффициенты
        return coeff < m.coeff;
    }

    /*bool operator<(const Monom& m) const {    //("3x1y2z1 + 2x2y2z1")
        if (pow_x != m.pow_x) {
            return pow_x < m.pow_x; 
        }
        if (pow_y != m.pow_y) {
            return pow_y < m.pow_y; 
        }
        if (pow_z != m.pow_z) {
            return pow_z < m.pow_z; 
        }
        return coeff < m.coeff; // Наконец, сравниваем коэффициенты
    }*/

    friend ostream& operator<<(ostream& ostr, const Monom& m)
    {
        ostr << "Коэффициент: " << m.coeff << ' ';
        ostr << "Степени: " << ' ';
        ostr << m.pow_x << m.pow_y << m.pow_z << endl;
        return ostr;
    }

};

