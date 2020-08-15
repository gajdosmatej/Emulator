//AUTOMATICKY VYGENEROVANE
#include "abstractDriverHeader.h"
class HeadDriver : public Driver{
public:
HeadDriver();

void light_on(Device * device);

void light_off(Device * device);

void blink(Device * device);

void processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper);
void execute(Device * device, QString command);
};
class ArrowDriver : public Driver{
public:
ArrowDriver();

void move_left(Device * device);

void move_up(Device * device);

void move_right(Device * device);

void move_down(Device * device);


void processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper);
void execute(Device * device, QString command);
};
