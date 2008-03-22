/******************************************************************
 *** Виджет, позволяющий построить эволюцию изображающих точек  ***
 ******************************************************************/

// Time-stamp: <mainwindow.cpp - 17:26:37 16.05.2006>

#include "mainwindow.h"
#include "translate.h"

#include <QtGui>

#include "dsanim.h"

MainWindow::MainWindow()
{
  dsanim = new DSAnim(this);
  cBox = new QComboBox(this);
  cBox->insertItem(0, translate("Нелинейный осциллятор"));
  cBox->insertItem(1, translate("Осциллятор В-д-П"));
  cBox->insertItem(2, translate("Осциллятор Релея"));
  cBox->insertItem(3, translate("Автоген. с ж. возбужд."));
  cBox->insertItem(4, translate("Брюсселятор"));
  cBox->insertItem(5, translate("Ресcлер"));
  cBox->insertItem(6, translate("Отобр. Эно"));
  cBox->insertItem(7, translate("Шарик на столе"));
  cBox->insertItem(8, translate("Отобр. Икеды"));
  cBox->insertItem(9, translate("Гофр. волновод"));
  cBox->setFrame(true);
  cBox->setEditable(false);

  label1 = new QLabel(translate("гамма:"));
  label2 = new QLabel(translate("a:"));
  label3 = new QLabel(translate("b:"));
  label4 = new QLabel(translate("хол. итерац.:"));
  label5 = new QLabel(translate("итерац. отрис.:"));
  lineEdit1 = new QLineEdit("2");
  lineEdit2 = new QLineEdit("2");
  lineEdit3 = new QLineEdit("2");
  lineEdit4 = new QLineEdit("1000");
  lineEdit5 = new QLineEdit("100");

  lineEdit4->setEnabled(false);
  lineEdit5->setEnabled(false);

  connect(cBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setDS(int)));

  QHBoxLayout *hStaticLayout1 = new QHBoxLayout();
  hStaticLayout1->addWidget(label4);
  hStaticLayout1->addWidget(lineEdit4);
  QHBoxLayout *hStaticLayout2 = new QHBoxLayout();
  hStaticLayout2->addWidget(label5);
  hStaticLayout2->addWidget(lineEdit5);

  gBox1 = new QGroupBox(translate("Задайте параметры ДС"), this);
  QGridLayout *gridLayout1 = new QGridLayout;
  gridLayout1->addWidget(label1, 0, 0);
  gridLayout1->addWidget(lineEdit1, 0, 1);
  gridLayout1->addWidget(label2, 1, 0);
  gridLayout1->addWidget(lineEdit2, 1, 1);
  gridLayout1->addWidget(label3, 2, 0);
  gridLayout1->addWidget(lineEdit3, 2, 1);
  gridLayout1->setMargin(0);
  gridLayout1->setSpacing(0);
  gBox1->setLayout(gridLayout1);

  label21 = new QLabel(translate("коор ВЛ угла:"));
  label22 = new QLabel(translate("коор НП угла:"));
  lineEdit21 = new QLineEdit("-5");
  lineEdit22 = new QLineEdit("5");
  lineEdit221 = new QLineEdit("5");
  lineEdit222 = new QLineEdit("-5");

  gBox2 = new QGroupBox(translate("Задайте параметры ФП"), this);
  QGridLayout *gridLayout2 = new QGridLayout;
  gridLayout2->addWidget(label21, 0, 0);
  gridLayout2->addWidget(lineEdit21, 0, 1);
  gridLayout2->addWidget(lineEdit221, 0, 2);
  gridLayout2->addWidget(label22, 1, 0);
  gridLayout2->addWidget(lineEdit22, 1, 1);
  gridLayout2->addWidget(lineEdit222, 1, 2);
  gridLayout2->setMargin(0);
  gridLayout2->setSpacing(0);
  gBox2->setLayout(gridLayout2);

  start = new QPushButton(translate("Запуск анимации"));
  pause = new QPushButton(translate("Приостановка анимации"));
  stop = new QPushButton(translate("Остановка анимации"));
  drawStatic = new QPushButton(translate("Рисовать статич."));
  drawStatic->setDisabled(true);

  gBox3 = new QGroupBox(translate("Рисовать анимацию"), this);
  gBox3->setCheckable(true);
  gBox3->setChecked(true);
  QVBoxLayout *gLayout3 = new QVBoxLayout;
  gLayout3->addWidget(start);
  gLayout3->addWidget(pause);
  gLayout3->addWidget(stop);
  gLayout3->setMargin(0);
  gLayout3->setSpacing(0);
  gBox3->setLayout(gLayout3);

  connect(start, SIGNAL(clicked()), this, SLOT(startAnim()));
  connect(pause, SIGNAL(clicked()), dsanim, SLOT(pause()));
  connect(stop, SIGNAL(clicked()), dsanim, SLOT(stop()));
  connect(drawStatic, SIGNAL(clicked()), this, SLOT(startAnim()));
  connect(gBox3, SIGNAL(toggled(bool)), drawStatic, SLOT(setDisabled(bool)));
  connect(gBox3, SIGNAL(toggled(bool)), this, SLOT(setStatic(bool)));
  connect(gBox3, SIGNAL(toggled(bool)), lineEdit4, SLOT(setDisabled(bool)));
  connect(gBox3, SIGNAL(toggled(bool)), lineEdit5, SLOT(setDisabled(bool)));

  QVBoxLayout *vLayout = new QVBoxLayout;
  vLayout->addStretch();
  vLayout->addWidget(cBox);
  vLayout->addStretch();
  vLayout->addWidget(gBox1);
  vLayout->addStretch();
  vLayout->addWidget(gBox2);
  vLayout->addStretch();
  vLayout->addWidget(gBox3);
  vLayout->addStretch();
  vLayout->addWidget(drawStatic);
  vLayout->addLayout(hStaticLayout1);
  vLayout->addLayout(hStaticLayout2);
  vLayout->addStretch();
  vLayout->setMargin(0);
  vLayout->setSpacing(0);
  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(dsanim);
  mainLayout->addLayout(vLayout);
  mainLayout->setMargin(0);
  mainLayout->setSpacing(0);
  setLayout(mainLayout);
}

