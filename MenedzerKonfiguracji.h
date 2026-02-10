#ifndef MENEDZERKONFIGURACJI_H
#define MENEDZERKONFIGURACJI_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <vector>

class MenedzerKonfiguracji : public QObject
{
    Q_OBJECT

public:
    explicit MenedzerKonfiguracji(QObject *parent = nullptr) : QObject(parent) {}

    bool zapiszKonfiguracje(const QString& sciezka,
                            const std::vector<double>& a,
                            const std::vector<double>& b,
                            int opoznienie,
                            double odchylenie,
                            double Kp,
                            double Ti,
                            double Td,
                            int typCalki,
                            int trybGeneratora,
                            double amplituda,
                            double czestotliwosc,
                            double StalaSkladniowa,
                            double Wypelnienie,
                            int interwalMs)
    {
        QJsonObject json;

        QJsonObject arxObj;
        arxObj["wektorA"] = wektorDoJson(a);
        arxObj["wektorB"] = wektorDoJson(b);
        arxObj["opoznienie"] = opoznienie;
        arxObj["odchylenie"] = odchylenie;
        json["arx"] = arxObj;

        QJsonObject pidObj;
        pidObj["Kp"] = Kp;
        pidObj["Ti"] = Ti;
        pidObj["Td"] = Td;
        pidObj["typCalki"] = typCalki;
        json["pid"] = pidObj;

        QJsonObject genObj;
        genObj["tryb"] = trybGeneratora;
        genObj["amplituda"] = amplituda;
        genObj["czestotliwosc"] = czestotliwosc;
        genObj["StalaSkladniowa"] = StalaSkladniowa;
        genObj["Wypelnienie"] = Wypelnienie;
        json["generator"] = genObj;

        json["interwalMs"] = interwalMs;

        QJsonDocument doc(json);
        QFile plik(sciezka);

        if (!plik.open(QIODevice::WriteOnly)) {
            return 0;
        }

        plik.write(doc.toJson(QJsonDocument::Indented));
        plik.close();
        return 1;
    }
    bool wczytajKonfiguracje(const QString& sciezka,
                             std::vector<double>& a,
                             std::vector<double>& b,
                             int& opoznienie,
                             double& odchylenie,
                             double& Kp,
                             double& Ti,
                             double& Td,
                             int& typCalki,
                             int& trybGeneratora,
                             double& amplituda,
                             double& czestotliwosc,
                             double& StalaSkladniowa,
                             double& Wypelnienie,
                             int& interwalMs)
    {
        QFile plik(sciezka);
        if (!plik.open(QIODevice::ReadOnly)) {
            return 0;
        }

        QByteArray dane = plik.readAll();
        plik.close();

        QJsonDocument doc = QJsonDocument::fromJson(dane);
        if (doc.isNull()) {
            return 0;
        }

        QJsonObject json = doc.object();

        if (json.contains("arx")) {
            QJsonObject arx = json["arx"].toObject();
            a = jsonDoWektora(arx["wektorA"].toArray());
            b = jsonDoWektora(arx["wektorB"].toArray());
            opoznienie = arx["opoznienie"].toInt(1);
            odchylenie = arx["odchylenie"].toDouble(0.0);
        }

        if (json.contains("pid")) {
            QJsonObject pid = json["pid"].toObject();
            Kp = pid["Kp"].toDouble(1.0);
            Ti = pid["Ti"].toDouble(0.0);
            Td = pid["Td"].toDouble(0.0);
            typCalki = pid["typCalki"].toInt(0);

        }

        if (json.contains("generator")) {
            QJsonObject gen = json["generator"].toObject();
            trybGeneratora = gen["tryb"].toInt(0);
            amplituda = gen["amplituda"].toDouble(1.0);
            czestotliwosc = gen["czestotliwosc"].toDouble(1.0);
            StalaSkladniowa = gen["StalaSkladniowa"].toDouble(0.0);
            Wypelnienie = gen["Wypelnienie"].toDouble(0.0);
        }

        interwalMs = json["interwalMs"].toInt(200);

        return 1;
    }

private:
    static QJsonArray wektorDoJson(const std::vector<double>& wektor)
    {
        QJsonArray array;
        for (double val : wektor) {
            array.append(val);
        }
        return array;
    }

    static std::vector<double> jsonDoWektora(const QJsonArray& jsonArray)
    {
        std::vector<double> wektor;
        for (const QJsonValue& val : jsonArray) {
            wektor.push_back(val.toDouble());
        }
        return wektor;
    }
};

#endif // MENEDZERKONFIGURACJI_H
