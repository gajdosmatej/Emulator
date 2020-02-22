#include "classes.h"

//iniciace portu
Controller::Controller(Editor * editor, Compiler * comp){

    for(int i = 0; i < this->portsNumber; ++i){ this->PORTS.push_back(new Port);   }

    this->window = editor;
    this->compiler = comp;
	this->driverLibrary = new DriverLibrary(this);
}

void Controller::loadText(){

    QString code = this->window->getText();
    this->compiler->validate(code);
}


Port::Port()
{

}
