#ifndef MARSPLAYER
#define MARSPLAYER

#include <QObject>
#include <QString>

class MarsPlayer : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString backGround READ backGround WRITE setBackGround NOTIFY
                 backGroundChanged)
  Q_PROPERTY(QString backGroundPath READ backGroundPath WRITE setBackGround
                 NOTIFY backGroundPathChanged)

 public:
  explicit MarsPlayer(QObject *parent = nullptr);

  Q_INVOKABLE void changeBackGround(QString url);

  QString backGround() const;
  QString backGroundPath() const;
  void setBackGround(QString url);

 signals:
  void backGroundChanged(QString url);
  void backGroundPathChanged(QString url);

 public slots:

 private:
  QString m_strBackGroundPath{""};
  QString m_strBackGroundChoosePath{""};
};

#endif  // MARSPLAYER
