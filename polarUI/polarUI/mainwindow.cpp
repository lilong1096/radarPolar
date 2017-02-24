#include "mainwindow.h"
#include "radarpolar.h"
#include <qwt_polar_panner.h>
#include <qwt_polar_magnifier.h>
#include <QtWidgets/QHBoxLayout>
#include <qwt_polar_curve.h>
#include "QDateTime"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *w = new QWidget( this );
	m_radarPlot = new RadarPolar(w);

	m_radarPanner = new QwtPolarPanner(m_radarPlot->canvas());
	m_radarPanner->setEnabled(true);

	m_radarZoomer =new QwtPolarMagnifier(m_radarPlot->canvas());
	m_radarPanner->setEnabled(true);

	QHBoxLayout *layout = new QHBoxLayout( w );

	layout->addWidget(m_radarPlot, 0);

	setCentralWidget(w);

	RadarData *tempData = (RadarData *)m_radarPlot->getCurve(0)->data();
	tempData->setPolarData(0, 0);
	tempData->setPolarData(0, 120);
	m_dTimeData = 0;

	qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); 
	for (int i = 0; i < 100; i++)
	{
		m_az[i] = qrand() % 350 + 5;
		m_rd[i] = qrand() % 120;
	}
	connect(&m_timerTst, SIGNAL(timeout()), this, SLOT(tickRun()));
	m_timerTst.start(100);
}

MainWindow::~MainWindow()
{

}

void MainWindow::tickRun()
{
	m_dTimeData += 10.0;
	if (360 < m_dTimeData)
	{
		m_dTimeData = 0;
		qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); 
		for (int i = 0; i < 100; i++)
		{
			m_az[i] = qrand() % 350 + 5;
			m_rd[i] = qrand() % 120;
		}
		//m_timerTst.stop();
		return;
	}
	RadarData *tempData = (RadarData *)m_radarPlot->getCurve(0)->data();
	tempData->clearAll();
	tempData->setPolarData(0, 0);
	tempData->setPolarData(m_dTimeData, 120);

	RadarData *targetData = (RadarData *)m_radarPlot->getCurve(1)->data();
	targetData->clearDataByAzimuthRange(m_dTimeData - 10, m_dTimeData);
	for (int i = 0; i < 100; i++)
	{
		if (0 <= m_dTimeData - m_az[i] && 10 >= m_dTimeData - m_az[i])
		{
			targetData->setPolarData(m_az[i], m_rd[i]);
		}
	}
	
	m_radarPlot->replot();
}
