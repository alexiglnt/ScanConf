#include "mainwindow.h"

#include <QApplication>
#include <QChartView>
#include <QHBoxLayout>
#include <QLabel>

#include "SystemInfo.h"

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


    // Create and configure CPU name label
    SystemInfo sysInfo;
    QString cpuName = sysInfo.getCpuName();
    QLabel *cpuLabel = new QLabel("CPU Name: " + cpuName);

    // Create and configure RAM info label
    QString ramInfo = sysInfo.getRamInfo();
    QLabel *ramLabel = new QLabel("RAM Info: " + ramInfo);

    // Create and configure Disk info label
    QString diskInfo = sysInfo.getDiskInfo(); // Assuming getDiskInfo() is your function for retrieving disk info
    QLabel *diskLabel = new QLabel("Disk Info: " + diskInfo);


    // Add the labels to a layout
    vertical_layout->addWidget(cpuLabel); // Add the CPU label
    vertical_layout->addWidget(ramLabel); // Add the RAM label
    vertical_layout->addWidget(diskLabel); // Add the Disk label
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



    // Create the system info JSON object
    QJsonObject systemInfoJson = sysInfo.createSystemInfoJson(sysInfo);

    // Convert the JSON object to a JSON document
    QJsonDocument jsonDoc(systemInfoJson);

    // Convert the JSON document to a string
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);

    // Display the JSON string (you can replace this with your preferred way of displaying)
    qDebug() << "System Info JSON:";
    qDebug().noquote() << jsonString;


    // Appel de la fonction qui affiche les charts
    w.update_charts();


    w.setCentralWidget(window);
    w.setWindowState(Qt::WindowMaximized);

    w.show();
    return a.exec();
}
