#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include "qprismdialog.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QString>
#include <QGraphicsPixmapItem>
#include "beam.h"
#include "utils.h"
#include "flatness.h"

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
		Point center;
		for (Light& light : manager.light_list) {
			center += light.coordinates;
		}
		for (Prism& prism : manager.prism_list) {
			center += prism.center;
		}
		center *= (1/(manager.number_of_light() + manager.number_of_prism()));
		switch(e->key()) {
//			move
			case Qt::Key_Q :
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.move(0, 0, -move_speed);
					}
					for (Light& light : manager.light_list) {
						light.move(0, 0, -move_speed);
					}
				} else {
					manager.active_object->move(0, 0, -move_speed);
				}
				break;

			case Qt::Key_E:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.move(0, 0, move_speed);
					}
					for (Light& light : manager.light_list) {
						light.move(0, 0, move_speed);
					}
				} else {
					manager.active_object->move(0, 0, move_speed);
				}
				break;
			case Qt::Key_W:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.move(0, move_speed, 0);
					}
					for (Light& light : manager.light_list) {
						light.move(0, move_speed, 0);
					}
				} else {
					manager.active_object->move(0, -move_speed, 0);
				}
				break;
			case Qt::Key_S:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.move(0, -move_speed, 0);
					}
					for (Light& light : manager.light_list) {
						light.move(0, -move_speed, 0);
					}
				} else {
					manager.active_object->move(0, move_speed, 0);
				}
				break;

			case Qt::Key_A :
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.move(move_speed, 0, 0);
					}
					for (Light& light : manager.light_list) {
						light.move(move_speed, 0, 0);
					}
				} else {
					manager.active_object->move(-move_speed, 0, 0);
				}
				break;

			case Qt::Key_D:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.move(-move_speed, 0, 0);
					}
					for (Light& light : manager.light_list) {
						light.move(-move_speed, 0, 0);
					}
				} else {
					manager.active_object->move(move_speed, 0, 0);
				}
				break;
//			rotate
			case Qt::Key_K:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.rotate(0, -rotate_speed, 0, center);
					}
					for (Light& light : manager.light_list) {
						light.rotate(0, -rotate_speed, 0, center);
					}
				} else {
					manager.active_object->rotate(0, rotate_speed, 0);
				}
				break;
			case Qt::Key_I:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.rotate(0, rotate_speed, 0, center);
					}
					for (Light& light : manager.light_list) {
						light.rotate(0, rotate_speed, 0, center);
					}
				} else {
					manager.active_object->rotate(0, -rotate_speed, 0);
				}
				break;
			case Qt::Key_L:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.rotate(0, 0, -rotate_speed, center);
					}
					for (Light& light : manager.light_list) {
						light.rotate(0, 0, -rotate_speed, center);
					}
				} else {
					manager.active_object->rotate(0, 0, rotate_speed);
				}
				break;
			case Qt::Key_J:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.rotate(0, 0, rotate_speed, center);
					}
					for (Light& light : manager.light_list) {
						light.rotate(0, 0, rotate_speed, center);
					}
				} else {
					manager.active_object->rotate(0, 0, -rotate_speed);
				}
				break;
			case Qt::Key_O:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.rotate(-rotate_speed, 0, 0, center);
					}
					for (Light& light : manager.light_list) {
						light.rotate(-rotate_speed, 0, 0, center);
					}
				} else {
					manager.active_object->rotate(-rotate_speed, 0, 0);
				}
				break;
			case Qt::Key_U:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.rotate(rotate_speed, 0, 0, center);
					}
					for (Light& light : manager.light_list) {
						light.rotate(rotate_speed, 0, 0, center);
					}
				} else {
					manager.active_object->rotate(rotate_speed, 0, 0);
				}
				break;
//			resize
			case Qt::Key_T:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.resize(resize_speed, center);
					}
					for (Light& light : manager.light_list) {
						light.resize(resize_speed, center);
					}
				} else {
					manager.active_object->resize(resize_speed);
				}
				break;
			case Qt::Key_Y:
				if (e->modifiers() & Qt::ShiftModifier) {
					for (Prism& prism : manager.prism_list) {
						prism.resize(1/resize_speed, center);
					}
					for (Light& light : manager.light_list) {
						light.resize(1/resize_speed, center);
					}
				} else {
					manager.active_object->resize(1/resize_speed);
				}
				break;
			default:
				break;
		}
	}
	if (ui->radioButton->isChecked()) {
		visualize_carcass();
	} else {
		visualize_trass();
	}
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
				QVector<QPoint> polyvector;
				for (Point& p : edge.points) {
					polyvector.push_back(manager.camera.to_screen(p));
				}

				QPolygon polygon(polyvector);
				scene.addPolygon(polygon);
			}
			p1 = prism.center;
			p_1 = manager.camera.to_screen(p1);
			scene.addEllipse(p_1.x(), p_1.y(), 3, 3);
		}
	}

	draw_lights(false);
}


