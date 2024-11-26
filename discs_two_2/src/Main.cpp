#include "Platform/Platform.hpp" // sfml

//#include "circle.h"		// for the circles
#include "fps.h"		// for displaying how many fps the animation has
#include "simulation.h" // for initializing and randomizing all the circles

#include <chrono> // for measuring time each frame has taken for a in real time animation

#include <iomanip> // for saving images in a nice format
#include <sstream>

// function definitions
void save_frame_to_image(sf::RenderWindow& window, int frame);

// saves window to png
void save_frame_to_image(sf::RenderWindow& window, int frame)
{
	std::ostringstream oss;
	oss << "./frame_" << std::setfill('0') << std::setw(4) << frame << ".png"; // 0001, 0002, ..., 0010, 0011, ...

	std::string file_name = oss.str();

	sf::Vector2u windowSize = window.getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(window);
	sf::Image screenshot = texture.copyToImage();
	screenshot.saveToFile(file_name);
}

int main()
{
	util::Platform platform; // for app icon I think

	sf::RenderWindow window;					// window
	platform.setIcon(window.getSystemHandle()); // app icon
	sf::Vector2f window_size(1920, 1080);
	window.create(sf::VideoMode(window_size.x, window_size.y), "SFML works!");
	sf::Event event;

	simulation kolka(160, window_size);

	/* attractors
	sf::Vector2f one_tenth = window_size / 10.f;
	kolka.add_attractor(one_tenth, 0.05);
	kolka.add_attractor(window_size - one_tenth, 0.05);
	//*/
	//* for real time simulation
	time_per_frame fps;
	fps.update();
	fps.update();
	//*/

	while (window.isOpen()) // for real time simulation
	//for(int frame = 0; (frame < 30 * 35) && window.isOpen(); frame++) // for rendering an animation
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

					kolka.add_attractor(sf::Vector2f(mouse_pos.x, mouse_pos.y), -5000);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

					kolka.add_attractor(sf::Vector2f(mouse_pos.x, mouse_pos.y), 5000);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					kolka.remove_most_recent_attractor();
				}
			}
		}

		window.clear();
		kolka.draw(window);
		window.display();

		kolka.update(fps.frame_time_in_s()); // for real time simulation
		//kolka.update(1/180.f);

		//float frame_time = 1/30.0;  // for rendering an animation
		//kolka.update(frame_time);
		//save_frame_to_image(window, frame);
		//std::cout << "frame: " << frame << "\n";

		fps.update();	   // for real time simulation
		fps.display_fps(); //
	}
	return 0;
}
