//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_ARDUINOPROPERTY_DISPLAYCOMPONENT_H
#define COM_LILICLOUD_ARDUINOPROPERTY_DISPLAYCOMPONENT_H

#include <Property.h>

class DisplayComponent {
protected:
    /**
     * X position
     */
    int x;

    /**
     * Y position
     */
    int y;

    /**
     * Component width
     */
    int w;

    /**
     * Component height
     */
    int h;

    /**
     * Flag to indicate if component is selected
     */
    Property<bool> selectedProperty;

public:

    /**
     * Constructor
     */
    DisplayComponent()
    {
        this->selectedProperty = new Property<bool>(false);
    }

    ~DisplayComponent()
    {
        delete this->selectedProperty;
    }

    /**
     * Get x position
     */
    int getX()
    {
        return this->x;
    }

    /**
     * Set x position
     */
    void setX(int x)
    {
        this->x = x;
    }

    /**
     * Get y position
     */
    int getY()
    {
        return this->y;
    }

    /**
     * Set y position
     */
    void setY(int y)
    {
        this->y = y;
    }

    /**
     * Get component width
     */
    int getWidth()
    {
        return this->w;
    }

    /**
     * Set component width
     */
    void setWidth(int w)
    {
        this->w = w;
    }

    /**
     * Get component height
     */
    int getHeight()
    {
        return this->h;
    }

    /**
     * Set component height
     */
    void setHeight(int h)
    {
        this->h = h;
    }

    /**
     * Set position x, y
     */
    void setPosition(int x, int y)
    {
        this->setX(x);
        this->setY(y);
    }

    /**
     * Set component size
     */
    void setSize(int w, int h)
    {
        this->setWidth(w);
        this->setHeight(h);
    }

    /**
     * Flag to indicate if component is selected
     */
    bool isSelected()
    {
        return this->selectedProperty->get();
    }

    /**
     * Set component as selected
     */
    void setSelected(bool selected)
    {
        this->selectedProperty->set(selected);
    }

    /**
     * Draw component
     */
    void draw()
    {
        // Nothing to do for base class
    }
};

#endif //COM_LILICLOUD_ARDUINOPROPERTY_DISPLAYCOMPONENT_H
