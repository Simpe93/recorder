#include "windowlist.h"

#include <QVariant>
#include <QDebug>
#include <QPixmap>
#include <QImage>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

WindowList::WindowList() {
  getWindowStats();
}

QList<QImage> WindowList::getImages() {
  return m_images;
}

void WindowList::getWindowStats() {
  Display *display = XOpenDisplay(NULL);
  if (!display) {
    qWarning() << "Failed to connect to X server";
    return;
  }

  Window window = DefaultRootWindow(display);

  Atom atom = XInternAtom(display, "_NET_CLIENT_LIST", true);
  Atom actualType;
  int actualFormat;
  unsigned long nrItems;
  unsigned long bytesAfter;

  unsigned char *data;
  int status = XGetWindowProperty(display, window, atom, 0L, (~0L), false, AnyPropertyType, &actualType, &actualFormat, &nrItems, &bytesAfter, &data);
  Window * win = (Window*) data;

  if (status >= Success && nrItems) {
    int t = 0;
    for (int i = 0; i < nrItems; ++i) {

      char *windowName;
      char *className;
      {
        XTextProperty textData;
        Atom atom = XInternAtom(display, "WM_NAME", true);
        int status = XGetTextProperty(display, win[i], &textData, atom);
        windowName = (char*)textData.value;
      }
      {
        XTextProperty textData;
        Atom atom = XInternAtom(display, "WM_CLASS", true);
        int status = XGetTextProperty(display, win[i], &textData, atom);
        className = (char*)textData.value;
      }

      if (windowName && className) {
        qWarning() << QString(windowName) << QString(className);
      }

      Atom atom2 = XInternAtom(display, "_NET_WM_ICON", true);

      unsigned long nitems, bytesAfter2;
      unsigned char *ret;
      int format;
      Atom type;
      XGetWindowProperty(display, win[i], atom2, 0, 1, 0, AnyPropertyType, &type, &format, &nitems, &bytesAfter2, &ret);
      int width = *(int*)ret;
      XFree(ret);
      XGetWindowProperty(display, win[i], atom2, 1, 1, 0, AnyPropertyType, &type, &format, &nitems, &bytesAfter2, &ret);
      int height = *(int*)ret;
      XFree(ret);

      int size = width * height;
      XGetWindowProperty(display, win[i], atom2, 2, size, 0, AnyPropertyType, &type, &format, &nitems, &bytesAfter2, &ret);
      unsigned int* imgData = new unsigned int[size];
      unsigned long* ul = (unsigned long*)ret;

      for (int i = 0; i < nitems; ++i) {
        imgData[i] = (unsigned int)ul[i];
      }

      XFree(ret);

      QImage img(width, height, QImage::Format_RGBA8888);
      unsigned char* argb = (unsigned char*)imgData;
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          unsigned char a = argb[3];
          unsigned char r = argb[2] * a / 255;
          unsigned char g = argb[1] * a / 255;
          unsigned char b = argb[0] * a / 255;

          unsigned int rgba = ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu);
          img.setPixel(x, y, rgba);

          argb += 4;
        }
      }

      img.save(QString("/home/simpe/QtProjects/test_%1.png").arg(t++));
      m_images.append(img);

      qWarning() << width << height;
    }
  }

  XFree(data);
}
