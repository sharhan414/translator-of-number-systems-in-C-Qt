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

    ui->lineEdit_2->setReadOnly(true);
    ui->textEdit->setReadOnly(true);

    ui->spinBox->setMaximum(36);
    ui->spinBox->setMinimum(2);
    ui->spinBox->setValue(10);
    ui->spinBox->setAlignment(Qt::Alignment::enum_type::AlignHCenter);


    ui->spinBox_2->setMaximum(36);
    ui->spinBox_2->setMinimum(2);
    ui->spinBox_2->setValue(2);
    ui->spinBox_2->setAlignment(Qt::Alignment::enum_type::AlignHCenter);

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
    connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(slotClicSpin2(int)));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(slotClicSpin2(int)));

\
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
 int w=width(),h=height();
 int heights=41,wSpin=60;


ui->lineEdit->setGeometry(5,h*0.13,w-wSpin-10,heights);
ui->spinBox->setGeometry(w-65,h*0.13,wSpin,heights);

ui->spinBox_2->setGeometry(w/2-wSpin,h*0.33,wSpin+10,heights);

ui->lineEdit_2->setGeometry(10,h*0.52,w-20,heights);

ui->textEdit->setGeometry(10,h*0.67,w-20,heights*3);


}

void MainWindow::paintEvent(QPaintEvent *)
{
QPainter paint(this);


QFont font("Times",11);
QFontMetrics mtr(font);
paint.setFont(font);
//
QString Text="Введите значение ";
//QString Text="entered value";
int edit_x=ui->lineEdit->width();
int text_edins=(edit_x-mtr.width(Text))/2;
paint.drawText(text_edins,ui->lineEdit->pos().y()-mtr.height()/2,Text);

//
QString TextSpin2="Установите с.с 2-го числа.";
//QString TextSpin2="set the n.s of the 2 number";
int NachaloText2=mtr.width(TextSpin2);
int PointText2=(width()-NachaloText2-ui->spinBox_2->width())/2;
paint.drawText(PointText2,ui->spinBox_2->pos().y()-mtr.height()/2,TextSpin2);

//
QString Text10="Значения в 10-й с.с";
//QString Text10="Values in the 10 n.s";
int NachaloText=mtr.width(Text10);
int PointText=(ui->lineEdit_2->width()-NachaloText)/2;
paint.drawText(PointText,ui->lineEdit_2->pos().y()-mtr.height()/2,Text10);

//
QString TextRand="Ответ: значения в "+QString::number(ui->spinBox_2->value())+"-й с.с";
//QString TextRand="Response: the values in "+QString::number(ui->spinBox_2->value())+" n.s";

int NachaloTextR=mtr.width(TextRand);
int PointTextR=(ui->textEdit->width()-NachaloTextR)/2;
paint.drawText(PointTextR,ui->textEdit->pos().y()-mtr.height()/2,TextRand);

}

void MainWindow::slotPerevesti(QString Text)
{
 QString Simvols="0123456789abcdefghijklmnopqrstuvwxyz";
 QString SimvolsSystem="";

   for (int i=0;i!=ui->spinBox->value();++i){
       SimvolsSystem.push_back(Simvols[i]);
   }
   qDebug()<<"ZNACH Simvols size="<<Simvols.size();
   SimvolsSystem.push_back(".");

 for (int i=0;i!=Text.size();++i) {
if(std::find(SimvolsSystem.begin(),SimvolsSystem.end(),Text[i])==SimvolsSystem.end()){

    QMessageBox m(this);
    m.setText("Такого символа не бывает в "+QString::number(ui->spinBox->value())+" с.с");
    m.setIcon(QMessageBox::Icon::Warning);
    m.setWindowTitle("Error");
    m.exec();

disconnect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
    ui->lineEdit->setText(TextLine);
connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
return;
    }
 }

TranslateNumbers numbers;
auto text=Text.toStdString();

auto num=numbers.TranslateNumbersSystemTo10(ui->spinBox->value(),text);

if(num>2000000000000000000.0){
    QMessageBox m(this);
    m.setText("<center>Too big number.</center><center>Restrictions 2*10<sup>18</sup><center>");
    m.resize(250,100);
    m.setIcon(QMessageBox::Icon::Warning);
    m.setWindowTitle("Error");
    m.exec();
    disconnect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
        ui->lineEdit->setText(TextLine);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotPerevesti(QString)));
    return;
}

auto Nums=numbers.TranslateToNumbersSystem(10,num);
auto otvet=numbers.TranslateToNumbersSystem(ui->spinBox_2->value(),num);
QString n,m;

n=n.fromStdString(otvet);
m=m.fromStdString(Nums);

ui->lineEdit_2->setText(m);
ui->textEdit->setText(n);

TextLine=Text;

}

void MainWindow::slotClicSpin2(int)
{
  slotPerevesti(ui->lineEdit->text());
}

