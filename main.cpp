#include <QApplication>
#include <QDialog>
#include <QToolButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStyle>
#include <QList>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

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

  dialog->setAttribute(Qt::WA_TranslucentBackground);
  dialog->setWindowFlags(Qt::FramelessWindowHint);

  QGroupBox *wrapper = new QGroupBox();
  wrapper->setProperty("cssClass", "Wrapper");

  QVBoxLayout *wrapperLayout = new QVBoxLayout(wrapper);
  wrapperLayout->setContentsMargins(0, 15, 15, 15);
  wrapperLayout->setSpacing(15);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  QList<QPair<QString, QString>> data = {
    {"Screen",    "/home/simpe/QtProjects/recorder/screen.png"},
    {"Window",    "/home/simpe/QtProjects/recorder/window.png"},
    {"Selection", "/home/simpe/QtProjects/recorder/selection.png"}
  };

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->setContentsMargins(0, 0, 0, 0);
  buttonLayout->setSpacing(0);

  buttonLayout->addStretch(1);

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
    buttonLayout->addWidget(button);
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

  buttonLayout->addStretch(1);
  wrapperLayout->addLayout(buttonLayout);

  QVBoxLayout *groupLayout = new QVBoxLayout();
  groupLayout->setContentsMargins(0, 0, 0, 0);
  groupLayout->setSpacing(0);

  QGroupBox *gb1 = new QGroupBox();
  QGroupBox *gb2 = new QGroupBox();
  QGroupBox *gb3 = new QGroupBox();

  gb1->setMaximumSize(QSize(300, 60));
  gb1->setMinimumSize(QSize(300, 60));

  gb2->setMaximumSize(QSize(300, 60));
  gb2->setMinimumSize(QSize(300, 60));

  gb3->setMaximumSize(QSize(300, 60));
  gb3->setMinimumSize(QSize(300, 60));

  gb1->setProperty("cssClass", "Group1");
  gb2->setProperty("cssClass", "Group2");
  gb3->setProperty("cssClass", "Group3");

  QHBoxLayout *gb1Layout = new QHBoxLayout(gb1);
  gb1Layout->setContentsMargins(0, 0, 15, 0);
  gb1Layout->setSpacing(0);

  gb1Layout->addWidget(new QLabel("Audio"));
  gb1Layout->addStretch(1);
  gb1Layout->addWidget(new QCheckBox());

  QHBoxLayout *gb2Layout = new QHBoxLayout(gb2);
  gb2Layout->setContentsMargins(0, 0, 15, 0);
  gb2Layout->setSpacing(0);

  gb2Layout->addWidget(new QLabel("Bitrate"));
  gb2Layout->addStretch(1);
  QComboBox *cb = new QComboBox();
  cb->addItem("12 000");
  cb->addItem("8 000");
  cb->addItem("6 000");
  cb->addItem("2 000");
  cb->addItem("1 000");

  gb2Layout->addWidget(cb);

  QHBoxLayout *gb3Layout = new QHBoxLayout(gb3);
  gb3Layout->setContentsMargins(0, 0, 15, 0);
  gb3Layout->setSpacing(0);

  gb3Layout->addWidget(new QLabel("Output"));
  gb3Layout->addStretch(1);
  gb3Layout->addWidget(new QPushButton("..."));

  groupLayout->addWidget(gb1, 0, Qt::AlignCenter);
  groupLayout->addWidget(gb2, 0, Qt::AlignCenter);
  groupLayout->addWidget(gb3, 0, Qt::AlignCenter);
  groupLayout->addStretch(1);

  wrapperLayout->addLayout(groupLayout);

  // Record
  QVBoxLayout *recordLayout = new QVBoxLayout();
  recordLayout->setContentsMargins(0, 0, 0, 0);
  recordLayout->setSpacing(0);

  QGroupBox *recordGroup = new QGroupBox();
  recordGroup->setMaximumSize(QSize(300, 60));
  recordGroup->setMinimumSize(QSize(300, 60));
  recordGroup->setProperty("cssClass", "RecordGroup");

  QHBoxLayout *recordGroupLayout = new QHBoxLayout(recordGroup);
  recordGroupLayout->setContentsMargins(0, 0, 15, 0);
  recordGroupLayout->setSpacing(0);

  QPushButton *recordButton = new QPushButton();
  recordButton->setProperty("cssClass", "RecordButton");
  recordButton->setMaximumSize(QSize(30, 30));
  recordButton->setMinimumSize(QSize(30, 30));
  recordButton->setIcon(QIcon("/home/simpe/QtProjects/recorder/record.png"));
  recordButton->setIconSize(QSize(25, 25));

  recordGroupLayout->addWidget(recordButton);
  recordGroupLayout->addStretch(1);
  recordGroupLayout->addWidget(new QLabel("00:13:37"));

  recordLayout->addWidget(recordGroup, 0, Qt::AlignCenter);

  wrapperLayout->addLayout(recordLayout);

  layout->addWidget(wrapper);
  dialog->setLayout(layout);

  dialog->show();
  a.exec();

  return 0;
}
