#include "Clangtesting.h"

Clangtesting::Clangtesting(QWidget *parent)
    : QMainWindow(parent)
    , m_currentMode(Add)
    , m_studentModel(new StudentTableModel(this))
{
    ui.setupUi(this);
    
    // Set up the student table view
    ui.tableViewStudents->setModel(m_studentModel);
    
    // Set minimum date to reasonable value (e.g., 100 years ago)
    QDate minDate = QDate::currentDate().addYears(-100);
    ui.dateEditDOB->setMinimumDate(minDate);
    ui.dateEditDOB->setMaximumDate(QDate::currentDate());
    ui.dateEditDOB->setDate(QDate::currentDate().addYears(-18)); // Default to 18 years old
    
    // Load students from file
    StudentDatabase::getInstance().loadFromFile(QDir::currentPath() + "/students.json");
    
    // Setup signal/slot connections
    setupConnections();
    
    // Load students into the table
    loadStudents();
    
    // Initialize in Add mode
    clearStudentForm();
    switchToTab(0); // Start with student list tab
}

Clangtesting::~Clangtesting()
{
    // Save students to file before exit
    StudentDatabase::getInstance().saveToFile(QDir::currentPath() + "/students.json");
}

void Clangtesting::setupConnections()
{
    // Connect database changed signal to update the view
    connect(&StudentDatabase::getInstance(), &StudentDatabase::databaseChanged,
            this, &Clangtesting::onDatabaseChanged);
    
    // Connect action signals to slots (these are handled automatically by Qt's naming convention)
}

void Clangtesting::loadStudents()
{
    QVector<Student> students = StudentDatabase::getInstance().getAllStudents();
    m_studentModel->setStudents(students);
    
    // Resize columns to content
    ui.tableViewStudents->resizeColumnsToContents();
}

void Clangtesting::clearStudentForm()
{
    ui.lineEditStudentId->clear();
    ui.lineEditFirstName->clear();
    ui.lineEditLastName->clear();
    ui.dateEditDOB->setDate(QDate::currentDate().addYears(-18)); // Default to 18 years old
    ui.comboBoxGender->setCurrentIndex(0); // Default to first gender (Male)
    ui.lineEditEmail->clear();
    ui.lineEditPhone->clear();
    ui.textEditAddress->clear();
    ui.comboBoxMajor->setCurrentIndex(0); // Default to first major (Computer Science)
    ui.doubleSpinBoxGPA->setValue(0.0);
    
    // Enable Student ID field in Add mode, disable in Edit mode
    ui.lineEditStudentId->setEnabled(m_currentMode == Add);
}

void Clangtesting::populateStudentForm(const Student& student)
{
    ui.lineEditStudentId->setText(student.getStudentId());
    ui.lineEditFirstName->setText(student.getFirstName());
    ui.lineEditLastName->setText(student.getLastName());
    ui.dateEditDOB->setDate(student.getDateOfBirth());
    
    // Set gender combo box
    int genderIndex = 0; // Default to Male
    if (student.getGender() == "Female") {
        genderIndex = 1;
    } else if (student.getGender() == "Other") {
        genderIndex = 2;
    }
    ui.comboBoxGender->setCurrentIndex(genderIndex);
    
    ui.lineEditEmail->setText(student.getEmail());
    ui.lineEditPhone->setText(student.getPhone());
    ui.textEditAddress->setText(student.getAddress());
    
    // Set major combo box
    int majorIndex = ui.comboBoxMajor->findText(student.getMajor());
    if (majorIndex >= 0) {
        ui.comboBoxMajor->setCurrentIndex(majorIndex);
    } else if (!student.getMajor().isEmpty()) {
        ui.comboBoxMajor->addItem(student.getMajor());
        ui.comboBoxMajor->setCurrentText(student.getMajor());
    }
    
    ui.doubleSpinBoxGPA->setValue(student.getGPA());
}

Student Clangtesting::getStudentFromForm()
{
    QString id = ui.lineEditStudentId->text().trimmed();
    QString firstName = ui.lineEditFirstName->text().trimmed();
    QString lastName = ui.lineEditLastName->text().trimmed();
    QDate dob = ui.dateEditDOB->date();
    QString gender = ui.comboBoxGender->currentText();
    QString email = ui.lineEditEmail->text().trimmed();
    QString phone = ui.lineEditPhone->text().trimmed();
    QString address = ui.textEditAddress->toPlainText().trimmed();
    QString major = ui.comboBoxMajor->currentText().trimmed();
    double gpa = ui.doubleSpinBoxGPA->value();
    
    return Student(id, firstName, lastName, dob, gender, email, phone, address, major, gpa);
}

bool Clangtesting::validateStudentForm()
{
    // Check for mandatory fields
    if (ui.lineEditStudentId->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("Student ID is required."));
        ui.lineEditStudentId->setFocus();
        return false;
    }
    
    if (ui.lineEditFirstName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("First Name is required."));
        ui.lineEditFirstName->setFocus();
        return false;
    }
    
    if (ui.lineEditLastName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("Last Name is required."));
        ui.lineEditLastName->setFocus();
        return false;
    }
    
    // In Add mode, check if student ID already exists
    if (m_currentMode == Add) {
        QString studentId = ui.lineEditStudentId->text().trimmed();
        if (!StudentDatabase::getInstance().getStudent(studentId).getStudentId().isEmpty()) {
            QMessageBox::warning(this, tr("Validation Error"), 
                                tr("A student with ID '%1' already exists.").arg(studentId));
            ui.lineEditStudentId->setFocus();
            return false;
        }
    }
    
    // Validate email format (simple check)
    QString email = ui.lineEditEmail->text().trimmed();
    if (!email.isEmpty() && !email.contains('@')) {
        QMessageBox::warning(this, tr("Validation Error"), tr("Invalid email format."));
        ui.lineEditEmail->setFocus();
        return false;
    }
    
    return true;
}

