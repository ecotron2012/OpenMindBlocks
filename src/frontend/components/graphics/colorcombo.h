#include <QComboBox>
#include <QVBoxLayout>
#include <QVariant>
#include "colordelegate.h"

static void addColorItem(QComboBox* cb, const QColor& color) {
    cb->addItem(QString()); 
    int row = cb->count() - 1;
    cb->setItemData(row, color, Qt::UserRole);
    cb->setItemData(row, color.name(QColor::HexRgb), Qt::ToolTipRole);
}

QComboBox* createColorCombo(QWidget* parent = nullptr) {
    auto* cb = new QComboBox(parent);
    cb->setItemDelegate(new ColorDelegate(cb));
    cb->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    addColorItem(cb, QColor("#e53935")); // rojo
    addColorItem(cb, QColor("#8e24aa")); // púrpura
    addColorItem(cb, QColor("#3949ab")); // azul
    addColorItem(cb, QColor("#1e88e5")); // celeste
    addColorItem(cb, QColor("#43a047")); // verde
    addColorItem(cb, QColor("#fdd835")); // amarillo
    addColorItem(cb, QColor("#fb8c00")); // naranjo
    addColorItem(cb, QColor("#6d4c41")); // café
    addColorItem(cb, QColor("#546e7a")); // gris azulado

    cb->setCurrentIndex(0);
    return cb;
}
