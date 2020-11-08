#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>


namespace Ui
{
    class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
    QString getRequest();

signals:
    void sendFindData();
private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
