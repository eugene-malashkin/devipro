#include "logic.h"
#include <QFile>

bool Slide::readXml(const QDomElement &i_element)
{
  name = i_element.firstChildElement("Name").text();
  if (name.isEmpty())
  {
    return false;
  }
  auto imageFileName = i_element.firstChildElement("Image").text();
  image = QImage(imageFileName);
  auto mainRectElement = i_element.firstChildElement("MainRect");
  mainRect = QRect(
        mainRectElement.attribute("left").toInt(),
        mainRectElement.attribute("top").toInt(),
        mainRectElement.attribute("width").toInt(),
        mainRectElement.attribute("height").toInt());
  return true;
}

bool Prototype::readXml(const QString &i_fileName)
{
  QFile file(i_fileName);
  if (!file.open(QIODevice::ReadOnly))
  {
    return false;
  }
  QDomDocument document;
  if (!document.setContent(file.readAll()))
  {
    return false;
  }
  auto commonElement = document.documentElement().firstChildElement("Common");
  auto backgroundFileName = commonElement.firstChildElement("Background").text();
  backgroundImage = QImage(backgroundFileName);
  firstSlide = commonElement.firstChildElement("FirstSlide").text();
  auto slidesElement = document.documentElement().firstChildElement("Slides");
  if (slidesElement.isNull())
  {
    return false;
  }
  slides.clear();
  for (auto slideElement = slidesElement.firstChildElement("Slide"); !slideElement.isNull(); slideElement = slideElement.nextSiblingElement("Slide"))
  {
    Slide slide;
    if (!slide.readXml(slideElement))
    {
      return false;
    }
    slides[slide.name] = slide;
  }
  return true;
}
