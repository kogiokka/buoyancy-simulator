#include "render/Cursor.h"


Cursor::Cursor(QObject* parent)
	: QObject(parent)
{ }

void Cursor::recordPos()
{
	prevPos = cursor.pos();
}

#include <iostream>
void Cursor::restorePos()
{
	cursor.setPos(prevPos);
}

void Cursor::shapeBlank()
{
	QGuiApplication::setOverrideCursor(Qt::BlankCursor);
}

void Cursor::shapeRestore()
{
	QGuiApplication::restoreOverrideCursor();
}
