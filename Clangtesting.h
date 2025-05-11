#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDate>

#include "ui_Clangtesting.h"
#include "Student.h"
#include "StudentDatabase.h"
#include "StudentTableModel.h"

class Clangtesting : public QMainWindow
{
    Q_OBJECT

public:
    Clangtesting(QWidget *parent = nullptr);
    ~Clangtesting();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSearch_clicked();
    void on_pushButtonRefresh_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonCancel_clicked();
    void on_actionImportStudents_triggered();
    void on_actionExportStudents_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionAdd_triggered();
    void on_actionEdit_triggered();
    void on_actionDelete_triggered();
    void on_tableViewStudents_doubleClicked(const QModelIndex& index);
    
    void onDatabaseChanged();

private:
    void setupConnections();
    void loadStudents();
    void clearStudentForm();
    void populateStudentForm(const Student& student);
    Student getStudentFromForm();
    bool validateStudentForm();
    void saveStudent();
    void switchToTab(int tabIndex);

    enum EditMode { Add, Edit };
    EditMode m_currentMode;
    QString m_currentStudentId;

    Ui::ClangtestingClass ui;
    StudentTableModel* m_studentModel;
};
