#ifndef FRACTALVIEWER_H
#define FRACTALVIEWER_H

#include <QMainWindow>
#include <QWidget>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class Fractal2D;
class QComboBox;
class QTextBrowser;
class QPushButton;

class FractalViewer : public QMainWindow
{
  Q_OBJECT

  public:
    FractalViewer();

  private slots:
    void open();
    void save();
    void about();
    void help();
    void setPosition(int ,int);
    //  void calculateOptions();
    //  void seCurrentIndex(int);

  private:
    void createActions();
    void createMenus();
    void createToolBars();
    void updateActions();

    Fractal2D *myfractal;

    QAction *openAct;
    QAction *saveAct;
    QAction *generateAct;
    QAction *calculateAct;
    QAction *calculateCorrAct;
    QAction *calculateRenyiAct;

    QAction *calculateAreaPerimeterAct;
    QAction *exitAct;
    QAction *calculateOptionAct;
    QAction *calculateCorrOptionAct;
    QAction *calculateRenyiOptionAct;
    QAction *calculateAreaPerimeterOptionsAct;
    QAction *aboutAct;
    QAction *helpAct;

    QMenu *fileMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;


    QComboBox *fractalCombo;
};

#endif
