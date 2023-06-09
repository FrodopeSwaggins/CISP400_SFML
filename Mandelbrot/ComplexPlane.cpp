#include "ComplexPlane.h"
#include <cmath>
#include <complex>
#include <sstream>

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}
void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	//Set a local variable for the x size to BASE_WIDTH* (BASE_ZOOM to the m_ZoomCount power)	
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	//Set a local variable for the y size to BASE_HEIGHT* m_aspectRatio* (BASE_ZOOM to the m_ZoomCount power)
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}
void ComplexPlane::setCenter(Vector2f coord)
{
	//setCenter for m_view to the given coordinate
	m_view.setCenter(coord);
}
View ComplexPlane::getView()
{
	return m_view;

}
void ComplexPlane::setMouseLocation(Vector2f coord)
{
	//Store the given value in the m_mouseLocation variable
	m_mouseLocation = coord;
}
void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set" << endl << "Center: (0,0)" << endl << "Cursor: (n,n)" << endl << "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;

	text.setString(ss.str());

}

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
	sf::Vector2f z(0.0, 0.0);
	size_t count = 0;
	while (count < MAX_ITER && z.x * z.x + z.y * z.y < 4.0)
	{
		sf::Vector2f zNew(z.x * z.x - z.y * z.y + coord.x, 2.0 * z.x * z.y + coord.y);
		z = zNew;
		count++;
	}
	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		r = static_cast<Uint8>(count * 255 / MAX_ITER);
		g = static_cast<Uint8>(count * 255 / MAX_ITER);
		b = static_cast<Uint8>(count * 255 / MAX_ITER);
	}
}