#ifndef VIEWER_H
#define VIEWER_H
#include <QGLViewer/qglviewer.h>
#include "eigenmesh.h"
class Viewer : public QGLViewer
{
public:
    Viewer();
    ~Viewer();
    virtual void draw();
    virtual void init();
    bool stopDraw;
    enum showMode{POINTS,FACE,CONTOUR_LINE,FACE_CONTOUR_LINE};


    float getScale() const;
    void setScale(float value);
    bool showSrc,showDst;
    EigenMesh srcMesh,dstMesh;
    showMode srcMode;
    showMode dstMode;
    Eigen::Vector3f lineColor;
    Eigen::Vector3f srcDefaultColor;
    Eigen::Vector3f dstDefaultColor;
    Eigen::Vector3f srcKeyColor;
    Eigen::Vector3f dstKeyColor;
    std::map<int,int>pointsMap;
    int getSrcPointSize() const;
    void setSrcPointSize(int value);

    int getDstPointSize() const;
    void setDstPointSize(int value);

    std::vector<int> getSrcSelectIds() const;
    void setSrcSelectIds(const std::vector<int> &value);

    std::vector<int> getDstSelectIds() const;
    void setDstSelectIds(const std::vector<int> &value);

    bool getShowSrc() const;
    void setShowSrc(bool value);

    bool getShowDst() const;
    void setShowDst(bool value);

    std::vector<int> getSrcKeyIds() const;
    void setSrcKeyIds(const std::vector<int> &value);

    std::vector<int> getDstKeyIds() const;
    void setDstKeyIds(const std::vector<int> &value);

    std::map<int, int> getPointsMap() const;
    void setPointsMap(const std::map<int, int> &value);
    std::vector<int> srcSelectIds;
    std::vector<int> srcKeyIds;
    std::vector<int> dstSelectIds;
    std::vector<int> dstKeyIds;
    showMode getSrcMode() const;
    void setSrcMode(const showMode &value);

    showMode getDstMode() const;
    void setDstMode(const showMode &value);

private:

    bool initialized;
    float scale;
    int srcPointSize;
    int dstPointSize;


    void drawMesh(EigenMesh& mesh,Eigen::Vector3f defaultColor,Eigen::Vector3f keyColor,showMode mode,int pointSize,std::vector<int> selectIds,std::vector<int> keyIds);
    void drawMatchLine(EigenMesh& src,EigenMesh& dst,std::map<int,int> pointsMap,Eigen::Vector3f color);
    void setMaterialAndLight();
//signals:
//    void srcShowModeChange();
//    void dstShowModeChange();

};

#endif // VIEWER_H
