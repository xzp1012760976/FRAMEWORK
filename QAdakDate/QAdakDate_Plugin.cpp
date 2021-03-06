#include <QtPlugin>
#include "QAdakDate.h"
#include "QAdakDate_Plugin.h"

#include "../UTILS/mali_yil.cpp"

QAdakDate_Plugin::QAdakDate_Plugin(QObject * parent) : QObject(parent)
{
    initialized = false;
}

void QAdakDate_Plugin::initialize(QDesignerFormEditorInterface * )
{
    if (initialized) {
        return;
    }
    initialized = true;
}

bool QAdakDate_Plugin::isInitialized() const
{
    return initialized;
}

QWidget * QAdakDate_Plugin::createWidget(QWidget *parent)
{
    return new QAdakDate(parent);
}

QString QAdakDate_Plugin::name() const
{
    return "QAdakDate";
}

QString QAdakDate_Plugin::group() const
{
    return "Input Widgets";
}

QIcon QAdakDate_Plugin::icon() const
{
    return QIcon();
}

QString QAdakDate_Plugin::toolTip() const
{
    return "Tarih";
}

QString QAdakDate_Plugin::whatsThis() const
{
    return "";
}

bool QAdakDate_Plugin::isContainer() const
{
    return false;
}

QString QAdakDate_Plugin::domXml() const
{
    return "<widget class=\"QAdakDate\" name=\"adakDate\">\n"
            " <property name=\"QAdakDate\">\n"
            "  <rect>\n"
            "   <x>0</x>\n"
            "   <y>0</y>\n"
            "   <width>100</width>\n"
            "   <height>100</height>\n"
            "  </rect>\n"
            " </property>\n"
            " <property name=\"whatsThis\" >\n"
            "  <string>Tarih Widgeti</string>\n"
            " </property>\n"
            "</widget>\n";

}

QString QAdakDate_Plugin::includeFile() const
{
        return "QAdakDate.h";
}

Q_EXPORT_PLUGIN2(QAdakDate, QAdakDate_Plugin)