void Clangtesting::saveStudent()
{
    if (!validateStudentForm()) {
        return;
    }
    
    Student student = getStudentFromForm();
    bool success = false;
    
    if (m_currentMode == Add) {
        success = StudentDatabase::getInstance().addStudent(student);
    } else { // Edit mode
        success = StudentDatabase::getInstance().updateStudent(student);
    }
    
    if (success) {
        switchToTab(0); // Switch back to student list tab
        loadStudents(); // Refresh the list
    } else {
        QMessageBox::critical(this, tr("Error"), 
                            tr("Failed to %1 student record.").arg(m_currentMode == Add ? "add" : "update"));
    }
}

void Clangtesting::switchToTab(int tabIndex)
{
    ui.tabWidget->setCurrentIndex(tabIndex);
}

// Slot implementations
void Clangtesting::on_pushButtonAdd_clicked()
{
    m_currentMode = Add;
    clearStudentForm();
    switchToTab(1); // Switch to Add/Edit tab
}

void Clangtesting::on_pushButtonEdit_clicked()
{
    QModelIndexList selection = ui.tableViewStudents->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::information(this, tr("Information"), 
                              tr("Please select a student to edit."));
        return;
    }
    
    int row = selection.first().row();
    Student student = m_studentModel->getStudentAt(row);
    
    m_currentMode = Edit;
    m_currentStudentId = student.getStudentId();
    
    populateStudentForm(student);
    ui.lineEditStudentId->setEnabled(false); // Disable ID field in edit mode
    
    switchToTab(1); // Switch to Add/Edit tab
}

void Clangtesting::on_pushButtonDelete_clicked()
{
    QModelIndexList selection = ui.tableViewStudents->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::information(this, tr("Information"), 
                              tr("Please select a student to delete."));
        return;
    }
    
    int row = selection.first().row();
    Student student = m_studentModel->getStudentAt(row);
    
    int result = QMessageBox::question(this, tr("Confirm Deletion"),
                                     tr("Are you sure you want to delete student '%1'?").arg(student.getFullName()),
                                     QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes) {
        bool success = StudentDatabase::getInstance().deleteStudent(student.getStudentId());
        
        if (!success) {
            QMessageBox::critical(this, tr("Error"), tr("Failed to delete student record."));
        }
        // Database changed signal will trigger UI update
    }
}

void Clangtesting::on_pushButtonSearch_clicked()
{
    QString searchText = ui.lineEditSearch->text().trimmed();
    if (searchText.isEmpty()) {
        loadStudents(); // Show all students if search is empty
        return;
    }
    
    QVector<Student> students = StudentDatabase::getInstance().searchStudents(searchText);
    m_studentModel->setStudents(students);
    
    ui.statusBar->showMessage(tr("%1 student(s) found").arg(students.size()), 3000);
}

void Clangtesting::on_pushButtonRefresh_clicked()
{
    ui.lineEditSearch->clear();
    loadStudents();
}

void Clangtesting::on_pushButtonSave_clicked()
{
    saveStudent();
}

void Clangtesting::on_pushButtonCancel_clicked()
{
    switchToTab(0); // Switch back to student list tab
}

void Clangtesting::on_actionImportStudents_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Import Students"),
                                                QDir::homePath(),
                                                tr("CSV Files (*.csv)"));
    
    if (filePath.isEmpty()) {
        return; // User canceled
    }
    
    bool success = StudentDatabase::getInstance().importFromCSV(filePath);
    
    if (success) {
        QMessageBox::information(this, tr("Import Successful"),
                                tr("Students imported successfully."));
        loadStudents();
    } else {
        QMessageBox::critical(this, tr("Import Failed"),
                            tr("Failed to import students from CSV file."));
    }
}

void Clangtesting::on_actionExportStudents_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export Students"),
                                                QDir::homePath() + "/students.csv",
                                                tr("CSV Files (*.csv)"));
    
    if (filePath.isEmpty()) {
        return; // User canceled
    }
    
    bool success = StudentDatabase::getInstance().exportToCSV(filePath);
    
    if (success) {
        QMessageBox::information(this, tr("Export Successful"),
                                tr("Students exported successfully."));
    } else {
        QMessageBox::critical(this, tr("Export Failed"),
                            tr("Failed to export students to CSV file."));
    }
}

void Clangtesting::on_actionExit_triggered()
{
    close();
}

void Clangtesting::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Student Management System"),
                      tr("<h2>Student Management System</h2>"
                         "<p>Version 1.0</p>"
                         "<p>A simple application to manage student records.</p>"
                         "<p>&copy; 2025 Your Name</p>"));
}

void Clangtesting::on_actionAdd_triggered()
{
    on_pushButtonAdd_clicked();
}

void Clangtesting::on_actionEdit_triggered()
{
    on_pushButtonEdit_clicked();
}

void Clangtesting::on_actionDelete_triggered()
{
    on_pushButtonDelete_clicked();
}

void Clangtesting::on_tableViewStudents_doubleClicked(const QModelIndex& index)
{
    // Double-clicking a student row opens it for editing
    if (index.isValid()) {
        int row = index.row();
        Student student = m_studentModel->getStudentAt(row);
        
        m_currentMode = Edit;
        m_currentStudentId = student.getStudentId();
        
        populateStudentForm(student);
        ui.lineEditStudentId->setEnabled(false); // Disable ID field in edit mode
        
        switchToTab(1); // Switch to Add/Edit tab
    }
}

void Clangtesting::onDatabaseChanged()
{
    loadStudents();
    ui.statusBar->showMessage(tr("Database updated"), 3000);
}
