#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include "Student.h"

class StudentTableModel : public QAbstractTableModel
{
public:
    enum Columns {
        ID = 0,
        FirstName,
        LastName,
        DateOfBirth,
        Gender,
        Email,
        Phone,
        Major,
        GPA,
        ColumnCount
    };

    StudentTableModel(QObject* parent = nullptr);
    
    void setStudents(const QVector<Student>& students);
    Student getStudentAt(int row) const;
    
    // QAbstractTableModel interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
private:
    QVector<Student> m_students;
};
