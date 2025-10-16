#include <QStyledItemDelegate>
#include <QPainter>

class ColorSwatchDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QSize sizeHint(const QStyleOptionViewItem& opt, const QModelIndex& idx) const override {
        Q_UNUSED(idx);
        return QSize(36, 28); 
    }

    void paint(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const override {
        p->save();
        QStyleOptionViewItem o(opt);
        o.text.clear(); 
        opt.widget->style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &o, p, opt.widget);

        QColor c = idx.data(Qt::UserRole).value<QColor>();
        QRect r = opt.rect.adjusted(6, 4, -6, -4);
        p->setRenderHint(QPainter::Antialiasing, true);
        p->setPen(QPen(Qt::black, 1));
        p->setBrush(c);
        p->drawRoundedRect(r, 4, 4);

        p->restore();
    }
};
