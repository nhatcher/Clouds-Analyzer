  
#include <QtGui>
#include <QWidget>
#include "fractalviewer.h"
#include "Fractal2D.h"
class HelpBrowser;


FractalViewer::FractalViewer()
{
	myfractal= new Fractal2D;
    setCentralWidget(myfractal);
	createActions();
	createMenus();
	fractalCombo = new QComboBox();

	fractalCombo->addItem("Koch");
	fractalCombo->addItem("Fbm1d");
	fractalCombo->addItem("Clouds");
	fractalCombo->addItem("Clouds3D");
	fractalCombo->addItem("Henon");
	//fractalCombo->addItem("Image");
	//fractalCombo->addItem("None");
		
	fractalCombo->setItemIcon(0,QIcon(":/images/kochIcon.png"));
	fractalCombo->setItemIcon(1,QIcon(":/images/fbm1dIcon.png"));
	fractalCombo->setItemIcon(2,QIcon(":/images/icon.png"));
	fractalCombo->setItemIcon(3,QIcon(":/images/icon.png"));
	fractalCombo->setCurrentIndex(2);
	connect(fractalCombo, SIGNAL(activated(int)),myfractal,SLOT(setCurrentIndex(int)));
	connect(myfractal, SIGNAL(positionChanged(int , int )), this, SLOT(setPosition(int , int )));
	createToolBars();
	
	setToolButtonStyle ( Qt::ToolButtonTextUnderIcon );

	setWindowTitle(tr("Clouds Analyzer"));
	resize(500, 400);
	setWindowIcon(QIcon(":/images/icon.png"));
	statusBar()->showMessage(tr("Ready"));
}
void FractalViewer::setPosition(int i, int j)
{
	QString message;
	QTextStream(&message) << "(" << i<<","<<j<<")";
	statusBar()->showMessage(message);
}
void FractalViewer::help()
{
	HelpBrowser::showPage("help.html");
}
void FractalViewer::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"), QDir::currentPath());
	if (!fileName.isEmpty()) {
		QImage image(fileName);
		if (image.isNull()) {
			QMessageBox::information(this, tr("Fractal Analyzer"), tr("Cannot load %1.").arg(fileName));
			return;
		}
		updateActions();
		myfractal->loadImage(image);
	}
}

void FractalViewer::save()
{
    QImage image;
    image=myfractal->getImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(),  tr("Images (*.png, *.xpm, *.jpg)"));
    image.save(fileName);
}

