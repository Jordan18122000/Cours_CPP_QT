#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadElement = new ThreadElement(this);

    m_process = new QProcess(this);

    connectSignalsSlots();     //on connecte les signaux/slots
}

MainWindow::~MainWindow()
{
    m_process->kill();
    delete m_process;
    delete ui;
}


void MainWindow::connectSignalsSlots()
{
    //QObject::connect(m_process, SIGNAL(channelReadyRead(int)), this, SLOT(readProcessOutput(int)));
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::spinBox);
    connect(threadElement, &ThreadElement::my_signal, this, &MainWindow::spinBox);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::steghide);
}

void MainWindow::spinBox(int number)
{
    ui->label->setText("coucou caca " + QString::number(number));
}

void MainWindow::steghide()
{
    // Ouvrir une boîte de dialogue pour sélectionner l'image
    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
    QString password = "1234";

    QProcess steghideProcess;
    steghideProcess.start("steghide", QStringList() << "extract" << "-sf" << imagePath);
    steghideProcess.waitForFinished(-1);

    if (!steghideProcess.waitForStarted()) {
        qDebug() << "Error: failed to start steghide process";
        return;
    }
    if (!steghideProcess.waitForFinished(-1)) {
        qDebug() << "Error: failed to finish steghide process";
        return;
    }
    if (steghideProcess.exitCode() != 0) {
        qDebug() << "Error: steghide process exited with error code" << steghideProcess.exitCode();
        qDebug() << "Error message:" << steghideProcess.readAllStandardError();
        return;
    }
    QString steghideOutput = steghideProcess.readAllStandardOutput();
    qDebug() << "Steghide output:" << steghideOutput;

    //steghideProcess.start("steghide extract -sf " + imagePath + " -p " + "JordanCLEMENT");
    //steghideProcess.waitForFinished(-1);

    // Lire la sortie de steghide (le mot caché) et l'afficher dans le navigateur de texte
    //QString steghideOutput = steghideProcess.readAllStandardOutput();
    ui->plainTextEdit->setPlainText(steghideOutput);
    qDebug() << steghideOutput;
}



