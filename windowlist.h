#ifndef WINDOWLIST_H
#define WINDOWLIST_H

#include <QObject>
#include <QImage>
#include <QList>

class WindowList : public QObject {
  Q_OBJECT
public:
  WindowList();

  QList<QImage> getImages();

private:
  void getWindowStats();

private:
  QList<QImage> m_images;
};

#endif // WINDOWLIST_H
