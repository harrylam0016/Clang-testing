#include "Student.h"

Student::Student()
    : m_gpa(0.0)
{
}

Student::Student(const QString& id, const QString& firstName, const QString& lastName,
                 const QDate& dateOfBirth, const QString& gender, const QString& email,
                 const QString& phone, const QString& address, const QString& major, double gpa)
    : m_studentId(id)
    , m_firstName(firstName)
    , m_lastName(lastName)
    , m_dateOfBirth(dateOfBirth)
    , m_gender(gender)
    , m_email(email)
    , m_phone(phone)
    , m_address(address)
    , m_major(major)
    , m_gpa(gpa)
{
}

QString Student::getStudentId() const
{
    return m_studentId;
}

QString Student::getFirstName() const
{
    return m_firstName;
}

QString Student::getLastName() const
{
    return m_lastName;
}

QString Student::getFullName() const
{
    return m_firstName + " " + m_lastName;
}

QDate Student::getDateOfBirth() const
{
    return m_dateOfBirth;
}

QString Student::getGender() const
{
    return m_gender;
}

QString Student::getEmail() const
{
    return m_email;
}

QString Student::getPhone() const
{
    return m_phone;
}

QString Student::getAddress() const
{
    return m_address;
}

QString Student::getMajor() const
{
    return m_major;
}

double Student::getGPA() const
{
    return m_gpa;
}

void Student::setStudentId(const QString& id)
{
    m_studentId = id;
}

void Student::setFirstName(const QString& firstName)
{
    m_firstName = firstName;
}

void Student::setLastName(const QString& lastName)
{
    m_lastName = lastName;
}

void Student::setDateOfBirth(const QDate& dateOfBirth)
{
    m_dateOfBirth = dateOfBirth;
}

void Student::setGender(const QString& gender)
{
    m_gender = gender;
}

void Student::setEmail(const QString& email)
{
    m_email = email;
}

void Student::setPhone(const QString& phone)
{
    m_phone = phone;
}

void Student::setAddress(const QString& address)
{
    m_address = address;
}

void Student::setMajor(const QString& major)
{
    m_major = major;
}

void Student::setGPA(double gpa)
{
    m_gpa = gpa;
}
