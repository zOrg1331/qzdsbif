/*******************************************************************************
 *** Главный программный модуль приложения для построения картины эволюции   ***
 ***                          изображающих точек                             ***
 *******************************************************************************/

// Time-stamp: <main.cpp - 22:59:07 26.02.2006>

#include <QApplication>
#include <QPlastiqueStyle>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QApplication::setStyle(new QPlastiqueStyle());
  QFont defaultFont("Sans Serif", 10, QFont::Normal);
  defaultFont.setPointSize(10);
  QApplication::setFont(defaultFont);

  MainWindow window;
  window.show();
  return app.exec();
}
