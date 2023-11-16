#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QChart *chart = new QChart();
    QChart *chart2 = new QChart();
    QChart *chart3 = new QChart();
    QChart *chart4 = new QChart();
    QChart *chart5 = new QChart();
    QChart *chart6 = new QChart();

    QChartView *chartView;
    QChartView *chartView2;
    QChartView *chartView3;
    QChartView *chartView4;
    QChartView *chartView5;
    QChartView *chartView6;

    QPieSeries *Series;
    QPieSeries *Series2;
    QPieSeries *Series3;
    QPieSeries *Series4;
    QPieSeries *Series5;
    QPieSeries *Series6;

private:
    Ui::MainWindow *ui;

public slots:
    void update_charts();
};
#endif // MAINWINDOW_H
