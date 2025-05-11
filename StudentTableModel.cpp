#include "StudentTableModel.h"

StudentTableModel::StudentTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void StudentTableModel::setStudents(const QVector<Student>& students)
{
    beginResetModel();
    m_students = students;
    endResetModel();
}

Student StudentTableModel::getStudentAt(int row) const
{
    if (row >= 0 && row < m_students.size()) {
        return m_students[row];
    }
    return Student();
}

int StudentTableModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_students.size();
}

int StudentTableModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return ColumnCount;
}

QVariant StudentTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_students.size() || index.row() < 0) {
        return QVariant();
    }
    
    const Student& student = m_students[index.row()];
    
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case ID:
                return student.getStudentId();
            case FirstName:
                return student.getFirstName();
            case LastName:
                return student.getLastName();
            case DateOfBirth:
                return student.getDateOfBirth().toString("yyyy-MM-dd");
            case Gender:
                return student.getGender();
            case Email:
                return student.getEmail();
            case Phone:
                return student.getPhone();
            case Major:
                return student.getMajor();
            case GPA:
                return QString::number(student.getGPA(), 'f', 2);
            default:
                return QVariant();
        }
    }
    
    return QVariant();
}

QVariant StudentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case ID:
                return tr("ID");
            case FirstName:
                return tr("First Name");
            case LastName:
                return tr("Last Name");
            case DateOfBirth:
                return tr("Date of Birth");
            case Gender:
                return tr("Gender");
            case Email:
                return tr("Email");
            case Phone:
                return tr("Phone");
            case Major:
                return tr("Major");
            case GPA:
                return tr("GPA");
            default:
                return QVariant();
        }
    }
    
    return QVariant();
}
