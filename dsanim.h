// Time-stamp: <dsanim.h - 11:01:38 23.04.2006>

#ifndef DSANIM_H
#define DSANIM_H

#include <QWidget>

class QTimer;

struct DoublePoint {
  double x, y;
};

class DSAnim : public QWidget
{
  Q_OBJECT

public:
  DSAnim(QWidget *parent = 0);

  // Перехватываем контроль над размерами виджета
  QSize sizeHint() const;
  // тип ДС
  int dsType;
  // координаты области ФП
  int TLXcorner, TLYcorner, BRXcorner, BRYcorner;
  // параметры ДС
  double A, B, C;
  // может рисовать только статическую картинку?
  bool STATIC;
  // сколько будет холостых итераций
  int WASTETIME;
  // сколько потом рисовать итераций на одном "холсте"
  int DRAWTIMES;

public slots:

  void start();
  void pause();
  void stop();

private slots:

  void recalc();

signals:

protected:

  // Событие перерисовки
  void paintEvent(QPaintEvent *event);
  virtual void mousePressEvent(QMouseEvent *ev);

private:
  bool ALREADYSHOWN;
  int numDots;
  QVector <DoublePoint> point;
  QVector <DoublePoint> pointOld;
  QVector <double> pointZ;
  void paintDS(QPainter &painter);
  void rk_s(QVector<double> &tmpPoint);
  void otobr(QVector<double> &tmpPoint, QVector<double> &tmpPointOld);
  void sys_rk(double x, double x1, int m, int n, QVector<double>& y);
  void sys_rk_step(double x, double h, int n, QVector<double>& y);
  double f(int i, double x, QVector<double> y);

  // Добавляем таймер
  int timerCount;
  QTimer *autoStartTimer;
};

#endif
