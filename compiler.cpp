#include "classes.h"


Compiler::Compiler(Editor * editor){

    this->window = editor;
    this->window->readOnly();

}

void Compiler::validate(QString &code){

    if(this->controller->driverLibrary->existCommand(2, code)){
	QString text = "yes";
		this->window->setText(text);
    this->controller->driverLibrary->doCommand(2, code);
	}else
		this->window->setText(code);

}