void MainWindow::visualize_trass() {

	scene.clear();
	Beam beam = manager.camera.get_initial_beam(0, 0);
	Point cross_point_nearest;
	Edge cross_edge_nearest;
	Prism cross_prism_nearest;

	for (int x = 0; x < screen_size_x; ++x) {
		for (int y = 0; y < screen_size_y; ++y) {

			bool got_intersection = false;

			for (const Prism& prism : manager.prism_list) {
				if (beam.cross_prism(prism, cross_point_nearest, cross_edge_nearest, got_intersection)) {
					cross_prism_nearest = prism;
				}
			}

			if (!got_intersection) {
				painter->setPen("white");
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
						double angle = light_beam.get_angle(cross_edge_nearest.flatness);
						change_color(color, light.intensity,
									 cross_prism_nearest.diff_reflect * fabs(cos(angle)),
									 light_beam.p1.distance(cross_point_nearest));
					}
				}

				painter->setPen(color);
			}

			painter->drawPoint(x, y);
			beam.p2.set_y(beam.p2.get_y() + 1);
		}
		beam.p2.set_x(beam.p2.get_x() + 1);
		beam.p2.set_y(beam.p2.get_y() - screen_size_y);
	}

	QGraphicsPixmapItem* it = scene.addPixmap(*pixmap);
	it->setPos(-screen_size_x / 2, -screen_size_y / 2);

	draw_lights(true);
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


void MainWindow::draw_lights(bool check)
{
	for (Light& light : manager.light_list) {
		if (manager.check_visible(light)) {
			Point coord = light.coordinates;
			if (check) {
				Point cross_point_nearest;
				Edge cross_edge_nearest;
				bool got_intersection = false;
				Beam beam(manager.camera.coordinates, coord);
				for (const Prism& prism : manager.prism_list) {
					beam.cross_prism(prism, cross_point_nearest, cross_edge_nearest, got_intersection);
				}
				if (got_intersection && manager.camera.coordinates.distance(cross_point_nearest) <
						manager.camera.coordinates.distance(coord)) {
					return;
				}
			}
			Point coord2(coord);
			coord2.set_x(coord2.get_x() + 10);
			QPoint p = manager.camera.to_screen(coord);
			QPoint p2 = manager.camera.to_screen(coord2);

			double dx = p.x() - p2.x();
			double dy = p.y() - p2.y();
			double d = sqrt(dx * dx + dy * dy);

			scene.addEllipse(p.x(), p.y(), d, d, QPen("black"),
							 QBrush(light.intensity));
		}
	}
}

void MainWindow::on_actionSave_triggered()
{
	QString file_path = QFileDialog::getSaveFileName(this, tr("Сохраните суперпозицию"), "",
													 tr("Суперпозиция призм (*.pzm);;Все файлы (*)"));
	if (file_path.isEmpty()) {
		return;
	}
	QFile file(file_path);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(this, tr("Невозможно открыть файл"), file.errorString());
		return;
	}
	QTextStream out(&file);

	const QString tab = ("\t");
	const QString new_line("\r\n");
	const QString sec_split("-----------------------\r\n");
	out << "LIGHTS: " << manager.light_list.size() << new_line;
	for (Light& light : manager.light_list) {
		out << light.coordinates.get_x() << tab << light.coordinates.get_y() << tab << light.coordinates.get_z() << tab\
			<< light.intensity.red() << tab << light.intensity.green() << tab << light.intensity.blue() << new_line;
	}
	out << sec_split;
	out << "PRISMS: " << manager.prism_list.size() << new_line;
	for (Prism& prism : manager.prism_list) {
		out << prism.center.get_x() << tab << prism.center.get_y() << tab << prism.center.get_z() << new_line \
			<< tab << prism.diff_reflect << tab << prism.reflect << tab << prism.refract << new_line;
		out << "TOP_EDGES: " << prism.top_edges.size() << new_line;
		for (Edge& edge : prism.top_edges) {
			out << "POINTS: " << edge.points.size() << new_line;
			for (Point& point : edge.points) {
				out << point.get_x() << tab << point.get_y() << tab << point.get_z() << new_line;
			}
		}
		out << "SIDE_EDGES: " << prism.side_edges.size() << new_line;
		for (Edge& edge : prism.side_edges) {
			out << "POINTS: " << edge.points.size() << new_line;
			for (Point& point : edge.points) {
				out << point.get_x() << tab << point.get_y() << tab << point.get_z() << new_line;
			}
		}
	}
	out << sec_split;
	file.close();
}

