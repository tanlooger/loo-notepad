#include "replace.h"
#include "ui_replace.h"
#include <QTextDocument>
#include <QMessageBox>

Replace::Replace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Replace)
{
    ui->setupUi(this);
}

Replace::~Replace()
{
    delete ui;
}

void Replace::on_findButton_clicked()
{
    bool ok;
    if(ui->checkBox->isChecked())
        ok = this->textEdit->find(ui->lineEditFind->text(), QTextDocument::FindCaseSensitively);
    else
        ok = this->textEdit->find(ui->lineEditFind->text(), 0);
    if(!ok)QMessageBox::information(this, "Info", "Can't find \""+ui->lineEditFind->text()+"\"");
}

void Replace::on_replaceButton_clicked()
{
    if(this->textEdit->find(ui->lineEditFind->text())){
        this->textEdit->textCursor().insertText(ui->lineEditReplace->text());
    }
}

void Replace::on_replaceAllButton_clicked()
{
    QTextDocument::FindFlags flags;
    if(ui->checkBox->isChecked())flags |= QTextDocument::FindCaseSensitively;
    this->textEdit->moveCursor(QTextCursor::Start);
    while(1){
        if(this->textEdit->find(ui->lineEditFind->text(), flags)){
            this->textEdit->textCursor().insertText(ui->lineEditReplace->text());
        }else{
            QMessageBox::information(this, "Info", "All character replaced");
            break;
        }
    }
}

void Replace::on_cancelButton_clicked()
{
    this->done(0);
}
