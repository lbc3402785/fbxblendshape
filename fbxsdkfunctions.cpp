#include "fbxsdkfunctions.h"
#include <QObject>
#include <iostream>
#include <fstream>
#include <QString>
#include <QFile>
#include <QTextStream>
FbxSDKFunctions::~FbxSDKFunctions()
{
    bool lResult;
    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);

}

bool FbxSDKFunctions::loadFbxFile(std::string filePath)
{
    FbxString lFilePath(filePath.c_str());
    bool lResult;
    if( lFilePath.IsEmpty() )
    {
        lResult = false;
        FBXSDK_printf("\n\nUsage: ImportScene <FBX file name>\n\n");
    }
    else
    {
        FBXSDK_printf("\n\nFile: %s\n\n", lFilePath.Buffer());
        lResult = LoadScene(lSdkManager, lScene, lFilePath.Buffer());
    }
    if(lResult){
        DisplayAnimation(lScene);
    }
    loaded=lResult;
    return lResult;
}

FbxSDKFunctions::FbxSDKFunctions()
{
    lSdkManager = NULL;
    lScene = NULL;
    model = NULL;
    count=sets.getCount();
    blendShapeName="Genesis8MaleBlendShapes";
    loaded=false;
    QString baseExpressionList=sets.getBaseExpressionList();
    loadDictionary(baseExpressionList,dictionary);
}

void FbxSDKFunctions::loadMesh(EigenMesh& mesh,const FbxMesh* base)
{
    if (base) {
        int lControlPointsCount = base->GetControlPointsCount();
        FbxVector4* baseModel = base->GetControlPoints();
        Eigen::Matrix3Xf& points=mesh.getPoints();
        points.resize(3,lControlPointsCount);
        for (int j = 0; j < lControlPointsCount; j++)
        {
            FbxVector4& pValue=baseModel[j];
            float x= (float)pValue[0];
            float y = (float)pValue[1];
            float z = (float)pValue[2];
            points.col(j)=Eigen::Vector3f(x,y,z);
        }
        Eigen::Matrix3Xi& faces=mesh.getFaces();
        Eigen::Matrix4Xi& polygons=mesh.getPolygons();
        for (int polyIndex = 0; polyIndex < base->GetPolygonCount(); ++polyIndex)
        {
            const auto polySize = base->GetPolygonSize(polyIndex);
            if(polySize==4){
                mesh.setPolygonMode(EigenMesh::PolygonMode::Quadri);
                polygons.resize(4,base->GetPolygonCount());
            }else{
                mesh.setPolygonMode(EigenMesh::PolygonMode::Triangle);
                faces.resize(3,base->GetPolygonCount());
            }
            for (int polyVertIndex = 0; polyVertIndex < polySize; ++polyVertIndex) {
                if(polySize==4){
                    polygons(polyVertIndex,polyIndex)=base->GetPolygonVertex(polyIndex, polyVertIndex);
                }else{
                    faces(polyVertIndex,polyIndex)=base->GetPolygonVertex(polyIndex, polyVertIndex);
                }
            }
        }
        FbxLayerElementArrayTemplate<FbxVector4>* lNormals = NULL;
        bool lStatus = base->GetNormals(&lNormals);
        if(lStatus&&lNormals&&lNormals->GetCount()==lControlPointsCount){
            Eigen::Matrix3Xf& normals=mesh.getNormals();
            normals.resize(3,lControlPointsCount);
            for (int j = 0; j < lControlPointsCount; j++){
                const FbxVector4& nValue=lNormals->GetAt(j);
                float x= (float)nValue[0];
                float y = (float)nValue[1];
                float z = (float)nValue[2];
                normals.col(j)=Eigen::Vector3f(x,y,z);
            }
        }
    }

}

