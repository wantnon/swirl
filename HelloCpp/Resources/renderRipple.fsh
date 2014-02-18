

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;//used as heightMap
uniform sampler2D colorMap;


uniform float bending;
uniform vec2 texSize;
uniform float angleAllPixel;

uniform vec2 backGroundTexSize;
uniform vec2 backGroundTexLUPos;
uniform vec2 texLUPos;

void main() {

    //float time = CC_Time[1];//don't use CC_Time, because it not do wrap and may end up with huge value and overflow causing wrong effect
    
    //texCoord_colorMap
    vec2 texCoord_colorMap=vec2((v_texCoord.s*texSize.x+texLUPos.x-backGroundTexLUPos.x)/backGroundTexSize.x,
                                (v_texCoord.t*texSize.y+backGroundTexLUPos.y-texLUPos.y)/backGroundTexSize.y
                                );

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

    
    //offsetH
    vec3 h_rgb=texture2D(CC_Texture0, texCoord_heightMap+offsetT).rgb;
    float h_r=h_rgb.r;
    float h_b=h_rgb.b;
    float h=(h_r+h_b)*max(0.0,1.0-r*2.0);
    float _offsetH=h*0.8;
    vec2 offsetH=vec2(_offsetH,_offsetH);
    //final color
	gl_FragColor=texture2D(colorMap,texCoord_colorMap+offsetH)*(1.0+h*7.0);
    gl_FragColor.a=1.0;//(1.0-h*0.2);
    


}

