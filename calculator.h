#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void NumPressed();
    void OperatorPressed();
    void EqualsPressed();

    void SwapSign();

    void AddToMemory();
    void CopyFromMemory();

    void ClearMemory();
    void ClearAll();

private:
    Ui::Calculator *ui;
    QString strOperator = "";

    double sumSoFar = 0;
    double rightOperand = 0;
    double memory = 0;

    bool digitPressed = false;

};
#endif // CALCULATOR_H
