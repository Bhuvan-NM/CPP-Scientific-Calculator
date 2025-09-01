#include "calculator.h"
#include "./ui_calculator.h"
#include <QtCore/qlogging.h>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
  connect(ui->addBtn, &QPushButton::clicked, this,
          &Calculator::on_addBtn_Clicked);
}

Calculator::~Calculator() { delete ui; }

void Calculator::on_addBtn_Clicked() { qDebug() << "Add button clicked"; }