void FractalViewer::about()
{
	QMessageBox::about(this, tr("About Fractal Analyzer"),
					   tr("A program designed to analyze the fractal structure of the interstelar medium. Developed by: Sandra Ocando & Nicolas Hatcher. 2008." ));
}

 void FractalViewer::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	openAct->setIcon(QIcon(":/images/openIcon.png"));
	//openAct->setEnabled(false);
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
	
	saveAct = new QAction(tr("&Save..."), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setIcon(QIcon(":/images/saveIcon.png"));
	//saveAct->setEnabled(false);
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
	
	generateAct = new QAction(tr("&Generate..."), this);
	generateAct->setShortcut(tr("Ctrl+G"));
	generateAct->setIcon(QIcon(":/images/generateIcon.png"));
	connect(generateAct, SIGNAL(triggered()), myfractal, SLOT(generate()));
    
	calculateAct = new QAction(tr("Calculate &Box-Counting Dimension.."), this);
	calculateAct->setShortcut(tr("Ctrl+B"));
	calculateAct->setIcon(QIcon(":/images/calculateIcon.png"));
	calculateAct->setIconText(tr("Box-Counting"));
	connect(calculateAct, SIGNAL(triggered()), myfractal, SLOT(calculate()));
	
 	calculateCorrAct = new QAction(tr("Calculate &Correlation Dimension.."), this);
 	calculateCorrAct->setShortcut(tr("Ctrl+C"));
 	calculateCorrAct->setIcon(QIcon(":/images/correlation.png"));
 	calculateCorrAct->setIconText(tr("Correlation"));
 	connect(calculateCorrAct, SIGNAL(triggered()), myfractal, SLOT(calculateCorr()));
    
	calculateRenyiAct = new QAction(tr("Calculate &Renyi Dimension.."), this);
	calculateRenyiAct->setShortcut(tr("Ctrl+R"));
	calculateRenyiAct->setIcon(QIcon(":/images/renyi.png"));
	calculateRenyiAct->setIconText(tr("Renyi dimension"));
	connect(calculateRenyiAct, SIGNAL(triggered()), myfractal, SLOT(calculateRenyi()));
	
	calculateAreaPerimeterAct = new QAction(tr("Calculate &Area Perimeter Dimension"), this);    
	calculateAreaPerimeterAct->setIcon(QIcon(":/images/calculateAreaPerimeterIcon.png"));
	calculateAreaPerimeterAct->setShortcut(tr("Ctrl+A"));
	calculateAreaPerimeterAct->setIconText(tr("Area-Perimeter"));
	connect(calculateAreaPerimeterAct, SIGNAL(triggered()), myfractal, SLOT(calculateAreaPerimeter()));

	calculateOptionAct = new QAction(tr("&Box counting Settings"),this);
	//calculateOptionAct->setShortcut(tr("Ctrl+B"));
	calculateOptionAct->setIcon(QIcon(":/images/calculateIcon.png"));
	connect(calculateOptionAct, SIGNAL(triggered()), myfractal, SLOT(calculateOptions()));
	
	calculateCorrOptionAct = new QAction(tr("Correlation &Settings"),this);
	//calculateCorrOptionAct->setShortcut(tr("Ctrl+S"));
	calculateCorrOptionAct->setIcon(QIcon(":/images/correlation.png"));
	connect(calculateCorrOptionAct, SIGNAL(triggered()), myfractal, SLOT(calculateCorrOptions()));
    
	calculateRenyiOptionAct = new QAction(tr("&Renyi Settings"),this);
	//calculateRenyiOptionAct->setShortcut(tr("Ctrl+R"));
	calculateRenyiOptionAct->setIcon(QIcon(":/images/renyi.png"));
	connect(calculateRenyiOptionAct, SIGNAL(triggered()), myfractal, SLOT(calculateRenyiOptions()));
	
	calculateAreaPerimeterOptionsAct = new QAction(tr("Area Perimeter Settings"),this);
	calculateAreaPerimeterOptionsAct->setIcon(QIcon(":/images/calculateAreaPerimeterIcon.png"));
	connect(calculateAreaPerimeterOptionsAct, SIGNAL(triggered()), myfractal, SLOT(calculateAreaPerimeterOptions()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
	
	helpAct = new QAction(tr("Help"), this);
	helpAct->setIcon(QIcon(":/images/helpIcon.png"));
	connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));
	
	aboutAct = new QAction(tr("About"), this);
	aboutAct->setIcon(QIcon(":/images/helpIcon.png"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	

}

 void FractalViewer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	toolsMenu = new QMenu(tr("&Tools"), this);
	toolsMenu->addAction(generateAct);
	toolsMenu->addAction(calculateAreaPerimeterAct);
	toolsMenu->addAction(calculateAct);
	toolsMenu->addAction(calculateCorrAct);
	toolsMenu->addAction(calculateRenyiAct);
	toolsMenu->addSeparator();
	
	optionsMenu = new QMenu(tr("&Options"), this);
	optionsMenu->addAction(calculateOptionAct);
	optionsMenu->addAction(calculateAreaPerimeterOptionsAct);
	optionsMenu->addAction(calculateCorrOptionAct);
	optionsMenu->addAction(calculateRenyiOptionAct);
	toolsMenu->addSeparator();
	 
	helpMenu = new QMenu(tr("&Help"), this);
	//helpMenu->addAction(helpAct);
	helpMenu->addAction(aboutAct);
	

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(toolsMenu);
	menuBar()->addMenu(optionsMenu);
	menuBar()->addMenu(helpMenu);
}


void FractalViewer::createToolBars()
{
	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);
	
	fileToolBar->addWidget(fractalCombo);
	fileToolBar->addAction(generateAct);
	fileToolBar->addAction(calculateAct);
	
	fileToolBar->addAction(calculateAreaPerimeterAct);
	fileToolBar->addAction(calculateCorrAct);
	fileToolBar->addAction(calculateRenyiAct);
	
	QSize iconSize(40,40);
	fileToolBar->setIconSize(iconSize);

}

void FractalViewer::updateActions(){}

HelpBrowser::HelpBrowser(const QString &path, const QString &page,QWidget *parent): QWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_GroupLeader);
	textBrowser = new QTextBrowser;
	homeButton = new QPushButton(tr("&Home"));
	closeButton = new QPushButton(tr("Close"));
	closeButton->setShortcut(tr("Esc"));
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(homeButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(closeButton);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(textBrowser);
	setLayout(mainLayout);
	setWindowTitle("Clouds Analyzer's Help");
	connect(homeButton,SIGNAL(clicked()),textBrowser, SLOT(home()));
	connect(closeButton,SIGNAL(clicked()),this, SLOT(close()));
	setWindowIcon(QIcon(":/images/helpIcon.png"));
	textBrowser->setSearchPaths(QStringList() << path );
	textBrowser->setSource(page);
	
}
void HelpBrowser::showPage(const QString &page)
{
	QString path = QApplication::applicationDirPath() + "/doc";
	HelpBrowser *browser = new HelpBrowser(path,page);
	browser->resize(700,600); 
	browser->show();
}
