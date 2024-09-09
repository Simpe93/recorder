#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStyle>

#include "mydialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setApplicationName("Recording");

  QFile stylesheet("/home/simpe/QtProjects/recorder/style.qss");
  if (stylesheet.open(QIODevice::ReadOnly | QFile::Text)) {
    QTextStream in(&stylesheet);
    const QString data = in.readAll();
    a.setStyleSheet(data);
    stylesheet.close();
  }

  MyDialog *dialog = new MyDialog();

  dialog->show();
  a.exec();

  return 0;
}
