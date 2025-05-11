#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Student.h"

// Helper function declaration
QString escapeCSV(const QString& field);

class StudentDatabase : public QObject
{
    Q_OBJECT

public:
    static StudentDatabase& getInstance();

    bool addStudent(const Student& student);
    bool updateStudent(const Student& student);
    bool deleteStudent(const QString& studentId);
    Student getStudent(const QString& studentId) const;
    QVector<Student> getAllStudents() const;
    QVector<Student> searchStudents(const QString& searchText) const;
    
    bool saveToFile(const QString& filePath);
    bool loadFromFile(const QString& filePath);
    
    bool importFromCSV(const QString& filePath);
    bool exportToCSV(const QString& filePath);

signals:
    void databaseChanged();

private:
    StudentDatabase(QObject* parent = nullptr);
    ~StudentDatabase();
    StudentDatabase(const StudentDatabase&) = delete;
    StudentDatabase& operator=(const StudentDatabase&) = delete;
    
    QMap<QString, Student> m_students;  // Map student ID to Student object
    QString m_defaultDatabasePath;
};
