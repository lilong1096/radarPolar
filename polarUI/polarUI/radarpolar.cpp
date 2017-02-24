#include "radarpolar.h"
#include <qwt_polar_grid.h>
#include <qwt_polar_curve.h>
#include <qwt_symbol.h>
#include <..\..\..\..\..\..\LL\RakrClient\include\QWT\qwt_legend.h>
#include <qwt_polar_marker.h>

RadarPolar::RadarPolar(QWidget *parent)
	: QwtPolarPlot(QwtText( "Radar polar clutter" ), parent)
{
	setAutoReplot( false );
	setPlotBackground( Qt::darkBlue );
	setScale( QwtPolar::Azimuth,0.0, 360.0, 20.0);
	//setScaleMaxMinor( QwtPolar::Azimuth, 2 );
	setScale( QwtPolar::Radius, 0, 120);

	m_pGrid = new QwtPolarGrid();

	m_pGrid->setPen(QPen(Qt::yellow));

	m_pGrid->showGrid(QwtPolar::ScaleAzimuth);
	m_pGrid->showGrid(QwtPolar::ScaleRadius);

	m_pGrid->setAxisPen(QwtPolar::AxisAzimuth, QPen( Qt::black ));
	m_pGrid->showAxis( QwtPolar::AxisAzimuth, true );
	m_pGrid->showAxis( QwtPolar::AxisLeft, true );
	m_pGrid->showAxis( QwtPolar::AxisRight, true );
	m_pGrid->showAxis( QwtPolar::AxisTop, true );
	m_pGrid->showAxis( QwtPolar::AxisBottom, true );
	m_pGrid->showGrid( QwtPolar::Azimuth, true );
	m_pGrid->showGrid( QwtPolar::Radius, true );
	m_pGrid->attach( this );
	
	m_pCurveLine = new QwtPolarCurve();
	m_pCurveLine->setStyle(QwtPolarCurve::Lines);
	/*m_pCurveLine->setPen(QPen( Qt::red, 2 ));*/
	
	m_pLineData = new RadarData();
	m_pCurveLine->setData(m_pLineData);
	m_pCurveLine->attach(this);

	m_pCurveTarget = new QwtPolarCurve();
	m_pCurveTarget->setTitle("Target");
	m_pCurveTarget->setStyle(QwtPolarCurve::NoCurve);
	m_pCurveTarget->setPen(QPen(Qt::green, 2));
	m_pCurveTarget->setSymbol(new QwtSymbol(QwtSymbol::Rect,
		QBrush( Qt::cyan ), QPen( Qt::white ), QSize( 3, 3 )));
	m_pTargetData = new RadarData();
	m_pCurveTarget->setData(m_pTargetData);
	m_pCurveTarget->attach(this);
	

	QwtPolarMarker *marker = new QwtPolarMarker();
	marker->setPosition( QwtPointPolar( 0, 0 ) );
	marker->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::white ), QPen( Qt::green ), QSize( 9, 9 ) ) );
	marker->setLabelAlignment( Qt::AlignHCenter | Qt::AlignTop );

	QwtText text( "radar" );
	text.setColor( Qt::black );
	QColor bg( Qt::white );
	bg.setAlpha( 200 );
	text.setBackgroundBrush( QBrush( bg ) );

	marker->setLabel( text );
	marker->attach( this );
	
	
	//QwtLegend *legend = new QwtLegend;
	//insertLegend( legend,  QwtPolarPlot::BottomLegend );
}

RadarPolar::~RadarPolar()
{

}
