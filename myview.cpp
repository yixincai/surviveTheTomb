#include "myview.h"
#include <iostream> 
#include "mainwindow.h"
using namespace std;

/** Constructor pointer to a mainwindow.
  * @param mw pointer to the window
  */
myView :: myView(MainWindow *mw) 
{
    m = mw;
}
/** Capture Key Press Event and call keyPressEvent1 in MainWindow 
 * @param event a Key Press Event
 */
void myView::keyPressEvent(QKeyEvent *event){
	m->keyPressEvent1(event);
}

