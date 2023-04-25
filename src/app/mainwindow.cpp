#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadElement = new ThreadElement(this);

    m_process = new QProcess(this);
    attrInit();
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
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::steghide_decrypte);
    connect(ui->pushButton_cryptage, &QPushButton::clicked, this, &MainWindow::steghide_cryptage);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::steghide_clear);
    connect(ui->pushButton_passphrase, &QPushButton::clicked, this, &MainWindow::steghide_passphrase);
    connect(ui->pushButton_write_document, &QPushButton::clicked, this, &MainWindow::steghide_write_doc);
}

void MainWindow::spinBox(int number)
{
    ui->label->setText("Time :" + QString::number(number));
}

void MainWindow::steghide_decrypte()
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

void MainWindow::steghide_cryptage()
{
    if(m_send_txt_user == "" || m_send_txt_user=="NODE")
    {
        QMessageBox::information(nullptr, "Info Cryptage", "Aucun texte n'a pas été envoyé" "\n" "Veuillez écrire du texte et cliquer sur :" "\n" " \"Ecrire le message à cacher dans le document \" ");
    }
    else
    {
        // Demander le chemin de l'image à l'utilisateur
        QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
        if (imagePath.isEmpty()) {
            return;
        }

        // Demander la passphrase à l'utilisateur
        QString passphrase = QInputDialog::getText(nullptr, "Passphrase", "Entrer la passphrase pour crypter le fichier", QLineEdit::Password);
        if (passphrase.isEmpty()) {
            return;
        }

        m_passphrase_user = passphrase;
        qDebug() << "passphrase" << m_passphrase_user;

        // Demander le chemin du fichier à cacher
        /* QString filePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner le fichier à cacher", "", "Tous les fichiers (*)");
    if (filePath.isEmpty()) {
        return;
    }*/

        QString filePath = QDir::currentPath().remove("/bin/release") + "/documents/mot_de_passe.txt";
        qDebug() << "testing :" << filePath;

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
        QString shellFilePath = shellFolder + "/embed.sh";
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
        stream << "steghide embed -cf " << imagePath << " -ef " << filePath << " -p " << passphrase << " -q\n";
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

        // Suppression du fichier shell
        if (QFile::exists(shellFilePath))
        {
            if (!QFile::remove(shellFilePath))
            {
                qDebug() << "Erreur lors de la suppression du fichier shell";
            }
        }

        // Affichage d'un message de réussite
        QMessageBox::information(nullptr, "Cryptage terminé", "L'image a été cryptée avec succès.");
    }
}

void MainWindow::steghide_write_doc()
{
    QString filePath = QDir::currentPath().remove("/bin/release") + "/documents/mot_de_passe.txt";

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << ui->plainTextEdit_cryptage->toPlainText();
        file.close();

        // Affichage d'un message de confirmation
        QMessageBox::information(nullptr, "Sauvegarde réussie", "Le fichier a été enregistré avec succès.");
        m_send_txt_user="User_send_data";
    }
    else
    {
        // Affichage d'un message d'erreur
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ouvrir le fichier en écriture.");
        m_send_txt_user="NODE";
    }
}

void MainWindow::steghide_passphrase()
{
    if(m_passphrase_user == "")
    {
        QMessageBox::information(nullptr, "Info PassPhrase", "La PassPhrase n'a pas été définie" "\n" "Veuillez crypter une image");
    }
    else
    {
        QMessageBox::information(nullptr, "Info PassPhrase", "La PassPhrase entrée est :" + m_passphrase_user);
    }
}

void MainWindow::steghide_clear()
{
    ui->plainTextEdit->setPlainText("NONE");
}

void MainWindow::attrInit()
{
    // Vérifie si steghide est installé en essayant de lancer la commande "steghide"
    QProcess process;
    process.start("steghide --version");
    process.waitForFinished();
    if (process.exitCode() != QProcess::NormalExit || process.exitStatus() != QProcess::NormalExit) {
        // Si la commande échoue, affiche un message d'erreur et quitte l'application
        QMessageBox::critical(nullptr, "Erreur", "Steghide n'est pas installé sur votre système. Veuillez l'installer avant d'utiliser cette application.");
        exit(EXIT_FAILURE);
    }
}



