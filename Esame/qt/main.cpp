#include "mainwindow.h"

#include <QApplication>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtGui>
#include <QListWidget>
#include <QListWidgetItem>

int LetterEMI[27];
int LetterUniversal[27];
/**
 * @brief GetFromUrl
 * Questo metodo sbilisce una connessione con il server e recupera sotto
 * forma di stringa il file caricato sul server.
 * @param url
 * @return
 */
QString GetFromUrl(QString url)
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QString content = response->readAll();
    event.quit();
    return content;
}
/**
 * @brief LinkedList
 * Questo metodo processa la stringa nel file e mi crea
 * un array di stringhe già sotto forma di link (<a href ... >)
 * @param stringa
 * @return
 */
QStringList LinkedList(QString stringa)
{
    QStringList res = stringa.split("\n");

    for(int i = 0; i< res.count(); i++)
    {
        QStringList lista = res[i].remove('"').split(' ');
        if (lista.count() == 2)
        {
            QString description("Description:");
            QString hyperlinkText;
            if (lista[0].contains("http"))
                 hyperlinkText = "<a href=\""+lista[0]+"\">"+lista[1]+"</a>";
            else if (lista[0].isEmpty())
                hyperlinkText=lista[1];
            else
                 hyperlinkText = "<a href=\"https://it.wikipedia.org"+lista[0]+"\">"+lista[1]+"</a>";
            res[i]=hyperlinkText;
        }
        else if (lista.count()>2)
        {
            QString link = lista[0];
            QString value;
            for (int i = 1;i<lista.count();i++)
                value += lista[i];
            QString hyperlinkText;
            if (lista[0].contains("http"))
                 hyperlinkText = "<a href=\""+link+"\">"+value+"</a>";
            else if (lista[0].isEmpty())
                hyperlinkText=value;
            else
                 hyperlinkText = "<a href=\"https://it.wikipedia.org"+link+"\">"+value+"</a>";
            res[i]=hyperlinkText;
        }
        else if(lista.count()==1 && lista[0].contains("wiki"))
        {
            res[i]="<a href=\"https://it.wikipedia.org"+lista[0]+"\">"+lista[0]+"</a>";;
        }
    }
    return res;
}
/**
 * @brief CountLetter
 * Questo metodo serve per contare quante le iniziali dei cantanti
 * @param stringa
 * @param isEMI
 */
void CountLetter(QString stringa, bool isEMI)
{
    int NLetter = 27;
    int letters[NLetter];
    for (int i=0;i<NLetter;i++)
        letters[i]=0;
    QStringList res = stringa.split("\n");

    for(int i = 0; i< res.count(); i++)
    {
        QStringList lista = res[i].remove('"').split(' ');
        if (lista.count() > 1)
        {
            int a = lista[1][0].toUpper().toLatin1();
            int index = a-65;
            if (index >=0 && index <=25)
                if (isEMI)
                    LetterEMI[index]++;
                else
                    LetterUniversal[index]++;
            else
                if (isEMI)
                    LetterEMI[26]++;
                else
                    LetterUniversal[26]++;
        }
        else
            if (isEMI)
                LetterEMI[26]++;
            else
                LetterUniversal[26]++;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget centralwidget;
    w.show();
    QString EMIFILE = GetFromUrl("http://www.ivl.disco.unimib.it/minisites/cpp/List_of_EMI_artists.txt");
    QString UNIVERSALFILE = GetFromUrl("http://www.ivl.disco.unimib.it/minisites/cpp/List_of_Universal_artists.txt");
    QStringList ListaEMI = LinkedList(EMIFILE);
    QStringList ListaUNI = LinkedList(UNIVERSALFILE);
    w.setListEMI(ListaEMI);
    w.setListUNIVERSAL(ListaUNI);
    CountLetter(EMIFILE,true);
    CountLetter(UNIVERSALFILE,false);
    w.renderGraphic(LetterEMI,true);
    w.renderGraphic(LetterUniversal,false);
    w.renderGraphic2(ListaUNI.count(),ListaEMI.count());
    return a.exec();
}


