#pragma once

#include <QString>
#include <QDate>
#include <QVector>

class Student
{
public:
    Student();
    Student(const QString& id, const QString& firstName, const QString& lastName,
            const QDate& dateOfBirth, const QString& gender, const QString& email,
            const QString& phone, const QString& address, const QString& major, double gpa);
    
    QString getStudentId() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getFullName() const;
    QDate getDateOfBirth() const;
    QString getGender() const;
    QString getEmail() const;
    QString getPhone() const;
    QString getAddress() const;
    QString getMajor() const;
    double getGPA() const;
    
    void setStudentId(const QString& id);
    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setDateOfBirth(const QDate& dateOfBirth);
    void setGender(const QString& gender);
    void setEmail(const QString& email);
    void setPhone(const QString& phone);
    void setAddress(const QString& address);
    void setMajor(const QString& major);
    void setGPA(double gpa);
    
private:
    QString m_studentId;
    QString m_firstName;
    QString m_lastName;
    QDate m_dateOfBirth;
    QString m_gender;
    QString m_email;
    QString m_phone;
    QString m_address;
    QString m_major;
    double m_gpa;
};
