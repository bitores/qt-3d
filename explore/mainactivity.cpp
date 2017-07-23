#include "mainactivity.h"
#include "cgdemo.h"
#include <QDockWidget>
#include <QTextEdit>

MainActivity::MainActivity(QWidget *parent) :
    QMainWindow(parent)
{
    this->setGeometry(200,100,1400,600);
    CGDemo *demo = new CGDemo();
    QTextEdit *edit=new QTextEdit(this);
    QTextEdit *edit1=new QTextEdit(this);
    QTextEdit *edit2=new QTextEdit(this);
    QTextEdit *edit3=new QTextEdit(this);
    QTextEdit *edit4=new QTextEdit(this);

    setCentralWidget(demo);

    QDockWidget *leftDock=new QDockWidget("left",this);
    leftDock->setWidget(edit1);
    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea
    | Qt::BottomDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    QDockWidget *rightDock=new QDockWidget("right",this);
    rightDock->setWidget(edit2);
    rightDock->setAllowedAreas(Qt::RightDockWidgetArea
    | Qt::BottomDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);

    QDockWidget *bottem1=new QDockWidget("bo1",this);
    bottem1->setWidget(edit3);
    bottem1->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, bottem1);

    QDockWidget *bottem2=new QDockWidget("bo2",this);
    bottem2->setWidget(edit4);
    bottem2->setAllowedAreas( Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, bottem2);
}
