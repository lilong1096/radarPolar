#ifndef RADARPOLAR_H
#define RADARPOLAR_H

#include <qwt_series_data.h>
#include <qwt_polar_plot.h>


#include <vector>


class QwtPolarGrid;
class QwtPolarCurve;

class RadarData : public QwtSeriesData<QwtPointPolar>
{
public:
	RadarData()
	{

	}

	void setPolarData(double dAzimuth, double dRadius)
	{
		m_vcPolarData.push_back(QwtPointPolar(dAzimuth, dRadius));
	}

	void clearAll()
	{
		m_vcPolarData.clear();
	}

	void clearDataByAzimuthRange(double dMinRange, double dMaxRange)
	{
		int nLen = m_vcPolarData.size();
		std::vector<QwtPointPolar>::iterator it;
		double dRealRange = 0;
		for (it = m_vcPolarData.begin(); it != m_vcPolarData.end(); )
		{
			dRealRange = (*it).azimuth();
			if (dRealRange >= dMinRange && dRealRange <= dMaxRange)
			{
				it = m_vcPolarData.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	virtual size_t size() const
	{
		return m_vcPolarData.size();
	}

	virtual QwtPointPolar sample( size_t i ) const
	{
		return m_vcPolarData.at(i);
	}

	virtual QRectF boundingRect() const
	{
		if ( d_boundingRect.width() < 0.0 )
			d_boundingRect = qwtBoundingRect( *this );

		return d_boundingRect;
	}

protected:
	std::vector<QwtPointPolar> m_vcPolarData;
};

class RadarPolar : public QwtPolarPlot
{
	Q_OBJECT

public:
	RadarPolar(QWidget * = NULL);
	~RadarPolar();

	QwtPolarCurve *getCurve(int nId)
	{
		if (0 == nId)
		{
			return m_pCurveLine;
		}
		else if (1 == nId)
		{
			return m_pCurveTarget;
		}
		return NULL;
	}
private:

	RadarData *m_pLineData;
	RadarData *m_pTargetData;
	QwtPolarGrid *m_pGrid;
	QwtPolarCurve *m_pCurveLine;
	QwtPolarCurve *m_pCurveTarget;
	
};

#endif // RADARPOLAR_H
