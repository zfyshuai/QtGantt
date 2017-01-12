#include "ganttwidget.h"
#include "ui_ganttwidget.h"

#include "ganttscene.h"

#include <QScrollBar>
#include <QAbstractItemModel>


GanttWidget::GanttWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GanttWidget)
{
    ui->setupUi(this);
    init();

    ui->playerControl->hide();
    ui->playerSettings->hide();

    if(layout())
    {
        layout()->setMargin(0);
        layout()->setSpacing(0);
    }

    ui->treeView->setContentsMargins(0,0,0,0);
    ui->treeView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeView->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

    installEventFilter(ui->intervalSlider);

    ui->playerControl->setSettings(ui->playerSettings);

}

GanttWidget::~GanttWidget()
{
    delete ui;
}

void GanttWidget::setPlayerSpeeds(qreal minMultiply, qreal maxMultiply)
{
    ui->playerSettings->setMultiplies(minMultiply,maxMultiply);
}

void GanttWidget::showPlayer(bool show)
{
    m_playerShown = show;
    ui->playerControl->setVisible(show);
    ui->playerSettings->setVisible(show);

//    if(m_scene)
//        m_scene->setDrawCurrentDtSlider(show);

    update();
}

bool GanttWidget::player() const
{
    return m_playerShown;
}

void GanttWidget::setModel(IGanttModel *model)
{
    _treeInfo->setModel(model);
}

void GanttWidget::setView(QTreeView *view, bool inner)
{
    /// TODO
}

void GanttWidget::onGanttViewCustomContextMenuRequested(const QPoint &point)
{
    QPoint widgetPoint =ui->ganttView->mapTo(this,point);

    emit customContextMenuRequested(point);
}

void GanttWidget::init()
{
    _treeInfo = new GanttInfoTree(this);
    _scene = new GanttScene(ui->ganttView,ui->widgetDtLine,this);
    connectSceneToInfo();
}

void GanttWidget::connectSceneToInfo()
{
    connect(_treeInfo,SIGNAL(itemAdded(GanttInfoItem*)),_scene,SLOT(onItemAdded(GanttInfoItem*)));
    connect(_treeInfo,SIGNAL(itemRemoved(GanttInfoItem*)),_scene,SLOT(onItemRemoved(GanttInfoItem*)));

    connect(_treeInfo,SIGNAL(endInsertItems()),_scene,SLOT(onEndInsertItems()));

}