void FbxSDKFunctions::loadMesh(EigenMesh &mesh, const FbxShape *shape)
{
    if (shape) {
        int lControlPointsCount = shape->GetControlPointsCount();
        FbxVector4* baseModel = shape->GetControlPoints();
        Eigen::Matrix3Xf& points=mesh.getPoints();
        points.resize(3,lControlPointsCount);
        for (int j = 0; j < lControlPointsCount; j++)
        {
            FbxVector4& pValue=baseModel[j];
            float x= (float)pValue[0];
            float y = (float)pValue[1];
            float z = (float)pValue[2];
            points.col(j)=Eigen::Vector3f(x,y,z);
        }

        FbxLayerElementArrayTemplate<FbxVector4>* lNormals = NULL;
        bool lStatus = shape->GetNormals(&lNormals);
        if(lStatus&&lNormals&&lNormals->GetCount()==lControlPointsCount){
            Eigen::Matrix3Xf& normals=mesh.getNormals();
            normals.resize(3,lControlPointsCount);
            for (int j = 0; j < lControlPointsCount; j++){
                const FbxVector4& nValue=lNormals->GetAt(j);
                float x= (float)nValue[0];
                float y = (float)nValue[1];
                float z = (float)nValue[2];
                normals.col(j)=Eigen::Vector3f(x,y,z);
            }
        }
    }

}

void FbxSDKFunctions::loadDictionary(QString path,std::map<std::string, std::string> &map)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> result;
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        std::cout<<line.toStdString()<<std::endl<<std::flush;
        std::pair<std::string,std::string> pair=std::make_pair(line.toStdString(),line.toStdString());
        map.insert(pair);
        line = in.readLine();
    }
}
// to get a string from the node default translation values
FbxString GetDefaultTranslationInfo(
                                  const FbxNode* pNode
                                  )
{
    FbxVector4 v4;
    v4 = ((FbxNode*)pNode)->LclTranslation.Get();

    return FbxString("Translation (X,Y,Z): ") + FbxString(v4[0]) + ", " + FbxString(v4[1]) + ", " + FbxString(v4[2]);
}
// to get a string from the node visibility value
FbxString GetNodeVisibility(
                          const FbxNode* pNode
                          )
{
    return FbxString("Visibility: ") + (pNode->GetVisibility() ? "Yes":"No");
}
void Add_TreeViewItem_KFbxNode_Parameters(FbxNode *pNode,TreeModel* model,TreeItem* parent){
    if(pNode == NULL||model==NULL) return;
    model->insertTreeViewItem(parent,{GetDefaultTranslationInfo(pNode).Buffer()});
    model->insertTreeViewItem(parent,{GetNodeVisibility(pNode).Buffer()});
}
void FbxSDKFunctions::DisplayAnimation(FbxScene* pScene)
{
    int i;
    for (i = 0; i < pScene->GetSrcObjectCount<FbxAnimStack>(); i++)
    {
        FbxAnimStack* lAnimStack = pScene->GetSrcObject<FbxAnimStack>(i);
        FbxString lOutputString = "Animation Stack Name: ";
        lOutputString += lAnimStack->GetName();
        lOutputString += "\n";
        FBXSDK_printf(lOutputString);
        DisplayAnimation(lAnimStack, pScene->GetRootNode());
    }
}

