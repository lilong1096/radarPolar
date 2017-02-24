#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"

class RadarPolar;
class QwtPolarPanner;
class QwtPolarMagnifier;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = NULL );
	~MainWindow();

public slots:

	void tickRun();

private:
	RadarPolar *m_radarPlot;
	QwtPolarPanner *m_radarPanner;
	QwtPolarMagnifier *m_radarZoomer;
	double m_dTimeData;
	QTimer m_timerTst;

	//3¸öÐé¼ÙÄ¿±ê

	double m_az[100];
	double m_rd[100];


};

#endif // MAINWINDOW_H
