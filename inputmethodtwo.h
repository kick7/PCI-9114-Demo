#ifndef INPUTMETHODTWO_H
#define INPUTMETHODTWO_H

#include <QObject>
#include "conio.h"
#include "windows.h"
#include "DAQPilot.h"

class InputMethodTwo : public QObject
{
    Q_OBJECT
public:
    explicit InputMethodTwo(QObject *parent = nullptr);

signals:
    void signal_error_information(QString message);

    void signal_successful_informarion(QString message);

private:
    void m_init();

    void m_start();

    void m_stop();

public slots:
    void start();

    void stop();

public:
    QString taskName;

private:
    HANDLE hDAQPilotTask;

    bool isRunning;
};

#endif // INPUTMETHODTWO_H
