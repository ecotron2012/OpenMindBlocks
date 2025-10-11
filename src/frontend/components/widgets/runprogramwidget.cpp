#include "runprogramwidget.h"
#include <qicon.h>
#include <qpixmap.h>
#include <qpushbutton.h>

RunProgramWidget::RunProgramWidget(QWidget *parent) : QPushButton(parent) {
  QIcon icon = QIcon(":icons/run_program.png");
  this->setIconSize(QSize(100, 100));
  this->setIcon(icon);
  this->setStyleSheet(R"(
    QPushButton {
        background-color: #34B4FB;       /* color de fondo */
    }
    QPushButton:hover {
        background-color: #2F95E9;       /* al pasar el mouse */
    }
    QPushButton:pressed {
        background-color: #2776D3;       /* al hacer clic */
    })");
}

void RunProgramWidget::runProgram(){
	emit execute();
}
