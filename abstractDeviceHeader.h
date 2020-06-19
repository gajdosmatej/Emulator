#include "qt.h"

class Device : public QObject{
  Q_OBJECT
public:
    int ID;
    int INPUT = 0;
    int period;
    int OUTPUT = 0;
    QString name;
    Device();

protected slots:
    virtual void work() = 0;

protected:
    QTimer * timer;

};
