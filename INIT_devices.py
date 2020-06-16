from os import walk

def init():
    header = open("./devicesDefinitions.h", "w")
    header.write("//AUTOMATICKY VYGENEROVANE\n")
    header.close()

    source = open("./devicesDefinitions.cpp", "w")
    source.write("//AUTOMATICKY VYGENEROVANE\n#include \"devicesDefinitions.h\"\n")
    source.close()


def getVariable(text, substr):

    i1 = text.index(substr)
    i2 = text.index(":", i1) + 2;
    i3 = text.index(";", i2);

    return text[i2:i3]

def makeClassHeader(prototype, className):

    classHeader = "class " + className + " : public Device{\n"
    classHeader += "Q_OBJECT\n"
    classHeader += "public:\n"
    classHeader += className + "();\n\n"
    classHeader += "protected slots:\n"
    classHeader += "void work();\n"
    classHeader += "};\n"

    header = open("./devicesDefinitions.h", "a")
    header.write(classHeader)
    header.close()


def makeClassSource(prototype, className):

    prototypeText = prototype.read()

    classSource = className + "::" + className + "(){\n"

    id = getVariable(prototypeText, "ID")
    classSource += "this->ID = " + id + ";\n"

    period = getVariable(prototypeText, "period")
    classSource += "this->period = " + period + ";\n"

    classSource += "};\n"

    header = open("./devicesDefinitions.cpp", "a")
    header.write(classSource)
    header.close()



init()
pathDevices = "./PROTO_DEVICES"
devicePrototypes = []

for (dirpath, dirnames, filenames) in walk(pathDevices):

    for f in filenames:
        deviceProto = open(pathDevices + "/" + f, "r")
        makeClassHeader(deviceProto, f)
        makeClassSource(deviceProto, f)

    break
