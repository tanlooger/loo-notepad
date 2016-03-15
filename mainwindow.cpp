#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QPrinterInfo>
#include <QRegExp>
#include <QFontDialog>
#include <QTextCursor>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    settings(new QSettings("Tanlooger", "qt-notepad", this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setVisible(settings->value("isStatusBar").toBool());
    ui->actionStatus_Bar->setChecked(settings->value("isStatusBar").toBool());
    ui->actionWord_Wrap->setChecked(settings->value("isWordWrap").toBool());
    ui->textEdit->setLineWrapMode(settings->value("isWordWrap").toBool() ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
    QFont font = qvariant_cast<QFont>(settings->value("font"));
    ui->textEdit->setFont(font);

    this->stat = new QLabel(this);
    stat->setAlignment(Qt::AlignRight);
    ui->statusBar->addPermanentWidget(stat);
}

MainWindow::~MainWindow()
{
    if(this->file && this->file->isOpen())this->file->close();
    delete ui;
}

/*********MENU FILE ACTIONS BEGIN**********************/
void MainWindow::on_actionNew_triggered()
{
    if(this->isTextChanged){
        this->text_changed_msgbox();
    }else{
        if(this->file && this->file->isOpen())this->file->close();
        this->setWindowTitle("Untitled - qt-notepad");
        ui->textEdit->clear();
        this->isTextChanged = false;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(this->file && this->isTextChanged){
        this->text_changed_msgbox();
    }else{
        QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
        if(filename.isEmpty())return;
        //this->openfile->open(filename)

        this->file = new QFile(filename, this);
        if (!this->file->open(QIODevice::ReadWrite | QIODevice::Text))return;
        this->setWindowTitle(filename);

        QTextStream stream(this->file);
        ui->textEdit->clear();
        ui->textEdit->setText(stream.readAll());
        this->isTextChanged = false;
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(!this->file){
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setDirectory(QDir::homePath());
        dialog.setOption(QFileDialog::DontUseNativeDialog, true);
        QString filename = dialog.getSaveFileName(this).trimmed();
        this->file = new QFile(filename, this);
        if (!this->file->open(QIODevice::ReadWrite | QIODevice::Text))return;
        this->setWindowTitle(filename);
    }

    this->file->resize(this->file->fileName(), 0);
    QTextStream stream(this->file);
    stream << ui->textEdit->toPlainText();
    this->file->flush();
    this->isTextChanged = false;
}

void MainWindow::on_textEdit_textChanged()
{
    this->isTextChanged = true;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(this->isTextChanged){
        event->ignore();
        this->text_changed_msgbox();
        event->accept();
    }else{
        event->accept();
    }

}

void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDirectory(QDir::homePath());
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    QString filename = dialog.getSaveFileName(this).trimmed();
    this->file = new QFile(filename, this);
    if (!this->file->open(QIODevice::ReadWrite | QIODevice::Text))return;
    this->setWindowTitle(filename);
}

void MainWindow::on_actionPage_Setup_triggered()
{
    QStringList printerList = QPrinterInfo::availablePrinterNames();
    if(printerList.isEmpty()){
        QMessageBox::information(this, "Info", "No Printer Device Found");
        return;
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QStringList printerList = QPrinterInfo::availablePrinterNames();
    if(printerList.isEmpty()){
        QMessageBox::information(this, "Info", "No Printer Device Found");
        return;
    }
}


void MainWindow::on_actionExit_triggered()
{
    if(this->isTextChanged)
        this->text_changed_msgbox();
    qApp->quit();
}


void MainWindow::text_changed_msgbox()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
          this->on_actionSave_triggered();
          break;
      case QMessageBox::Discard:
          // Don't Save was clicked
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
}


/***************MENU EDIT ACTIONS BEGIN*************/


void MainWindow::on_actionUndo_triggered()
{

}

void MainWindow::on_actionCut_triggered()
{

}

void MainWindow::on_actionCopy_triggered()
{

}

void MainWindow::on_actionPaste_triggered()
{

}

void MainWindow::on_actionDelete_triggered()
{

}

void MainWindow::on_actionFind_triggered()
{

}

void MainWindow::on_actionFind_Next_triggered()
{

}

void MainWindow::on_actionReplace_triggered()
{

}

void MainWindow::on_actionGo_To_triggered()
{

}

void MainWindow::on_actionSelect_All_triggered()
{

}

void MainWindow::on_actionTime_Date_triggered()
{

}



/********MENU FORMAT ACTIONS BEGIN************/
void MainWindow::on_actionWord_Wrap_triggered(bool checked)
{
    settings->setValue("isWordWrap", checked);
    ui->textEdit->setLineWrapMode(checked ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if(!ok)return;
    ui->textEdit->setFont(font);
    settings->setValue("font", font);
}




/**********MENU VIEW ACTIONS BEGIN*************/
void MainWindow::on_actionStatus_Bar_triggered(bool checked)
{
    settings->setValue("isStatusBar", checked);
    this->statusBar()->setVisible(checked);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    if(!ui->actionStatus_Bar->isChecked())return;
    QTextCursor cursor = ui->textEdit->textCursor();
    int y = cursor.blockNumber() + 1;
    int x = cursor.columnNumber() + 1;
    QString xy = "Ln " + QString::number(y) + ", Col " + QString::number(x) + "       ";
//    if(stat==NULL) this->stat = new QLabel(this);
//    stat->setAlignment(Qt::AlignRight);
    this->stat->setText(xy);
//    ui->statusBar->addPermanentWidget(stat);
}


/*********MENU HELP ACTIONS BEGIN**************/

void MainWindow::on_actionView_Help_triggered()
{

}

void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString s ="qt-notepad is absolutely free and open source software, so "
                "you can do everything that you want with qt-notepad and it's "
                "source code, but you can't prevent others use this software "
                "and source code.";
    QMessageBox::about(this, "qt-notepad", s);
}

