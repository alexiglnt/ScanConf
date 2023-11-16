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


    chart->setTitle("Potentiel de gaz à effet de serre");
    chart2->setTitle("Energie Primaire");
    chart3->setTitle("Epuisement des ressources abiotiques");
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

    chart->removeAxis(axisX);
    chart->removeAxis(axisY);
    chart2->removeAxis(axisX2);
    chart2->removeAxis(axisY2);
    chart3->removeAxis(axisX3);
    chart3->removeAxis(axisY3);

    Series = new QPieSeries(chart);
    Series2 = new QPieSeries(chart2);
    Series3 = new QPieSeries(chart3);

    std::vector<float> val;
    for(int i=0;i<6;i+=1)
    {
        val.push_back(i);
    }
    Series->append(new QPieSlice("a",13.2));

    chart->addSeries(Series);
    chart2->addSeries(Series2);
    chart3->addSeries(Series3);


/*
    // Affichage Chart 1
    axisX = new QBarCategoryAxis;
    QStringList categories {"Usage", "Manufacturing RAM", "Manufacturing CPU", "Manufacturing SSD", "Manufacturing HDD", "Manufacturing Others"};
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignLeft);
    Series->attachAxis(axisX);

    axisY = new QValueAxis;
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignBottom);
    Series->attachAxis(axisY);


    // Affichage Chart 2
    axisX2 = new QBarCategoryAxis;
    axisX2->append(categories);
    chart2->addAxis(axisX2, Qt::AlignLeft);
    Series2->attachAxis(axisX2);

    axisY2 = new QValueAxis;
    axisY2->setRange(0,15);
    chart2->addAxis(axisY2, Qt::AlignBottom);
    Series2->attachAxis(axisY2);


    // Affichage Chart 3
    axisX3 = new QBarCategoryAxis;
    axisX3->append(categories);
    chart3->addAxis(axisX3, Qt::AlignLeft);
    Series3->attachAxis(axisX3);

    axisY3 = new QValueAxis;
    axisY3->setRange(0,15);
    chart3->addAxis(axisY3, Qt::AlignBottom);
    Series3->attachAxis(axisY3);
*/





    chart->legend()->setVisible(true);


    chartView->update();
    chartView2->update();
    chartView3->update();

}

