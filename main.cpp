#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStyle>

#include "mydialog.h"
#include "windowlist.h"

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

  WindowList *list = new WindowList();
  MyDialog *dialog = new MyDialog(list->getImages());

  dialog->show();
  a.exec();

  return 0;
}
