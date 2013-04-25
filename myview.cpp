#include "myview.h"
#include <iostream> 
#include "mainwindow.h"
using namespace std;

/** Constructor passing X and Y coordinates,
  * height, width and MainWindow pointer.
  *
  * @param nx x coordinate of the rectangle
  * @param ny y coordinate of the rectangle
  * @param nw width of the rectangle
  * @param nh height of the rectangle
  * @param m pointer to the MainWindow this GUITile is in
  */
myView :: myView(MainWindow *mw) 
{
    m = mw;
}
/** Capture Mouse Press Event and call moveTile in MainWindow 
 * @param event a Mouse Event
 */
void myView::keyPressEvent(QKeyEvent *event){
	m->keyPressEvent1(event);
}

