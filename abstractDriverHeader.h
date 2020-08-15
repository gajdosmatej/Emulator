#include "qt.h"
class Device;
class DeviceWindowWrapper;

class Driver{
public:
    virtual void execute(Device * device, QString command) = 0;
    virtual void processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper ) = 0;
    int ID;
    QVector<QString> functions;
    int portNumber;

};
