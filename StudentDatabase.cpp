#include "StudentDatabase.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>

StudentDatabase::StudentDatabase(QObject* parent)
    : QObject(parent)
{
    m_defaultDatabasePath = QDir::currentPath() + "/students.json";
}

StudentDatabase::~StudentDatabase()
{
    saveToFile(m_defaultDatabasePath);
}

StudentDatabase& StudentDatabase::getInstance()
{
    static StudentDatabase instance;
    return instance;
}

bool StudentDatabase::addStudent(const Student& student)
{
    QString studentId = student.getStudentId();
    
    // Check if student with the same ID already exists
    if (m_students.contains(studentId)) {
        return false;
    }
    
    m_students.insert(studentId, student);
    emit databaseChanged();
    return true;
}

bool StudentDatabase::updateStudent(const Student& student)
{
    QString studentId = student.getStudentId();
    
    // Check if student exists
    if (!m_students.contains(studentId)) {
        return false;
    }
    
    m_students[studentId] = student;
    emit databaseChanged();
    return true;
}

bool StudentDatabase::deleteStudent(const QString& studentId)
{
    if (!m_students.contains(studentId)) {
        return false;
    }
    
    m_students.remove(studentId);
    emit databaseChanged();
    return true;
}

Student StudentDatabase::getStudent(const QString& studentId) const
{
    if (m_students.contains(studentId)) {
        return m_students[studentId];
    }
    
    return Student(); // Return empty student if not found
}

QVector<Student> StudentDatabase::getAllStudents() const
{
    return m_students.values().toVector();
}

QVector<Student> StudentDatabase::searchStudents(const QString& searchText) const
{
    QVector<Student> results;
    QString searchTextLower = searchText.toLower();
    
    for (const Student& student : m_students.values()) {
        if (student.getStudentId().toLower().contains(searchTextLower) ||
            student.getFirstName().toLower().contains(searchTextLower) ||
            student.getLastName().toLower().contains(searchTextLower)) {
            results.append(student);
        }
    }
    
    return results;
}

bool StudentDatabase::saveToFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing: " << filePath;
        return false;
    }
    
    QJsonArray studentsArray;
    
    for (const Student& student : m_students.values()) {
        QJsonObject studentObj;
        studentObj["id"] = student.getStudentId();
        studentObj["firstName"] = student.getFirstName();
        studentObj["lastName"] = student.getLastName();
        studentObj["dateOfBirth"] = student.getDateOfBirth().toString("yyyy-MM-dd");
        studentObj["gender"] = student.getGender();
        studentObj["email"] = student.getEmail();
        studentObj["phone"] = student.getPhone();
        studentObj["address"] = student.getAddress();
        studentObj["major"] = student.getMajor();
        studentObj["gpa"] = student.getGPA();
        
        studentsArray.append(studentObj);
    }
    
    QJsonDocument document(studentsArray);
    file.write(document.toJson());
    file.close();
    
    return true;
}

bool StudentDatabase::loadFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading: " << filePath;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument document = QJsonDocument::fromJson(data);
    if (document.isNull() || !document.isArray()) {
        qDebug() << "Invalid JSON format in file: " << filePath;
        return false;
    }
    
    QJsonArray studentsArray = document.array();
    m_students.clear();
    
    for (const QJsonValue& value : studentsArray) {
        QJsonObject studentObj = value.toObject();
        
        Student student;
        student.setStudentId(studentObj["id"].toString());
        student.setFirstName(studentObj["firstName"].toString());
        student.setLastName(studentObj["lastName"].toString());
        student.setDateOfBirth(QDate::fromString(studentObj["dateOfBirth"].toString(), "yyyy-MM-dd"));
        student.setGender(studentObj["gender"].toString());
        student.setEmail(studentObj["email"].toString());
        student.setPhone(studentObj["phone"].toString());
        student.setAddress(studentObj["address"].toString());
        student.setMajor(studentObj["major"].toString());
        student.setGPA(studentObj["gpa"].toDouble());
        
        m_students.insert(student.getStudentId(), student);
    }
    
    emit databaseChanged();
    return true;
}

