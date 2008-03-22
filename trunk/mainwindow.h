/****************************************************************************
 ***          Заголовочный файл программы для построения ДС               ***
 ****************************************************************************/

// Time-stamp: <mainwindow.h - 14:56:08 18.04.2006>

#ifndef BIFWIDGET_H
#define BIFWIDGET_H

#include <QObject>
#include <QWidget>

class QLabel;
class QLineEdit;
class QGroupBox;
class QComboBox;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class DSAnim;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow();

private slots:

  void setDS(int);
  void startAnim();
  void setStatic(bool);

private:

  DSAnim *dsanim;
  QComboBox *cBox;
  QLabel *label1;
  QLabel *label2;
  QLabel *label3;
  QLabel *label4;
  QLabel *label5;
  QLineEdit *lineEdit1;
  QLineEdit *lineEdit2;
  QLineEdit *lineEdit3;
  QLineEdit *lineEdit4;
  QLineEdit *lineEdit5;
  QGroupBox *gBox1;
  QLabel *label21;
  QLabel *label22;
  QLineEdit *lineEdit21;
  QLineEdit *lineEdit22;
  QLineEdit *lineEdit221;
  QLineEdit *lineEdit222;
  QGroupBox *gBox2;
  QGroupBox *gBox3;
  QPushButton *start;
  QPushButton *pause;
  QPushButton *stop;
  QPushButton *drawStatic;
};

#endif
