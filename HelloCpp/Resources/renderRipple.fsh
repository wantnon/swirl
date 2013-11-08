

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;//used as heightMap
uniform sampler2D colorMap;

uniform float bending;
uniform vec2 texSize;
uniform float angleAllPixel;

void main() {

    //float time = CC_Time[1];//don't use CC_Time, because it not do wrap and may end up with huge value and overflow causing wrong effect
    
    //texCoord_colorMap
    vec2 texCoord_colorMap=vec2(v_texCoord.s,1.0-v_texCoord.t);
    //texCoord_HMap
    vec2 texCoord_heightMap=v_texCoord;
    //r
    float r=distance(texCoord_heightMap,vec2(0.5,0.5));
    //offsetT
    float angleMax=bending;
    float angle=angleAllPixel+max(0.0,angleMax-angleMax/0.5*r);
    float cosAngle=cos(angle);
    float sinAngle=sin(angle);
    vec2 texCoord_roted=vec2(cosAngle*(texCoord_heightMap.s-0.5)-sinAngle*(texCoord_heightMap.t-0.5)+0.5,
                             cosAngle*(texCoord_heightMap.t-0.5)+sinAngle*(texCoord_heightMap.s-0.5)+0.5);
    vec2 offsetT=texCoord_roted-texCoord_heightMap;
    //offsetT2
    //andle2=2*angle
    float cosAngle2=2.0*cosAngle*cosAngle-1.0;
    float sinAngle2=2.0*sinAngle*cosAngle;
    vec2 texCoord_roted2=vec2(cosAngle2*(texCoord_heightMap.s-0.5)-sinAngle2*(texCoord_heightMap.t-0.5)+0.5,
                             cosAngle2*(texCoord_heightMap.t-0.5)+sinAngle2*(texCoord_heightMap.s-0.5)+0.5);
    vec2 offsetT2=texCoord_roted2-texCoord_heightMap;
    //offsetH
    vec3 h_rgb=texture2D(CC_Texture0, texCoord_heightMap+offsetT).rgb;
    float h1=h_rgb.r;
    float h3=h_rgb.b;
    float h2=texture2D(CC_Texture0, texCoord_heightMap+offsetT2).g;
    float h=(h1+h2+h3)*max(0.0,1.0-r*2.0);
    float _offsetH=pow(h,1.5)*0.5;
    vec2 offsetH=vec2(_offsetH,_offsetH);
    //final color
	gl_FragColor=texture2D(colorMap,texCoord_colorMap+vec2(offsetH.s,offsetH.t))*(1.0-h);
    gl_FragColor.a=(1.0-h*0.2);
}

