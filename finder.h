#ifndef FINDER_H
#define FINDER_H

#include <QDialog>
#include <QTextEdit>
#include <QFocusEvent>

namespace Ui {
class Finder;
}

class Finder : public QDialog
{
    Q_OBJECT

public:
    explicit Finder(QWidget *parent = 0);
    ~Finder();
    QTextEdit* textEdit;


public slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_buttonFinder_clicked();

    void on_ButtonCancel_clicked();

private:
    Ui::Finder *ui;
};

#endif // FINDER_H
