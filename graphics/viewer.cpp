#include "viewer.h"
#include "GL/freeglut.h"
Viewer::Viewer()
{
    showSrc=true;
    showDst=true;
    scale=1.0f;
    srcPointSize=6;
    dstPointSize=2;
    stopDraw=false;
    initialized=false;
    srcMode=showMode::CONTOUR_LINE;
    dstMode=showMode::CONTOUR_LINE;
//    srcDefaultColor<<0,1,0;
    srcDefaultColor<<0.667,0.667,0.667;
    dstDefaultColor<<0.667,0.667,0.498;
    srcKeyColor<<0,0,1;
    dstKeyColor<<1,0,0;
    lineColor<<1, 0, 0;
    this->camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
    startAnimation();
}
Viewer::~Viewer()
{
    stopAnimation();
}



float Viewer::getScale() const
{
    return scale;
}

void Viewer::setScale(float value)
{
    scale = value;
}

Viewer::showMode Viewer::getDstMode() const
{
    return dstMode;
}

void Viewer::setDstMode(const showMode &value)
{
    dstMode = value;
    //emit dstShowModeChange();
}

Viewer::showMode Viewer::getSrcMode() const
{
    return srcMode;
}

void Viewer::setSrcMode(const showMode &value)
{
    srcMode = value;
    //emit srcShowModeChange();
}

std::map<int, int> Viewer::getPointsMap() const
{
    return pointsMap;
}

void Viewer::setPointsMap(const std::map<int, int> &value)
{
    pointsMap = value;
}

bool Viewer::getShowDst() const
{
    return showDst;
}

void Viewer::setShowDst(bool value)
{
    showDst = value;
}

std::vector<int> Viewer::getSrcKeyIds() const
{
    return srcKeyIds;
}

void Viewer::setSrcKeyIds(const std::vector<int> &value)
{
    srcKeyIds = value;
}

std::vector<int> Viewer::getDstKeyIds() const
{
    return dstKeyIds;
}

void Viewer::setDstKeyIds(const std::vector<int> &value)
{
    dstKeyIds = value;
}

bool Viewer::getShowSrc() const
{
    return showSrc;
}

void Viewer::setShowSrc(bool value)
{
    showSrc = value;
}

int Viewer::getSrcPointSize() const
{
    return srcPointSize;
}

void Viewer::setSrcPointSize(int value)
{
    srcPointSize = value;
}

int Viewer::getDstPointSize() const
{
    return dstPointSize;
}

void Viewer::setDstPointSize(int value)
{
    dstPointSize = value;
}

std::vector<int> Viewer::getSrcSelectIds() const
{
    return srcSelectIds;
}

void Viewer::setSrcSelectIds(const std::vector<int> &value)
{
    srcSelectIds = value;
}

std::vector<int> Viewer::getDstSelectIds() const
{
    return dstSelectIds;
}

