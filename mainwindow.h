#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QHBoxLayout>
#include <QChartView>
#include <QLabel>
#include "ServerImpact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ServerImpact* all_datas = new ServerImpact();

    QChart *chart = new QChart();
    QChart *chart2 = new QChart();

    QChartView *chartView;
    QChartView *chartView2;

    QPieSeries *Series;
    QPieSeries *Series2;

    QHBoxLayout* ShowConfig(QHBoxLayout* BoxH, QString string);

private:
    Ui::MainWindow *ui;

public slots:
    void update_charts();
};
#endif // MAINWINDOW_H
