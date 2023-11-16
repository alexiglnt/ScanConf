#include "mainwindow.h"

#include <QApplication>
#include <QChartView>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    // Gestion Layout
    // QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *main_layout = new QVBoxLayout();
    QVBoxLayout *vertical_layout = new QVBoxLayout();

    QWidget *window = new QWidget();
    QWidget *charts = new QWidget();

    main_layout->setContentsMargins(0, 0, 0, 0);
    // layout->addWidget(w.chartView);
    window->setLayout(main_layout);
    charts->setLayout(vertical_layout);
    main_layout->addWidget(charts);

    vertical_layout->addWidget(w.chartView);
    vertical_layout->addWidget(w.chartView2);
    vertical_layout->addWidget(w.chartView3);

    // Appel de la fonction qui affiche les charts
    w.update_charts();


    w.setCentralWidget(window);
    w.setWindowState(Qt::WindowMaximized);


    w.show();
    return a.exec();
}
