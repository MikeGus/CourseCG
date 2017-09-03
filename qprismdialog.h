#ifndef QPRISMDIALOGUE_H
#define QPRISMDIALOGUE_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "prism.h"
#include <QObject>

class PrismDialog : public QDialog
{

	private:
		Q_OBJECT

		QLabel* labelTopRad;
		QLabel* labelBottomRad;
		QLabel* labelHeight;
		QLabel* labelEdges;
		QLabel* labelReflection;
		QLabel* labelDifReflection;
		QLabel* labelRefraction;

		QLineEdit* editTopRad;
		QLineEdit* editBottomRad;
		QLineEdit* editHeight;
		QLineEdit* editEdges;
		QLineEdit* editReflection;
		QLineEdit* editDifReflection;
		QLineEdit* editRefraction;

		QDialogButtonBox* buttons;

		void setUpGUI();

	public:
		explicit PrismDialog(QWidget* parent = 0);

	signals:
		void AcceptPrism(Prism& prism);

	public slots:
		void slotAcceptPrism();

};

#endif // QPRISMDIALOGUE_H
