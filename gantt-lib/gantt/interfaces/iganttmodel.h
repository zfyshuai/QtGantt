#ifndef IGANTTMODEL_H
#define IGANTTMODEL_H

#include "gantt-lib_global.h"
#include "utcdatetime.h"

#include <QModelIndex>


class GANTTLIBSHARED_EXPORT IGanttModel
{
public:
    IGanttModel();
    virtual ~IGanttModel();

    enum IGanttTag{
        IGanttNode = 1,
        IGanttLeaf = 2
    };

    // --- Interface

    virtual IGanttTag   iGanttTag(const QModelIndex &index) const = 0;  /// < Leaf or Node?
    virtual QString     iGanttTitle(const QModelIndex &iGanttIndex) const = 0;
    virtual UtcDateTime iGanttStart(const QModelIndex &iGanttIndex) const = 0;
    virtual TimeSpan    iGanttTimeSpan(const QModelIndex &iGanttIndex) const = 0;
    virtual QColor      iGanttColor(const QModelIndex &iGanttIndex) const = 0;

    virtual QModelIndex iGanttIndex(const QString &iGanttTitle) const = 0;     ///< QModelIndex через Title

    // ---

public:
    bool iGanttIsDot(QModelIndex &index){
        return iGanttTimeSpan(index).microseconds() == 0;
    }

};

#endif // IGANTTMODEL_H
