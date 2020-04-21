#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableWidget>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setListEMI(QStringList Lista);
    void setListUNIVERSAL(QStringList lista);
    void renderGraphic(int array[27],bool isEMI);
    void renderGraphic2(int Universal,int EMI);
    void resizeEvent(QResizeEvent*);

private:
    Ui::MainWindow *ui;
    QList<QLabel*>* Etichette;
    QTableWidgetItem* EMIW;
    QTableWidgetItem* UNIW;
    QList<QBarSet*>* MBarSet;
    QList<QBarSeries*>* MBarSeries;
    QList<QChart*>* MChart;
    QList<QBarCategoryAxis*>* MAxis;
    QList<QValueAxis*>* MVaxis;
    QList<QGraphicsScene*>* MGraphic;
};
#endif // MAINWINDOW_H
