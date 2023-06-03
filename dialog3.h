#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>

namespace Ui {
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = nullptr);
    ~Dialog3();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::Dialog3 *ui;
};

#endif // DIALOG3_H
