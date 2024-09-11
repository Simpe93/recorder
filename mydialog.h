#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPoint>
#include <QList>
#include <QImage>

class QRubberBand;

class MyDialog : public QDialog {
  Q_OBJECT
public:
  MyDialog(QList<QImage> images, QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  void setupUi();

private:
  QList<QImage> m_images;

  bool m_selectionEnabled;

  QRubberBand *m_rubberBand;
  QPoint m_pos;
};

#endif // DIALOG_H
