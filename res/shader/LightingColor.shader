#shader vertex
#version 410 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 normal;
out vec2 v_TexCoord;
out vec4 v_Normal;
out vec4 v_FragPos;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform mat4 u_NormMat;
void main() {
   gl_Position = u_Proj * u_View * u_Model * position;
   v_FragPos = u_Model * vec4(position.xyz, 1.0f);
   v_TexCoord = texCoord;
   v_Normal = vec4(mat3(u_NormMat) * normal.xyz, 0.0f);
}
// -------------------------------
#shader fragment
#version 410 core
in vec4 v_FragPos;
in vec2 v_TexCoord;
in vec4 v_Normal;
uniform vec4 u_ObjectColor;
uniform vec4 u_LightColor;
uniform vec4 u_LightPos;
uniform vec4 u_ViewPos;
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
    vec4 viewDir = normalize(u_ViewPos - v_FragPos);
    vec4 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec4 specularColor = specularStrength * spec * u_LightColor;  
    // total
    color = (ambientColor + diffuseColor + specularColor) * u_ObjectColor;
    // color = mix(color, texColor, 0.1);
}
