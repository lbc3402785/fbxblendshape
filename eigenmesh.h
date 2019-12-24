#ifndef EIGENMESH_H
#define EIGENMESH_H
#include <Eigen/Dense>

class EigenMesh
{
public:
    EigenMesh();
    Eigen::Matrix3Xf& getPoints();
    Eigen::Matrix3Xf getPoints() const;
    void setPoints(const Eigen::Matrix3Xf &value);
    Eigen::Matrix3Xf& getNormals();
    //Eigen::Matrix3Xf getNormals() const;
    void setNormals(const Eigen::Matrix3Xf &value);

    //Eigen::Matrix3Xi getFaces() const;
    Eigen::Matrix3Xi& getFaces();
    void setFaces(const Eigen::Matrix3Xi &value);
    Eigen::Matrix4Xf& getColors();
    //Eigen::Matrix4Xf getColors() const;
    void setColors(const Eigen::Matrix4Xf &value);
    enum PolygonMode{Triangle,Quadri};
    PolygonMode getPolygonMode() const;
    void setPolygonMode(const PolygonMode &value);
    Eigen::Matrix4Xi& getPolygons();
    //Eigen::Matrix4Xi getPolygons() const;
    void setPolygons(const Eigen::Matrix4Xi &value);

private:
    Eigen::Matrix3Xf points;
    Eigen::Matrix3Xf normals;
    Eigen::Matrix3Xi faces;
    Eigen::Matrix4Xi polygons;
    Eigen::Matrix4Xf colors;
    PolygonMode polygonMode;
};

#endif // EIGENMESH_H
