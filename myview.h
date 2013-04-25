#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>

class MainWindow;

class myView : public QGraphicsView  {
    Q_OBJECT

public:
    myView(MainWindow *);
    
private:
    MainWindow* m;
    
protected:
    void keyPressEvent(QKeyEvent *e);
    
    
};

#endif
