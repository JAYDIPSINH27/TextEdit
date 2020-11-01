#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QtCore>
#include <QMainWindow>
#include <QDirModel>
#include <QFileSystemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSystemTrayIcon;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionAbout_TextEdit_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionSelect_Font_triggered();

    void showCursorPos();

    void on_treeView_doubleClicked(const QModelIndex &index);



    void on_actionItalic_triggered(bool checked);

    void on_actionCenter_triggered();

    void on_actionLeft_Align_triggered();

    void on_actionRight_Align_triggered();

    void on_actionJustified_triggered();


private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *TrayIcon;
    QString File_Path;
    QDirModel *model;
    QFileSystemModel *dirmodel;


};



#endif // MAINWINDOW_H
