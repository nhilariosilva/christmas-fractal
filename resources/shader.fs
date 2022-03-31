#version 330 core

out vec4 FragColor;

in vec3 fColor;

uniform float incColor_r;
uniform float incColor_g;
uniform float incColor_b;

void main(){
  vec3 finalColor = vec3(fColor.x + incColor_r, fColor.y + incColor_g, fColor.z + incColor_b);

  if(finalColor.x > 1){
    finalColor.x = 2-finalColor.x;
  }
  if(finalColor.y > 1){
    finalColor.y = 2-finalColor.y;
  }
  if(finalColor.z > 1){
    finalColor.z = 2-finalColor.z;
  }

  if(finalColor.x < 0){
    finalColor.x -= finalColor.x;
  }
  if(finalColor.y < 0){
    finalColor.y = -finalColor.y;
  }
  if(finalColor.z < 0){
    finalColor.z = -finalColor.z;
  }

  FragColor = vec4(finalColor, 1.0f);
}
