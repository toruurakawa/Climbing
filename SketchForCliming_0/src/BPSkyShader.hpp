//
//  BPSkyShader.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/19/15.
//
//

#pragma once
#include "BPShader.hpp"

class BPSkyShader : BPShader {
    
public:
    void setup() {
        fragmentShaderString = GLSL120(
#ifdef GL_ES
                                       precision mediump float;
#endif
                                       
                                       uniform vec2 u_resolution;
                                       uniform float u_time;
                                       
                                       // 2D Random
                                       float random (in vec2 st) {
                                           return fract(sin(dot(st.xy,
                                                                vec2(12.9898,78.233)))
                                                        * 43758.5453123);
                                       }
                                       
                                       // 2D Noise based on Morgan McGuire @morgan3d
                                       // https://www.shadertoy.com/view/4dS3Wd
                                       float noise (in vec2 st) {
                                           vec2 i = floor(st);
                                           vec2 f = fract(st);
                                           
                                           // Four corners in 2D of a tile
                                           float a = random(i);
                                           float b = random(i + vec2(1.0, 0.0));
                                           float c = random(i + vec2(0.0, 1.0));
                                           float d = random(i + vec2(1.0, 1.0));
                                           
                                           // Smooth Interpolation
                                           
                                           // Cubic Hermine Curve.  Same as SmoothStep()
                                           vec2 u = f*f*(3.0-2.0*f);
//                                           u = smoothstep(0.,1.,f);
                                           
                                           // Mix 4 coorners porcentages
                                           return mix(a, b, u.x) + 
                                           (c - a)* u.y * (1.0 - u.x) + 
                                           (d - b) * u.x * u.y;
                                       }
                                       
                                       void main() {
                                           vec2 st = gl_FragCoord.xy/u_resolution.xy;
                                           
                                           // Scale the coordinate system to see
                                           // some noise in action
                                           vec2 pos = vec2(st * 5.);
                                           
                                           // Use the noise function
                                           float n1 = noise(pos);
                                           float n2 = noise((pos + vec2(u_time)) * .5);
                                           float n3 = noise((pos + vec2(u_time / 2.)) * .25);
                                           vec3 color = vec3(n1 * 0.1);
                                           color.r += vec3(n1 * 0.1).r;
                                           color.g += vec3(n2 * 0.1).r;
                                           color.b += vec3(n3 * 0.1).r;
                                           gl_FragColor = vec4(color, 1.0);
                                       }
        );
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderString);
        shader.bindDefaults();
        shader.linkProgram();
    }
    void draw(int w, int h){
        shader.begin();
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        renderFrame(w, h);
        shader.end();
    }
};