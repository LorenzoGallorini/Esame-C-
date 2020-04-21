#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QListWidgetItem>

using namespace QtCharts;
/**
 * @brief MainWindow::MainWindow
 * Costruttore
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab->setGeometry(this->rect());
    Etichette = new QList<QLabel*>();
    MBarSet = new QList<QBarSet*>();
    MBarSeries = new QList<QBarSeries*>();
    MChart = new QList<QChart*>();
    MAxis = new QList<QBarCategoryAxis*>();
    MVaxis = new QList<QValueAxis*>();
    MGraphic = new QList<QGraphicsScene*>();
}
/**
 * @brief MainWindow::~MainWindow
 * Distruttore
 */
MainWindow::~MainWindow()
{
    for(int i=0;i<Etichette->count();i++)
       delete Etichette->at(i);
    delete Etichette;
    delete EMIW;
    delete UNIW;
    for(int i =0;i<MBarSet->count();i++)
        delete MBarSet->at(i);
    delete MBarSet;
    for(int i = 0; i<MBarSeries->count();i++)
        delete MBarSeries->at(i);
    delete MBarSeries;
    for(int i=0;i<MAxis->count();i++)
        delete MAxis->at(i);
    delete MAxis;
    for(int i=0;i<MVaxis->count();i++)
        delete MVaxis->at(i);
    delete MVaxis;
    for(int i=0;i<MChart->count();i++)
        delete MChart->at(i);
    delete MChart;
    for (int i = 0;i<MGraphic->count();i++)
        delete MGraphic->at(i);
    delete MGraphic;
    delete ui;
}
/**
 * @brief MainWindow::setListEMI
 * Questo metodo imposta la lista di etichette della casa discografica EMI
 * @param lista
 */
void MainWindow::setListEMI(QStringList lista)
{

    ui->EMI->insertColumn(0);
    EMIW =  new QTableWidgetItem("Artisti EMI");
    ui->EMI->setHorizontalHeaderItem(0,EMIW);

    for (int i=0;i<lista.count();i++)
    {

        ui->EMI->insertRow(i);
        QLabel* t = new QLabel(lista[i]);
        t->setOpenExternalLinks(true);
        ui->EMI->setCellWidget(i,0,t);
        Etichette->append(t);
    }
    ui->EMI->resizeColumnsToContents();
}
/**
 * @brief MainWindow::setListUNIVERSAL
 * Questo metodo imposta la lista di etichette della casa discografica Universal
 * @param lista
 */
void MainWindow::setListUNIVERSAL(QStringList lista)
{
    ui->UNIVERSAL->insertColumn(0);
    UNIW = new QTableWidgetItem("Artisti Universal");
    ui->UNIVERSAL->setHorizontalHeaderItem(0, UNIW);
    for (int i=0;i<lista.count();i++)
    {
        ui->UNIVERSAL->insertRow(i);
        QLabel* t = new QLabel(lista[i]);
        t->setOpenExternalLinks(true);
        ui->UNIVERSAL->setCellWidget(i,0,t);
    }
    ui->UNIVERSAL->resizeColumnsToContents();
}
/**
 * @brief MainWindow::renderGraphic
 * Questo metodo serve per Renderizzare i due grafici relativi alle lettere
 * @param array
 * @param isEMI
 */
void MainWindow::renderGraphic(int array[27],bool isEMI)
{
        QBarSet *set0;
        if (isEMI)
           set0 = new QBarSet("Artisti EMI");
        else
           set0 = new QBarSet("Artisti Universal");
        MBarSet->append(set0);
        for(int i=0; i<27;i++)
            *set0<<array[i];
        QBarSeries *series = new QBarSeries();
        MBarSeries->append(series);
        series->append(set0);
        QChart *chart = new QChart();
        MChart->append(chart);
        chart->addSeries(series);
        if (isEMI)
            chart->setTitle("Artisti EMI suddivisi per lettere");
        else
            chart->setTitle("Artisti Universal suddivisi per lettere");
        chart->setAnimationOptions(QChart::AllAnimations);
        QStringList categories;
        QString ALFABETO = "a_b_c_d_e_f_g_h_i_j_k_l_m_n_o_p_q_r_s_t_u_v_w_x_y_z_#";
        categories.append(ALFABETO.split("_"));
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        MAxis->append(axisX);
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        QValueAxis *axisY = new QValueAxis();
        MVaxis->append(axisY);
        axisY->setRange(0,100);
        axisY->applyNiceNumbers();
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        chart->legend()->setVisible(true);

        chart->legend()->setAlignment(Qt::AlignBottom);
         if (isEMI)
            chart->setGeometry(ui->GraficoEMI->rect());
         else
             chart->setGeometry(ui->GraficoUniversal->rect());
        QGraphicsScene *scene = new QGraphicsScene();
        MGraphic->append(scene);
        scene->addItem(chart);
        if (isEMI)
        {
            scene->setSceneRect(ui->GraficoEMI->rect());
            ui->GraficoEMI->setScene(scene);
        }
        else
        {
            scene->setSceneRect(ui->GraficoUniversal->rect());
            ui->GraficoUniversal->setScene(scene);
        }
}
/**
 * @brief MainWindow::renderGraphic2
 * Questo grafico renderizza il numero di artisti per ogni casa discografica
 * @param Universal
 * @param EMI
 */
void MainWindow::renderGraphic2(int Universal,int EMI)
{
    QBarSet *set0;
    set0 = new QBarSet("Artisti");
    MBarSet->append(set0);
    *set0<<Universal<<EMI;
    QBarSeries *series = new QBarSeries();
    MBarSeries->append(series);
    series->append(set0);
    QChart *chart = new QChart();
    MChart->append(chart);
    chart->addSeries(series);
    chart->setTitle("Artisti Universal e EMI");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories;
    QString ALFABETO = "Universal_EMI";
    categories.append(ALFABETO.split("_"));
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    MAxis->append(axisX);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    MVaxis->append(axisY);
    axisY->setRange(0,1000);
    axisY->applyNiceNumbers();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QGraphicsScene *scene = new QGraphicsScene();
    MGraphic->append(scene);
    chart->setGeometry(ui->GraficoUniversal->rect());

    scene->addItem(chart);
    scene->setSceneRect(ui->GraficoUniversal->rect());
    ui->GraficoArtisti->setScene(scene);
}
/**
 * @brief MainWindow::resizeEvent
 * Questo metodo serve per gestire la posizione dei contenuti in base alla grandezza della finestra
 * @param event
 */
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   ui->label_2->move(event->size().width()/2-55,25);
   ui->tabWidget->resize(event->size().width(),event->size().height());
   ui->tabWidget->move(0,10);
   ui->EMI->resize(event->size().width()/2-50,event->size().height()-150);
   ui->EMI->move(event->size().width()/2,50);
   ui->UNIVERSAL->resize(event->size().width()/2-50,event->size().height()-150);
   ui->GraficoEMI->resize(event->size().width(),event->size().height());
   ui->GraficoUniversal->resize(event->size().width(),event->size().height());
   ui->GraficoArtisti->resize(event->size().width(),event->size().height());
}

