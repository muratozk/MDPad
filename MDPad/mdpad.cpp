#include "mdpad.h"
#include "ui_mdpad.h"


MDPad::MDPad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MDPad)
{
    ui->setupUi(this);
    tmpNewFile = "Adsız";
    find = new FindDialog();
    connect(find,SIGNAL(sendFindData()),this,SLOT(findRequest()));

    setCentralWidget(ui->textEdit);

    ui->action_DurumCubugu->setChecked(true);
    ui->action_SozcukKaydir->setChecked(true);
    this->setWindowTitle(tmpNewFile+" - MDPad");

}

MDPad::~MDPad()
{
    delete ui;
}

void MDPad::on_actionMDPad_Hakkinda_triggered()
{
    QMessageBox::about(this,"MDPad v0.2",
                       "MDPad Open Source to Inspire Notepad\n\n"
                       "v0.1 Information\n"
                       "First version created\n"
                       "v.01\n"
                       "Release Date: 01.09.2020\n\n"
                       "v0.2 Information\n\n"
                       "Major and minor bug fixed and new added features\n"
                       "Changed icon, add find features, file read bug fixed etc.\n"
                       "v0.2\n"
                       "Release Date: 08.11.2020\n"
                       "v0.3 Information\n\n"
                       "Minor bug fixed and new added features\n"
                       "Add word wrap on/off, status bar hide/visible, font change it etc.\n"
                       "v0.3\n"
                       "Release Date: 19.12.2020\n\n"
                       "Murat OZKAN");
}

void MDPad::on_textEdit_textChanged()
{
    int say = ui->textEdit->toPlainText().size();
    QTextCursor cursor = ui->textEdit->textCursor();
    int line = cursor.blockNumber()+1;

    if(say<1)
        ui->textEdit->setFont(font);

    if(say<1)
    {
        ui->statusBar->showMessage("");
        return;
    }
    ui->statusBar->showMessage("Line: " + QString::number(line)+ ",Char: " + QString::number(say));
}

void MDPad::on_action_Ileri_Al_triggered()
{
    ui->textEdit->redo();
}

void MDPad::on_action_Geri_Al_triggered()
{
    ui->textEdit->undo();
}

void MDPad::on_action_Kes_triggered()
{
    ui->textEdit->cut();
}

void MDPad::on_action_Kopyala_triggered()
{
    ui->textEdit->copy();
}

void MDPad::on_action_Yapistir_triggered()
{
    ui->textEdit->paste();
}

void MDPad::on_actionYazdir_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}

void MDPad::on_actionYeni_triggered()
{
    ui->textEdit->clear();
}

void MDPad::on_actionAc_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, ("Open Text File"),
                                            "C:/",
                                            ("Text Files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Dosya Açılamadı!","Dosya bulunamadı!");
        return;
    }

    QTextStream in(&file);
    QString text = file.readAll();
    ui->textEdit->setPlainText(text);
    file.close();
}

void MDPad::on_actionKaydet_triggered()
{
    QString data = ui->textEdit->toPlainText();
    QTextStream io;
    QFile file(fileName);
    if(!fileName.isEmpty())
    {
        if(!file.open(QIODevice::WriteOnly | QFile::Text))
        {
            return;
        }
        io.setDevice(&file);
        io << ui->textEdit->toPlainText();
        file.flush();
        file.close();
    }
    else
    {
        on_actionFarkli_Kaydet_triggered();
    }

}

void MDPad::on_actionFarkli_Kaydet_triggered()
{
    QString data = ui->textEdit->toPlainText();
    QString fileName = QFileDialog::getSaveFileName(this, ("Open Text File"),
                                                    "C:/",
                                                    ("Text Files (*.txt)"));

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QFile::Text))
        {
            return;
        }
        QTextStream io;
        io.setDevice(&file);
        io << ui->textEdit->toPlainText();
        file.flush();
        file.close();
    }
}

void MDPad::on_action_Cikis_triggered()
{
    close();
}


void MDPad::on_actionYaz_Tipi_triggered()
{
    //Look it after have a bug(textedit cler after default font)
    bool ok;
    font = QFontDialog::getFont(&ok,QFont("Trebutched MS",14),this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
}
void MDPad::on_action_DurumCubugu_toggled(bool arg1)
{

    if(arg1)
    {
        ui->statusBar->show();
    }
    else
    {
        ui->statusBar->hide();
    }
}


void MDPad::on_action_Bul_triggered()
{
    find->show();
}

void MDPad::findRequest()
{
    find->close();
    QString aranan_text = find->getRequest();
    QString searchString = aranan_text;
    QTextDocument *document = ui->textEdit->document();

    bool found = false;

    document->undo();

    if (searchString.isEmpty()) {
        QMessageBox::information(this, tr("Aranacak bir kelime girin"),
                                 "Boş bilgi var formda \n"
                                 "Lütfen geçerli bir kelime girin");
    } else
    {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::yellow);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull())
            {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();

        if (found == false) {
            QMessageBox::information(this, tr("Sonuç Bulunamadı!"),
                                     tr("Üzgünüm, herhangi bir sonuç bulunamadı!"));
        }
    }


}

void MDPad::on_action_TumunuSec_triggered()
{
    ui->textEdit->selectAll();
}

void MDPad::on_actionSaat_Tarih_triggered()
{
    QDateTime dt;
    QString dtString = dt.currentDateTime().toString("hh:mm dd.MM.yyyy");
    ui->textEdit->appendPlainText(dtString);
}

void MDPad::on_actionYeni_Pencere_triggered()
{
    // Look after have a bug(slow open app)
    QString executeApp = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    QString dir = qApp->applicationDirPath();
    QString app = dir + "/" + executeApp;
    reApp.start(app);

}

void MDPad::on_action_YardimGoruntule_triggered()
{
    QMessageBox::aboutQt(this);
}

void MDPad::on_action_SozcukKaydir_toggled(bool arg1)
{

    if(arg1)
    {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    }
    else
    {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    }

}
