#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include "qprismdialog.h"
#include <QColorDialog>
#include <QGraphicsPixmapItem>
#include "beam.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->radioButton->toggle();
	setFixedSize(900, 600);
	ui->graphicsView->setFixedSize(screen_size_x, screen_size_y);
	ui->graphicsView->setScene(&scene);
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene.setSceneRect(-screen_size_x / 2, -screen_size_y / 2, screen_size_x, screen_size_y);

	pixmap = new QPixmap(screen_size_x, screen_size_y);
	painter = new QPainter(pixmap);
}

MainWindow::~MainWindow()
{
	delete painter;
	delete pixmap;
	delete ui;
}

void MainWindow::on_actionInfo_triggered()
{
	QMessageBox msgInfo;
	msgInfo.setWindowTitle("Информация");
	msgInfo.setText("Назначение программы");
	msgInfo.setIcon(QMessageBox::Information);
	msgInfo.setInformativeText("Данная программа позволяет составлять суперпозицию призматических объектов и строить на ее основе реалистическое изображение с помощью глобальной модели освещения и метода трассировки лучей.");
	msgInfo.exec();
}

void MainWindow::on_btnAddPrism_clicked()
{
	PrismDialog* addPrismDialog = new PrismDialog(this);
	connect(addPrismDialog, SIGNAL(AcceptPrism(Prism&)), this, SLOT(addPrism(Prism&)));
	addPrismDialog->exec();
	ui->graphicsView->setFocus();

	ui->radioButton->toggle();
	visualize_carcass();
}

void MainWindow::on_btnDelPrism_clicked()
{
	if (ui->listWidget->currentItem()) {
		manager.del_prism(ui->listWidget->currentRow());
		delete ui->listWidget->takeItem(ui->listWidget->currentRow());
	}
	ui->graphicsView->setFocus();
	if (manager.prism_list.empty()) {
		manager.active_object = nullptr;
	}
	else {
		manager.active_object = &(manager.prism_list[ui->listWidget->currentRow()]);
	}

	scene.clear();

	ui->radioButton->toggle();
	visualize_carcass();
}

void MainWindow::on_btnAddLight_clicked()
{
	if (manager.light_full()) {
		QMessageBox msgInfo;
		msgInfo.setWindowTitle("Информация");
		msgInfo.setText("Ограничение");
		msgInfo.setIcon(QMessageBox::Information);
		msgInfo.setInformativeText("Превышено количество источников освещения.");
		msgInfo.exec();
	}
	else {
		Point coord(0, 0, 0);
		QColor intensity = QColorDialog::getColor();
		Light light(coord, intensity);
		QString str = QString("Источник ") + QString::number(manager.number_of_light());

		ui->listWidget_2->addItem(str);
		manager.add_light(light);

		ui->listWidget_2->setCurrentRow(ui->listWidget_2->count() - 1);
		manager.active_object = &(manager.light_list[ui->listWidget_2->currentRow()]);

		ui->graphicsView->setFocus();
	}


	scene.clear();

	ui->radioButton->toggle();
	visualize_carcass();
}

void MainWindow::on_btnDelLight_clicked()
{
	if (ui->listWidget_2->currentItem()) {
		manager.del_light(ui->listWidget_2->currentRow());
		delete ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
	}
	if (manager.light_list.empty()) {
		manager.active_object = nullptr;
	}
	else {
		manager.active_object = &(manager.light_list[ui->listWidget_2->currentRow()]);
	}


	scene.clear();

	ui->radioButton->toggle();
	visualize_carcass();
}

void MainWindow::addPrism(Prism& prism)
{
	QString str = QString("Призма ") + QString::number(manager.number_of_prism());

	ui->listWidget->addItem(str);
	manager.add_prism(prism);

	ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
	manager.active_object = &(manager.prism_list[ui->listWidget->currentRow()]);

	scene.clear();
	visualize_carcass();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	if (manager.active_object != nullptr) {
		switch(e->key()) {
//			move
			case Qt::Key_Q :
				manager.active_object->move(move_speed, 0, 0);
				break;
			case Qt::Key_A :
				manager.active_object->move(-move_speed, 0, 0);
				break;
			case Qt::Key_W:
				manager.active_object->move(0, -move_speed, 0);
				break;
			case Qt::Key_S:
				manager.active_object->move(0, move_speed, 0);
				break;
			case Qt::Key_E:
				manager.active_object->move(0, 0, move_speed);
				break;
			case Qt::Key_D:
				manager.active_object->move(0, 0, -move_speed);
				break;
//			rotate
			case Qt::Key_U:
				manager.active_object->rotate(0, rotate_speed, 0);
				break;
			case Qt::Key_J:
				manager.active_object->rotate(0, -rotate_speed, 0);
				break;
			case Qt::Key_I:
				manager.active_object->rotate(0, 0, rotate_speed);
				break;
			case Qt::Key_K:
				manager.active_object->rotate(0, 0, -rotate_speed);
				break;
			case Qt::Key_O:
				manager.active_object->rotate(rotate_speed, 0, 0);
				break;
			case Qt::Key_L:
				manager.active_object->rotate(-rotate_speed, 0, 0);
				break;
//			resize
			case Qt::Key_T:
				manager.active_object->resize(resize_speed);
				break;
			case Qt::Key_Y:
				manager.active_object->resize(1/resize_speed);
				break;
			default:
				break;
		}
	}

	ui->radioButton->toggle();
	visualize_carcass();
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
	manager.active_object = &(manager.prism_list[currentRow]);
	ui->graphicsView->setFocus();
}

