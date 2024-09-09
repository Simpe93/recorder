#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPoint>

class QRubberBand;

class MyDialog : public QDialog {
  Q_OBJECT
public:
  MyDialog(QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  void setupUi();

private:
  bool m_selectionEnabled;

  QRubberBand *m_rubberBand;
  QPoint m_pos;
};

#endif // DIALOG_H
