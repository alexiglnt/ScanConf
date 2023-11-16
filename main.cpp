#include "mainwindow.h"

#include <QApplication>
#include <QChartView>
#include <QHBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    // Gestion Layout
    QVBoxLayout *main_layout = new QVBoxLayout();
    QVBoxLayout *vertical_layout = new QVBoxLayout();
    QHBoxLayout *layout_H_chart1 = new QHBoxLayout();
    QHBoxLayout *layout_H_chart2 = new QHBoxLayout();
    QHBoxLayout *layout_H_chart3 = new QHBoxLayout();

    QWidget *window = new QWidget();
    QWidget *charts = new QWidget();
    QWidget *chart1 = new QWidget();
    QWidget *chart2 = new QWidget();
    QWidget *chart3 = new QWidget();

    main_layout->setContentsMargins(0, 0, 0, 0);
    // layout->addWidget(w.chartView);
    window->setLayout(main_layout);

    charts->setLayout(vertical_layout);
    chart1->setLayout(layout_H_chart1);
    chart2->setLayout(layout_H_chart2);
    chart3->setLayout(layout_H_chart3);
    QStringList titres {"Potentiel de gaz à effet de serre", "Epuisement des ressources abiotiques", "Energie Primaire"};

    QLabel *titre1 = new QLabel("Potentiel de gaz à effet de serre");
    titre1->setAlignment(Qt::AlignCenter);
    QLabel *titre2 = new QLabel("Epuisement des ressources abiotiques");
    titre2->setAlignment(Qt::AlignCenter);
    QLabel *titre3 = new QLabel("Energie Primaire");
    titre3->setAlignment(Qt::AlignCenter);

    vertical_layout->addWidget(titre1);
    vertical_layout->addWidget(chart1);
    vertical_layout->addWidget(titre2);
    vertical_layout->addWidget(chart2);
    vertical_layout->addWidget(titre3);
    vertical_layout->addWidget(chart3);
    main_layout->addWidget(charts);

    layout_H_chart1->addWidget(w.chartView);
    layout_H_chart2->addWidget(w.chartView3);
    layout_H_chart3->addWidget(w.chartView5);

    layout_H_chart1->addWidget(w.chartView2);
    layout_H_chart2->addWidget(w.chartView4);
    layout_H_chart3->addWidget(w.chartView6);

    // Appel de la fonction qui affiche les charts
    w.update_charts();


    w.setCentralWidget(window);
    w.setWindowState(Qt::WindowMaximized);


    w.show();
    return a.exec();
}
