#pragma once
#include <QWidget>

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *i_parent = nullptr);
};
