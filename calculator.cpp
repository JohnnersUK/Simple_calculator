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

    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)
    {
        ui->Display->setText(btnVal);
    }
    else
    {
        QString newValStr = displayVal + btnVal;
        double  newVal = newValStr.toDouble();

        ui->Display->setText(QString::number(newVal, 'g', 16));
    }
}

void Calculator::OpperatorPressed()
{
    QPushButton * btn = (QPushButton*)sender();
    QString btnLabel = btn->text();


    /*
    switch(btnLabel)
    {

    }
    */
}
