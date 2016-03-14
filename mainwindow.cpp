#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QPrinterInfo>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if(!this->isTextChanged){
        if(this->file){
            this->file->flush();
            this->file->close();
        }
        this->file = new QFile("file.txt");
    }
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
          // Save was clicked
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

void MainWindow::on_actionOpen_triggered()
{
    if(this->file && this->isTextChanged){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
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
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
    if(filename.isEmpty())return;
    //this->openfile->open(filename)

    this->file = new QFile(filename, this);
    if (!this->file->open(QIODevice::ReadWrite | QIODevice::Text))return;

    QTextStream stream(this->file);
    ui->textEdit->clear();
    ui->textEdit->setText(stream.readAll());
}

void MainWindow::on_actionSave_triggered()
{
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
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
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
    }else{
        event->accept();
    }

}

void MainWindow::on_actionSave_As_triggered()
{

}

void MainWindow::on_actionPate_Setup_triggered()
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
    if(!this->isTextChanged) qApp->quit();
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
          // Save was clicked
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




