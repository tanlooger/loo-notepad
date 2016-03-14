#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QCloseEvent>
#include <QPageSetupDialog>
#include <QPrinter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_textEdit_textChanged();

    void closeEvent (QCloseEvent *event);


    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionPate_Setup_triggered();

    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QFile* file;
    bool isTextChanged = false;
    QPrinter * printer;

};

#endif // MAINWINDOW_H
