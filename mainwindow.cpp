#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>


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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_charts()
{
    double calcul;
    double calcul2;

    chart->removeAllSeries();
    chart2->removeAllSeries();

    Series = new QPieSeries(chart);
    Series2 = new QPieSeries(chart2);

    Impact* impacts = new Impact();
    Verbose* verbose = new Verbose();

    Impact* ASSEMBLY_1 = new Impact();
    Impact* CPU_1 = new Impact();
    Impact* RAM_1 = new Impact();
    Impact* SSD_1 = new Impact();
    Impact* POWER_SUPPLY_1 = new Impact();
    Impact* CASE_1 = new Impact();
    Impact* MOTHERBOARD_1 = new Impact();

    for (int i = 0; i < 8; i++)
    {
        ImpactType* gwp=new ImpactType();
        ImpactType* adp=new ImpactType();
        ImpactType* pe=new ImpactType();
        for (int j = 0; j < 3; j++)
        {
            ImpactData* embedded=new ImpactData();
            ImpactData* use=new ImpactData();
            embedded->value = QRandomGenerator::global()->bounded(10) + 1; //random entre 1 et 10
            use->value = QRandomGenerator::global()->bounded(10) + 1; // random entre 1 et 10


            switch (j)
            {
            case 0:
                gwp->embedded = embedded;
                gwp->use = use;
                break;
            case 1:
                adp->embedded = embedded;
                adp->use = use;
                break;
            case 2:
                pe->embedded = embedded;
                pe->use = use;
                break;
            default:
                break;
            }
        }
        switch (i)
        {
        case 0:
            impacts->gwp = gwp;
            impacts->adp = adp;
            impacts->pe = pe;
            break;
        case 1:
            ASSEMBLY_1->gwp = gwp;
            ASSEMBLY_1->adp = adp;
            ASSEMBLY_1->pe = pe;
            break;
        case 2:
            CPU_1->gwp = gwp;
            CPU_1->adp = adp;
            CPU_1->pe = pe;
            break;
        case 3:
            RAM_1->gwp = gwp;
            RAM_1->adp = adp;
            RAM_1->pe = pe;
            break;
        case 4:
            SSD_1->gwp = gwp;
            SSD_1->adp = adp;
            SSD_1->pe = pe;
            break;
        case 5:
            POWER_SUPPLY_1->gwp = gwp;
            POWER_SUPPLY_1->adp = adp;
            POWER_SUPPLY_1->pe = pe;
            break;
        case 6:
            CASE_1->gwp = gwp;
            CASE_1->adp = adp;
            CASE_1->pe = pe;
            break;
        case 7:
            MOTHERBOARD_1->gwp = gwp;
            MOTHERBOARD_1->adp = adp;
            MOTHERBOARD_1->pe = pe;
            break;
        default:
            break;
        }
    }
    //assignation valeurs


    //assignation

    verbose->ASSEMBLY_1 = ASSEMBLY_1;
    verbose->CPU_1 = CPU_1;
    verbose->RAM_1 = RAM_1;
    verbose->SSD_1 = SSD_1;
    verbose->POWER_SUPPLY_1 = POWER_SUPPLY_1;
    verbose->CASE_1 = CASE_1;
    verbose->MOTHERBOARD_1 = MOTHERBOARD_1;

    all_datas->impacts = impacts;
    all_datas->verbose = verbose;



    QStringList categories{ "Usage", "Manufacturing RAM", "Manufacturing CPU", "Manufacturing SSD", "Manufacturing HDD", "Manufacturing Others" };
    QStringList categories2{ "Usage", "Manufacturing" };
    //ordre : gwp puis pe puis adp



    int cpt = 0;
    foreach(QString categorie, categories)
    {
        switch (cpt)
        {
        case 0:
            Series->append(new QPieSlice(categorie, all_datas->impacts->gwp->use->value));
            break;
        case 1:
            Series->append(new QPieSlice(categorie, all_datas->verbose->RAM_1->gwp->embedded->value));
            break;
        case 2:
            Series->append(new QPieSlice(categorie, all_datas->verbose->CPU_1->gwp->embedded->value));
            break;
        case 3:
            Series->append(new QPieSlice(categorie, all_datas->verbose->SSD_1->gwp->embedded->value));
            break;
        case 4:
            Series->append(new QPieSlice(categorie, 0));
            break;
        case 5:
            calcul = all_datas->verbose->ASSEMBLY_1->gwp->embedded->value + all_datas->verbose->POWER_SUPPLY_1->gwp->embedded->value + all_datas->verbose->CASE_1->gwp->embedded->value + all_datas->verbose->POWER_SUPPLY_1->gwp->embedded->value + all_datas->verbose->MOTHERBOARD_1->gwp->embedded->value;
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
            Series2->append(new QPieSlice(categorie, all_datas->impacts->gwp->use->value));
            break;
        case 1:
            calcul2 = all_datas->verbose->SSD_1->gwp->embedded->value + all_datas->verbose->RAM_1->gwp->embedded->value + all_datas->verbose->CPU_1->gwp->embedded->value + all_datas->verbose->ASSEMBLY_1->gwp->embedded->value + all_datas->verbose->POWER_SUPPLY_1->gwp->embedded->value + all_datas->verbose->CASE_1->gwp->embedded->value + all_datas->verbose->POWER_SUPPLY_1->gwp->embedded->value + all_datas->verbose->MOTHERBOARD_1->gwp->embedded->value;
            Series2->append(new QPieSlice(categorie, calcul2));
            break;
        default:
            break;
        }
        cpt += 1;
    }
    chart->addSeries(Series);
    chart2->addSeries(Series2);



    chart->legend()->setVisible(true);


    chartView->update();
    chartView2->update();
}

QHBoxLayout* MainWindow::ShowConfig(QHBoxLayout* BoxH, QString string){

    QLabel *Label = new QLabel(string);
    Label->setAlignment(Qt::AlignCenter);

    BoxH->addWidget(Label);// Add the Label

    return BoxH;
}

