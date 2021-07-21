#include "MarsPlayer.h"

#include <QSettings>

MarsPlayer::MarsPlayer(QObject* parent) : QObject(parent) {
  setBackGround(nullptr);
}

void MarsPlayer::changeBackGround(QString url) { setBackGround(url); }

QString MarsPlayer::backGround() const { return m_strBackGroundPath; }

QString MarsPlayer::backGroundPath() const { return m_strBackGroundChoosePath; }

void MarsPlayer::setBackGround(QString url) {
  QSettings* settingini = new QSettings("setting.ini", QSettings::IniFormat);
  QString backGroundPath = settingini->value("Path/Background").toString();
  if (nullptr == url) {
    if (nullptr != backGroundPath) {
      m_strBackGroundPath = backGroundPath;
      m_strBackGroundChoosePath = backGroundPath;
    }
  } else {
    if (url != m_strBackGroundPath) {
      settingini->setValue("Path/Background", url);
      m_strBackGroundPath = url;
      m_strBackGroundChoosePath = url;
      emit backGroundChanged(m_strBackGroundPath);
      emit backGroundPathChanged(m_strBackGroundChoosePath);
    }
  }

  delete settingini;
}
