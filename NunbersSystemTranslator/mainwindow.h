#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString TextLine;

    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent*)override;
    void paintEvent(QPaintEvent*)override;
private slots:
    void slotPerevesti(QString);
    void slotClicSpin2(int);
};
#endif // MAINWINDOW_H
