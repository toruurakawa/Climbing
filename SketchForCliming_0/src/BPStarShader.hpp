//
//  BPStarShader.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/19/15.
//
//

#pragma once
#include "BPShader.hpp"
#include "BPStar.hpp"

class BPStarShader : BPShader {
    ofVboMesh mesh;
    ofShader initPosShader;
    ofFbo posFbo;
    ofShader magnitudeShader;
    ofImage magnitudeImg;
    vector< BPStar >stars;
    int i, x, y;
    ofFbo starFbo;
    ofShader starShader;
    ofImage positionImg;
    
    
public:
    bool isDrawingMesh, isDrawingShader;

    void addVertex(ofVec2f v) {
        x = i % 20;
        y = i / 20;
        cout << v << endl;
        mesh.addVertex(ofVec2f(v.x, v.y));
        mesh.addTexCoord(ofVec2f(v.x, v.y));
        i++;
    }
    
    void addStar(BPStar s) {
        stars.push_back(s);
        addVertex(s.getPosition());
    }
    
    void setInitialPos() {
        string fragmentShaderForInit = GLSL120(
                                               void main() {
                                                   vec2 st = gl_TexCoord[0].st;
                                                   gl_FragColor = vec4(st, 0.0, 1.0);
                                               }
                                               );
        initPosShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderForInit);
        initPosShader.bindDefaults();
        initPosShader.linkProgram();
        
        ofMesh quad;
        quad.getVertices().resize(4);
        quad.getTexCoords().resize(4);
        quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

        int _width = ofGetWidth();
        int _height = ofGetHeight();
        
        ofFbo::Settings mySettings;
        mySettings.width = _width;
        mySettings.height = _height;
        mySettings.internalformat = GL_RGBA32F;
        mySettings.maxFilter = GL_NEAREST;
        mySettings.minFilter = GL_NEAREST;
        posFbo.allocate(mySettings);
        posFbo.begin();
        initPosShader.begin();
        quad.setVertex(0, ofVec3f(0,0,0));
        quad.setVertex(1, ofVec3f(_width,0,0));
        quad.setVertex(2, ofVec3f(_width,_height,0));
        quad.setVertex(3, ofVec3f(0,_height,0));
        
        quad.setTexCoord(0, ofVec2f(0,0));
        quad.setTexCoord(1, ofVec2f(_width,0));
        quad.setTexCoord(2, ofVec2f(_width,_height));
        quad.setTexCoord(3, ofVec2f(0,_height));
        
        quad.draw();
        shader.end();
        posFbo.end();
        
//        // maginitude
//        magnitudeImg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
//        int i = 0;
//        for (auto it = stars.begin(); it != stars.end(); it++ ) {
//            i++;
//            ofColor c = ofColor(it->getMagnitude() / 5. * 255);
//            magnitudeImg.setColor(it->getPosition().x, it->getPosition().y, c);
//        }
//        magnitudeImg.update();

        
        string fragmentShaderForStar = GLSL120(uniform float time;
                                               uniform vec2 resolution;
                                               uniform sampler2DRect positionTexture;
                                               void main( void ) {
                                                   vec3 c;
                                                   vec2 p = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;//-1~+1の座標系
                                                   float s = sin(time*10. + p.x * 10. + p.y * 10.);
                                                   float ratio = resolution.x / resolution.y;
                                                   for(int i = 0; i < 200; i++){
                                                       vec3 o = texture2DRect(positionTexture, vec2(i + .5, 0.)).xyz;
                                                       o.x = (o.x * resolution.x) / resolution.y - ratio / 2.;
                                                       o.y = (o.y - 0.5);
                                                       float mag = o.z;
                                                       c += vec3(0.000025 * mag * (0.8 + 0.2 * s)  / dot(p - o.xy, p - o.xy));// * (texture2DRect(positionTexture, vec2(i, 0)).b * 2. + sin(time * 20. + i/10.) * texture2DRect(positionTexture, vec2(i, 0)).b * 0.1) ;

                                                   }
                                                   gl_FragColor = vec4(c, c.r);
                                               });
        starShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderForStar);
        starShader.bindDefaults();
        starShader.linkProgram();
        
