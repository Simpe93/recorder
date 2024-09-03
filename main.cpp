#include <QApplication>
#include <QDialog>
#include <QToolButton>
#include <QHBoxLayout>
#include <QIcon>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setApplicationName("Recording");

  QDialog *dia = new QDialog();

  QHBoxLayout * layout = new QHBoxLayout();
  layout->setSpacing(0);

  QToolButton * but1 = new QToolButton();
  QToolButton * but2 = new QToolButton();
  QToolButton * but3 = new QToolButton();

  but1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  but2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  but3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  but1->setText("Screen");
  but2->setText("Window");
  but3->setText("Selection");

  but1->setIconSize(QSize(32, 32));
  but2->setIconSize(QSize(32, 32));
  but3->setIconSize(QSize(32, 32));

  QIcon test1("/home/simpe/QtProjects/rpmchecker/screen.png");
  QIcon test2("/home/simpe/QtProjects/rpmchecker/window.png");
  QIcon test3("/home/simpe/QtProjects/rpmchecker/selection.png");

  but1->setIcon(test1);
  but2->setIcon(test2);
  but3->setIcon(test3);

  but1->setMaximumSize(QSize(100, 100));
  but1->setMinimumSize(QSize(100, 100));
  but1->setFocusPolicy(Qt::NoFocus);

  but2->setMaximumSize(QSize(100, 100));
  but2->setMinimumSize(QSize(100, 100));
  but2->setFocusPolicy(Qt::NoFocus);

  but3->setMaximumSize(QSize(100, 100));
  but3->setMinimumSize(QSize(100, 100));
  but3->setFocusPolicy(Qt::NoFocus);

  but1->setStyleSheet("QToolButton {"
                      "border-top-left-radius: 20px;"
                      "border-bottom-left-radius: 20px;"
                      "border: 2px solid #555;"
                      "border-right: 0px;"
                      "background-color: #fff;"
                      "outline: 0px;"
                      "}");
  but2->setStyleSheet("QToolButton {"
                      "border: 2px solid #555;"
                      "background-color: #fff;"
                      "outline: 0px;"
                      "}");
  but3->setStyleSheet("QToolButton {"
                      "border-top-right-radius: 20px;"
                      "border-bottom-right-radius: 20px;"
                      "border: 2px solid #555;"
                      "border-left: 0px;"
                      "background-color: #fff;"
                      "outline: 0px;"
                      "}");

  but1->setCursor(Qt::PointingHandCursor);
  but2->setCursor(Qt::PointingHandCursor);
  but3->setCursor(Qt::PointingHandCursor);

  QObject::connect(but1, &QToolButton::clicked, [=]() {
    but1->setStyleSheet("QToolButton {"
                        "border-top-left-radius: 20px;"
                        "border-bottom-left-radius: 20px;"
                        "border: 2px solid #555;"
                        "border-right: 0px;"
                        "background-color: #d6d6d6;"
                        "outline: 0px;"
                        "}");
    but2->setStyleSheet("QToolButton {"
                        "border: 2px solid #555;"
                        "background-color: #fff;"
                        "outline: 0px;"
                        "}");
    but3->setStyleSheet("QToolButton {"
                        "border-top-right-radius: 20px;"
                        "border-bottom-right-radius: 20px;"
                        "border: 2px solid #555;"
                        "border-left: 0px;"
                        "background-color: #fff;"
                        "outline: 0px;"
                        "}");
  });

  QObject::connect(but2, &QToolButton::clicked, [=]() {
    but1->setStyleSheet("QToolButton {"
                        "border-top-left-radius: 20px;"
                        "border-bottom-left-radius: 20px;"
                        "border: 2px solid #555;"
                        "border-right: 0px;"
                        "background-color: #fff;"
                        "outline: 0px;"
                        "}");
    but2->setStyleSheet("QToolButton {"
                        "border: 2px solid #555;"
                        "background-color: #d6d6d6;"
                        "outline: 0px;"
                        "}");
    but3->setStyleSheet("QToolButton {"
                        "border-top-right-radius: 20px;"
                        "border-bottom-right-radius: 20px;"
                        "border: 2px solid #555;"
                        "border-left: 0px;"
                        "background-color: #fff;"
                        "outline: 0px;"
                        "}");
  });

  QObject::connect(but3, &QToolButton::clicked, [=]() {
    but1->setStyleSheet("QToolButton {"
                        "border-top-left-radius: 20px;"
                        "border-bottom-left-radius: 20px;"
                        "border: 2px solid #555;"
                        "border-right: 0px;"
                        "background-color: #fff;"
                        "outline: 0px;"
                        "}");
    but2->setStyleSheet("QToolButton {"
                        "border: 2px solid #555;"
                        "background-color: #fff;"
                        "outline: 0px;"
                        "}");
    but3->setStyleSheet("QToolButton {"
                        "border-top-right-radius: 20px;"
                        "border-bottom-right-radius: 20px;"
                        "border: 2px solid #555;"
                        "border-left: 0px;"
                        "background-color: #d6d6d6;"
                        "outline: 0px;"
                        "}");
  });

  layout->addStretch(1);
  layout->addWidget(but1);
  layout->addWidget(but2);
  layout->addWidget(but3);
  layout->addStretch(1);

  dia->setLayout(layout);

  dia->resize(400, 300);
  dia->show();

  // Parser parser;
  // parser.parse();

  a.exec();

  return 0;
}
