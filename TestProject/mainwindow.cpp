#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Difficulty select");
    msgBox.setText("Unavailable in this version");
    msgBox.exec();
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("CheckboxInt");
    msgBox.setText(QString("Checkbox argument is %1").arg(arg1));
    msgBox.exec();
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    ui->pushButton->setVisible(arg1);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString text;
    if(ui->checkBox->checkState() == Qt::CheckState::Checked)
    {
        text = "check box 1 checked";
    }
    else
    {
        text = "check box 1 unchecked";
    }
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    QMessageBox msgBox;
    msgBox.setText(button->text());
    msgBox.exec();
}

