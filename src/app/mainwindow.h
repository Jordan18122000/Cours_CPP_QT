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
    void steghide(void);

private:
    QProcess *m_process;    ///< Processus de selection d'imprimante
    Ui::MainWindow *ui;
    void connectSignalsSlots();

private slots:

};

#endif // MAINWINDOW_H
