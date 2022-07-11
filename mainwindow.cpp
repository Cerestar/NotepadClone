#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(mWindowTitle);
    this->setCentralWidget(ui->base_PlainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->base_PlainTextEdit->setPlainText(QString());
}

void MainWindow::setFilenameAsWindowTitle(QString filename) {
    QFileInfo fileInfo(filename);
    setWindowTitle(fileInfo.fileName() + " - " + mWindowTitle);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(filename);

    if(filename.isEmpty() && filename.isNull()) return;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    currentFile = filename;
    setFilenameAsWindowTitle(filename);

    //get file content
    QTextStream in(&file);
    QString text = in.readAll();
    ui->base_PlainTextEdit->setPlainText(text);

    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(currentFile);

    if(currentFile.isEmpty() && currentFile.isNull()) {
        on_actionSave_as_triggered();
        return;
    }

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    //save file
    QTextStream out(&file);
    QString text = ui->base_PlainTextEdit->toPlainText();
    out << text;

    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as...");
    QFile file(filename);

    if(filename.isEmpty() && filename.isNull()) return;

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFile = filename;
    setFilenameAsWindowTitle(filename);

    //save file
    QTextStream out(&file);
    QString text = ui->base_PlainTextEdit->toPlainText();
    out << text;

    file.close();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->base_PlainTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->base_PlainTextEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->base_PlainTextEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->base_PlainTextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->base_PlainTextEdit->redo();
}