void MainWindow::on_actionLoad_triggered()
{
	QString file_path = QFileDialog::getOpenFileName(this, tr("Выберите файл"), tr(""), tr("*.pzm"));
	if (file_path.isEmpty()) {
		return;
	}
	QFile file(file_path);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(this, tr("Невозможно открыть файл"), file.errorString());
		return;
	}

	clear_all();

	QTextStream in(&file);
	QString sec_split("-----------------------");
	QString buffer_string;

	in >> buffer_string;
	if (buffer_string.compare("LIGHTS:") != 0) {
		QMessageBox::information(this, tr("Файл поврежден"), tr("Формат файла не прошел проверку"));
		clear_all();
		return;
	}
	int light_number = 0;
	in >> light_number;
	for (int i = 0; i < light_number; ++i) {
		Light buffer_light;

		read_light(in, buffer_light);

		QString str = QString("Источник ") + QString::number(manager.number_of_light());
		ui->listWidget_2->addItem(str);
		manager.add_light(buffer_light);

		ui->listWidget_2->setCurrentRow(ui->listWidget_2->count() - 1);
		manager.active_object = &(manager.light_list[ui->listWidget_2->currentRow()]);

		ui->graphicsView->setFocus();
	}

	in >> buffer_string;
	if (buffer_string.compare(sec_split) != 0) {
		QMessageBox::information(this, tr("Файл поврежден"), tr("Формат файла не прошел проверку"));
		clear_all();
		return;
	}

	in >> buffer_string;
	if (buffer_string.compare("PRISMS:") != 0) {
		QMessageBox::information(this, tr("Файл поврежден"), tr("Формат файла не прошел проверку"));
		clear_all();
		return;
	}

	int prism_number = 0;
	in >> prism_number;

	for (int i = 0; i < prism_number; ++i) {
		Prism buffer_prism;
		read_prism(in, buffer_prism);

		QString str = QString("Призма ") + QString::number(manager.number_of_prism());

		ui->listWidget->addItem(str);
		manager.add_prism(buffer_prism);

		ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
		manager.active_object = &(manager.prism_list[ui->listWidget->currentRow()]);
	}

	ui->radioButton->toggle();
	visualize_carcass();

	file.close();
}


void MainWindow::clear_all()
{
	manager = Manager();
	ui->listWidget->clear();
	ui->listWidget_2->clear();
	scene.clear();
}

void MainWindow::read_point(QTextStream& stream, Point& point)
{
	double buffer_double = 0;

	stream >> buffer_double;
	point.set_x(buffer_double);

	stream >> buffer_double;
	point.set_y(buffer_double);

	stream >> buffer_double;
	point.set_z(buffer_double);
}

void MainWindow::read_color(QTextStream& stream, QColor& color)
{
	int buffer_int = 0;

	stream >> buffer_int;
	color.setRed(buffer_int);

	stream >> buffer_int;
	color.setGreen(buffer_int);

	stream >> buffer_int;
	color.setBlue(buffer_int);
}

void MainWindow::read_edge(QTextStream& stream, Edge& edge)
{
	QString buffer_string;
	stream >> buffer_string;

	if (buffer_string.compare("POINTS:") != 0) {
		QMessageBox::information(this, tr("Файл поврежден"), tr("Формат файла не прошел проверку"));
		clear_all();
		return;
	}

	int point_number = 0;
	stream >> point_number;

	for (int k = 0; k < point_number; ++k) {
		Point point;
		read_point(stream, point);
		edge.points.push_back(point);
	}
	edge.setup_flatness();
}

void MainWindow::read_light(QTextStream& stream, Light& light)
{
	read_point(stream, light.coordinates);
	read_color(stream, light.intensity);
}

void MainWindow::read_prism(QTextStream& stream, Prism& prism)
{
	QString buffer_string;

	read_point(stream, prism.center);
	stream >> prism.diff_reflect >> prism.reflect >> prism.refract;

	stream >> buffer_string;
	if (buffer_string.compare("TOP_EDGES:") != 0) {
		QMessageBox::information(this, tr("Файл поврежден"), tr("Формат файла не прошел проверку"));
		clear_all();
		return;
	}

	int top_edges_number = 0;
	stream >> top_edges_number;
	for (int j = 0; j < top_edges_number; ++j) {
		Edge edge;
		read_edge(stream, edge);
		prism.top_edges.push_back(edge);
	}

	stream >> buffer_string;
	if (buffer_string.compare("SIDE_EDGES:") != 0) {
		QMessageBox::information(this, tr("Файл поврежден"), tr("Формат файла не прошел проверку"));
		clear_all();
		return;
	}

	int side_edges_number = 0;
	stream >> side_edges_number;
	for (int j = 0; j < side_edges_number; ++j) {
		Edge edge;
		read_edge(stream, edge);
		prism.side_edges.push_back(edge);
	}

	prism.calculate_radius();
}
