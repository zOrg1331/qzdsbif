// Time-stamp: <translate.h - 19:05:17 29.01.2006>
/************************************************************************
 ***      ��� ��������� ������� ��������� ������� ������� � ���       ***
 ************************************************************************/

/* code: ���������� ����� <zorg1331@mail.ru> */

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QTextCodec>

// ��������� ������� � ��������� koi8-r � UTF-8
inline QString translate(QString encodedString)
{
  QTextCodec *codec = QTextCodec::codecForName("koi8-r");
  QByteArray newString("");
  newString.append(encodedString);
  QString string = codec->toUnicode(newString);
  return string;
}

#endif
