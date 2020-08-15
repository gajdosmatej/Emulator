from os import walk

def init():
    header = open("./devicesDefinitions.h", "w")
    header.write("//AUTOMATICKY VYGENEROVANE\n#include \"abstractDeviceHeader.h\"\n")
    header.close()

    source = open("./devicesDefinitions.cpp", "w")
    source.write("//AUTOMATICKY VYGENEROVANE\n\n#include \"classes.h\"\n\n")
    source.close()


    headerDriver = open("./driversDefinitions.h", "w")
    headerDriver.write("//AUTOMATICKY VYGENEROVANE\n#include \"abstractDriverHeader.h\"\n")
    headerDriver.close()

    sourceDriver = open("./driversDefinitions.cpp", "w")
    sourceDriver.write("//AUTOMATICKY VYGENEROVANE\n\n#include \"classes.h\"\n\n")
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


def makeDriverLibraryConstructor(driverNames):

    text = "#include \"classes.h\"\n"
    text += "//AUTOMATICKY GENEROVANE\n"
    text += "DriverLibrary::DriverLibrary(Controller * par, Editor * w){\n"
    text += "this->controller = par;\n"
    text += "this->window = w;\n"

    for driver in driverNames:
        text += "this->drivers.append(new " + driver + ");\n"

    text += "}"

    file = open("./driverLibraryConstruct.cpp", "w")
    file.write(text)
    file.close()

def makeDriverClassHeader(prototypeText, className):

    classHeader = "class " + className + " : public Driver{\n"
    classHeader += "public:\n"
    classHeader += className + "();"

    tempText = prototypeText
    while "):" in tempText:

        classHeader += getFunctionName(tempText) + ";"
        tempText = tempText[tempText.index("};") +1 : ]


    classHeader += "\nvoid execute(Device * device, QString command);\n"
    classHeader += "};\n"

    header = open("./driversDefinitions.h", "a")
    header.write(classHeader)
    header.close()


def makeDriverClassSource(prototypeText, className):

    #funkce
    classSource = ""
    tempText = prototypeText
    while "):" in tempText:

        wholeName = getFunctionName(tempText)

        TYPE = wholeName[: wholeName.index(" ")+1]
        NAME = wholeName[wholeName.index(" ") + 1 :]

        classSource += TYPE + className + "::" + NAME

        classSource += getVariable(tempText, "):", "};") + "}\n\n"
        tempText = tempText[tempText.index("};") +1 : ]

    #konstruktor
    classSource += className + "::" + className + "(){\n"
    classSource += "this->ID = " + getVariable(prototypeText, "ID", ";") + ";\n"
    classSource += "this->functions = {"

    #pole existujicich funkci
    tempText = prototypeText
    while "):" in tempText:

        wholeName = getFunctionName(tempText)
        NAME = wholeName[wholeName.index(" ") + 1 : wholeName.index("(")]

        if NAME == "processOutput":
            tempText = tempText[tempText.index("};") +1 : ]
            continue

        classSource += "\"" + NAME + "\","
        tempText = tempText[tempText.index("};") +1 : ]

    classSource = classSource[:-1]
    classSource += "};"

    classSource += "\n}\n\n"

    #execute
    classSource += "void " + className + "::execute(Device * device, QString command){\n"
    tempText = prototypeText
    while "):" in tempText:

        wholeName = getFunctionName(tempText)
        NAME = wholeName[wholeName.index(" ") + 1 : wholeName.index("(")]

        if NAME == "processOutput":
            tempText = tempText[tempText.index("};") +1 : ]
            continue

        classSource += "if(command == \"" + NAME + "\"){    this->" + NAME + "(device);  }\n"
        tempText = tempText[tempText.index("};") +1 : ]

    classSource += "}\n\n"

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

    classSource += "this->name = \"" + className + "\";\n"

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
    driverNames = []

    for (dirpath, dirnames, filenames) in walk(pathDrivers):

        for f in filenames:
            driverProto = open(pathDrivers + "/" + f, "r")
            driverText = driverProto.read()
            makeDriverClassHeader(driverText, f)
            makeDriverClassSource(driverText, f)
            driverNames.append(f)

        break

    makeDriverLibraryConstructor(driverNames)

init()
devices()
drivers()
