#include <QApplication>
#include <QDialog>
#include <QToolButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStyle>
#include <QList>

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

  QDialog *dialog = new QDialog();

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setSpacing(0);

  QList<QPair<QString, QString>> data = {
    {"Screen",    "/home/simpe/QtProjects/recorder/screen.png"},
    {"Window",    "/home/simpe/QtProjects/recorder/window.png"},
    {"Selection", "/home/simpe/QtProjects/recorder/selection.png"}
  };

  QList<QToolButton*> buttons;

  int i = 1;
  for (QPair<QString, QString> entry : data) {
    QToolButton *button = new QToolButton();
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->setText(entry.first);
    button->setIconSize(QSize(32, 32));
    button->setIcon(QIcon(entry.second));

    button->setMaximumSize(QSize(100, 100));
    button->setMinimumSize(QSize(100, 100));
    button->setFocusPolicy(Qt::NoFocus);

    button->setProperty("cssClass", QString("Button%0").arg(i++));
    button->setCursor(Qt::PointingHandCursor);

    buttons.append(button);
  }

  for (QToolButton *button : buttons) {
    QObject::connect(button, &QToolButton::clicked, [=](){
      const QString cssClass = button->property("cssClass").toString();
      for (QToolButton *b : buttons) {
        const QString cssStyle = b->property("cssClass").toString();
        if (cssStyle == cssClass) {
          b->setProperty("cssClass", QString("%0_Selected").arg(cssStyle));
        } else {
          b->setProperty("cssClass", cssStyle.split("_").first());
        }

        dialog->style()->unpolish(b);
        dialog->style()->polish(b);
      }

      dialog->update();
    });
  }

  layout->addStretch(1);
  for (QToolButton *button : buttons) {
    layout->addWidget(button);
  }
  layout->addStretch(1);

  dialog->setLayout(layout);

  dialog->resize(400, 300);
  dialog->show();

  a.exec();

  return 0;
}
