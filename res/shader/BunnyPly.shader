#shader vertex
#version 410 core
layout(location = 0) in uint id;
layout(location = 1) in vec4 position;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 normal;
out vec2 v_TexCoord;
out vec4 v_Normal;
out vec4 v_FragPos;
out vec4 v_ObjectColor;
out vec4 v_ViewPos;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform mat4 u_NormMat;
uniform vec4 u_ObjectColor;
uniform vec4 u_ViewPos;
uniform vec4 u_Ray;
void main() {
   gl_Position = u_Proj * u_View * u_Model * position;
   v_FragPos = u_Model * vec4(position.xyz, 1.0f);
   v_TexCoord = texCoord;
   v_Normal = vec4(mat3(u_NormMat) * normal.xyz, 0.0f);
   float r2 = 0.0001f;
   vec3 p = u_ViewPos.xyz - v_FragPos.xyz;
   float h = dot(p, normalize(u_Ray.xyz));
   float d2 = dot(p, p) - h * h;
   v_ObjectColor = (d2 <= r2) ? vec4(1.0f) : u_ObjectColor;
   v_ViewPos = u_ViewPos;
}
// -------------------------------
#shader fragment
#version 410 core
in vec4 v_FragPos;
in vec2 v_TexCoord;
in vec4 v_Normal;
in vec4 v_ObjectColor;
in vec4 v_ViewPos;
uniform vec4 u_LightColor;
uniform vec4 u_LightPos;
uniform sampler2D u_Texture;
layout(location = 0) out vec4 color;
void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    // ambient
    float ambientStrength = 0.2;
    vec4 ambientColor = ambientStrength * u_LightColor;
    // diffuse
    vec4 normal = normalize(v_Normal);
    vec4 lightDir = normalize(u_LightPos - v_FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec4 diffuseColor = diff * u_LightColor;
    // specular
    float specularStrength = 0.5;
    int shininess = 32;
    vec4 viewDir = normalize(v_ViewPos - v_FragPos);
    vec4 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec4 specularColor = specularStrength * spec * u_LightColor;  
    // total
    color = (ambientColor + diffuseColor + specularColor) * v_ObjectColor;
    // color = mix(color, texColor, 0.1);
}
