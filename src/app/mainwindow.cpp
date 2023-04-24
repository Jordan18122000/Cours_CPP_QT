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
   /* QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
    QString output;
    // Demander la passphrase à l'utilisateur
    qDebug() << "Entrer la passphrase pour extraire le fichier : ";
    QString passphrase = QInputDialog::getText(NULL, "Passphrase", "Entrer la passphrase pour extraire le fichier", QLineEdit::Password);
    qDebug() << "passphrase" << passphrase;

    QProcess steghideProcess;
    QStringList arguments;
    arguments << "extract" << "-sf" << imagePath << "-p" << passphrase;
    steghideProcess.start("steghide", arguments);

    //arguments << "-c" << QString("steghide extract -sf %1").arg(imagePath);
    //steghideProcess.start("/bin/bash", arguments);
    //steghideProcess.waitForFinished(-1);
    // Écrire la confirmation "o" dans l'entrée standard de Steghide
    if (steghideProcess.waitForStarted()) {
        steghideProcess.write("o");
        steghideProcess.closeWriteChannel();
        steghideProcess.waitForFinished();
        output = steghideProcess.readAllStandardOutput();
        qDebug() << "output";
        qDebug() << output;
    } else {
        qDebug() << "Erreur : impossible de démarrer le processus Steghide";
    }

    qDebug() << "path" << imagePath;
    qDebug() << "arguments" << arguments;
    //steghideProcess.start("steghide", QStringList() << "extract" << "-sf" << imagePath);
    //steghideProcess.waitForFinished(-1);

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
    qDebug() << output;*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
    // Ouvrir une boîte de dialogue pour sélectionner l'image
     /*   QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
        if (imagePath.isEmpty()) {
            return;
        }

        // Demander la passphrase à l'utilisateur
        QString passphrase = QInputDialog::getText(nullptr, "Passphrase", "Entrer la passphrase pour extraire le fichier", QLineEdit::Password);
        if (passphrase.isEmpty()) {
            return;
        }

        // Lancer la commande Steghide avec la passphrase et l'image sélectionnées
        QStringList arguments;
        //arguments << "extract" << "-sf" << imagePath << "-p" << passphrase << "-f";
        //arguments << "extract" << "-sf" << "/home/jordan/Documents/Github/Cours_CPP_QT/Image.jpg" << "-p" << passphrase << "-f";
        //arguments << "extract" << "-sf" << "/home/jordan/Documents/Github/Cours_CPP_QT/Image.jpg" << "-f";
        //arguments << "extract" << "-sf" << imagePath << "-p" << passphrase << "-f" << "-q";
        arguments << "extract" << "-sf" << imagePath << "-f" << "-p" << passphrase << "-q";

        QString command = "steghide " + arguments.join(" ");
        qDebug() << "command :" << command;
        QProcess steghideProcess;
        steghideProcess.start("steghide", arguments);

        // Écrire la confirmation "o" dans l'entrée standard de Steghide
        //steghideProcess.write("1234"); // Le "\n" est ajouté pour simuler la touche Entrée

        // Attendre que Steghide demande la passphrase
        //steghideProcess.waitForReadyRead();

        // Ajouter la ligne suivante pour entrer la passphrase
        //steghideProcess.write(passphrase.toLocal8Bit() + '\n');

        // Attendre que Steghide ait terminé
        steghideProcess.waitForFinished(-1);

        // Lire la sortie de Steghide
        QString steghideOutput = QString::fromLocal8Bit(steghideProcess.readAllStandardOutput());

        // Vérifier si Steghide s'est terminé avec succès
        if (steghideProcess.exitCode() == 0) {
            // Extraire le nom de fichier à partir de la sortie de Steghide
            QRegularExpression re("extracted: (.+)$");
            QRegularExpressionMatch match = re.match(steghideOutput);
            QString extractedFilename;
            if (match.hasMatch()) {
                extractedFilename = match.captured(1);
            }

            // Afficher le nom du fichier extrait et son contenu
            if (!extractedFilename.isEmpty()) {
                QFile extractedFile(extractedFilename);
                if (extractedFile.open(QIODevice::ReadOnly)) {
                    QByteArray fileContent = extractedFile.readAll();
                    ui->plainTextEdit->setPlainText(QString::fromUtf8(fileContent));
                    extractedFile.close();
                }
                ui->statusBar->showMessage(QString("Fichier extrait : %1").arg(extractedFilename));
            } else {
                ui->plainTextEdit->setPlainText("Aucun fichier n'a été extrait.");
            }
        } else {

            qDebug() << "Erreur : Steghide a terminé avec un code de sortie non nul" << steghideProcess.exitCode();
            qDebug() << "Erreur message :" << steghideProcess.readAllStandardError();

            ui->plainTextEdit->setPlainText(QString("Erreur : %1").arg(steghideOutput));
            qDebug() << "Sortie Steghide :" << steghideOutput;
            ui->statusBar->showMessage("Extraction de fichier impossible.", 5000);
        }*/

    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.bmp)");
    if (imagePath.isEmpty()) {
        return;
    }

    // Demander la passphrase à l'utilisateur
    QString passphrase = QInputDialog::getText(nullptr, "Passphrase", "Entrer la passphrase pour extraire le fichier", QLineEdit::Password);
    if (passphrase.isEmpty()) {
        return;
    }

    // Trouver le chemin du dossier Cours_CPP_QT
    /*QProcess findProcess;
    findProcess.start("find / -name Cours_CPP_QT -type d 2>/dev/null");
    findProcess.waitForFinished();
    QString qtFolder = QString::fromLocal8Bit(findProcess.readAllStandardOutput().trimmed());*/

    // Demander à l'utilisateur de sélectionner le dossier où le fichier shell doit être créé
    /*QString dirPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un dossier", "", QFileDialog::ShowDirsOnly);
    if (dirPath.isEmpty()) {
        return;
    }*/

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
    process.start("bash", QStringList() << shellFilePath);

    if (!process.waitForStarted())
    {
        qDebug() << "Impossible de démarrer la commande";
        return;
    }
    process.waitForFinished();
    qDebug() << "Commande terminée avec le code de sortie" << process.exitCode();

    // Suppression du fichier shell temporaire
    // QFile::remove(shellFilePath);

    // Récupération de la sortie standard et d'erreur
    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QString errorOutput = QString::fromUtf8(process.readAllStandardError());
    qDebug() << "errorOutput :" << errorOutput;
    qDebug() << "output :" << output;

    // Vérification de l'existence du fichier
    if (!QFile::exists("extract.txt"))
    {
        qDebug() << "Erreur lors de l'extraction : " << errorOutput;
        return;
    }
    if (output.startsWith("Extraction réussie "))
    {
        QString extractedText = output.mid(20); // remove "Extraction réussie "
        qDebug() << "Le texte extrait est :" << extractedText;
        // Chemin absolu vers le fichier d'extraction
        QString extractFilePath = shellFolder + "/extract.txt";
        QFile extractFile(extractFilePath);

        // Vérifier si le fichier a bien été créé
        if (!extractFile.exists()) {
            qDebug() << "Erreur lors de la création du fichier extract.txt";
            return;
        }

        if (extractFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&extractFile);
            stream << extractedText;
            extractFile.close();
            QMessageBox::information(this, tr("Extraction réussie"), tr("Le texte a été extrait et enregistré dans le fichier extract.txt."));
        }
        else
        {
            QMessageBox::critical(this, tr("Erreur d'écriture"), tr("Impossible d'enregistrer le texte extrait dans le fichier extract.txt."));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Extraction impossible"), errorOutput);
        qDebug() << "Erreur lors de l'extraction :" << errorOutput;
    }



/*
    if (output.startsWith("Extraction réussie "))
    {
        QString extractedText = output.mid(20); // remove "Extraction réussie "
        QFile file("extract.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << extractedText;
            file.close();
            QMessageBox::information(this, tr("Extraction réussie"), tr("Le texte a été extrait et enregistré dans le fichier extract.txt."));
        }
        else
        {
            QMessageBox::critical(this, tr("Erreur d'écriture"), tr("Impossible d'enregistrer le texte extrait dans le fichier extract.txt."));
        }
    }
    else
    {
        //QMessageBox::warning(this, tr("Extraction impossible"), output);
         QMessageBox::warning(this, tr("Extraction impossible"), errorOutput);
         qDebug() << "errorOutput :" << errorOutput;
         qDebug() << "output :" << output;
    }*/




}



