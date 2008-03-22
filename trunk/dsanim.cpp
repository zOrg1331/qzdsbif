// Time-stamp: <dsanim.cpp - 17:39:46 16.05.2006>

#include <QtGui>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>

#include <math.h>

#include "dsanim.h"

DSAnim::DSAnim(QWidget *parent) : QWidget(parent)
{
  // Вставляем таймер
  autoStartTimer = new QTimer(this);
  // На каждий тик таймера пересчитываем систему
  connect(autoStartTimer, SIGNAL(timeout()), this, SLOT(recalc()));
  // Цвет фона
  setPalette(QPalette(QColor(50, 220, 225)));
  // инициализируем переменные
  dsType = 1;
  TLXcorner = -5;
  TLYcorner = 5;
  BRXcorner = 5;
  BRYcorner = -5;
  numDots = 20;
  A = B = C = 0.0;
  STATIC = false;
  ALREADYSHOWN = false;
  WASTETIME = 1000;
  DRAWTIMES = 100;
  // задаем как расположены точки вначале
  DoublePoint pointXY;
  for (double i = TLXcorner; i <= BRXcorner; i += (double)(BRXcorner-TLXcorner)/(double)numDots) {
    for (double j = TLYcorner; j >= BRYcorner; j -= (double)(TLYcorner-BRYcorner)/(double)numDots) {
      pointXY.x = j;
      pointXY.y = i;
      point.append(pointXY);
      pointOld.append(pointXY);
      pointZ.append(0);
    }
  }
}

void DSAnim::recalc()
{
  QVector<double> tmpPoint;
  QVector<double> tmpPointOld;
  // Пересчитываем координаты точек, в соответствии с заданной ДС
  for (int i = 0; i < point.size(); i++) {
    // пробегаем по всем заданным точкам, используя их как начальные
    // условия для заданной ДС
    tmpPoint.clear();
    tmpPointOld.clear();
    tmpPoint.append(point.at(i).x);
    tmpPoint.append(point.at(i).y);
    if (5 == dsType) {
      tmpPoint.append(pointZ.at(i));
    }
    if (dsType <= 5) {
      rk_s(tmpPoint);
    } else {
      tmpPointOld.append(pointOld.at(i).x);
      tmpPointOld.append(pointOld.at(i).y);
      otobr(tmpPoint, tmpPointOld);
    }
    point[i].x = tmpPoint.at(0);
    point[i].y = tmpPoint.at(1);
    //    qDebug() << point.at(i).x << point.at(i).y;
    if (5 == dsType) {
      pointZ[i] = tmpPoint.at(2);
    }
  }
  if (dsType > 5) {
    pointOld = point;
  }
  // После того, как посчитали, запускаем перерисовку
  update();
}

double DSAnim::f(int i, double x, QVector<double> y)
{
  if (1 == i) {
    switch (dsType) {
    case 0: return -A*y.at(1)-B*x-C-x*x*x;
    case 1: return (A-x*x)*y.at(1)-x;
    case 2: return (A-y.at(1)*y.at(1))*y.at(1)-x;
    case 3: return (A+B*x*x-x*x*x*x)*y.at(1)-x;
    case 4: return B*x-x*x*y.at(1);
    case 5: return x+A*y.at(1);
    }
  }
  if (0 == i) {
    switch (dsType) {
    case 0: return y.at(1);
    case 1: return y.at(1);
    case 2: return y.at(1);
    case 3: return y.at(1);
    case 4: return A-B*x+x*x*y.at(1)-x;
    case 5: return -(y.at(1)+y.at(2));
    }
  }
  if (2 == i) {
    // double result = B+y.at(2)*(x-C);
    // qDebug() << result;
    return B+y.at(2)*(x-C);
  }
  return 0.0;
}

