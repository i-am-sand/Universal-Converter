#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <exception>

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

void MainWindow::on_convertButton_clicked() {
  ui->outputEdit->clear();
  ui->errorLabel->clear();
  try {
      bool ok1 = false;
      bool ok2 = false;
      int from_base = ui->fromBaseEdit->text().toInt(&ok1);
      int to_base = ui->toBaseEdit->text().toInt(&ok2);
      if (!ok1 || from_base < 2 || from_base > 500) {
          throw std::runtime_error("Ошибка: основание исходной системы должно быть от 2 до 500");
        }
      if (!ok2 || to_base < 2 || to_base > 500) {
          throw std::runtime_error("Ошибка: основание целевой системы должно быть от 2 до 500");
        }
      std::string input = ui->inputEdit->text().toStdString();
      std::string result = converter_.convert(input, from_base, to_base);
      ui->outputEdit->setPlainText(QString::fromStdString(result));
    } catch (const std::exception& error) {
      ui->errorLabel->setText(QString::fromStdString(error.what()));
    }
};

void MainWindow::on_loadButton_clicked() {
  ui->errorLabel->clear();

  QString file_name = QFileDialog::getOpenFileName(
      this,
      "Open input file",
      "",
      "Text files (*.txt);;All files (*)"
      );

  if (file_name.isEmpty()) {
      return;
    }

  QFile file(file_name);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      ui->errorLabel->setText("Ошибка: не удалось открыть файл");
      return;
    }

  QTextStream in(&file);

  QString from_base = in.readLine();
  QString to_base = in.readLine();
  QString input = in.readLine();

  ui->fromBaseEdit->setText(from_base);
  ui->toBaseEdit->setText(to_base);
  ui->inputEdit->setText(input);
}

void MainWindow::on_saveButton_clicked() {
  ui->errorLabel->clear();

  QString file_name = QFileDialog::getSaveFileName(
      this,
      "Save result",
      "",
      "Text files (*.txt);;All files (*)"
      );

  if (file_name.isEmpty()) {
      return;
    }

  QFile file(file_name);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      ui->errorLabel->setText("Ошибка: не удалось сохранить файл");
      return;
    }

  QTextStream out(&file);
  out << ui->outputEdit->toPlainText();
}