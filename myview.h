#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>

class MainWindow;
/**
 * A class to capture key press event from GraphicsView

 * @author Yixin Cai
 */
class myView : public QGraphicsView  {
    Q_OBJECT

public:
    /** constructor */ 
    myView(MainWindow *);
    
private:
    /** a pointer to MainWindow */
    MainWindow* m;
    
protected:
    /** overwritting keyPressEvent */
    void keyPressEvent(QKeyEvent *e);
    
    
};

#endif
