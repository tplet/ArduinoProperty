//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_SSD1306DISPLAYCOMPONENT_H
#define COM_LILICLOUD_ARDUINOPROPERTY_SSD1306DISPLAYCOMPONENT_H

#include <DisplayComponent.h>
#include <Adafruit_SSD1306.h>

class SSD1306DisplayComponent : public DisplayComponent {
protected:
    /**
     * Screen
     */
    Adafruit_SSD1306 * screen;

public:
    /**
     * Constructor
     */
    SSD1306DisplayComponent(Adafruit_SSD1306 * screen) : DisplayComponent()
    {
        this->screen = screen;
    }

    /**
     * Draw component
     */
    void draw(bool display = false)
    {
        DisplayComponent::draw();
    }
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_SSD1306DISPLAYCOMPONENT_H
