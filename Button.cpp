//
// Created by brado on 10/24/2023.
//

#include "Button.h"


Button::Button(glm::vec2 position, glm::vec2 scale, glm::vec3 color, Shape shape, float rsRadius, string text, glm::vec2 localTexLoc, float texScale, glm::vec3 texCol, bool toggleable, bool defaultVal, int scrWidth, int scrHeight) : Object(position, scale, rsRadius, color, shape, scrWidth,scrHeight) {
    this->textStr = text;
    this->texLoc = localTexLoc;
    this->texScale = texScale;
    this->texCol = texCol;
    this->toggleable = toggleable;
    this->On = defaultVal;
    this->scrPixelScale = {scrWidth, scrHeight};
    this->physicalText = new Text(this->textStr, this->texLoc, this->texScale, this->texCol, Center);
}

Button::~Button() {
    this->Object::~Object();
}

void Button::display(Shader* objShader, Shader* texShader) {
    this->Object::display(objShader);

    glm::vec2 textPosPix = convertScSpToPix(position + texLoc);
    physicalText->RenderText(texShader);
}

bool Button::clickOnButton(glm::vec2 clickPos) {
    if(clickPos.x >= position.x && clickPos.x <= position.x + scale.x && clickPos.y >= position.y && clickPos.y <= position.y + scale.y){
        cout<< "click"<<endl;
        if(toggleable){
            On = !On;
        }else{
            On = true;
        }
        return true;
    }
    return false;
}