#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include "settings.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    assign();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::assign()
{
    Settings& sets=Settings::instance();
    ui->expressionDir->setText(sets.getExpressionDir());
    ui->expressionList->setText(sets.getExpressionList());
    //ui->outputDir->setText(sets.getOutputDir());
    ui->blendShapeName->setText(sets.getBlendShapeName());
    ui->count->setText(QString::number(sets.getCount()));
    ui->rangeMin->setText(QString::number(sets.getRangeMin()));
    ui->rangeMax->setText(QString::number(sets.getRangeMax()));
}

void Dialog::on_save_clicked()
{
    Settings& set = Settings::instance();
    set.setExpressionDir(ui->expressionDir->text());
    set.setExpressionList(ui->expressionList->text());
    set.setCount(ui->count->text().toInt());
    set.setBlendShapeName(ui->blendShapeName->text());
    set.setRangeMin(ui->rangeMin->text().toFloat());
    set.setRangeMax(ui->rangeMax->text().toFloat());
    //set.setOutputDir(ui->outputDir->text());
    set.saveSettings();
    accept();
}

void Dialog::on_reset_clicked()
{
    Settings& sets = Settings::instance();
    sets.reset();
    assign();
}

void Dialog::on_cancel_clicked()
{
    reject();
}
