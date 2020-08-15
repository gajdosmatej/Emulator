//AUTOMATICKY VYGENEROVANE
#include "abstractDriverHeader.h"
class HeadDriver : public Driver{
public:
HeadDriver();

void light_on(Device * device);

void light_off(Device * device);

void blink(Device * device);
void execute(Device * device, QString command);
void processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper);
};