void MainWindow::setDS(int newDS)
{
  if (newDS == 0) {
    label1->setText(translate("гамма:"));
    label2->setText(translate("a:"));
    label2->setVisible(true);
    label3->setText(translate("b:"));
    label3->setVisible(true);
    lineEdit1->setText("2");
    lineEdit2->setText("2");
    lineEdit2->setVisible(true);
    lineEdit3->setText("2");
    lineEdit3->setVisible(true);
    lineEdit4->setText("100");
    lineEdit5->setText("200");
    start->setEnabled(true);
  }
  if (newDS == 1) {
    label1->setText(translate("ламбда:"));
    label2->setVisible(false);
    label3->setVisible(false);
    lineEdit1->setText("1");
    lineEdit4->setText("100");
    lineEdit5->setText("200");
    lineEdit2->setVisible(false);
    lineEdit3->setVisible(false);
    start->setEnabled(true);
  }
  if (newDS == 2) {
    label1->setText(translate("ламбда:"));
    label2->setVisible(false);
    label3->setVisible(false);
    lineEdit1->setText("1");
    lineEdit2->setVisible(false);
    lineEdit3->setVisible(false);
    lineEdit4->setText("100");
    lineEdit5->setText("200");
    start->setEnabled(true);
  }
  if (newDS == 3) {
    label1->setText(translate("ламбда:"));
    label2->setText("k:");
    label2->setVisible(true);
    label3->setVisible(false);
    lineEdit1->setText("1");
    lineEdit2->setText("2");
    lineEdit2->setVisible(true);
    lineEdit3->setVisible(false);
    lineEdit4->setText("100");
    lineEdit5->setText("200");
    start->setEnabled(true);
  }
  if (newDS == 4) {
    label1->setText(translate("A:"));
    label2->setText("B:");
    label2->setVisible(true);
    label3->setVisible(false);
    lineEdit1->setText("1");
    lineEdit2->setText("2");
    lineEdit2->setVisible(true);
    lineEdit3->setVisible(false);
    lineEdit4->setText("200");
    lineEdit5->setText("200");
    start->setEnabled(true);
  }
  if (newDS == 5) {
    label1->setText(translate("a:"));
    label2->setText(translate("b:"));
    label2->setVisible(true);
    label3->setText(translate("c:"));
    label3->setVisible(true);
    lineEdit1->setText("0.2");
    lineEdit2->setText("0.2");
    lineEdit2->setVisible(true);
    lineEdit3->setText("1");
    lineEdit3->setVisible(true);
    lineEdit4->setText("3000");
    lineEdit5->setText("100");
    start->setEnabled(true);
  }
  if (newDS == 6) {
    label1->setText(translate("ламбда:"));
    label2->setText(translate("b:"));
    label2->setVisible(true);
    label3->setText(translate("c:"));
    label3->setVisible(false);
    lineEdit1->setText("0.2");
    lineEdit2->setText("0.1");
    lineEdit2->setVisible(true);
    lineEdit3->setText("1");
    lineEdit3->setVisible(false);
    lineEdit4->setText("10");
    lineEdit5->setText("100");
    start->setEnabled(true);
  }
  if (newDS == 7) {
    label1->setText(translate("e:"));
    label2->setText(translate("k:"));
    label2->setVisible(true);
    label3->setText(translate("c:"));
    label3->setVisible(false);
    lineEdit1->setText("0.0");
    lineEdit2->setText("0.2");
    lineEdit2->setVisible(true);
    lineEdit3->setText("1");
    lineEdit3->setVisible(false);
    lineEdit4->setText("10");
    lineEdit5->setText("100");
    start->setEnabled(true);
  }
  if (newDS == 8) {
    label1->setText(translate("a:"));
    label2->setText(translate("b:"));
    label2->setVisible(true);
    label3->setText(translate("c:"));
    label3->setVisible(false);
    lineEdit1->setText("0.5");
    lineEdit2->setText("1.0");
    lineEdit2->setVisible(true);
    lineEdit3->setText("1");
    lineEdit3->setVisible(false);
    start->setEnabled(true);
  }
  if (newDS == 9) {
    label1->setText(translate("a:"));
    label2->setText(translate("k:"));
    label2->setVisible(true);
    label3->setText(translate("h:"));
    label3->setVisible(true);
    lineEdit1->setText("0.2");
    lineEdit2->setText("0.2");
    lineEdit2->setVisible(true);
    lineEdit3->setText("1");
    lineEdit3->setVisible(true);
    start->setEnabled(true);
  }
}

void MainWindow::startAnim()
{
  dsanim->TLXcorner = lineEdit21->text().toInt();
  dsanim->TLYcorner = lineEdit221->text().toInt();
  dsanim->BRXcorner = lineEdit22->text().toInt();
  dsanim->BRYcorner = lineEdit222->text().toInt();
  dsanim->WASTETIME = lineEdit4->text().toInt();
  dsanim->DRAWTIMES = lineEdit5->text().toInt();
  dsanim->stop();
  dsanim->dsType = cBox->currentIndex();
  dsanim->A = lineEdit1->text().toFloat();
  dsanim->B = lineEdit2->text().toFloat();
  dsanim->C = lineEdit3->text().toFloat();
  dsanim->start();
}

void MainWindow::setStatic(bool _Static)
{
  dsanim->STATIC = !_Static;
}