void FbxSDKFunctions::DisplayAnimation(FbxAnimStack *pAnimStack, FbxNode *pNode, bool isSwitcher,TreeItem* parent)
{
    int l;
    int nbAnimLayers = pAnimStack->GetMemberCount<FbxAnimLayer>();
    int nbAudioLayers = pAnimStack->GetMemberCount<FbxAudioLayer>();

    for (l = 0; l < nbAnimLayers; l++)
    {
        FbxAnimLayer* lAnimLayer = pAnimStack->GetMember<FbxAnimLayer>(l);
        DisplayAnimation(lAnimLayer, pNode, isSwitcher,parent);
    }

    for (l = 0; l < nbAudioLayers; l++)
    {
        FbxAudioLayer* lAudioLayer = pAnimStack->GetMember<FbxAudioLayer>(l);
        DisplayAnimation(lAudioLayer, isSwitcher);
    }
}
FbxString GetNodeNameAndAttributeTypeName(const FbxNode* pNode)
{
    FbxString s = pNode->GetName();

    FbxNodeAttribute::EType lAttributeType;

    if(pNode->GetNodeAttribute() == NULL)
    {
        s += " (No node attribute type)";
    }
    else
    {
        lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

        switch (lAttributeType)
        {
        case FbxNodeAttribute::eMarker:                s += " (Marker)";               break;
        case FbxNodeAttribute::eSkeleton:              s += " (Skeleton)";             break;
        case FbxNodeAttribute::eMesh:                  s += " (Mesh)";                 break;
        case FbxNodeAttribute::eCamera:                s += " (Camera)";               break;
        case FbxNodeAttribute::eLight:                 s += " (Light)";                break;
        case FbxNodeAttribute::eBoundary:              s += " (Boundary)";             break;
        case FbxNodeAttribute::eOpticalMarker:        s += " (Optical marker)";       break;
        case FbxNodeAttribute::eOpticalReference:     s += " (Optical reference)";    break;
        case FbxNodeAttribute::eCameraSwitcher:       s += " (Camera switcher)";      break;
        case FbxNodeAttribute::eNull:                  s += " (Null)";                 break;
        case FbxNodeAttribute::ePatch:                 s += " (Patch)";                break;
        case FbxNodeAttribute::eNurbs:                  s += " (NURB)";                 break;
        case FbxNodeAttribute::eNurbsSurface:         s += " (Nurbs surface)";        break;
        case FbxNodeAttribute::eNurbsCurve:           s += " (NURBS curve)";          break;
        case FbxNodeAttribute::eTrimNurbsSurface:    s += " (Trim nurbs surface)";   break;
        case FbxNodeAttribute::eUnknown:          s += " (Unidentified)";         break;
        }
    }

    return s;
}
void DisplayCurveKeys(FbxAnimCurve* pCurve){

}
void DisplayListCurveKeys(FbxAnimCurve* pCurve, FbxProperty* pProperty){

}
void FbxSDKFunctions::DisplayAnimation(FbxAnimLayer *pAnimLayer, FbxNode *pNode, bool isSwitcher,TreeItem* parent)
{
    int lModelCount;
   FbxString lOutputString;
   TreeItem* curParent=NULL;
   if(model){
       if(!parent){
           curParent=model->insertTreeViewItem({QObject::tr(pNode->GetName())});
       }else{
           curParent=model->insertTreeViewItem(parent,{QObject::tr(GetNodeNameAndAttributeTypeName(pNode))});
           Add_TreeViewItem_KFbxNode_Parameters(pNode,model,curParent);
       }

       //std::cout<<"append child :"<<QObject::tr(pNode->GetName()).toStdString()<<std::endl<<std::flush;
   }
   DisplayChannels(pNode, pAnimLayer, DisplayCurveKeys, DisplayListCurveKeys, isSwitcher);

   for(lModelCount = 0; lModelCount < pNode->GetChildCount(); lModelCount++)
   {
       DisplayAnimation(pAnimLayer, pNode->GetChild(lModelCount), isSwitcher,curParent);
   }
}

void FbxSDKFunctions::DisplayAnimation(FbxAudioLayer *pAudioLayer, bool isSwitcher)
{

}

