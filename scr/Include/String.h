#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace std;

using ll = long long;
using llu = unsigned long long;
class String
{
private:
    char *data; // Mang luu chuoi ki tu
    llu length; // Do dai cua chuoi

    // Cac ham tien ich noi bo
    llu strlen(const char *) const;               // Ham tinh do dai cua chuoi
    void strcpy(char *, const char *) const;      // Ham copy chuoi
    int strcmp(const char *, const char *) const; // Ham so sanh chuoi
public:
    // ==== Constructors ====
    String();                    // Ham dung rong
    String(const char* s);       // Ham dung tu C-String
    String(const String &other); // Ham dung copy
    // ==== Destructor ====
    ~String();

    // ==== Operator overloading ====
    String& operator=(const String &);          // Gan chuoi
    String operator+(const String &) const;     // Cong 2 chuoi
    String operator+=(const String &);     // Cong 2 chuoi
    bool operator==(const String &) const;      // SS 2 chuoi
    char &operator[](llu position);             // Thay doi gia tri ki tu
    const char &operator[](llu position) const; // Truy xuat ki tu

    // ===== Method =======
    static String to_string(int value);
    static String to_string(long long value);
    static String to_string(unsigned long long value);
    static String to_string(double value, int precision = 2);
    llu size() const;                                 // tra ve do dai chuoi
    bool empty() const;                               // Ktra chuoi co rong khong
    const char *c_str() const;                        // tra ve C-String
    void clear();                                     // Xoa
    void push_back(char c);                           // Them ki tu
    String substr(llu position, llu n) const;         // Cat chuoi -> chuoi con
    llu find(const String &, llu position = 0) const; // Tim chuoi con
    friend double pow(llu, llu);

    // ===== Stream operators ========
    friend ostream &operator<<(ostream &, const String &);
    friend istream &operator>>(istream &, String &);
    sf::String toSFString() const {
        return sf::String(this->data);
    }
};
