#pragma once
#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT
public:
  explicit Calculator(QWidget *parent = nullptr);
  ~Calculator();

  void getInputs();
  float getResult() const;
  float add(const std::vector<float> &vals);

private slots:
  void on_equalsBtn_Clicked();

private:
  void rememberResult(float value);
  bool eventFilter(QObject *obj, QEvent *event) override;

  Ui::Calculator *ui;
  std::vector<float> history; // <-- store parsed numbers here
  float result;

  QVector<QString> resultHistory; // stores past results as strings
  int historyPos = -1;
};