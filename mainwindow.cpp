#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("tenA"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("11ii+2.1jj+3kk"));
    ui->tableWidget->insertRow(1);
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("tenB"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("2.1ii + 47ij +3kj"));
    ui->tableWidget->insertRow(2);
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("tenC"));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("4kk"));
    ui->textEdit_3->append("(tenA xx tenB + tenC)**tenA");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    int i =ui->tableWidget->rowCount();
    try
    {
        ui->tableWidget->insertRow(i);
    }
    catch (const char* msg)
    {
        QMessageBox box;
            box.setWindowTitle("Error!");
            box.setText(msg);
            box.exec();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    try
    {
        ui->listWidget_2->clear();
        for(int i=0; i < ui->tableWidget->rowCount();i++)
        {
            Tenzor *T1 = new Tenzor;
            T1->createTenzor(ui->tableWidget->item(i,1)->text());
            e.createTenzorMap(ui->tableWidget->item(i,0)->text(), T1);
        }
        QString eq = ui->textEdit_3->toPlainText();
        e.createEquation(eq);
        e.solveEquation();
        ui->listWidget_2->addItem("Tensor form:" + e.printResult());
        QString *matrix = e.printResultMatrixForm();
        ui->listWidget_2->addItem("Matrix form:");
        for(int i=0; i< 3; i++)
            ui->listWidget_2->addItem(matrix[i]);
    }
    catch (const char* msg)
    {
        QMessageBox box;
            box.setWindowTitle("Error");
            box.setText(msg);
            box.exec();
    }
    e.clearEquation();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget->clear();
}

void MainWindow::on_actionWhat_i_can_do_2_triggered()
{
    QMessageBox box;
        box.setWindowTitle("About");
        box.setText("1. Possible operations: \n"
                    "   Scalar multiplication * \n"
                    "   Tensor multiplication x \n"
                    "   Double scalar multiplaication ** \n"
                    "   Double tensor multiplication xx \n"
                    "   Multiplications *x and x* \n"
                    "   Addition + \n"
                    "   Substraction - \n"
                    "2. Use operation with brackets ");
        box.exec();
}
