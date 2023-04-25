#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QHostInfo>
#include <QLineEdit>
#include <QInputDialog>
#include "thread_element.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ThreadElement *threadElement;
public slots:
    void spinBox(int number);
    void steghide_decrypte(void);
    void steghide_cryptage(void);
    void steghide_write_doc(void);
    void steghide_passphrase(void);
    void steghide_clear(void);

private:
    QProcess *m_process;    ///< Processus de selection d'imprimante
    Ui::MainWindow *ui;

    /*---------------------------------------------------------------*/
    /* Private Members                                               */
    /*---------------------------------------------------------------*/
    QString m_passphrase_user;
    void connectSignalsSlots();


private slots:

};

#endif // MAINWINDOW_H