void FbxSDKFunctions::DisplayChannels(FbxNode* pNode, FbxAnimLayer* pAnimLayer, void (*DisplayCurve) (FbxAnimCurve* pCurve), void (*DisplayListCurve) (FbxAnimCurve* pCurve, FbxProperty* pProperty), bool isSwitcher)
{
    FbxAnimCurve* lAnimCurve = NULL;

    // Display general curves.
    if (!isSwitcher)
    {
        lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }

        lAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }

        lAnimCurve = pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
    }

    // Display curves specific to a light or marker.
    FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

    if (lNodeAttribute)
    {
        lAnimCurve = lNodeAttribute->Color.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COLOR_RED);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = lNodeAttribute->Color.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COLOR_GREEN);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }
        lAnimCurve = lNodeAttribute->Color.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COLOR_BLUE);
        if (lAnimCurve)
        {
            DisplayCurve(lAnimCurve);
        }

        // Display curves specific to a light.
        FbxLight* light = pNode->GetLight();
        if (light)
        {
            lAnimCurve = light->Intensity.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Intensity\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = light->OuterAngle.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Outer Angle\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = light->Fog.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Fog\n");
                DisplayCurve(lAnimCurve);
            }
        }

        // Display curves specific to a camera.
        FbxCamera* camera = pNode->GetCamera();
        if (camera)
        {
            lAnimCurve = camera->FieldOfView.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Field of View\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = camera->FieldOfViewX.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Field of View X\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = camera->FieldOfViewY.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Field of View Y\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = camera->OpticalCenterX.GetCurve(pAnimLayer);
            if (lAnimCurve)
            {
                FBXSDK_printf("        Optical Center X\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = camera->OpticalCenterY.GetCurve(pAnimLayer);
            if(lAnimCurve)
            {
                FBXSDK_printf("        Optical Center Y\n");
                DisplayCurve(lAnimCurve);
            }

            lAnimCurve = camera->Roll.GetCurve(pAnimLayer);
            if(lAnimCurve)
            {
                FBXSDK_printf("        Roll\n");
                DisplayCurve(lAnimCurve);
            }
        }

        // Display curves specific to a geometry.
        if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh ||
            lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs ||
            lNodeAttribute->GetAttributeType() == FbxNodeAttribute::ePatch)
        {
            FbxGeometry* lGeometry = (FbxGeometry*) lNodeAttribute;

            int lBlendShapeDeformerCount = lGeometry->GetDeformerCount(FbxDeformer::eBlendShape);
            for(int lBlendShapeIndex = 0; lBlendShapeIndex<lBlendShapeDeformerCount; ++lBlendShapeIndex)
            {
                FbxBlendShape* lBlendShape = (FbxBlendShape*)lGeometry->GetDeformer(lBlendShapeIndex, FbxDeformer::eBlendShape);
                if(std::string(lBlendShape->GetName())!=blendShapeName){
                    continue;
                }
                FbxGeometry* Geom = lBlendShape->GetGeometry();
                DisplayShape(Geom);
            }
        }
    }

    // Display curves specific to properties
    FbxProperty lProperty = pNode->GetFirstProperty();
    while (lProperty.IsValid())
    {
        if (lProperty.GetFlag(FbxPropertyFlags::eUserDefined))
        {
            FbxString lFbxFCurveNodeName  = lProperty.GetName();
            FbxAnimCurveNode* lCurveNode = lProperty.GetCurveNode(pAnimLayer);

            if (!lCurveNode){
                lProperty = pNode->GetNextProperty(lProperty);
                continue;
            }

            FbxDataType lDataType = lProperty.GetPropertyDataType();
            if (lDataType.GetType() == eFbxBool || lDataType.GetType() == eFbxDouble || lDataType.GetType() == eFbxFloat || lDataType.GetType() == eFbxInt)
            {
                FbxString lMessage;

                lMessage =  "        Property ";
                lMessage += lProperty.GetName();
                if (lProperty.GetLabel().GetLen() > 0)
                {
                    lMessage += " (Label: ";
                    lMessage += lProperty.GetLabel();
                    lMessage += ")";
                };


                for( int c = 0; c < lCurveNode->GetCurveCount(0U); c++ )
                {
                    lAnimCurve = lCurveNode->GetCurve(0U, c);
                    if (lAnimCurve)
                        DisplayCurve(lAnimCurve);
                }
            }
            else if(lDataType.GetType() == eFbxDouble3 || lDataType.GetType() == eFbxDouble4 || lDataType.Is(FbxColor3DT) || lDataType.Is(FbxColor4DT))
            {

                for( int c = 0; c < lCurveNode->GetCurveCount(0U); c++ )
                {
                    lAnimCurve = lCurveNode->GetCurve(0U, c);
                    if (lAnimCurve)
                    {
                        DisplayCurve(lAnimCurve);
                    }
                }

                for( int c = 0; c < lCurveNode->GetCurveCount(1U); c++ )
                {
                    lAnimCurve = lCurveNode->GetCurve(1U, c);
                    if (lAnimCurve)
                    {
                        DisplayCurve(lAnimCurve);
                    }
                }

                for( int c = 0; c < lCurveNode->GetCurveCount(2U); c++ )
                {
                    lAnimCurve = lCurveNode->GetCurve(2U, c);
                    if (lAnimCurve)
                    {
                        DisplayCurve(lAnimCurve);
                    }
                }
            }
            else if (lDataType.GetType() == eFbxEnum)
            {

                for( int c = 0; c < lCurveNode->GetCurveCount(0U); c++ )
                {
                    lAnimCurve = lCurveNode->GetCurve(0U, c);
                    if (lAnimCurve)
                        DisplayListCurve(lAnimCurve, &lProperty);
                }
            }
        }

        lProperty = pNode->GetNextProperty(lProperty);
    } // while

}

