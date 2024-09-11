#include "mydialog.h"

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
#include <QFrame>
#include <QMouseEvent>
#include <QRubberBand>
#include <QRect>

MyDialog::MyDialog(QList<QImage> images, QWidget* parent) : QDialog(parent), m_images(images), m_selectionEnabled(false), m_rubberBand(nullptr) {
  // setAttribute(Qt::WA_TranslucentBackground);
  // setWindowFlags(Qt::FramelessWindowHint);

  setupUi();
}

void MyDialog::setupUi() {
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

  for (QImage img : m_images) {
    QPixmap p = QPixmap::fromImage(img);
    QPushButton * b = new QPushButton("Test");
    b->setIcon(QIcon(p));
    layout->addWidget(b);
  }

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
          if (cssStyle.startsWith("Button3")) {
            m_selectionEnabled = true;
          } else {
            m_selectionEnabled = false;
          }

          if (cssStyle.startsWith("Button1")) {
            QDialog * dia = new QDialog();
            dia->setAttribute(Qt::WA_TranslucentBackground);
            dia->setWindowFlags(Qt::FramelessWindowHint);

            QFrame * frame = new QFrame();
            frame->setStyleSheet("QFrame {"
                                 "background-color: rgba(0, 0, 255, 40);"
                                 "border: 2px solid blue;"
                                 "}");

            frame->setMinimumSize(QSize(1920, 1080));
            frame->setMaximumSize(QSize(1920, 1080));

            QVBoxLayout* lay = new QVBoxLayout();
            lay->setContentsMargins(0, 0, 0, 0);
            lay->addWidget(frame);
            dia->setLayout(lay);

            dia->resize(1920, 1080);
            dia->move(0, 0);
            dia->show();
          }
        } else {
          b->setProperty("cssClass", cssStyle.split("_").first());
        }

        style()->unpolish(b);
        style()->polish(b);
      }

      update();
    });
  }

  buttonLayout->addStretch(1);
  wrapperLayout->addLayout(buttonLayout);

  // Settings
  QVBoxLayout *settingsLayout = new QVBoxLayout();
  settingsLayout->setContentsMargins(0, 0, 0, 0);
  settingsLayout->setSpacing(0);

  i = 1;
  QStringList settings = {"Audio", "Biterate", "Output"};
  for (QString setting : settings) {
    QFrame *settingBox = new QFrame();
    settingBox->setMaximumSize(QSize(300, 60));
    settingBox->setMinimumSize(QSize(300, 60));
    settingBox->setProperty("cssClass", QString("Group%0").arg(i++));

    QHBoxLayout *settingBoxLayout = new QHBoxLayout(settingBox);
    settingBoxLayout->setContentsMargins(15, 0, 15, 0);
    settingBoxLayout->setSpacing(0);

    settingBoxLayout->addWidget(new QLabel(setting));
    settingBoxLayout->addStretch(1);
    settingBoxLayout->addWidget(new QCheckBox());

    settingsLayout->addWidget(settingBox, 0, Qt::AlignCenter);
  }

  settingsLayout->addStretch(1);
  wrapperLayout->addLayout(settingsLayout);

  // Record
  QVBoxLayout *recordLayout = new QVBoxLayout();
  recordLayout->setContentsMargins(0, 0, 0, 0);
  recordLayout->setSpacing(0);

  QFrame *recordGroup = new QFrame();
  recordGroup->setMaximumSize(QSize(300, 60));
  recordGroup->setMinimumSize(QSize(300, 60));
  recordGroup->setProperty("cssClass", "RecordGroup");

  QHBoxLayout *recordGroupLayout = new QHBoxLayout(recordGroup);
  recordGroupLayout->setContentsMargins(15, 0, 15, 0);
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
  setLayout(layout);
}

#include <QPalette>
void MyDialog::mousePressEvent(QMouseEvent *event) {
  qWarning() << "Press event";

  m_pos = event->pos();
  if (!m_rubberBand) {
    m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    QPalette p = m_rubberBand->palette();
    p.setColor(QPalette::Active, QPalette::Highlight, Qt::green);
    m_rubberBand->setPalette(p);
  }
  m_rubberBand->setGeometry(QRect(m_pos, QSize()));
  m_rubberBand->show();
}

void MyDialog::mouseMoveEvent(QMouseEvent *event) {
  qWarning() << "Move event";

  if (m_rubberBand) {
    m_rubberBand->setGeometry(QRect(m_pos, event->pos()).normalized());
  }
}

void MyDialog::mouseReleaseEvent(QMouseEvent *event) {
  qWarning() << "Release event";

  if (m_rubberBand) {
    m_rubberBand->hide();
  }
  // determine selection, for example using QRect::intersects()
  // and QRect::contains().
}
