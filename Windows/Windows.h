#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Windows.h"

class Windows : public QMainWindow
{
    Q_OBJECT

public:
    Windows(QWidget *parent = Q_NULLPTR);

private:
    Ui::WindowsClass ui;
};
