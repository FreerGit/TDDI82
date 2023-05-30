#include <SFML/Graphics.hpp> // includes most things in SFML
#include "file_handler.h"
#include <iostream>
using namespace sf;

// int const width  { 640 };
// int const height { 480 };

int main ()
{
    File_handler handler{};
    Game_map map = handler.load_map("game_map.txt");
    std::cout << map.width << std::endl;
    RenderWindow window {
        VideoMode { map.width, map.height },
        "SFML DEMO"
    };

    /* skapa en cirkel */
    float const r { 16.0 };
    CircleShape circle { r };

    // placera cirkeln pÃ¥ skÃ¤rmen
    circle.setPosition (map.width / 2, map.height / 2);
    
    // sÃ¤tt vilken punkt som Ã¤r origo
    // i cirkeln (det Ã¤r denna punkt som
    // cirkelns position Ã¤r specificerad ifrÃ¥n
    circle.setOrigin (r, r);

    // sÃ¤tt en bakgrundsfÃ¤rg pÃ¥ cirkeln
    circle.setFillColor (Color::Green);

    /* ladda in en texture (bild) */
    Texture texture;
    if ( !texture.loadFromFile ("fighter.png") )
    {
        // gick inte att ladda bilden
        return 1;
    }
    
    // skapa sprite
    Sprite sprite { texture };
    sprite.setPosition (map.width / 2, map.height / 2);

    // sÃ¤tt origin pÃ¥ sprite till mitten
    auto size { texture.getSize () };
    sprite.setOrigin (size.x / 2, size.y / 2);

    float const speed { 4.0 };

    // skapa en klocka
    Clock clock;

    double const fps { 60.0 };
    
    // berÃ¤kna hur lÃ¥ng tid vi har per frame
    auto const target { milliseconds (1000.0 / fps) };

    /* skapa text */
    Font font;
    if ( !font.loadFromFile ("font.ttf") )
    {
        // kunde inte ladda typsnitt
        return 2;
    }

    // skapa text objekt
    Text text { "Demo", font };
    
    auto bounds { text.getGlobalBounds () };
    text.setPosition ((map.width - bounds.width) / 2, 0);
    
    // loopa sÃ¥lÃ¤nge fÃ¶nstret finns
    while ( window.isOpen () )
    {
        // bÃ¶rja tidtagning
        clock.restart ();
        
        /* hantera events */
        Event event;
        // hÃ¤mta ett event i taget
        while ( window.pollEvent (event) )
        {
            if ( event.type == Event::Closed)
            {
                window.close ();
            }
            // har en mus-knapp tryckts?
            else if ( event.type == Event::MouseButtonPressed )
            {
                auto mouse { event.mouseButton };
                // Ã¤r det vÃ¤nster musknapp?
                if ( mouse.button == Mouse::Button::Left )
                {
                    // flytta cirkeln
                    circle.setPosition (mouse.x, mouse.y);
                }
            }
        }
        
        /* hantera logiken */
        auto old_position { sprite.getPosition () };
        
        if ( Keyboard::isKeyPressed (Keyboard::Key::W) )
        {
            sprite.setRotation (0);
            sprite.move (0, -speed);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::S) )
        {
            sprite.setRotation (180);
            sprite.move (0, speed);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::A) )
        {
            sprite.setRotation (-90);
            sprite.move (-speed, 0);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::D) )
        {
            sprite.setRotation (90);
            sprite.move (speed, 0);
        }

        auto sprite_box { sprite.getGlobalBounds () };
        auto circle_box { circle.getGlobalBounds () };
        if ( sprite_box.intersects (circle_box) )
        {
            // om kollision, flytta tillbaks sprite
            sprite.setPosition (old_position);
        }
        
        /* rita ut */
        window.clear (); // rensa skÃ¤rmen

        window.draw (text); // rita ut texten
        window.draw (circle); // rita ut cirkeln
        window.draw (sprite); // rita ut bilden
        
        window.display (); // visa Ã¤ndringarna

        // rÃ¤kna ut hur lÃ¥ng tid vi har kvar tills nÃ¤sta
        // frame ska bÃ¶rja
        auto wait_time { target - clock.getElapsedTime () };

        // vÃ¤nta tiden som blev Ã¶ver
        sleep (wait_time);
    }
}