//        starFbo.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
//        starFbo.begin();
//        ofClear(0);
//        starFbo.end();
        
        positionImg.allocate(200, 1, OF_IMAGE_COLOR_ALPHA);
        int j = 0;
        for (auto it = stars.begin(); it != stars.end(); it++ ) {
            ofColor c;
            float x = it->getPosition().x / (float)ofGetWidth();
            float y = it->getPosition().y / (float)ofGetHeight();
            cout << "(" << x  << ", " << y << ")" << endl;
            c = ofFloatColor(x,
                            y,
                        it->getMagnitude(),
                        0);
            cout << "<" << c.r / 255.  << ", " << c.g / 255. << ">" << endl;
            positionImg.setColor(j, 0, c);
            j++;
        }
        positionImg.update();

        ofFbo pfbo;
    }
    
    void setup() {
        vertexShaderString = GLSL120(
                                     uniform float u_time;
                                       uniform sampler2DRect positionTexture;
                                       uniform sampler2DRect magnitudeTexture;
                                    varying float mag;
                                       void main(){
//                                           gl_Position = ftransform();  // 座標変換するだけ
                                           vec2 st = gl_Vertex.xy;
                                           vec2 texPos = texture2DRect(positionTexture, st).xy;
                                           vec2 magnitude = texture2DRect(magnitudeTexture, st).xy;
                                           mag = magnitude.r / 255. * (0.8 + 0.2 * sin(u_time * 20. + st.x + st.y));
                                           gl_Position = gl_ModelViewProjectionMatrix * vec4(texPos, 0.0, 1.0);
                                           gl_PointSize = 100.;//magnitude.r * 300;  // 点の大きさを変更する
                                       }
                                       );

        fragmentShaderString = GLSL120(
                                       varying float mag;

                                       void main()
                                       {
                                           vec3 n;
                                           n.xy = gl_PointCoord * 2.0 - 1.0;  // 座標値を [0, 1] → [-1, 1] に変換する
                                           float d = dot(n.xy, n.xy);
                                           if (d > .1) {
                                               discard;
                                           }
                                           float r = 100 * mag /sqrt(d);
                                           gl_FragColor = vec4(vec3(1.), r);
                                       }
                                       );
        shader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderString);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderString);
        shader.bindDefaults();
        shader.linkProgram();
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        
    }
    
    void draw(int w, int h){
        if (isDrawingMesh) {
            int i = 0;
            for (auto it = stars.begin(); it != stars.end(); it++ ) {
                i++;
                if (i < 0) {
                    ofColor c = ofColor((1 + sin(i + ofGetElapsedTimef() / 2.)) / 2.* 100  / 5. * 255);
                    magnitudeImg.setColor(it->getPosition().x, it->getPosition().y, c);
                } else {
                    ofColor c = ofColor(it->getMagnitude() / 5. * 255);
                    magnitudeImg.setColor(it->getPosition().x, it->getPosition().y, c);
                }
            }
            magnitudeImg.update();
            
            shader.begin();
            shader.setUniform1f("u_time", ofGetElapsedTimef());
            shader.setUniformTexture("positionTexture", posFbo.getTextureReference(), 1);
            shader.setUniformTexture("magnitudeTexture", magnitudeImg.getTextureReference(), 2);
            glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_POINT_SPRITE);
            mesh.draw();
            glDisable(GL_POINT_SMOOTH);
            glDisable(GL_POINT_SPRITE);
            glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
            shader.end();
        }

        if (isDrawingShader) {
            int j = 0;
            for (auto it = stars.begin(); it != stars.end(); it++ ) {
                ofColor c;
                float x = it->getPosition().x / (float)ofGetWidth() * sin(ofGetElapsedTimef());
                float y = it->getPosition().y / (float)ofGetHeight();
                c = ofFloatColor(x,
                                 y,
                                 it->getMagnitude(),
                                 0);
                positionImg.setColor(j, 0, c);
                j++;
            }
            positionImg.update();
            starShader.begin();
            shader.setUniformTexture("positionTexture", positionImg.getTextureReference(), 1);
            starShader.setUniform1f("time", ofGetElapsedTimef());
            starShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
            ofMesh quad;
            quad.getVertices().resize(4);
            quad.getTexCoords().resize(4);
            quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
            int _width = ofGetWidth(); int _height = ofGetHeight();
            quad.setVertex(0, ofVec3f(0,0,0));
            quad.setVertex(1, ofVec3f(_width,0,0));
            quad.setVertex(2, ofVec3f(_width,_height,0));
            quad.setVertex(3, ofVec3f(0,_height,0));
            quad.setTexCoord(0, ofVec2f(0,0));
            quad.setTexCoord(1, ofVec2f(_width,0));
            quad.setTexCoord(2, ofVec2f(_width,_height));
            quad.setTexCoord(3, ofVec2f(0,_height));
            quad.draw();
            starShader.end();
        }

        
    }

    
};