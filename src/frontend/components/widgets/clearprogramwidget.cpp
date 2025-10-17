#include "clearprogramwidget.h"
#include <qicon.h>
#include <qpixmap.h>
#include <qpushbutton.h>

ClearProgramWidget::ClearProgramWidget(QWidget *parent) : QPushButton(parent) {
  QIcon icon = QIcon(":icons/clear_canvas.png");
  this->setIconSize(QSize(100, 100));
  this->setIcon(icon);
  this->setStyleSheet(R"(
    QPushButton {
        background-color: #E62727;       /* color de fondo */
    }
    QPushButton:hover {
        background-color: #FF3B3B;       /* al pasar el mouse */
    }
    QPushButton:pressed {
        background-color: #B81F1F;       /* al hacer clic */
    })");
}

void ClearProgramWidget::clearProgram(){
	emit clearSignal();
}
