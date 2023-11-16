#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Gestion des Charts
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    chartView3 = new QChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);

    chartView4 = new QChartView(chart4);
    chartView4->setRenderHint(QPainter::Antialiasing);

    chartView5 = new QChartView(chart5);
    chartView5->setRenderHint(QPainter::Antialiasing);

    chartView6 = new QChartView(chart6);
    chartView6->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_charts()
{
    chart->removeAllSeries();
    chart2->removeAllSeries();
    chart3->removeAllSeries();
    chart4->removeAllSeries();
    chart5->removeAllSeries();
    chart6->removeAllSeries();


    Series = new QPieSeries(chart);
    Series2 = new QPieSeries(chart2);
    Series3 = new QPieSeries(chart3);
    Series4 = new QPieSeries(chart4);
    Series5 = new QPieSeries(chart5);
    Series6 = new QPieSeries(chart6);

    QStringList categories {"Usage", "Manufacturing RAM", "Manufacturing CPU", "Manufacturing SSD", "Manufacturing HDD", "Manufacturing Others"};
    QStringList categories2 {"Usage", "Manufacturing"};
    foreach(QString categorie, categories)
    {
       Series->append(new QPieSlice(categorie,10));
       Series3->append(new QPieSlice(categorie,10));
       Series5->append(new QPieSlice(categorie,10));
    }

    foreach(QString categorie, categories2)
    {
       Series2->append(new QPieSlice(categorie,10));
       Series4->append(new QPieSlice(categorie,10));
       Series6->append(new QPieSlice(categorie,10));
    }

    chart->addSeries(Series);
    chart2->addSeries(Series2);
    chart3->addSeries(Series3);
    chart4->addSeries(Series4);
    chart5->addSeries(Series5);
    chart6->addSeries(Series6);








    chart->legend()->setVisible(true);


    chartView->update();
    chartView2->update();
    chartView3->update();

}

