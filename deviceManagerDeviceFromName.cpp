#include "classes.h"
//AUTOMATICKY GENEROVANE
Device * DeviceManager::deviceFromName(QString name){

if(name == "Arrow"){    return new Arrow();    }
if(name == "ErrorDevice"){    return new ErrorDevice();    }
if(name == "Head"){    return new Head();    }
else{  return new ErrorDevice; }}