bool StudentDatabase::importFromCSV(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open CSV file for reading: " << filePath;
        return false;
    }
    
    QTextStream in(&file);
    
    // Read header
    QString header = in.readLine();
    QStringList headers = header.split(",");
    
    // Validate header
    QStringList requiredHeaders = {"ID", "FirstName", "LastName", "DateOfBirth", "Gender", 
                                  "Email", "Phone", "Address", "Major", "GPA"};
    
    // Check if all required headers are present
    for (const QString& required : requiredHeaders) {
        if (!headers.contains(required, Qt::CaseInsensitive)) {
            qDebug() << "CSV is missing required header: " << required;
            file.close();
            return false;
        }
    }
    
    // Clear existing students
    m_students.clear();
    
    // Read data rows
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        
        // Handle quoted fields correctly
        QStringList fields;
        bool inQuotes = false;
        QString field;
        
        for (int i = 0; i < line.length(); ++i) {
            QChar c = line.at(i);
            
            if (c == '\"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                fields.append(field);
                field.clear();
            } else {
                field.append(c);
            }
        }
        fields.append(field); // Add the last field
        
        if (fields.size() != headers.size()) {
            qDebug() << "CSV line has incorrect number of fields:" << line;
            continue;
        }
        
        // Create student from CSV fields
        Student student;
        
        for (int i = 0; i < headers.size(); ++i) {
            QString headerName = headers[i].trimmed().toLower();
            QString value = fields[i].trimmed();
            
            if (headerName == "id") {
                student.setStudentId(value);
            } else if (headerName == "firstname") {
                student.setFirstName(value);
            } else if (headerName == "lastname") {
                student.setLastName(value);
            } else if (headerName == "dateofbirth") {
                student.setDateOfBirth(QDate::fromString(value, "yyyy-MM-dd"));
            } else if (headerName == "gender") {
                student.setGender(value);
            } else if (headerName == "email") {
                student.setEmail(value);
            } else if (headerName == "phone") {
                student.setPhone(value);
            } else if (headerName == "address") {
                student.setAddress(value);
            } else if (headerName == "major") {
                student.setMajor(value);
            } else if (headerName == "gpa") {
                student.setGPA(value.toDouble());
            }
        }
        
        // Add student to database
        if (!student.getStudentId().isEmpty()) {
            m_students.insert(student.getStudentId(), student);
        }
    }
    
    file.close();
    emit databaseChanged();
    return true;
}

bool StudentDatabase::exportToCSV(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing: " << filePath;
        return false;
    }
    
    QTextStream out(&file);
    
    // Write header
    out << "ID,FirstName,LastName,DateOfBirth,Gender,Email,Phone,Address,Major,GPA\n";
    
    // Write data
    for (const Student& student : m_students.values()) {
        out << student.getStudentId() << ","
            << escapeCSV(student.getFirstName()) << ","
            << escapeCSV(student.getLastName()) << ","
            << student.getDateOfBirth().toString("yyyy-MM-dd") << ","
            << student.getGender() << ","
            << escapeCSV(student.getEmail()) << ","
            << escapeCSV(student.getPhone()) << ","
            << escapeCSV(student.getAddress()) << ","
            << escapeCSV(student.getMajor()) << ","
            << QString::number(student.getGPA(), 'f', 2) << "\n";
    }
    
    file.close();
    return true;
}

// Helper function to escape CSV fields
QString escapeCSV(const QString& field)
{
    // If the field contains commas, quotes, or newlines, wrap it in quotes and escape any quotes
    if (field.contains(',') || field.contains('\"') || field.contains('\n')) {
        QString escaped = field;
        escaped.replace("\"", "\"\""); // Escape quotes by doubling them
        return "\"" + escaped + "\"";
    }
    return field;
}
