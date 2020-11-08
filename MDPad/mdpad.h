#ifndef MDPAD_H
#define MDPAD_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QDateTime>
#include <QProcess>
#include "finddialog.h"

namespace Ui {
class MDPad;
}

class MDPad : public QMainWindow
{
    Q_OBJECT

public:
    explicit MDPad(QWidget *parent = nullptr);
    ~MDPad();
    QString find_Text;

private slots:
    void findRequest();
    void on_actionMDPad_Hakkinda_triggered();
    void on_textEdit_textChanged();
    void on_action_Ileri_Al_triggered();
    void on_action_Geri_Al_triggered();
    void on_action_Kes_triggered();
    void on_action_Kopyala_triggered();
    void on_action_Yapistir_triggered();
    void on_actionYazdir_triggered();
    void on_actionYeni_triggered();
    void on_actionAc_triggered();
    void on_actionKaydet_triggered();
    void on_actionYaz_Tipi_triggered();
    void on_action_DurumCubugu_toggled(bool arg1);
    void on_actionFarkli_Kaydet_triggered();
    void on_action_Cikis_triggered();
    void on_action_Bul_triggered();
    void on_action_TumunuSec_triggered();
    void on_actionSaat_Tarih_triggered();
    void on_actionYeni_Pencere_triggered();
    void on_action_YardimGoruntule_triggered();

public slots:
    void statusbar_state(bool durum);

private:
    Ui::MDPad *ui;
    bool durum;
    QFont font;
    QString fileName;
    FindDialog *find;
    QProcess reApp;

};

#endif // MDPAD_H
