#pragma once
#include <QImage>
#include <QRect>
#include <QList>
#include <QMap>
#include <QDomDocument>

struct Slide
{
  QString name;
  QImage image;
  QRect mainRect;
  bool readXml(const QDomElement &i_element);
};
using Slides = QMap<QString,Slide>;

struct Prototype
{
  QImage backgroundImage;
  QString firstSlide;
  Slides slides;
  bool readXml(const QString &i_fileName);
};
