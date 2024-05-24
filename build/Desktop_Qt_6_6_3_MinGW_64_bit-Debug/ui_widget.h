/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *fractalLabel;
    QLabel *toolBar;
    QCheckBox *zoomBox;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        Widget->setMinimumSize(QSize(800, 0));
        fractalLabel = new QLabel(Widget);
        fractalLabel->setObjectName("fractalLabel");
        fractalLabel->setEnabled(true);
        fractalLabel->setGeometry(QRect(0, 30, 800, 600));
        toolBar = new QLabel(Widget);
        toolBar->setObjectName("toolBar");
        toolBar->setGeometry(QRect(0, 0, 800, 30));
        zoomBox = new QCheckBox(Widget);
        zoomBox->setObjectName("zoomBox");
        zoomBox->setGeometry(QRect(670, 0, 81, 27));
        zoomBox->setChecked(true);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        fractalLabel->setText(QString());
        toolBar->setText(QString());
        zoomBox->setText(QCoreApplication::translate("Widget", "ZoomBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