void DSAnim::sys_rk(double x, double x1, int m, int n, QVector<double>& y)
{
  double h = double(x1-x)/double(m);

  for(int i = 0; i <= m-1; i++) {
      sys_rk_step(x+double(i*h), h, n, y);
  }
}

void DSAnim::sys_rk_step(double x, double h, int n, QVector<double>& y)
{
  int i;
  QVector<double> yt, k1, k2, k3, k4;
  yt.clear();
  k1.clear();
  k2.clear();
  k3.clear();
  k4.clear();

  for(i = 0; i < n; i++) {
    k1.append(h*f(i, x, y));
  }
  for(i = 0; i < n; i++) {
    yt.append(y.at(i)+0.5*k1.at(i));
  }
  for(i = 0; i < n; i++) {
    k2.append(h*f(i, x+k1.at(0)*0.5, yt));
  }
  yt.clear();
  for(i = 0; i < n; i++) {
    yt.append(y.at(i)+0.5*k2.at(i));
  }
  for(i = 0; i < n; i++) {
    k3.append(h*f(i, x+k2.at(0)*0.5, yt));
  }
  yt.clear();
  for(i = 0; i < n; i++) {
    yt.append(y.at(i)+k3.at(i));
  }
  for(i = 0; i < n; i++) {
    k4.append(h*f(i, x+k3.at(0), yt));
  }
  for(i = 0; i < n; i++) {
    y[i] = y.at(i)+double(k1.at(i)+2.0*k2.at(i)
			  +2.0*k3.at(i)+k4.at(i))/double(6);
  }
}

void DSAnim::rk_s(QVector<double> &tmpPoint)
{
  if (5 == dsType) {
    sys_rk_step(tmpPoint.at(0), 0.01, 3, tmpPoint);
  } else {
    //    sys_rk(tmpPoint.at(0), tmpPoint.at(0)+0.1, 100, 2, tmpPoint);
    sys_rk_step(tmpPoint.at(0), 0.01, 2, tmpPoint);
  }
}

QSize DSAnim::sizeHint() const
{
  // Минимальный размер виджета анимации
  // см. coinAnim QSizePolicy в coinmain.cpp
  QSize size;
  size = QSize(700, 700);
  return size;
}

void DSAnim::start()
{
  // Стартуем только если таймер "молчит"
  if (autoStartTimer->isActive()) { return; }
  // // задаем как расположены точки вначале
  // DoublePoint pointXY;
  // point.clear();
  // for (int i = TLXcorner; i <= BRXcorner; i += abs(TLXcorner-BRXcorner)/numDots) {
  //   for (int j = TLYcorner; j >= BRYcorner; j -= abs(TLYcorner-BRYcorner)/numDots) {
  //     pointXY.x = i;
  //     pointXY.y = j;
  //     point.append(pointXY);
  //   }
  // }
  autoStartTimer->start();
  if (!STATIC) {
    this->setUpdatesEnabled(true);
  }
}

void DSAnim::pause()
{
  if (autoStartTimer->isActive()) {
    autoStartTimer->stop();
  } else {
    autoStartTimer->start();
  }
}

void DSAnim::stop()
{
  autoStartTimer->stop();
  // задаем как расположены точки вначале
  DoublePoint pointXY;
  point.clear();
  pointZ.clear();
  pointOld.clear();
  for (double i = TLXcorner; i <= BRXcorner; i += (double)(BRXcorner-TLXcorner)/(double)numDots) {
    for (double j = TLYcorner; j >= BRYcorner; j -= (double)(TLYcorner-BRYcorner)/(double)numDots) {
      pointXY.x = j;
      pointXY.y = i;
      point.append(pointXY);
      pointOld.append(pointXY);
      pointZ.append(0);
    }
  }
  update();
}

