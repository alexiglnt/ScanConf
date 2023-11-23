#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ServerImpact.h"
#include "ServerImpactFactory.h"
#include "SystemInfo.h"

#include <QCoreApplication>
#include <QJsonObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_charts(bool up)
{
    if (up) {
        current_category += 1;
    } else {
        current_category -= 1;
    }

    if (current_category < 0) {
        current_category = 2;
    } if (current_category > 2) {
        current_category = 0;
    }

    double calcul;
    double calcul2;

    QPieSeries* Series = new QPieSeries(chart1->m_chart);
    QPieSeries* Series2 = new QPieSeries(chart2->m_chart);

    QStringList categories{ "Usage", "Manufacturing RAM", "Manufacturing CPU", "Manufacturing SSD", "Manufacturing HDD", "Manufacturing Others" };
    QStringList categories2{ "Usage", "Manufacturing" };

    int cpt = 0;
    switch(current_category)
    {
    case 0:
        foreach(QString categorie, categories)
        {
            switch (cpt)
            {
            case 0:
                Series->append(new QPieSlice(categorie, all_datas->globalImpacts.gwp.use.value ));
                break;
            case 1:
                Series->append(new QPieSlice(categorie, all_datas->verbose["RAM-1"].impacts.gwp.use.value));
                break;
            case 2:
                Series->append(new QPieSlice(categorie, all_datas->verbose["CPU-1"].impacts.gwp.use.value));
                break;
            case 3:
                Series->append(new QPieSlice(categorie, all_datas->verbose["SSD-1"].impacts.gwp.use.value));
                break;
            case 4:
                Series->append(new QPieSlice(categorie, 0));
                break;
            case 5:
                calcul = all_datas->verbose["ASSEMBLY-1"].impacts.gwp.use.value + all_datas->verbose["POWER_SUPPLY-1"].impacts.gwp.use.value + all_datas->verbose["CASE-1"].impacts.gwp.use.value + all_datas->verbose["MOTHERBOARD-1"].impacts.gwp.use.value;
                qDebug() << "Calcul : " << calcul;
                Series->append(new QPieSlice(categorie, calcul));
                break;
            default:
                break;
            }
            cpt += 1;
        }
        cpt = 0;
        //ordre : gwp puis pe puis adp et usage puis manufacturing
        foreach(QString categorie, categories2)
        {
            switch (cpt)
            {
            case 0:
                Series2->append(new QPieSlice(categorie, all_datas->globalImpacts.gwp.use.value));
                break;
            case 1:
                //calcul2 = all_datas->verbose["SSD-1"].impacts.gwp.use.value + all_datas->verbose["RAM-1"].impacts.gwp.use.value + all_datas->verbose["CPU-1"].impacts.gwp.use.value + all_datas->verbose["POWER_SUPPLY-1"].impacts.gwp.use.value + all_datas->verbose["CASE-1"].impacts.gwp.use.value + all_datas->verbose["MOTHERBOARD-1"].impacts.gwp.use.value + all_datas->verbose["ASSEMBLY-1"].impacts.gwp.use.value;
                calcul2 = all_datas->globalImpacts.gwp.embedded.value;
                qDebug() << "Calcul2 : " << calcul2;
                Series2->append(new QPieSlice(categorie, calcul2));
                break;
            default:
                break;
            }
            cpt += 1;
        }
        break;
    case 1:
        foreach(QString categorie, categories)
        {
            switch (cpt)
            {
            case 0:
                Series->append(new QPieSlice(categorie, all_datas->globalImpacts.adp.use.value ));
                break;
            case 1:
                Series->append(new QPieSlice(categorie, all_datas->verbose["RAM-1"].impacts.adp.use.value));
                break;
            case 2:
                Series->append(new QPieSlice(categorie, all_datas->verbose["CPU-1"].impacts.adp.use.value));
                break;
            case 3:
                Series->append(new QPieSlice(categorie, all_datas->verbose["SSD-1"].impacts.adp.use.value));
                break;
            case 4:
                Series->append(new QPieSlice(categorie, 0));
                break;
            case 5:
                calcul = all_datas->verbose["ASSEMBLY-1"].impacts.adp.use.value + all_datas->verbose["POWER_SUPPLY-1"].impacts.adp.use.value + all_datas->verbose["CASE-1"].impacts.adp.use.value + all_datas->verbose["MOTHERBOARD-1"].impacts.adp.use.value;
                qDebug() << "Calcul : " << calcul;
                Series->append(new QPieSlice(categorie, calcul));
                break;
            default:
                break;
            }
            cpt += 1;
        }
        cpt = 0;
        //ordre : gwp puis pe puis adp et usage puis manufacturing
        foreach(QString categorie, categories2)
        {
            switch (cpt)
            {
            case 0:
                Series2->append(new QPieSlice(categorie, all_datas->globalImpacts.adp.use.value));
                break;
            case 1:
                //calcul2 = all_datas->verbose["SSD-1"].impacts.gwp.use.value + all_datas->verbose["RAM-1"].impacts.gwp.use.value + all_datas->verbose["CPU-1"].impacts.gwp.use.value + all_datas->verbose["POWER_SUPPLY-1"].impacts.gwp.use.value + all_datas->verbose["CASE-1"].impacts.gwp.use.value + all_datas->verbose["MOTHERBOARD-1"].impacts.gwp.use.value + all_datas->verbose["ASSEMBLY-1"].impacts.gwp.use.value;
                calcul2 = all_datas->globalImpacts.adp.embedded.value;
                qDebug() << "Calcul2 : " << calcul2;
                Series2->append(new QPieSlice(categorie, calcul2));
                break;
            default:
                break;
            }
            cpt += 1;
        }
        break;
    case 2:
        foreach(QString categorie, categories)
        {
            switch (cpt)
            {
            case 0:
                Series->append(new QPieSlice(categorie, all_datas->globalImpacts.pe.use.value ));
                break;
            case 1:
                Series->append(new QPieSlice(categorie, all_datas->verbose["RAM-1"].impacts.pe.use.value));
                break;
            case 2:
                Series->append(new QPieSlice(categorie, all_datas->verbose["CPU-1"].impacts.pe.use.value));
                break;
            case 3:
                Series->append(new QPieSlice(categorie, all_datas->verbose["SSD-1"].impacts.pe.use.value));
                break;
            case 4:
                Series->append(new QPieSlice(categorie, 0));
                break;
            case 5:
                calcul = all_datas->verbose["ASSEMBLY-1"].impacts.pe.use.value + all_datas->verbose["POWER_SUPPLY-1"].impacts.pe.use.value + all_datas->verbose["CASE-1"].impacts.pe.use.value + all_datas->verbose["MOTHERBOARD-1"].impacts.pe.use.value;
                qDebug() << "Calcul : " << calcul;
                Series->append(new QPieSlice(categorie, calcul));
                break;
            default:
                break;
            }
            cpt += 1;
        }
        cpt = 0;
        //ordre : gwp puis pe puis adp et usage puis manufacturing
        foreach(QString categorie, categories2)
        {
            switch (cpt)
            {
            case 0:
                Series2->append(new QPieSlice(categorie, all_datas->globalImpacts.pe.use.value));
                break;
            case 1:
                //calcul2 = all_datas->verbose["SSD-1"].impacts.gwp.use.value + all_datas->verbose["RAM-1"].impacts.gwp.use.value + all_datas->verbose["CPU-1"].impacts.gwp.use.value + all_datas->verbose["POWER_SUPPLY-1"].impacts.gwp.use.value + all_datas->verbose["CASE-1"].impacts.gwp.use.value + all_datas->verbose["MOTHERBOARD-1"].impacts.gwp.use.value + all_datas->verbose["ASSEMBLY-1"].impacts.gwp.use.value;
                calcul2 = all_datas->globalImpacts.pe.embedded.value;
                qDebug() << "Calcul2 : " << calcul2;
                Series2->append(new QPieSlice(categorie, calcul2));
                break;
            default:
                break;
            }
            cpt += 1;
        }
        break;
    }


    chart1->Series = Series;
    chart2->Series = Series2;

    // Maj des charts
    chart1->update();
    chart2->update();
}

QHBoxLayout* MainWindow::ShowConfig(QHBoxLayout* BoxH, QString string){

    QLabel *Label = new QLabel(string);
    Label->setAlignment(Qt::AlignCenter);

    BoxH->addWidget(Label);// Add the Label

    return BoxH;
}


void MainWindow::recoverInfoPC()
{
    SystemInfo sysInfo;
    systemInfoJson = sysInfo.createSystemInfoJson(sysInfo);
}

void MainWindow::recoverAPI()
{
    ServImpactFactory = new ServerImpactFactory(this);

    ServImpactFactory->postServerImpact(&systemInfoJson);

    // Appel de la fonction qui affiche les charts
    QObject::connect(ServImpactFactory, &ServerImpactFactory::endRead, this, &MainWindow::new_datas);
}

void MainWindow::new_datas(ServerImpact* new_datas)
{
    all_datas=new_datas;
    update_charts(true);
}

void MainWindow::onButtonBeforeClicked()
{
    this->update_charts(false);
}

void MainWindow::onButtonAfterClicked()
{
    this->update_charts(true);
}

