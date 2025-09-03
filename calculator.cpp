#include "calculator.h"
#include "./ui_calculator.h"
#include <QKeyEvent>
#include <QString>
#include <QTextStream>
#include <QtCore/qobject.h>
#include <QtWidgets/qlineedit.h>
#include <iostream>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
  ui->inputField->installEventFilter(this);
  result = 0.f;

  connect(ui->equalsBtn, &QPushButton::clicked, this,
          &Calculator::on_equalsBtn_Clicked);
  connect(ui->inputField, &QLineEdit::returnPressed, this,
          &Calculator::on_equalsBtn_Clicked);

  // In Calculator constructor, after ui->setupUi(this)
  auto appendText = [this](const QString &s) {
    auto t = ui->inputField->text();
    if (t == "0")
      t.clear();
    ui->inputField->setText(t + s);
  };

  // Put your buttons in lists and connect in a loop
  const QList<QPushButton *> digits = {ui->btn0, ui->btn1, ui->btn2, ui->btn3,
                                       ui->btn4, ui->btn5, ui->btn6, ui->btn7,
                                       ui->btn8, ui->btn9};
  for (auto *b : digits) {
    connect(b, &QPushButton::clicked, this, [=] {
      appendText(b->text()); // "0".."9"
    });
  }

  const QList<QPushButton *> ops = {ui->addBtn, ui->subtractBtn,
                                    ui->multiplyBtn, ui->divideBtn};
  for (auto *b : ops) {
    connect(b, &QPushButton::clicked, this, [=] {
      appendText(" " + b->text() + " "); // add spaces for easier parsing
    });
  }

  // Equals handled separately
  connect(ui->equalsBtn, &QPushButton::clicked, this,
          &Calculator::on_equalsBtn_Clicked);
}

bool Calculator::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->inputField && event->type() == QEvent::KeyPress) {
    auto *ke = static_cast<QKeyEvent *>(event);

    if (ke->key() == Qt::Key_Up) {
      if (!resultHistory.isEmpty()) {
        if (historyPos == -1)
          historyPos = resultHistory.size();
        if (historyPos > 0)
          historyPos--;
        ui->inputField->setText(resultHistory[historyPos]);
        ui->inputField->selectAll(); // optional: highlight it
        return true;                 // handled
      }
    } else if (ke->key() == Qt::Key_Down) {
      if (!resultHistory.isEmpty() && historyPos != -1) {
        if (historyPos < resultHistory.size() - 1) {
          historyPos++;
          ui->inputField->setText(resultHistory[historyPos]);
        } else {
          // moved past the newest item → clear and stop browsing
          historyPos = resultHistory.size();
          ui->inputField->clear();
        }
        ui->inputField->selectAll();
        return true; // handled
      }
    }
  }
  return QMainWindow::eventFilter(obj, event);
}

Calculator::~Calculator() { delete ui; }

void Calculator::getInputs() {
  QStringList tokens = ui->inputField->text().split(" ", Qt::SkipEmptyParts);

  if (tokens.empty()) {
    return;
  }

  result = tokens[0].toFloat();

  for (int i = 1; i < tokens.size(); i += 2) {
    QString op = tokens[i];
    if (i + 1 >= tokens.size())
      break;
    float val = tokens[i + 1].toFloat();

    if (op == "+") {
      result += val;
    } else if (op == "-") {
      result -= val;
    } else if (op == "×") {
      result *= val;
    } else if (op == "÷") {
      if (val != 0) {
        result /= val;
      } else {
        std::cerr << "Error: Division by zero" << std::endl;
        return;
      }
    }
  }
}

float Calculator::add(const std::vector<float> &vals) {
  float s = 0.f;
  for (float v : vals)
    s += v;
  return s;
}

void Calculator::on_equalsBtn_Clicked() {
  getInputs();
  rememberResult(result);
  ui->inputField->setText(QString::number(result, 'g', 10));
}

void Calculator::rememberResult(float value) {
  QString s = QString::number(value, 'g', 10); // nice default formatting
  if (resultHistory.isEmpty() || resultHistory.back() != s) {
    resultHistory.push_back(s);
  }
  historyPos = resultHistory.size(); // reset cursor to “after last”
}

float Calculator::getResult() const { return result; }