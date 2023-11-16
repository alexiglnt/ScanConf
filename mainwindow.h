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

    QChartView *chartView;
    QChartView *chartView2;
    QChartView *chartView3;

    QPieSeries *Series;
    QPieSeries *Series2;
    QPieSeries *Series3;

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    QBarCategoryAxis *axisX2 = new QBarCategoryAxis;
    QBarCategoryAxis *axisX3 = new QBarCategoryAxis;
    QValueAxis *axisY = new QValueAxis;
    QValueAxis *axisY2 = new QValueAxis;
    QValueAxis *axisY3 = new QValueAxis;

private:
    Ui::MainWindow *ui;

public slots:
    void update_charts();
};
#endif // MAINWINDOW_H
