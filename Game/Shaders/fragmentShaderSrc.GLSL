#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec3 TexCoord;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightDir; 
uniform int isSpotLightOn;
uniform int nbLight;
uniform float cutOff; 
float quadratic;

struct Pointlight
{
    vec3 position;
    vec3 Diffuse;
    vec3 Ambient;
    vec3 Specular;
    float quadratic;
};
uniform Pointlight pointlight[10];

uniform vec4 color;  
uniform sampler3D textures[];
uniform int nbtextures;

vec4 GenerateTextures() 
{
    if (!(nbtextures > 0)) return vec4(1, 1, 1, 1); 

    vec4 Texture = texture(textures[0], TexCoord);

    if (nbtextures > 1) Texture = mix(Texture, texture(textures[1], TexCoord), 0.5);

    if (nbtextures > 2) Texture = mix(Texture, texture(textures[2], TexCoord), 0.5);

    if (nbtextures > 3) Texture = mix(Texture, texture(textures[3], TexCoord), 0.2);

    return Texture;
}

void main()
{
    float shininess = 32.0f;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    //for point light 
    //
    vec3 pointlightResult = vec3(0.0f);
    for(int i = 0; i < nbLight; ++i)
    {
        vec3 lightDirnew = normalize(pointlight[i].position - FragPos);
        float distance = length(pointlight[i].position - FragPos);
        float attenuation = 1.0 / (1.0 * distance + pointlight[i].quadratic * (distance * distance));    
        vec3 ambientatt = pointlight[i].Ambient * (attenuation); 
        float newdiff = max(dot(norm, lightDirnew), 0.0);
        vec3 newdiffuse = pointlight[i].Diffuse * newdiff * (attenuation);    
        vec3 newreflectDir = reflect(-lightDirnew, norm);
        float newspec = pow(max(dot(viewDir, newreflectDir), 0.0), shininess);
        vec3 newspecular = pointlight[i].Specular * newspec * attenuation; 
        pointlightResult += ambientatt + newdiffuse + newspecular;
    }
    vec4 FragColorPoint = vec4(pointlightResult, 1.0f);

    //for spot light 
    //
    float distance2 = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 * distance2 + quadratic * (distance2 * distance2));    
    vec3 ambient = lightAmbient * attenuation;
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff2 = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse2 = diff2 * lightDiffuse * (attenuation * 3 );
    vec3 viewDir2 = normalize(viewPos - FragPos);
    vec3 reflectDir2 = reflect(-lightDirection, norm);  
    float spec2 = pow(max(dot(viewDir2, reflectDir2), 0.0), 32);
    vec3 specular2 = spec2 * lightSpecular * attenuation;  
    float theta = dot(lightDirection, normalize(-lightDir));
    float epsilon = cutOff;
    float intensity = clamp((theta - epsilon) / (1.0 - epsilon), 0.0, 1.0);
    vec3 result = ambient + (diffuse2 + specular2) * intensity;
    vec4 FragColorSpot = vec4(result, 1.0f);
   
    //mixing
    vec4 FragColorMix;

    if (isSpotLightOn == 1)
        FragColorMix = FragColorPoint + FragColorSpot;
    else if (isSpotLightOn == 0)     
        FragColorMix = FragColorPoint;


    vec4 Texture = GenerateTextures();
    if(nbtextures > 0)
    {
        FragColor = Texture * FragColorMix;
    }
    else
    {
        FragColor = color;
    }
}