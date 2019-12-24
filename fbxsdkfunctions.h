#ifndef FBXSDKFUNCTIONS_H
#define FBXSDKFUNCTIONS_H
#include <fbxsdk.h>
#include "Common/Common.h"
#include <string>
#include <vector>
#include <map>
#include "ui/treemodel.h"
#include "ui/treeitem.h"
#include "eigenmesh.h"
#include "settings.h"
class FbxSDKFunctions
{
public:
    static FbxSDKFunctions& instance(){
        static FbxSDKFunctions instance;
        // Prepare the FBX SDK.
        InitializeSdkObjects(instance.lSdkManager, instance.lScene);
        return instance;
    }
    ~FbxSDKFunctions();
    bool loadFbxFile(std::string filePath);

    TreeModel *getModel() const;
    void setModel(TreeModel *value);

    EigenMesh getBaseMesh() const;
    void setBaseMesh(const EigenMesh &value);

    std::vector<EigenMesh> getTargetShapes() const;
    void setTargetShapes(const std::vector<EigenMesh> &value);

    bool getLoaded() const;
    void setLoaded(bool value);

    std::vector<std::string> getNames() const;
    void setNames(const std::vector<std::string> &value);

private:
    FbxSDKFunctions();
    void loadMesh(EigenMesh& mesh,const FbxMesh* base);
    void loadMesh(EigenMesh& mesh,const FbxShape* shape);
    void loadDictionary(QString path,std::map<std::string,std::string>& map);
    void DisplayAnimation(FbxScene* pScene);
    void DisplayAnimation(FbxAnimStack* pAnimStack, FbxNode* pNode, bool isSwitcher = false,TreeItem* parent=NULL);
    void DisplayAnimation(FbxAnimLayer* pAnimLayer, FbxNode* pNode, bool isSwitcher = false,TreeItem* parent=NULL);
    void DisplayAnimation(FbxAudioLayer* pAudioLayer, bool isSwitcher = false);
    void DisplayChannels(FbxNode* pNode, FbxAnimLayer* pAnimLayer, void (*DisplayCurve) (FbxAnimCurve* pCurve), void (*DisplayListCurve) (FbxAnimCurve* pCurve, FbxProperty* pProperty), bool isSwitcher);
    void DisplayShape(FbxGeometry* pGeometry);
    Settings& sets=Settings::instance();
    FbxManager* lSdkManager;
    FbxScene* lScene;
    EigenMesh baseMesh;
    std::vector<EigenMesh> targetShapes;
    TreeModel* model;
    int count;
    std::map<std::string,std::string> dictionary;
    std::vector<std::string> names;
    std::string blendShapeName;
    bool loaded;
};

#endif // FBXSDKFUNCTIONS_H
