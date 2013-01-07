#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QMainWindow>
#include <QToolBox>
#include <QListView>
#include <QHash>

#include "modeleditorscene.h"

namespace Ui {
class ModelWindow;
}

class ModelWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ModelWindow(QWidget *parent = 0);
    ~ModelWindow();

public slots:
    void undockBlockDock(void);
    void undockModelDock(void);

    void addBlock(const std::string& group, const std::string&);
    
private:
    Ui::ModelWindow *ui;
    ModelEditorScene* editorScene;
    QToolBox* blockToolbox;
    boost::shared_ptr<IModel> model;

    QHash<QString, QListView*> toolboxListViews;
};

#endif // MODELWINDOW_H
