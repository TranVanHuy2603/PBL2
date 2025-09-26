#include "String.h"

// Cac ham tien ich noi bo
llu String::strlen(const char *s) const // Ham tinh do dai cua chuoi
{
    llu len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

void String::strcpy(char *dest, const char *src) const // Ham copy chuoi
{
    llu index = 0;
    while (src[index] != '\0')
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
}
int String::strcmp(const char *s1, const char *s2) const // Ham so sanh chuoi
{
    llu i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

// ==== Constructors ====
String::String() // Ham dung rong
{
    this->data = new char[1];
    this->data[0] = '\0';
    this->length = 0;
}
String::String(const char *s) // Ham dung tu C-String
{
    this->length = String::strlen(s);
    this->data = new char[this->length + 1];
    String::strcpy(data, s);
}
String::String(const String &other) // Ham dung copy
{
    length = other.length;
    data = new char[length + 1];
    String::strcpy(this->data, other.data);
}

// ==== Destructor ====
String::~String()
{
    delete[] data;
}

// ==== Operator overloading ====
String &String::operator=(const String &other) // Gan chuoi
{
    if (this != &other)
    {
        length = other.length;
        delete[] data;
        data = new char[length + 1];
        String::strcpy(this->data, other.data);
    }
    return *this;
}
String String::operator+(const String &other) const // Cong 2 chuoi
{
    llu new_length = length + other.length;
    char *new_data = new char[new_length + 1];
    String::strcpy(new_data, this->data);
    String::strcpy(new_data + length, other.data);

    delete[] this->data;

    return other;
}
String String::operator+=(const String &other) // Cong 2 chuoi
{
    llu new_length = length + other.length;
    char *new_data = new char[new_length + 1];
    String::strcpy(new_data, this->data);
    String::strcpy(new_data + length, other.data);

    delete[] this->data;
    length = new_length;
    String::strcpy(this->data, new_data);

    return *this;
}
bool String::operator==(const String &other) const // SS 2 chuoi
{
    return String::strcmp(this->data, other.data) == 0;
}
char &String::operator[](llu position) // Thay doi gia tri ki tu
{
    static char NGU = '\0';
    if (position < this->length)
        return *(this->data + position);
    else
        return NGU;
}
const char &String::operator[](llu position) const // Truy xuat ki tu
{
    static char NGU = '\0';
    if (position < this->length)
        return *(this->data + position);
    else
        return NGU;
}

// ===== Method =======
llu String::size() const // tra ve do dai chuoi
{
    return length;
}
bool String::empty() const // Ktra chuoi co rong khong
{
    if (data[0] == '\0')
        return false;
    return true;
}
const char *String::c_str() const // tra ve C-String
{
    return this->data;
}
void String::clear() // Xoa
{
    delete[] this->data;
    this->data = new char[1];
    this->data[0] = '\0';
    this->length = 0;
}
void String::push_back(char c) // Them ki tu
{
    char *newData = new char[length + 2];
    for (llu i = 0; i < length; i++)
        newData[i] = this->data[i];
    newData[length] = c;
    newData[length + 1] = '\0';

    delete[] this->data;
    this->data = newData;
    length++;
}
String String::substr(llu position, llu n) const // Cat chuoi -> chuoi con
{
    if (position >= this->length || n >= this->length)
        return String("");
    llu realLen = (position + n > length) ? (length - position) : n;
    char *buffer = new char[realLen + 1];

    for (llu i = 0; i < realLen; i++)
        buffer[i] = data[position + i];
    buffer[realLen] = '\0';

    String sub(buffer);
    delete[] buffer;
    return sub;
}
llu String::find(const String &str, llu position) const // Tim chuoi con
{
    if (str.length == 0 || str.length > length)
        return (llu)-1;

    for (llu i = position; i <= length - str.length; i++)
    {
        llu j = 0;
        while (j < str.length && data[i + j] == str.data[j])
            j++;
        if (j == str.length)
            return i;
    }
    return (llu)-1;
}

// ===== Stream operators ========
ostream &operator<<(ostream &o, const String &s)
{
    o << s.data;
    return o;
}

istream &operator>>(istream &in, String &s)
{
    in >> s.data;
    return in;
}