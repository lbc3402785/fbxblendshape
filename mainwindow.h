#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphics/viewer.h"
#include "settings.h"
#include "src/NumpyUtil.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_load_clicked();

    void on_save_clicked();

    void on_setting_triggered();
    void setBlendShapeWeight1(int value);
    void setBlendShapeWeight2(int value);
    void setBlendShapeWeight3(int value);
    void setBlendShapeWeight4(int value);
    void setBlendShapeWeight5(int value);
    void setBlendShapeWeight6(int value);
    void setBlendShapeWeight7(int value);
    void setBlendShapeWeight8(int value);
    void setBlendShapeWeight9(int value);
    void setBlendShapeWeight10(int value);
    void updateMesh();
    void on_actionPOINTS_triggered();

    void on_actionFACE_triggered();

    void on_actionCONTOUR_LINE_triggered();

    void on_actionFACE_CONTOUR_LINE_triggered();

private:
    Ui::MainWindow *ui;
    Viewer* modelViewer;
    MatF blendShapes;
    MatF baseShape;
    MatF EX;
    Eigen::Matrix4Xi polygons;
    bool hasBlendShapes;
    float min;
    float max;
    Settings &sets=Settings::instance();
    float computeRangeValue(int value);
};

#endif // MAINWINDOW_H
