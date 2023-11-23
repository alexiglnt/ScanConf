#include <QChartView>
#include <QPieSeries>
#include <QChart>

class Chart
{
public:
    Chart();
    QChart* m_chart = new QChart();
    QChartView* m_chartView;
    QPieSeries *Series;

    void update();
};


