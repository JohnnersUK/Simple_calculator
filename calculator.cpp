#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // Attach signals to slots
    for(int i = 0; i < 10; i++) // Number buttons
    {
        QString btnLabel = "Btn_" + QString::number(i);

        QPushButton* temp = Calculator::findChild<QPushButton *>(btnLabel);
        connect(temp, SIGNAL(released()), this, SLOT(NumPressed()));
    }

    // Connect the operators
    connect(Calculator::findChild<QPushButton*>("Btn_Add"), SIGNAL(released()),this,SLOT(OperatorPressed()));
    connect(Calculator::findChild<QPushButton*>("Btn_Sub"), SIGNAL(released()),this,SLOT(OperatorPressed()));
    connect(Calculator::findChild<QPushButton*>("Btn_Div"), SIGNAL(released()),this,SLOT(OperatorPressed()));
    connect(Calculator::findChild<QPushButton*>("Btn_Mul"), SIGNAL(released()),this,SLOT(OperatorPressed()));

    // Connect the equals
    connect(Calculator::findChild<QPushButton*>("Btn_Eq"), SIGNAL(released()),this, SLOT(EqualsPressed()));

    // Connect memory
    connect(Calculator::findChild<QPushButton*>("Btn_Mem"), SIGNAL(released()),this, SLOT(CopyFromMemory()));
    connect(Calculator::findChild<QPushButton*>("Btn_Mp"), SIGNAL(released()),this, SLOT(AddToMemory()));
    connect(Calculator::findChild<QPushButton*>("Btn_Ms"), SIGNAL(released()),this, SLOT(ClearMemory()));

    // Connect other
    connect(Calculator::findChild<QPushButton*>("Btn_Clr"), SIGNAL(released()),this,SLOT(ClearAll()));
    connect(Calculator::findChild<QPushButton*>("Btn_Sig"), SIGNAL(released()),this,SLOT(SwapSign()));

}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::NumPressed()
{
    QPushButton *btn = (QPushButton *)sender();
    QString btnVal = btn->text();
    QString displayVal = ui->Display->text();

    if(displayVal.toDouble() == 0)
    {
        ui->Display->setText(btnVal);
    }
    else
    {
        QString newValStr = displayVal + btnVal;
        double  newVal = newValStr.toDouble();

        ui->Display->setText(QString::number(newVal, 'g', 16));
    }

    digitPressed = true;
}

void Calculator::OperatorPressed()
{
    QPushButton * btn = (QPushButton*)sender();
    QString btnLabel = btn->text();
    QString displayVal = ui->Display->text();

    strOperator = btn->text();
    sumSoFar = displayVal.toDouble();

    ui->SubDisplay->setText(QString::number(sumSoFar, 'g', 16) + " " + strOperator);
    ui->Display->setText("0");
}

void Calculator::EqualsPressed()
{
    QString displayStr = ui->Display->text();

    // Check if a digit has been pressed
    if (digitPressed)
        rightOperand = displayStr.toDouble();   // Store the display into rightOperand

    if(strOperator == "+")
    {
        sumSoFar += rightOperand;
    }
    else if (strOperator == "-")
    {
        sumSoFar -= rightOperand;
    }
    else if(strOperator == "/")
    {
        sumSoFar /= rightOperand;
    }
    else if(strOperator == "*")
    {
        sumSoFar *= rightOperand;
    }

    ui->Display->setText(QString::number(sumSoFar, 'g', 16));
    ui->SubDisplay->setText(strOperator + " " + QString::number(rightOperand, 'g', 16));

    digitPressed = false;
}

void Calculator::ClearAll()
{
    // Clear the display
    ui->Display->setText("0");
    ui->SubDisplay->setText("");

    // Clear memory
    sumSoFar = 0;
    rightOperand = 0;
    strOperator = "";
}

void Calculator::SwapSign()
{
    double temp = ui->Display->text().toDouble();

    temp *= -1;

    ui->Display->setText(QString::number(temp, 'g', 16));
}

void Calculator::AddToMemory()
{
     double temp = ui->Display->text().toDouble();
     memory = temp;
}

void Calculator::CopyFromMemory()
{
    ui->Display->setText(QString::number(memory, 'g', 16));
    digitPressed = true;
}

void Calculator::ClearMemory()
{
    memory = 0;
}
