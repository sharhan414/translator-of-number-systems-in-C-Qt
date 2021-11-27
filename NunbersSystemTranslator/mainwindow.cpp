#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLineEdit>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>
#include "translatenumbers.h"
#include <string>
#include <QPushButton>
#include <QMessageBox>
#include <qiterator.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->EditValueTo10Syst->setReadOnly(true);
    ui->EditPrintValueNewSyst->setReadOnly(true);

    ui->SpinValuesSyst->setMaximum(36);
    ui->SpinValuesSyst->setMinimum(2);
    ui->SpinValuesSyst->setValue(10);
    ui->SpinValuesSyst->setAlignment(Qt::Alignment::enum_type::AlignHCenter);

    ui->SpinValuesToSyst->setMaximum(36);
    ui->SpinValuesToSyst->setMinimum(2);
    ui->SpinValuesToSyst->setValue(2);
    ui->SpinValuesToSyst->setAlignment(Qt::Alignment::enum_type::AlignHCenter);

    connect(ui->EditReadValues,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
    connect(ui->SpinValuesToSyst,SIGNAL(valueChanged(int)),this,SLOT(slotClicSpin2(int)));
    connect(ui->SpinValuesSyst,SIGNAL(valueChanged(int)),this,SLOT(slotClicSpin2(int)));

    ui->LabelPrintValue->setText("Ответ: значения в "+ui->SpinValuesToSyst->text()+"-й с.с");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    int w=width(),h=height();
    int heights=41,wSpin=60;



    ui->EditReadValues->setGeometry(5,h*0.13,w-wSpin-10,heights);
    ui->SpinValuesSyst->setGeometry(w-65,h*0.13,wSpin,heights);

    ui->SpinValuesToSyst->setGeometry((w-wSpin)/2,h*0.33,wSpin+10,heights);

    ui->EditValueTo10Syst->setGeometry(10,h*0.52,w-20,heights);

    ui->EditPrintValueNewSyst->setGeometry(10,h*0.67,w-20,heights*3);


}



void MainWindow::slotPerevesti(QString Text)
{
    QString Simvols="0123456789abcdefghijklmnopqrstuvwxyz";
    QString SimvolsSystem="";

    for (int i=0;i!=ui->SpinValuesSyst->value();++i)
    {
        SimvolsSystem.push_back(Simvols[i]);
    }
    qDebug()<<"ZNACH Simvols size="<<Simvols.size();
    SimvolsSystem.push_back(".");

    for (int i=0;i!=Text.size();++i)
    {
        if(std::find(SimvolsSystem.begin(),SimvolsSystem.end(),Text[i])==SimvolsSystem.end()){

        QMessageBox m(this);
        m.setText("Такого символа не бывает в "+QString::number(ui->SpinValuesSyst->value())+" с.с");
        m.setIcon(QMessageBox::Icon::Warning);
        m.setWindowTitle("Error");
        m.exec();

        disconnect(ui->EditReadValues,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
        ui->EditReadValues->setText(TextLine);
        connect(ui->EditReadValues,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
        return;
        }
    }

    TranslateNumbers numbers;
    auto text=Text.toStdString();

    auto num=numbers.TranslateNumbersSystemTo10(ui->SpinValuesSyst->value(),text);

    if(num>2'000'000'000'000'000'000.0)
    {
        QMessageBox m(this);
        m.setText("<center>Too big number.</center><center>Restrictions 2*10<sup>18</sup><center>");
        m.resize(250,100);
        m.setIcon(QMessageBox::Icon::Warning);
        m.setWindowTitle("Error");
        m.exec();
        disconnect(ui->EditReadValues,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
        ui->EditReadValues->setText(TextLine);
        connect(ui->EditReadValues,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
        return;
    }

    auto Nums=numbers.TranslateToNumbersSystem(10,num);
    auto otvet=numbers.TranslateToNumbersSystem(ui->SpinValuesToSyst->value(),num);
    QString n,m;

    n=n.fromStdString(otvet);
    m=m.fromStdString(Nums);

    ui->EditValueTo10Syst->setText(m);
    ui->EditPrintValueNewSyst->setText(n);
    ui->LabelPrintValue->setText("Ответ: значения в "+ui->SpinValuesToSyst->text()+"-й с.с");
    TextLine=Text;

}

void MainWindow::slotClicSpin2(int)
{
    slotPerevesti(ui->EditReadValues->text());
    this->update();
}

