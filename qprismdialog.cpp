#include "qprismdialog.h"
#include <QGridLayout>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QPushButton>
#include "point.h"
#include <QMessageBox>
#include <QDebug>

PrismDialog::PrismDialog(QWidget *parent) : QDialog(parent)
{
	setUpGUI();
	setWindowTitle(tr("Параметры призмы"));
	setModal(true);
}

void PrismDialog::setUpGUI()
{
	QGridLayout* formGridLayout = new QGridLayout(this);

	labelBottomRad = new QLabel(this);
	labelBottomRad->setText("Радиус ниж. основния");
	labelTopRad = new QLabel(this);
	labelTopRad->setText("Радиус вер. основния");
	labelHeight = new QLabel(this);
	labelHeight->setText("Высота");
	labelEdges = new QLabel(this);
	labelEdges->setText("Грани");
	labelReflection = new QLabel(this);
	labelReflection->setText("Коэф. зерк. отражения");
	labelDifReflection = new QLabel(this);
	labelDifReflection->setText("Коэф. диф. отражения");
	labelRefraction = new QLabel(this);
	labelRefraction->setText("Коэф. преломления");

	buttons = new QDialogButtonBox(this);
	buttons->addButton(QDialogButtonBox::Ok);
	buttons->addButton(QDialogButtonBox::Cancel);
	buttons->button(QDialogButtonBox::Ok)->setText(tr("Подтвердить"));
	buttons->button(QDialogButtonBox::Cancel)->setText(tr("Отмена"));

	editBottomRad = new QLineEdit(this);
	editBottomRad->setValidator(new QDoubleValidator(0, 1000, 1, this));
	labelBottomRad->setBuddy(editBottomRad);
	editTopRad = new QLineEdit(this);
	editTopRad->setValidator(new QDoubleValidator(0, 1000, 1, this));
	labelTopRad->setBuddy(editTopRad);
	editHeight = new QLineEdit(this);
	editHeight->setValidator(new QDoubleValidator(0.1, 1000, 1, this));
	labelHeight->setBuddy(editHeight);
	editEdges = new QLineEdit(this);
	editEdges->setValidator(new QIntValidator(3, 10000, this));
	labelEdges->setBuddy(editEdges);
	editReflection = new QLineEdit(this);
	editReflection->setValidator(new QDoubleValidator(0, 1, 2, this));
	labelReflection->setBuddy(editReflection);
	editDifReflection = new QLineEdit(this);
	editDifReflection->setValidator(new QDoubleValidator(0, 1, 2, this));
	labelDifReflection->setBuddy(editDifReflection);
	editRefraction = new QLineEdit(this);
	editRefraction->setValidator(new QDoubleValidator(0, 1, 2, this));
	labelRefraction->setBuddy(editRefraction);

	formGridLayout->addWidget(labelBottomRad, 0, 0);
	formGridLayout->addWidget(labelTopRad, 1, 0);
	formGridLayout->addWidget(labelHeight, 2, 0);
	formGridLayout->addWidget(labelEdges, 3, 0);
	formGridLayout->addWidget(labelReflection, 4, 0);
	formGridLayout->addWidget(labelDifReflection, 5, 0);
	formGridLayout->addWidget(labelRefraction, 6, 0);
	formGridLayout->addWidget(buttons, 7, 0, 2, 1);


	formGridLayout->addWidget(editBottomRad, 0, 1);
	formGridLayout->addWidget(editTopRad, 1, 1);
	formGridLayout->addWidget(editHeight, 2, 1);
	formGridLayout->addWidget(editEdges, 3, 1);
	formGridLayout->addWidget(editReflection, 4, 1);
	formGridLayout->addWidget(editDifReflection, 5, 1);
	formGridLayout->addWidget(editRefraction, 6, 1);

	setLayout(formGridLayout);

	connect(buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(slotAcceptPrism()));
	connect(buttons->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}

void PrismDialog::slotAcceptPrism()
{
	Point coord(0,0,0);
	float btm_rad = editBottomRad->text().replace(",",".").toFloat();
	float top_rad = editTopRad->text().replace(",",".").toFloat();

	if (btm_rad != 0 || top_rad != 0) {
		float height = editHeight->text().replace(",",".").toFloat();
		if (height != 0) {
			int edges = editEdges->text().replace(",",".").toInt();
			if (edges > 2) {
				float reflect = editReflection->text().replace(",",".").toFloat();
				float refract = editRefraction->text().replace(",",".").toFloat();
				float difreflect = editDifReflection->text().replace(",",".").toFloat();

				if (reflect + refract + difreflect <= 1) {
					Prism prism(coord, reflect, refract, difreflect, height, top_rad, btm_rad, edges);
					emit AcceptPrism(prism);
					close();
				}
				else {
					QMessageBox msgInfo;
					msgInfo.setText("Ошибка данных");
					msgInfo.setIcon(QMessageBox::Warning);
					msgInfo.setInformativeText("Сумма коэффициентов отражения и преломления не может превышать 1.");
					msgInfo.exec();
				}

			}
			else {
				QMessageBox msgInfo;
				msgInfo.setText("Ошибка данных");
				msgInfo.setIcon(QMessageBox::Warning);
				msgInfo.setInformativeText("Боковых граней не может быть меньше 3.");
				msgInfo.exec();
			}
		}
		else {
			QMessageBox msgInfo;
			msgInfo.setText("Ошибка данных");
			msgInfo.setIcon(QMessageBox::Warning);
			msgInfo.setInformativeText("Высота призмы не может быть нулевой.");
			msgInfo.exec();
		}
	}
	else {
		QMessageBox msgInfo;
		msgInfo.setText("Ошибка данных");
		msgInfo.setIcon(QMessageBox::Warning);
		msgInfo.setInformativeText("Призма не может выродиться в отрезок.");
		msgInfo.exec();
	}
}
