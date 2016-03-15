#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QCloseEvent>
#include <QPageSetupDialog>
#include <QPrinter>
#include <QSettings>
#include <QLabel>
#include <QClipboard>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSettings* settings;

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_textEdit_textChanged();

    void closeEvent (QCloseEvent *event);


    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionPage_Setup_triggered();

    void on_actionPrint_triggered();

    int text_changed_msgbox();


    void on_actionUndo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionFind_triggered();

    void on_actionFind_Next_triggered();

    void on_actionReplace_triggered();

    void on_actionGo_To_triggered();

    void on_actionSelect_All_triggered();

    void on_actionTime_Date_triggered();

    void on_actionWord_Wrap_triggered(bool checked);

    void on_actionFont_triggered();

    void on_actionStatus_Bar_triggered(bool checked);

    void on_actionView_Help_triggered();

    void on_actionAbout_Notepad_triggered();

    void on_textEdit_cursorPositionChanged();

private:
    Ui::MainWindow* ui;
    QFile* file;
    bool isTextChanged = false;
    QPrinter* printer;
    QLabel *stat;
};

#endif // MAINWINDOW_H
