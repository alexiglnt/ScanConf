#include "mainwindow.h"

#include <QApplication>
#include "SystemInfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////        Gestion Layout      //////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add Main Window
    QVBoxLayout *windowLayout = new QVBoxLayout();
    QWidget *window = new QWidget();


    windowLayout->setContentsMargins(0, 0, 0, 0);

    // Add vertical
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QWidget *mainWidget = new QWidget();


    // Add Graphique 1
    QHBoxLayout *graphLayout = new QHBoxLayout();
    QWidget *graphWidget = new QWidget();


    //Connect Layout

    window->setLayout(windowLayout);

    mainWidget->setLayout(verticalLayout);

    graphWidget->setLayout(graphLayout);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////   PC Configuration Information   //////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////     PC Configuration Information     /////

    QWidget *configWidgetText = new QWidget();
    QWidget *configWidgetValue = new QWidget();

    QHBoxLayout *configText = new QHBoxLayout();
    QHBoxLayout *configValue = new QHBoxLayout();

    configWidgetText->setLayout(configText);
    configWidgetValue->setLayout(configValue);


    ////////////////     CPU :     ////////////////
    ////  Create and configure CPU name label  ////
    SystemInfo sysInfo;
    QString cpuValue = sysInfo.getCpuName();
    configText = w.ShowConfig(configText, "CPU Name :"); // Add the CPU label (Text)
    configValue = w.ShowConfig(configValue, cpuValue); // Add the CPU label (Value return)


    ////////////////     RAM :     ////////////////
    ////  Create and configure RAM info label  ////
    QString ramValue = sysInfo.getRamInfo();
    configText = w.ShowConfig(configText, "RAM Info :"); // Add the RAM label (Text)
    configValue = w.ShowConfig(configValue, ramValue); // Add the RAM label (Value return)

    ///////////////     Disk :     ////////////////
    ////  Create and configure Disk info label  ///
    QString diskValue = sysInfo.getDiskInfo(); // Assuming getDiskInfo() is your function for retrieving disk info
    configText = w.ShowConfig(configText, "Disk Info : "); // Add the Disk label (Text)
    configValue = w.ShowConfig(configValue, diskValue); // Add the Disk label (Value return)

    //Add Config Widget
    verticalLayout->addWidget(configWidgetText);
    verticalLayout->addWidget(configWidgetValue);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////  Title and Graph  //////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    QStringList titles {"Potentiel de gaz à effet de serre", "Epuisement des ressources abiotiques", "Energie Primaire"};

    ///////////   Add Graph 1   ////////////
    QLabel *title_1 = new QLabel(titles[0]);
    title_1->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(title_1);
    verticalLayout->addWidget(graphWidget);

    graphLayout->addWidget(w.chartView);
    graphLayout->addWidget(w.chartView2);

    // Create the system info JSON object
    QJsonObject systemInfoJson = sysInfo.createSystemInfoJson(sysInfo);

    // Convert the JSON object to a JSON document
    QJsonDocument jsonDoc(systemInfoJson);

    // Convert the JSON document to a string
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);

    // Display the JSON string (you can replace this with your preferred way of displaying)
    qDebug() << "System Info JSON:";
    qDebug().noquote() << jsonString;

    windowLayout->addWidget(mainWidget);
    windowLayout->addWidget(graphWidget);

    // Appel de la fonction qui affiche les charts
    w.update_charts();

    w.setCentralWidget(window);
    w.setWindowState(Qt::WindowMaximized);

    w.show();
    return a.exec();
}
