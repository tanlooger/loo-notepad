#ifndef REPLACE_H
#define REPLACE_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT

public:
    explicit Replace(QWidget *parent = 0);
    ~Replace();
    QTextEdit* textEdit;

private slots:
    void on_findButton_clicked();

    void on_replaceButton_clicked();

    void on_replaceAllButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Replace *ui;
};

#endif // REPLACE_H
