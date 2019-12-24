#include "eigenmesh.h"

EigenMesh::EigenMesh()
{

}

Eigen::Matrix3Xf &EigenMesh::getPoints()
{
    return points;
}

Eigen::Matrix3Xf EigenMesh::getPoints() const
{
    return points;
}

void EigenMesh::setPoints(const Eigen::Matrix3Xf &value)
{
    points = value;
}

Eigen::Matrix3Xf &EigenMesh::getNormals()
{
    return normals;
}

//Eigen::Matrix3Xf EigenMesh::getNormals() const
//{
//    return normals;
//}

void EigenMesh::setNormals(const Eigen::Matrix3Xf &value)
{
    normals = value;
}

//Eigen::Matrix3Xi EigenMesh::getFaces() const
//{
//    return faces;
//}

Eigen::Matrix3Xi &EigenMesh::getFaces()
{
    return faces;
}

void EigenMesh::setFaces(const Eigen::Matrix3Xi &value)
{
    faces = value;
}

Eigen::Matrix4Xf &EigenMesh::getColors()
{
    return colors;
}

//Eigen::Matrix4Xf EigenMesh::getColors() const
//{
//    return colors;
//}

void EigenMesh::setColors(const Eigen::Matrix4Xf &value)
{
    colors = value;
}

EigenMesh::PolygonMode EigenMesh::getPolygonMode() const
{
    return polygonMode;
}

void EigenMesh::setPolygonMode(const PolygonMode &value)
{
    polygonMode = value;
}

Eigen::Matrix4Xi &EigenMesh::getPolygons()
{
    return polygons;
}

//Eigen::Matrix4Xi EigenMesh::getPolygons() const
//{
//    return polygons;
//}

void EigenMesh::setPolygons(const Eigen::Matrix4Xi &value)
{
    polygons = value;
}
