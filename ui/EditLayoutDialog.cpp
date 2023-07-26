#include "EditLayoutDialog.h"
#include "ui_EditLayoutDialog.h"
#include "core/debug.h"
#include "ui/EditLayoutDialog.h"
#include "ui/NewContactLayoutEditor.h"
#include "data/NewContactLayoutProfile.h"

MODULE_IDENTIFICATION("qlog.ui.EditLayoutDialog");

EditLayoutDialog::EditLayoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLayoutDialog)
{
    FCT_IDENTIFICATION;

    ui->setupUi(this);

    loadProfiles();
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
}

EditLayoutDialog::~EditLayoutDialog()
{
    FCT_IDENTIFICATION;
    delete ui;
}

void EditLayoutDialog::loadProfiles()
{
    FCT_IDENTIFICATION;

    QStringList layoutNames = NewContactLayoutProfilesManager::instance()->profileNameList();
    QStringListModel* layoutNamesModel = new QStringListModel(layoutNames, this);
    ui->listView->setModel(layoutNamesModel);
}

void EditLayoutDialog::addButton()
{
    FCT_IDENTIFICATION;

    NewContactLayoutEditor dialog(QString(), this);
    dialog.exec();
    loadProfiles();
}

void EditLayoutDialog::removeButton()
{
    FCT_IDENTIFICATION;

    QString removedProfile = ui->listView->currentIndex().data().toString();
    NewContactLayoutProfilesManager::instance()->removeProfile(removedProfile);
    NewContactLayoutProfilesManager::instance()->save();
    loadProfiles();
}

void EditLayoutDialog::editEvent(QModelIndex idx)
{
    FCT_IDENTIFICATION;

    QString layoutName = ui->listView->model()->data(idx).toString();
    NewContactLayoutEditor dialog(layoutName, this);
    dialog.exec();
}

void EditLayoutDialog::editButton()
{
    FCT_IDENTIFICATION;

    QModelIndexList selected = ui->listView->selectionModel()->selectedIndexes();
    if ( selected.size() > 0 )
    {
       editEvent(selected.at(0));
    }
}
