//
//  ThirdScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "ThirdScene.h"
#include "TitleScene.h"
#include "FirstScene.h"

void ThirdScene::setup(ofPtr<ofxScene> previousScene) {
    TitleScene* scene = dynamic_cast<TitleScene *>(previousScene.get());
    c.clear();
    c.loadFromXml(scene->c.getFilename());
    starShader.setup();
    starShader.stars = c.getStars();
}

void ThirdScene::update() {
    starShader.update();
    c.update();
}

void ThirdScene::draw() {
    ofBackground(0);
    starShader.draw();
    c.draw();
}
