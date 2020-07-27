from os import walk

def init():
    header = open("./devicesDefinitions.h", "w")
    header.write("//AUTOMATICKY VYGENEROVANE\n#include \"abstractDeviceHeader.h\"\n")
    header.close()

    source = open("./devicesDefinitions.cpp", "w")
    source.write("//AUTOMATICKY VYGENEROVANE\n\n#include \"devicesDefinitions.h\"\n\n")
    source.close()


    headerDriver = open("./driversDefinitions.h", "w")
    headerDriver.write("//AUTOMATICKY VYGENEROVANE\n")
    headerDriver.close()

    sourceDriver = open("./driversDefinitions.cpp", "w")
    sourceDriver.write("//AUTOMATICKY VYGENEROVANE\n\n#include \"driversDefinitions.h\"\n\n")
    sourceDriver.close()


def getVariable(text, substr, ending):

    i1 = text.index(substr)
    i2 = text.index(":", i1) + 2;
    i3 = text.index(ending, i2);

    return text[i2:i3]


def getFunctionName(text):

    i2 = text.index("):")
    i1 = text.rindex(";", 0, i2)

    return text[i1+1:i2+1]


def makeDriverClassHeader(prototypeText, className):

    classHeader = "class " + className + " : public Driver{\n"
    classHeader += "public:\n"
    #classHeader += className + "();\n\n"

    tempText = prototypeText
    while "):" in tempText:

        classHeader += getFunctionName(tempText) + ";"
        tempText = tempText[tempText.index("};") +1 : ]


    classHeader += "};\n"

    header = open("./driversDefinitions.h", "a")
    header.write(classHeader)
    header.close()


def makeDriverClassSource(prototypeText, className):

    classSource = ""
    tempText = prototypeText
    while "):" in tempText:

        wholeName = getFunctionName(tempText)

        TYPE = wholeName[: wholeName.index(" ")+1]
        NAME = wholeName[wholeName.index(" ") + 1 :]

        classSource += TYPE + className + "::" + NAME

        classSource += getVariable(tempText, "):", "};") + "}\n\n"
        tempText = tempText[tempText.index("};") +1 : ]


    source = open("./driversDefinitions.cpp", "a")
    source.write(classSource)
    source.close()



def makeDeviceClassHeader(prototypeText, className):

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


def makeDeviceClassSource(prototypeText, className):

    classSource = className + "::" + className + "() : Device(){\n"

    id = getVariable(prototypeText, "ID", ";")
    classSource += "this->ID = " + id + ";\n"

    period = getVariable(prototypeText, "period", ";")
    classSource += "this->period = " + period + ";\n"

    classSource += "};\n\n"

    classSource += "void " + className + "::work()\n"
    classSource += getVariable(prototypeText, "work()", "};")
    classSource += "};"

    header = open("./devicesDefinitions.cpp", "a")
    header.write(classSource)
    header.close()


def devices():
    pathDevices = "./PROTO_DEVICES"
    devicePrototypes = []

    for (dirpath, dirnames, filenames) in walk(pathDevices):

        for f in filenames:
            deviceProto = open(pathDevices + "/" + f, "r")
            deviceText = deviceProto.read()
            makeDeviceClassHeader(deviceText, f)
            makeDeviceClassSource(deviceText, f)

        break



def drivers():
    pathDrivers = "./PROTO_DRIVERS"
    driverPrototypes = []

    for (dirpath, dirnames, filenames) in walk(pathDrivers):

        for f in filenames:
            driverProto = open(pathDrivers + "/" + f, "r")
            driverText = driverProto.read()
            makeDriverClassHeader(driverText, f)
            makeDriverClassSource(driverText, f)

        break


init()
devices()
drivers()
