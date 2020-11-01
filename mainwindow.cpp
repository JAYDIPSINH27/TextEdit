#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QFont>
#include <QFontDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QDirModel>
#include <QTreeView>
#include <QDir>
#include <QModelIndex>
#include <QStatusBar>
#include <QPoint>
#include <QCursor>
#include <QDebug>
#include <QLabel>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QTextCursor>
#include <QTabWidget>
#include <QTabBar>
#include <QFileInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TextEdit");
    TrayIcon = new QSystemTrayIcon(this);
    TrayIcon->setIcon(QIcon(":/icon/TE.png"));
    TrayIcon->setVisible(true);
    //this->setCentralWidget(ui->textEdit);




    model= new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    ui->treeView->setModel(model);

 connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(showCursorPos()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showCursorPos()
{
    int row=ui->textEdit->textCursor().blockNumber()+1;
   int column=ui->textEdit->textCursor().columnNumber()+1;
   ui->statusbar->showMessage(QString("Line: %1 , column: %2").arg(row).arg(column));

}

void MainWindow::on_actionNew_triggered()
{

    File_Path="";
    ui->textEdit->setText("");
    QString File_Name=QFileDialog::getSaveFileName(this,"Open the File");
    QFile file(File_Name);
    File_Path = File_Name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      QMessageBox::warning(this,"..","First Save your File");
      return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
    QFileInfo fileInfo(File_Name);
    QString filename=fileInfo.fileName();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab { height: 100px; width: 100px; }");
     ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected {color:#f7f1e3;background-color:#2C3A47;font-weight: 450;}");

}

void MainWindow::on_actionOpen_triggered()
{
    QString File_Name=QFileDialog::getOpenFileName(this,"Open the File");
    QFile file(File_Name);
    File_Path = File_Name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
      QMessageBox::warning(this,"..","File is not open");
      return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
    QFileInfo fileInfo(File_Name);
    QString filename=fileInfo.fileName();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab { height: 100px; width: 100px; }");
     ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected {color:#f7f1e3;background-color:#2C3A47;font-weight: 450;}");


}

void MainWindow::on_actionSave_triggered()
{
    if(File_Path==NULL)
    {
        QString File_Name=QFileDialog::getSaveFileName(this,"Open the File");
        QFile file(File_Name);
        File_Path = File_Name;
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
          QMessageBox::warning(this,"..","First Save your File");
          return;
        }
        QTextStream out(&file);
        QString text=ui->textEdit->toPlainText();
        out<<text;
        file.flush();
        file.close();
        QFileInfo fileInfo(File_Name);
        QString filename=fileInfo.fileName();
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
        ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab { height: 100px; width: 100px; }");
         ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected {color:#f7f1e3;background-color:#2C3A47;font-weight: 450;}");
    }
    else
    {
    QFile file(File_Path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      QMessageBox::warning(this,"..","First Save as your file at some location");
      return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString File_Name=QFileDialog::getSaveFileName(this,"Open the File");
    QFile file(File_Name);
    File_Path = File_Name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      QMessageBox::warning(this,"..","First Save your File");
      return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
    QFileInfo fileInfo(File_Name);
    QString filename=fileInfo.fileName();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab { height: 100px; width: 100px; }");
     ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected {color:#f7f1e3;background-color:#2C3A47;font-weight: 450;}");
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
     ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
     ui->textEdit->undo();
}

void MainWindow::on_actionZoom_In_triggered()
{
    ui->textEdit->zoomIn();
}

void MainWindow::on_actionZoom_Out_triggered()
{
    ui->textEdit->zoomOut();

}
void MainWindow::on_actionAbout_TextEdit_triggered()
{
    QString About_Text="TextEditor\n\n";
    About_Text+="Version::0.0.1\n";
    About_Text+="Built Date::07/08/2020\n";
    About_Text+="Qt Creator Version::4.12.4\n";
    About_Text+="OS::Windows 10\n";
    About_Text+="(C) TextEditor (R)\n";
    QMessageBox::about(this,"About TextEdit",About_Text);
}
void MainWindow::on_actionSelect_Font_triggered()
{
    bool fontSelected;
    QFont font=QFontDialog::getFont(&fontSelected,this);
    if(fontSelected)
        ui->textEdit->setFont(font);
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString url=model->fileInfo(index).filePath();
//    QDesktopServices::openUrl(QUrl::fromLocalFile(url));

    QFile file(url);
    File_Path =url;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
      QMessageBox::warning(this,"..","File is not open");
      return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
    QFileInfo fileInfo(url);
    QString filename=fileInfo.fileName();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab { height: 100px; width: 100px; }");
     ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected {color:#f7f1e3;background-color:#2C3A47;font-weight: 450;}");
}




void MainWindow::on_actionItalic_triggered(bool checked)
{
    ui->textEdit->setFontItalic(checked);
}

void MainWindow::on_actionCenter_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_actionLeft_Align_triggered()
{
   ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_actionRight_Align_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_actionJustified_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignJustify);
}



