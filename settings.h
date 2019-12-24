#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>

const QString SETTINGS_FILE{"FbxConfig"};
class Settings
{
public:
    static Settings& instance() {static Settings obj; return obj; }
    void saveSettings();
    void reset();
    QString getOutputDir() const;
    void setOutputDir(const QString &value);
    QString getExpressionDir() const;
    void setExpressionDir(const QString &value);

    QString getExpressionList() const;
    void setExpressionList(const QString &value);
    int getCount() const;
    void setCount(int value);

    QString getBlendShapeName() const;
    void setBlendShapeName(const QString &value);

    QString getBaseExpressionList() const;
    void setBaseExpressionList(const QString &value);

    float getRangeMin() const;
    void setRangeMin(float value);

    float getRangeMax() const;
    void setRangeMax(float value);

private:
    Settings();
    void loadSettings();
    QString getDefaultExpressionDir();
    QString getDefaultExpressionList();
    QString getDefaultBaseExpressionList();
    QString getDefaultOutputDir();
    QString getDefaultBlendShapeName();
    QString expressionDir;
    QString expressionList;
    QString baseExpressionList;
    QString outputDir;
    QString blendShapeName;
    float rangeMin;
    float rangeMax;
    int count;
};

#endif // SETTINGS_H
