#include "Chart.h"

Chart::Chart()
{
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void Chart::update()
{
    m_chart->removeAllSeries();

    m_chart->addSeries(Series);

    m_chart->legend()->setVisible(true);

    m_chartView->update();
}
