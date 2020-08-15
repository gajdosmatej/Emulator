//AUTOMATICKY VYGENEROVANE
#include "abstractDeviceHeader.h"
class Arrow : public Device{
Q_OBJECT
public:
Arrow();

protected slots:
void work();
};
class ErrorDevice : public Device{
Q_OBJECT
public:
ErrorDevice();

protected slots:
void work();
};
class Head : public Device{
Q_OBJECT
public:
Head();

protected slots:
void work();
};
