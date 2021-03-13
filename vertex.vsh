attribute highp vec4 posAttr;
uniform highp mat4 matrix;
uniform highp mat4 matrix_edge;
uniform highp float shapingPercentage;
uniform highp float radius;

const float PI = 3.1415926538;

void main() {
   vec3 tmp = vec3(posAttr.x, posAttr.y, posAttr.z);
   tmp = tmp*((1.0f)-shapingPercentage) + normalize(tmp)*radius * shapingPercentage;
   gl_Position = matrix * matrix_edge * vec4(tmp, 1);
}
