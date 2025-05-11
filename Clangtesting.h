#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Clangtesting.h"

class Clangtesting : public QMainWindow
{
    Q_OBJECT

public:
    Clangtesting(QWidget *parent = nullptr);
    ~Clangtesting();

private:
    Ui::ClangtestingClass ui;
};
