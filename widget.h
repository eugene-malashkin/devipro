#pragma once
#include <memory>
#include <QWidget>
#include <QPainter>
#include "Logic.h"

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *i_parent = nullptr);

protected:
  void paintEvent(QPaintEvent *i_event) override;

private:
  std::unique_ptr<Prototype> d_prototype;
  QString d_currentSlideName;
  void drawBackground(QPainter &i_painter);
  void drawCurrentSide(QPainter &i_painter);
};
