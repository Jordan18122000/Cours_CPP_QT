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
    // Demander l'image à l'utilisateur
    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
    if (imagePath.isEmpty()) {
        return;
    }

    // Demander la passphrase à l'utilisateur
    QString passphrase = QInputDialog::getText(nullptr, "Passphrase", "Entrer la passphrase pour extraire le fichier", QLineEdit::Password);
    if (passphrase.isEmpty()) {
        return;
    }

    // Chemin absolu vers le dossier où nous pouvons créer le fichier shell
    QString shellFolder = QDir::currentPath().remove("/bin/release");
    qDebug() << "Chemin absolu du dossier du projet :" << shellFolder;

    // Vérifier si le dossier existe, sinon le créer
    QDir dir(shellFolder);
    if (!dir.exists()) {
        qDebug() << "Impossible de trouver le dossier";
        return;
    }
    // Chemin absolu vers le fichier shell
    QString shellFilePath = shellFolder + "/extract.sh";
    qDebug() <<"shellFilePath" << shellFilePath;
    QFile shellFile(shellFilePath);
    if (!shellFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Impossible de créer le fichier shell";
        return;
    }

    QTextStream stream(&shellFile);
    stream << "#!/bin/bash\n";
    stream << "chmod +x " << shellFilePath << "\n"; // Modifier les permissions pour exécuter le fichier
    stream << "steghide extract -sf " << imagePath << " -f -p " << passphrase << " -q\n";
    shellFile.close();


    if (!shellFile.exists())
    {
        qDebug() << "Fichier shell non trouvé : " << shellFilePath;
        return;
    }

    // Exécution du fichier shell
    QProcess process;
    process.setWorkingDirectory(shellFolder); // Spécifie le répertoire de travail pour le processus
    process.start("/bin/bash", QStringList() << shellFilePath);

    qDebug() << "Chemin absolu du fichier shell :" << shellFilePath;
    if (!process.waitForStarted())
    {
        qDebug() << "Impossible de démarrer la commande";
        return;
    }
    if (!process.waitForFinished()) {
        qDebug() << "Erreur: impossible de terminer le processus";
        return;
    }
    process.waitForFinished();
    qDebug() << "Commande terminée avec le code de sortie" << process.exitCode();

    // Récupération de la sortie standard et d'erreur
    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QString errorOutput = QString::fromUtf8(process.readAllStandardError());
    qDebug() << "errorOutput :" << errorOutput;
    qDebug() << "output :" << output;

    // Lecture du fichier mot_de_passe.txt
    QString passwordFilePath = shellFolder + "/mot_de_passe.txt";
    QFile passwordFile(passwordFilePath);
    // Vérification de l'existence du fichier
    if (!QFile::exists("mot_de_passe.txt"))
    {
        qDebug() << "Erreur lors de l'extraction : " << errorOutput;
        return;
    }
    if (!passwordFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier mot_de_passe.txt";
        return;
    }
    QTextStream passwordStream(&passwordFile);
    QString password = passwordStream.readLine();
    passwordFile.close();

    qDebug() << "Mot de passe : " << password;
    ui->plainTextEdit->setPlainText(password);


    // Suppression du fichier shell
    if (QFile::exists(shellFilePath))
    {
        if (!QFile::remove(shellFilePath))
        {
            qDebug() << "Erreur lors de la suppression du fichier shell";
        }
    }

    // Suppression du fichier mot_de_passe.txt
    if (QFile::exists(passwordFilePath))
    {
        if (!QFile::remove(passwordFilePath))
        {
            qDebug() << "Erreur lors de la suppression du fichier mot_de_passe.txt";
        }
    }
}



