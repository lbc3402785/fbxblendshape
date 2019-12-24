#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>
#include "fbxsdkfunctions.h"
#include "util/eigenfunctions.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modelViewer=new Viewer();
    modelViewer->init();
    ui->modelLayout->addWidget(modelViewer);
    modelViewer->setSrcMode(Viewer::showMode::FACE);
    modelViewer->update();
    ui->actionFACE->setChecked(true);
    connect(ui->verticalSlider1, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight1(int)));
    connect(ui->verticalSlider2, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight2(int)));
    connect(ui->verticalSlider3, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight3(int)));
    connect(ui->verticalSlider4, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight4(int)));
    connect(ui->verticalSlider5, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight5(int)));
    connect(ui->verticalSlider6, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight6(int)));
    connect(ui->verticalSlider7, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight7(int)));
    connect(ui->verticalSlider8, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight8(int)));
    connect(ui->verticalSlider9, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight9(int)));
    connect(ui->verticalSlider10, SIGNAL(valueChanged(int)),
            this, SLOT(setBlendShapeWeight10(int)));
    connect(ui->verticalSlider1,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider2,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider3,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider4,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider5,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider6,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider7,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider8,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider9,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    connect(ui->verticalSlider10,SIGNAL(sliderReleased()),this,SLOT(updateMesh()));
    hasBlendShapes=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_load_clicked()
{
    QString filename;
    QString lastpath="";
    filename = QFileDialog::getOpenFileName(this,tr("please select m1"), lastpath,tr("*.fbx;*.FBX"));
    FbxSDKFunctions& func=FbxSDKFunctions::instance();
    TreeModel* model=new TreeModel();
    func.setModel(model);
    if(func.loadFbxFile(filename.toStdString())){
        ui->treeView->setModel(model);
        ui->treeView->show();
        EigenMesh base=func.getBaseMesh();
        Eigen::Matrix3Xf &points=base.getPoints();
        EigenFunctions<float>::center(points);
        float curScale=EigenFunctions<float>::computeScale(points);
        modelViewer->stopDraw=true;
        modelViewer->setScale(curScale);
        modelViewer->srcMesh=base;
        modelViewer->stopDraw=false;
        modelViewer->update();
    }else{
        std::cout<<"load fbx file fail!"<<std::endl<<std::flush;
    }

}

void MainWindow::on_save_clicked()
{
    using namespace std;
    FbxSDKFunctions& func=FbxSDKFunctions::instance();
    if(func.getLoaded()){
        QString outputDir=sets.getOutputDir();
        QString expressionList=sets.getExpressionList();
        std::ofstream out(expressionList.toStdString());
        std::vector<std::string> names=func.getNames();
        EigenMesh base=func.getBaseMesh();
        Eigen::Matrix3Xf basePoints=base.getPoints();
        EigenFunctions<float>::center(basePoints);
        std::vector<EigenMesh> shapes=func.getTargetShapes();
        //        MatF blendShapes;
//        blendShapes.resize(basePoints.cols()*3,shapes.size());
        MatF X;
        X.resize(basePoints.cols()*3,shapes.size());
        std::vector<std::vector<bool>> zerochecks;
        std::vector<MatF> diffs;
        for(int i=0;i<names.size();i++){
            out<<names[i]<<std::endl;
            Eigen::Matrix3Xf points=shapes[i].getPoints();
            EigenFunctions<float>::center(points);
            MatF diff=(points-basePoints).transpose();
            MatF blendshape=Reshape(diff,1);
            X.col(i)=blendshape;
        }
        MatF A=X*X.transpose();
        Eigen::EigenSolver<MatF> es(A);
        MatF D = es.pseudoEigenvalueMatrix();
        MatF V = es.pseudoEigenvectors();

//        cout << "svd.singularValues()(2,0):" << endl << svd.singularValues()(0) << endl;
//        cout << "Its singular size:" << endl << svd.singularValues().rows()<<","<<svd.singularValues().cols()<< endl;
//        cout << "Its singular values are:" << endl << svd.singularValues() << endl;
        cout << "V.col(0):" << endl << V.col(0) << endl;
//        Eigen::ColPivHouseholderQR<MatF> lu_decomp(X);
//        auto rank = lu_decomp.rank();
//        cout << "rank:" << endl << rank << endl;
        //cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << U.rows()<<","<<U.cols() << endl<<flush;
        //cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl<<flush;
        out.close();
//        QString blendShapesOutput=outputDir+QDir::separator()+"G8M_BlendShapes.npz";
//        //cnpy::npz_save(blendShapesOutput.toStdString(),"EB",blendShapes.data(),{(unsigned long long)blendShapes.rows(),(unsigned long long)blendShapes.cols()},"w");
//        MatF shape=basePoints.transpose();
//        baseShape=Reshape(shape,1);
//        cnpy::npz_save(blendShapesOutput.toStdString(),"SM",baseShape.data(),{(unsigned long long)baseShape.rows(),(unsigned long long)baseShape.cols()},"a");
//        polygons=base.getPolygons();
//        MatI quadri=polygons.transpose();
//        cnpy::npz_save(blendShapesOutput.toStdString(),"QUADRI",quadri.data(),{(unsigned long long)quadri.rows(),(unsigned long long)quadri.cols()},"a");
//        std::cout<<"export data done!"<<std::endl<<std::flush;
//        hasBlendShapes=true;
//        EX.resize(blendShapes.cols(),1);
//        EX*=0;
    }
}

void MainWindow::on_setting_triggered()
{
    Dialog dia;
    dia.exec();
}

void MainWindow::setBlendShapeWeight1(int value)
{
    if(hasBlendShapes){
        EX(0,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight2(int value)
{
    if(hasBlendShapes){
        EX(1,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight3(int value)
{
    float step=(sets.getRangeMax()-sets.getRangeMin());
    if(hasBlendShapes){
        EX(2,0)=sets.getRangeMin()+value*step/3000;
    }
}

void MainWindow::setBlendShapeWeight4(int value)
{
    if(hasBlendShapes){
        EX(3,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight5(int value)
{
    if(hasBlendShapes){
        EX(4,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight6(int value)
{
    if(hasBlendShapes){
        EX(5,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight7(int value)
{
    if(hasBlendShapes){
        EX(6,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight8(int value)
{
    if(hasBlendShapes){
        EX(7,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight9(int value)
{
    if(hasBlendShapes){
        EX(8,0)=computeRangeValue(value);
    }
}

void MainWindow::setBlendShapeWeight10(int value)
{
    if(hasBlendShapes){
        EX(9,0)=computeRangeValue(value);
    }
}

void MainWindow::updateMesh()
{
    if(hasBlendShapes){
        std::cout<<"updateMesh"<<std::endl<<std::flush;
        std::cout<<"EX:"<<EX<<std::endl<<std::flush;
        MatF shape=baseShape+blendShapes*EX;
        shape=Reshape(shape,3);
        Eigen::Matrix3Xf points=shape.transpose();
        //Eigen::Matrix4Xi colors;
        //EigenFunctions<float>::saveEigenPoints(points,polygons,colors,"test.obj");
//        std::cout<<"transpose done!"<<std::endl<<std::flush;
        if(modelViewer){
            modelViewer->stopDraw=true;
            modelViewer->srcMesh.setPoints(points);
            modelViewer->stopDraw=false;
            modelViewer->update();
        }
    }
}

void MainWindow::on_actionPOINTS_triggered()
{
    modelViewer->setSrcMode(Viewer::showMode::POINTS);
    modelViewer->update();
    ui->actionPOINTS->setChecked(true);
    ui->actionFACE->setChecked(false);
    ui->actionCONTOUR_LINE->setChecked(false);
    ui->actionFACE_CONTOUR_LINE->setChecked(false);
}

void MainWindow::on_actionFACE_triggered()
{
    modelViewer->setSrcMode(Viewer::showMode::FACE);
    modelViewer->update();
    ui->actionPOINTS->setChecked(false);
    ui->actionFACE->setChecked(true);
    ui->actionCONTOUR_LINE->setChecked(false);
    ui->actionFACE_CONTOUR_LINE->setChecked(false);
}

void MainWindow::on_actionCONTOUR_LINE_triggered()
{
    modelViewer->setSrcMode(Viewer::showMode::CONTOUR_LINE);
    modelViewer->update();
    ui->actionPOINTS->setChecked(false);
    ui->actionFACE->setChecked(false);
    ui->actionCONTOUR_LINE->setChecked(true);
    ui->actionFACE_CONTOUR_LINE->setChecked(false);
}

void MainWindow::on_actionFACE_CONTOUR_LINE_triggered()
{
    modelViewer->setSrcMode(Viewer::showMode::FACE_CONTOUR_LINE);
    modelViewer->update();
    ui->actionPOINTS->setChecked(false);
    ui->actionFACE->setChecked(false);
    ui->actionCONTOUR_LINE->setChecked(false);
    ui->actionFACE_CONTOUR_LINE->setChecked(true);
}

float MainWindow::computeRangeValue(int value)
{
    float step=(sets.getRangeMax()-sets.getRangeMin());
    float result=sets.getRangeMin()+value*step/3000;
    return result;
}
