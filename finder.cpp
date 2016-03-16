#include "finder.h"
#include "ui_finder.h"
#include "mainwindow.h"
#include <QTextDocument>
#include <QMessageBox>
#include <QDebug>

Finder::Finder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finder)
{
    ui->setupUi(this);
}

Finder::~Finder()
{
    delete ui;
}

void Finder::on_lineEdit_textChanged(const QString &arg1)
{
    ui->buttonFinder->setDisabled(arg1.isEmpty());
}

void Finder::on_buttonFinder_clicked()
{
    bool ok;

    QTextDocument::FindFlags flags;

    if(ui->checkBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if(ui->radioUp->isChecked())
        flags |= QTextDocument::FindBackward;

    ok = this->textEdit->find(ui->lineEdit->text(), flags);

    if(!ok)QMessageBox::information(this, "Info", "Can't find \""+ui->lineEdit->text()+"\"");
}


void Finder::on_ButtonCancel_clicked()
{
    this->done(0);
}


