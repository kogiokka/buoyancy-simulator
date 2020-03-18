
#pragma once

#include <QtCore/QObject>
#include <QtGui/QCursor>
#include <QtGui/QGuiApplication>


class Cursor : public QObject
{
	Q_OBJECT

public:
	explicit Cursor(QObject* parent = nullptr);

private:
	QCursor cursor;
	QPoint prevPos;

public:
	Q_INVOKABLE void recordPos();
	Q_INVOKABLE void restorePos();
	Q_INVOKABLE void shapeBlank();
	Q_INVOKABLE void shapeRestore();
};