void FbxSDKFunctions::DisplayShape(FbxGeometry* pGeometry)
{
    int lBlendShapeCount, lBlendShapeChannelCount, lTargetShapeCount;
    FbxBlendShape* lBlendShape;
    FbxBlendShapeChannel* lBlendShapeChannel;
    FbxShape* lShape;

    lBlendShapeCount = pGeometry->GetDeformerCount(FbxDeformer::eBlendShape);
    for (int lBlendShapeIndex = 0; lBlendShapeIndex < lBlendShapeCount; ++lBlendShapeIndex)
    {
        lBlendShape = (FbxBlendShape*) pGeometry->GetDeformer(lBlendShapeIndex, FbxDeformer::eBlendShape);
        lBlendShapeChannelCount = lBlendShape->GetBlendShapeChannelCount();
        std::cout <<"lBlendShapeChannelCount:" << lBlendShapeChannelCount << std::endl;
        const FbxMesh* base=NULL;
        names.clear();
        for(int lBlendShapeChannelIndex = 0;  lBlendShapeChannelIndex < lBlendShapeChannelCount; ++lBlendShapeChannelIndex)
        {
            lBlendShapeChannel = lBlendShape->GetBlendShapeChannel(lBlendShapeChannelIndex);
            lTargetShapeCount = lBlendShapeChannel->GetTargetShapeCount();
            for (int lTargetShapeIndex = 0; lTargetShapeIndex < lTargetShapeCount; ++lTargetShapeIndex)
            {
                lShape = lBlendShapeChannel->GetTargetShape(lTargetShapeIndex);
                int lControlPointsCount = lShape->GetControlPointsCount();
                if(lControlPointsCount != count)continue;
                std::string filename =std::string(lShape->GetName());
                //if (filename.find("HD") != std::string::npos)continue;
                if(dictionary.find(filename)==dictionary.end())continue;
                //if (filename.find("HD") != std::string::npos|| filename.find("Tongue") != std::string::npos || filename.find("EyesCrossed") != std::string::npos || filename.find("EyesClosed") != std::string::npos || filename.find("EyesClosedR") != std::string::npos || filename.find("EyesCrossedL") != std::string::npos)continue;
                std::cout<<filename<<std::endl<<std::flush;
                std::vector<std::vector<int> > polygons;
                names.push_back(filename);
                if(!base){
                    base= static_cast<FbxMesh*>(lShape->GetBaseGeometry());
                    loadMesh(baseMesh,base);
                }
                EigenMesh mesh;
                loadMesh(mesh,lShape);
                if(base){
                    mesh.setPolygonMode(baseMesh.getPolygonMode());
                    mesh.setFaces(baseMesh.getFaces());
                    mesh.setPolygons(baseMesh.getPolygons());
                }
                targetShapes.push_back(mesh);
                //if (filename.find("HD") != std::string::npos|| filename.find("Tongue") != std::string::npos || filename.find("EyesCrossed") != std::string::npos || filename.find("EyesClosed") != std::string::npos || filename.find("EyesClosedR") != std::string::npos || filename.find("EyesCrossedL") != std::string::npos)continue;
            }

        }
    }
}

std::vector<std::string> FbxSDKFunctions::getNames() const
{
    return names;
}

void FbxSDKFunctions::setNames(const std::vector<std::string> &value)
{
    names = value;
}

bool FbxSDKFunctions::getLoaded() const
{
    return loaded;
}

void FbxSDKFunctions::setLoaded(bool value)
{
    loaded = value;
}

std::vector<EigenMesh> FbxSDKFunctions::getTargetShapes() const
{
    return targetShapes;
}

void FbxSDKFunctions::setTargetShapes(const std::vector<EigenMesh> &value)
{
    targetShapes = value;
}

EigenMesh FbxSDKFunctions::getBaseMesh() const
{
    return baseMesh;
}

void FbxSDKFunctions::setBaseMesh(const EigenMesh &value)
{
    baseMesh = value;
}



TreeModel *FbxSDKFunctions::getModel() const
{
    return model;
}

void FbxSDKFunctions::setModel(TreeModel *value)
{
    model = value;
}

