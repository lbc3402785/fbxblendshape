#include "settings.h"
#include <QSettings>
#include <QDir>
#include <QStandardPaths>
Settings::Settings()
{
    loadSettings();
}

void Settings::loadSettings()
{
    QSettings settings(SETTINGS_FILE);
    expressionDir=settings.value("expressionDir", getDefaultExpressionDir()).toString();
    expressionList=settings.value("expressionList", getDefaultExpressionList()).toString();
    baseExpressionList=settings.value("baseExpressionList", getDefaultBaseExpressionList()).toString();
    outputDir=settings.value("outputDir", getDefaultOutputDir()).toString();
    count=settings.value("count", 16384).toInt();
    blendShapeName=settings.value("blendShapeName", getDefaultBlendShapeName()).toString();
    rangeMin=settings.value("rangeMin", 0.0f).toFloat();
    rangeMax=settings.value("rangeMax", 1.0f).toFloat();
}

QString Settings::getDefaultExpressionDir()
{
    return "E:\\model\\export_male";
}

QString Settings::getDefaultExpressionList()
{
    return "E:\\model\\output_male\\expressList.txt";
}

QString Settings::getDefaultBaseExpressionList()
{
    return "E:\\model\\output_male\\baseExpressList.txt";
}

QString Settings::getDefaultOutputDir()
{
    return "E:\\model\\output_male";
}

QString Settings::getDefaultBlendShapeName()
{
    return "Genesis8MaleBlendShapes";
}

float Settings::getRangeMax() const
{
    return rangeMax;
}

void Settings::setRangeMax(float value)
{
    rangeMax = value;
}

float Settings::getRangeMin() const
{
    return rangeMin;
}

void Settings::setRangeMin(float value)
{
    rangeMin = value;
}

QString Settings::getBaseExpressionList() const
{
    return baseExpressionList;
}

void Settings::setBaseExpressionList(const QString &value)
{
    baseExpressionList = value;
}

QString Settings::getBlendShapeName() const
{
    return blendShapeName;
}

void Settings::setBlendShapeName(const QString &value)
{
    blendShapeName = value;
}

int Settings::getCount() const
{
    return count;
}

void Settings::setCount(int value)
{
    count = value;
}

QString Settings::getExpressionList() const
{
    return expressionList;
}

void Settings::setExpressionList(const QString &value)
{
    expressionList = value;
}

QString Settings::getExpressionDir() const
{
    return expressionDir;
}

void Settings::setExpressionDir(const QString &value)
{
    expressionDir = value;
}

QString Settings::getOutputDir() const
{
    return outputDir;
}

void Settings::setOutputDir(const QString &value)
{
    outputDir = value;
}


void Settings::saveSettings()
{
    QSettings settings(SETTINGS_FILE);
    settings.setValue("expressionDir", expressionDir);
    settings.setValue("expressionList", expressionList);
    settings.setValue("outputDir", outputDir);
    settings.setValue("count", count);
    settings.setValue("blendShapeName", blendShapeName);
    settings.setValue("rangeMin", rangeMin);
    settings.setValue("rangeMax", rangeMax);
    settings.sync();
}

void Settings::reset()
{
    expressionDir=getDefaultExpressionDir();
    expressionList=getDefaultExpressionList();
    outputDir=getDefaultOutputDir();
    blendShapeName=getDefaultBlendShapeName();
    count=16384;
    rangeMin=0.0f;
    rangeMax=1.0f;
}


