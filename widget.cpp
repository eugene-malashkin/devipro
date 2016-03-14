#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *i_parent)
  : QWidget(i_parent)
  , d_prototype(std::make_unique<Prototype>())
{
  showFullScreen();
  d_prototype->readXml("prototype.xml");
  d_currentSlideName = d_prototype->firstSlide;
}

void Widget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  drawBackground(painter);
  drawCurrentSide(painter);
}

void Widget::drawBackground(QPainter &i_painter)
{
  QRect sourceRect(0, 0, d_prototype->backgroundImage.width(), d_prototype->backgroundImage.height());
  QRect targetRect((width() - d_prototype->backgroundImage.width())/2, (height() - d_prototype->backgroundImage.height())/2, d_prototype->backgroundImage.width(), d_prototype->backgroundImage.height());
  i_painter.drawImage(targetRect, d_prototype->backgroundImage, sourceRect);
}

void Widget::drawCurrentSide(QPainter &i_painter)
{
  if (!d_prototype->slides.contains(d_currentSlideName))
  {
    return;
  }
  auto slide = d_prototype->slides[d_currentSlideName];
  auto imageWidth = slide.image.width();
  auto imageHeight = slide.image.height();
  QRect sourceRect(0, 0, imageWidth, imageHeight);
  QRect targetRect(width()/2 - slide.mainRect.center().x(), height()/2 - slide.mainRect.center().y(), imageWidth, imageHeight);
  i_painter.drawImage(targetRect, slide.image, sourceRect);
}