void Viewer::setDstSelectIds(const std::vector<int> &value)
{
    dstSelectIds = value;
}
void Viewer::drawMesh(EigenMesh &mesh,Eigen::Vector3f defaultColor,Eigen::Vector3f keyColor,showMode mode,int pointSize,std::vector<int> selectIds,std::vector<int> keyIds)
{
    Eigen::Matrix3Xf points=mesh.getPoints();
    Eigen::Matrix3Xi& faces=mesh.getFaces();
    Eigen::Matrix3Xf& normals=mesh.getNormals();
    Eigen::Matrix4Xf& colors=mesh.getColors();
    Eigen::Matrix4Xi& polygons=mesh.getPolygons();
    bool hasColor=colors.size()>0;
    bool hasNormal=normals.size()>0;
    bool hasFaces=faces.size()>0;
    bool haPolygons=polygons.size()>0;
    if(points.size()==0)return;
    if((hasFaces||haPolygons)&&mode!=showMode::POINTS){
        bool needDrawFace=(mode==FACE||mode==FACE_CONTOUR_LINE/*||mode==CONTOUR_LINE*/);
        if(needDrawFace){
            //std::cout<<11<<std::endl<<std::flush;
            if(mode==FACE||mode==FACE_CONTOUR_LINE){
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            if(mesh.getPolygonMode()==EigenMesh::PolygonMode::Triangle){
                for(int i=0;i<faces.cols();++i){
                    int i0=faces(0,i);
                    int i1=faces(1,i);
                    int i2=faces(2,i);
                    Eigen::Vector4f colorAlpha(0,0,0,1);
                    if(!hasColor){
                        memcpy(colorAlpha.data(),defaultColor.data(),sizeof(float)*3);
                    }else{
                        colorAlpha=(colors.col(i0)/255+colors.col(i1)/255+colors.col(i2)/255)/3;
                    }

                    glColor4fv(colorAlpha.data());
                    glBegin(GL_TRIANGLES);
                    Eigen::Vector3f p0=points.col(i0)/scale;
                    Eigen::Vector3f p1=points.col(i1)/scale;
                    Eigen::Vector3f p2=points.col(i2)/scale;
                    if(hasNormal){
                        Eigen::Vector3f n0=normals.col(i0);
                        glNormal3fv(n0.data());
                        Eigen::Vector3f n1=normals.col(i1);
                        glNormal3fv(n1.data());
                        Eigen::Vector3f n2=normals.col(i2);
                        glNormal3fv(n2.data());
                    }
                    glVertex3fv(p0.data());
                    glVertex3fv(p1.data());
                    glVertex3fv(p2.data());

                    glEnd();
                }

            }
            else{
                for(int i=0;i<polygons.cols();++i){
                    int i0=polygons(0,i);
                    int i1=polygons(1,i);
                    int i2=polygons(2,i);
                    int i3=polygons(3,i);
                    Eigen::Vector4f colorAlpha(0,0,0,1);
                    if(!hasColor){
                        memcpy(colorAlpha.data(),defaultColor.data(),sizeof(float)*3);
                    }else{
                        colorAlpha=(colors.col(i0)/255+colors.col(i1)/255+colors.col(i2)/255+colors.col(i3)/255)/4;
                    }

                    glColor4fv(colorAlpha.data());
                    glBegin(GL_POLYGON);
                    Eigen::Vector3f p0=points.col(i0)/scale;
                    Eigen::Vector3f p1=points.col(i1)/scale;
                    Eigen::Vector3f p2=points.col(i2)/scale;
                    Eigen::Vector3f p3=points.col(i3)/scale;
                    if(hasNormal){
                        Eigen::Vector3f n0=normals.col(i0);
                        glNormal3fv(n0.data());
                        Eigen::Vector3f n1=normals.col(i1);
                        glNormal3fv(n1.data());
                        Eigen::Vector3f n2=normals.col(i2);
                        glNormal3fv(n2.data());
                        Eigen::Vector3f n3=normals.col(i3);
                        glNormal3fv(n3.data());
                    }
                    glVertex3fv(p0.data());
                    glVertex3fv(p1.data());
                    glVertex3fv(p2.data());
                    glVertex3fv(p3.data());
                    glEnd();
                }
            }
        }
        bool need_draw_contour_line=(mode==CONTOUR_LINE||mode==FACE_CONTOUR_LINE);
        if(need_draw_contour_line){
            glDisable(GL_LIGHTING);
            glEnable(GL_POLYGON_OFFSET_LINE);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3fv(defaultColor.data());
            glLineWidth(1.0f);
            glPolygonOffset(1.0, 1.0);

             //std::cout<<33<<std::endl<<std::flush;
            if(mesh.getPolygonMode()==EigenMesh::PolygonMode::Triangle){
                for(int i=0;i<faces.cols();++i){
                    int i0=faces(0,i);
                    int i1=faces(1,i);
                    int i2=faces(2,i);
                    glBegin(GL_TRIANGLES);
                    Eigen::Vector3f p0=points.col(i0)/scale;
                    Eigen::Vector3f p1=points.col(i1)/scale;
                    Eigen::Vector3f p2=points.col(i2)/scale;
                    if(hasNormal){
                        Eigen::Vector3f n0=normals.col(i0);
                        glNormal3fv(n0.data());
                        Eigen::Vector3f n1=normals.col(i1);
                        glNormal3fv(n1.data());
                        Eigen::Vector3f n2=normals.col(i2);
                        glNormal3fv(n2.data());
                    }
                    glVertex3fv(p0.data());
                    glVertex3fv(p1.data());
                    glVertex3fv(p2.data());
                    glEnd();
                }
            }else{
                for(int i=0;i<polygons.cols();++i){
                    int i0=polygons(0,i);
                    int i1=polygons(1,i);
                    int i2=polygons(2,i);
                    int i3=polygons(3,i);
                    glBegin(GL_TRIANGLES);
                    Eigen::Vector3f p0=points.col(i0)/scale;
                    Eigen::Vector3f p1=points.col(i1)/scale;
                    Eigen::Vector3f p2=points.col(i2)/scale;
                    Eigen::Vector3f p3=points.col(i3)/scale;
                    if(hasNormal){
                        Eigen::Vector3f n0=normals.col(i0);
                        glNormal3fv(n0.data());
                        Eigen::Vector3f n1=normals.col(i1);
                        glNormal3fv(n1.data());
                        Eigen::Vector3f n2=normals.col(i2);
                        glNormal3fv(n2.data());
                        Eigen::Vector3f n3=normals.col(i3);
                        glNormal3fv(n3.data());
                    }
                    glVertex3fv(p0.data());
                    glVertex3fv(p1.data());
                    glVertex3fv(p2.data());
                    glVertex3fv(p3.data());
                    glEnd();
                }
            }

            glEnable(GL_LIGHTING);
        }
    }
    else{
        glDisable(GL_LIGHTING);
        glPointSize(pointSize);
        glBegin(GL_POINTS);
        for(int i=0;i<points.cols();i++){
            bool skip=selectIds.size()>0;
            for(int j=0;j<selectIds.size();j++){
                int index=selectIds[j];
                if(index==i){
                    skip=false;
                    break;
                }
            }
            if(skip)continue;

            Eigen::Vector3f p=points.col(i);
            p/=scale;
            if(hasColor){
                Eigen::Vector4f c =colors.col(i);
                c/=255.0;
                glColor4fv(c.data());
            }else{
                glColor3fv(defaultColor.data());
            }
            glVertex3fv(p.data());
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
    glDisable(GL_LIGHTING);
    glPointSize(pointSize+3);
    glBegin(GL_POINTS);
    glColor3fv(keyColor.data());
    for(int j=0;j<keyIds.size();j++){
        int index=keyIds[j];
        Eigen::Vector3f p=points.col(index);
        p/=scale;
        glVertex3fv(p.data());
    }
    glEnd();
    glEnable(GL_LIGHTING);

}

void Viewer::drawMatchLine(EigenMesh &src, EigenMesh &dst, std::map<int, int> pointsMap, Eigen::Vector3f color)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(color.data());
    glLineWidth(2);
    Eigen::Matrix3Xf srcPoints=src.getPoints();
    Eigen::Matrix3Xf dstPoints=dst.getPoints();
    glBegin(GL_LINES);
    for( std::map<int,int>::const_iterator it = pointsMap.begin(); it != pointsMap.end(); ++it )
    {
        int srcIndex = it->first;
        int dstIndex = it->second;
        Eigen::Vector3f p1=srcPoints.col(srcIndex);
        p1/=scale;
        Eigen::Vector3f p2=dstPoints.col(dstIndex);
        p2/=scale;
        glVertex3fv(p1.data());
        glVertex3fv(p2.data());

    }
    glEnd();
}

void Viewer::setMaterialAndLight()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glPointSize(1);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_SMOOTH);
    float shine=100.0;
    float al=0.1f;
    float dl=0.8f;
    float sl=0.2f;

    float defaultAmbientColor[4] = {al,al,al,1.f};
    float defaultDiffuseColor[4] =  {dl,dl,dl,1.f};
    float defaultSpecularColor[4] = {sl,sl,sl,1.f};


    glMaterialfv(GL_FRONT, GL_AMBIENT,   defaultAmbientColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   defaultDiffuseColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  defaultSpecularColor);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shine);

    glLightfv(GL_LIGHT0, GL_AMBIENT, defaultAmbientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, defaultDiffuseColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, defaultSpecularColor);
    glLightfv(GL_LIGHT0, GL_SHININESS, &shine);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void Viewer::draw(){
    if(stopDraw)return;
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    preDraw();
    if(showSrc){

        drawMesh(srcMesh,srcDefaultColor,srcKeyColor,srcMode,srcPointSize,srcSelectIds,srcKeyIds);
    }
    if(showDst){

        drawMesh(dstMesh,dstDefaultColor,dstKeyColor,dstMode,dstPointSize,dstSelectIds,dstKeyIds);
    }
    if(pointsMap.size()>0&&showSrc&&showDst){
        drawMatchLine(srcMesh,dstMesh,pointsMap,lineColor);
    }
    postDraw();
}
void Viewer::init(){
    if(!initialized){
        setMaterialAndLight();
        initialized=true;
    }
    if(!stopDraw){
        update();
    }
}
