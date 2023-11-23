#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include "ServerImpactFactory.h"
#include "Chart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ServerImpactFactory* ServImpactFactory;
    QJsonObject systemInfoJson;
    ServerImpact* all_datas;

    QStringList titles {"Potentiel de gaz à effet de serre", "Epuisement des ressources abiotiques", "Energie Primaire"};
    QLabel *title;

    Chart* chart1 = new Chart();
    Chart* chart2 = new Chart();

    int current_category=-1;

    QHBoxLayout* ShowConfig(QHBoxLayout* BoxH, QString string, bool bold = false);

    void recoverInfoPC();
    void recoverAPI();

private:
    Ui::MainWindow *ui;

public slots:
    void update_charts(bool up);
    void new_datas(ServerImpact* new_datas);
    void onButtonBeforeClicked();
    void onButtonAfterClicked();
};
#endif // MAINWINDOW_H