void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
	manager.active_object = &(manager.light_list[currentRow]);
	ui->graphicsView->setFocus();
}


void MainWindow::visualize_carcass()
{
	scene.clear();
	Point p1;
	Point p2;

	QPoint p_1;
	QPoint p_2;

	for (Prism& prism : manager.prism_list) {
		if (manager.check_visible(prism)) {
			for (Edge& edge : prism.side_edges) {
				for (int i = 0; i < 3; ++i) {
					p1 = edge.points[i];
					p2 = edge.points[i + 1];

					p_1 = manager.camera.to_screen(p1);
					p_2 = manager.camera.to_screen(p2);

					scene.addLine(p_1.x(), p_1.y(), p_2.x(), p_2.y());
				}
			}
		}
	}

	for (Light& light : manager.light_list) {
		if (manager.check_visible(light)) {
			Point coord = light.coordinates;
			Point coord2(coord);
			coord2.set_x(coord2.get_x() + 10);
			QPoint p = manager.camera.to_screen(coord);
			QPoint p2 = manager.camera.to_screen(coord2);

			double dx = p.x() - p2.x();
			double dy = p.y() - p2.y();
			double d = sqrt(dx * dx + dy * dy);

			scene.addEllipse(p.x(), p.y(), d, d, QPen(light.intensity));
		}
	}
}


void MainWindow::visualize_trass() {

	scene.clear();
	for (int x = 0; x < screen_size_x; ++x) {
		for (int y = 0; y < screen_size_y; ++y) {

			Beam beam = manager.camera.get_initial_beam(x, y);

			Point cross_point_nearest;
			Edge cross_edge_nearest;
			Prism cross_prism_nearest;

			bool got_intersection = false;

			for (const Prism& prism : manager.prism_list) {
				if (beam.cross_prism(prism, cross_point_nearest, cross_edge_nearest, got_intersection)) {
					cross_prism_nearest = prism;
				}
			}

			if (!got_intersection) {
				painter->setPen("black");
			}
			else {
				QColor color("black");

				for (Light& light : manager.light_list) {

					Beam light_beam(light.coordinates, cross_point_nearest);
					Point buffer_cross_point(cross_point_nearest);
					Edge buffer_cross_edge(cross_edge_nearest);

					bool changed = false;

					for (const Prism& prism : manager.prism_list) {
						if (light_beam.cross_prism_with_check(prism, buffer_cross_point, buffer_cross_edge, got_intersection)) {
							if (!(buffer_cross_edge == cross_edge_nearest)) {
								changed = true;
								break;
							}
						}
					}
					if (!changed) {
						const double coefficient = cross_prism_nearest.diff_reflect;

						double value = color.redF() + light.intensity.redF() * coefficient;
						value = value > 1 ? 1 : value;
						color.setRedF(value);

						value = color.greenF() + light.intensity.greenF() * coefficient;
						value = value > 1 ? 1 : value;
						color.setGreenF(value);

						value = color.blueF() + light.intensity.blueF() * coefficient;
						value = value > 1 ? 1 : value;
						color.setBlueF(value);
					}
				}

				painter->setPen(color);
			}

			painter->drawPoint(x, y);
		}
	}

	QGraphicsPixmapItem* it = scene.addPixmap(*pixmap);
	it->setPos(-screen_size_x / 2, -screen_size_y / 2);
}


void MainWindow::on_listWidget_pressed(const QModelIndex&)
{
	if (ui->listWidget->count()) {
		manager.active_object = &(manager.prism_list[ui->listWidget->currentRow()]);
	}
	else {
		manager.active_object = nullptr;
	}

	ui->graphicsView->setFocus();
}

void MainWindow::on_listWidget_2_pressed(const QModelIndex&)
{
	if (ui->listWidget_2->count()) {
		manager.active_object = &(manager.light_list[ui->listWidget_2->currentRow()]);
	}
	else {
		manager.active_object = nullptr;
	}

	ui->graphicsView->setFocus();
}

void MainWindow::on_radioButton_toggled(bool checked)
{
	if (checked) {
		visualize_carcass();
	}
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
	if (checked) {
		visualize_trass();
	}
}
