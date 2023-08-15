#version 330 core 

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec2 uvs;
in vec3 normals;
in vec3 fragPos;

out vec4 fragColor;

uniform Material material;
uniform DirectionalLight directionalLight;
uniform vec3 viewPos;

vec3 getDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);

void main() {
    vec3 norm = normalize(normals);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = getDirLight(directionalLight, norm, viewDir);
    fragColor = vec4(result, 1.0);
}

vec3 getDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * texture(material.diffuse, uvs).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, uvs).rgb; 
    vec3 specular = light.specular * spec * texture(material.specular, uvs).rgb;

    return (ambient + diffuse + specular);
}
