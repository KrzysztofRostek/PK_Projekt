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
                            double uMin, double uMax,
                            double yMin, double yMax,
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
        arxObj["sterowanie_min"] = uMin;
        arxObj["sterowanie_max"] = uMax;
        arxObj["regulowana_min"] = yMin;
        arxObj["regulowana_max"] = yMax;
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
            return false;
        }

        plik.write(doc.toJson(QJsonDocument::Indented));
        plik.close();
        return true;
    }

    bool wczytajKonfiguracje(const QString& sciezka,
                             std::vector<double>& a,
                             std::vector<double>& b,
                             int& opoznienie,
                             double& odchylenie,
                             double& uMin, double& uMax,
                             double& yMin, double& yMax,
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
            return false;
        }

        QByteArray dane = plik.readAll();
        plik.close();

        QJsonDocument doc = QJsonDocument::fromJson(dane);
        if (doc.isNull()) {
            return false;
        }

        QJsonObject json = doc.object();

        // Domyślne wartości
        a.clear();
        b.clear();
        opoznienie = 1;
        odchylenie = 0.0;
        uMin = -10.0;
        uMax = 10.0;
        yMin = -10.0;
        yMax = 10.0;

        if (json.contains("arx")) {
            QJsonObject arx = json["arx"].toObject();
            if (arx.contains("wektorA")) a = jsonDoWektora(arx["wektorA"].toArray());
            if (arx.contains("wektorB")) b = jsonDoWektora(arx["wektorB"].toArray());
            if (arx.contains("opoznienie")) opoznienie = arx["opoznienie"].toInt();
            if (arx.contains("odchylenie")) odchylenie = arx["odchylenie"].toDouble();
            if (arx.contains("sterowanie_min")) uMin = arx["sterowanie_min"].toDouble();
            if (arx.contains("sterowanie_max")) uMax = arx["sterowanie_max"].toDouble();
            if (arx.contains("regulowana_min")) yMin = arx["regulowana_min"].toDouble();
            if (arx.contains("regulowana_max")) yMax = arx["regulowana_max"].toDouble();
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
            Wypelnienie = gen["Wypelnienie"].toDouble(0.5);
        }

        interwalMs = json["interwalMs"].toInt(200);

        return true;
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