void DSAnim::paintEvent(QPaintEvent *)
{
  // Если рисуется статика, то останавливаем таймер
  if (STATIC && autoStartTimer->isActive()) {
    autoStartTimer->stop();
  }
  if (!STATIC) { // если нужна анимация
    QPainter painter(this);
    // Включаем сглаживание
    painter.setRenderHint(QPainter::Antialiasing);
    paintDS(painter);
  } else if (STATIC && !ALREADYSHOWN) { // если нужна статическая картинка
    ALREADYSHOWN = true;
    QPainter painter(this);
    // Включаем сглаживание
    painter.setRenderHint(QPainter::Antialiasing);
    // впустую нное кол-во раз считаем, чтобы все устаканилось
    for (int i = 0; i < WASTETIME; i++) {
      recalc();
    }
    // рисуем сразу много "срезов" во времени
    static int count = DRAWTIMES;
    while (count > 0) {
      recalc();
      paintDS(painter);
      count--;
    }
    this->setUpdatesEnabled(false);
  }
}

void DSAnim::paintDS(QPainter &painter)
{
  // отрисовываем все точки в векторе
  painter.setWindow(TLXcorner, BRYcorner,
		    (BRXcorner-TLXcorner), (TLYcorner-BRYcorner));
  QBrush brush(Qt::red);
  painter.setBrush(brush);
  QPen pen(Qt::blue);
  painter.setPen(pen);
  //  painter.scale(0.8, 0.8);
  //  painter.shear(-0.1, -0.5);
  double pointWidth = 0.003*abs(BRXcorner-TLXcorner);
  for (int i = 0; i < point.size()-1; i++) {
    if ((point.at(i).x >= TLXcorner) && (point.at(i).x <= BRXcorner) &&
	(point.at(i).y >= BRYcorner) && (point.at(i).y <= TLYcorner)) {
      painter.drawPoint(QPointF(point.at(i).x, point.at(i).y));
    }
  }
  if ((point.last().x >= TLXcorner) && (point.last().x <= BRXcorner) &&
      (point.last().y >= BRYcorner) && (point.last().y <= TLYcorner)) {
    painter.drawEllipse(QRectF(point.last().x-pointWidth, point.last().y-pointWidth,
			       2*pointWidth, 2*pointWidth));
  }
}

void DSAnim::otobr(QVector<double> &tmpPoint, QVector<double> &tmpPointOld)
{
  switch (dsType) {
  case 6: {
    tmpPoint[0] = 1.0-A*tmpPointOld.at(0)*tmpPointOld.at(0)-B*tmpPointOld.at(1);
    tmpPoint[1] = tmpPointOld.at(0);
    return;
  }
  case 7: {
    tmpPoint[0] = (1-A)*tmpPointOld.at(0)+B*sin(tmpPointOld.at(1));
    tmpPoint[1] = tmpPointOld.at(1)+tmpPoint.at(0);
    while (tmpPoint.at(1) > 2.0*M_PI) {
      tmpPoint[1] -= 2.0*M_PI;
    }
    return;
  }
  case 8: {
    double x = tmpPointOld.at(0);
    double y = tmpPointOld.at(1);
    tmpPoint[0] = A+B*(x*cos(x*x+y*y)-x*sin(x*x+y*y));
    tmpPoint[1] = B*(x*sin(x*x+y*y)+x*cos(x*x+y*y));
    return;
  }
  case 9: {
    tmpPoint[0] = tmpPointOld.at(0)-2*A*B*sin(B*tmpPointOld.at(1));
    tmpPoint[1] = tmpPointOld.at(1)+
      2*C*tan(tmpPointOld.at(0)-2*A*B*sin(B*tmpPointOld.at(1)));
    return;
  }
  }
}

void DSAnim::mousePressEvent(QMouseEvent *ev)
{
  double X = TLXcorner+(BRXcorner-TLXcorner)*(double)ev->x()/(double)width();
  double Y = BRYcorner+(TLYcorner-BRYcorner)*(double)ev->y()/(double)height();
  point.last().x = X;
  point.last().y = Y;
  pointOld.last().x = X;
  pointOld.last().y = Y;
}
